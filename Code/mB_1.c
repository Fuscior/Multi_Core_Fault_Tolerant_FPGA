
#include <stdio.h>
#include <stdbool.h>
#include "platform.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "xbasic_types.h"
#include "xil_exception.h"	//isr

//Base Address of the dwc_V2
Xuint32 *baseaddr_p = (Xuint32 *) XPAR_DWC_V3_05_0_S00_AXI_BASEADDR;
volatile unsigned int *setReg = (unsigned int *)XPAR_DWC_V3_05_0_S00_AXI_BASEADDR;	//set register

void debug_print(void);
void enable_ISR(void);
void myIsr(void *CallbackRef);

bool hold_flag=TRUE;
bool waite_flag=TRUE;

int arrayB[11]={1, 0, 3 , 0 ,5 ,0, 7,  0, 9 ,0};

int main()
{

    init_platform();
    enable_ISR();


    for(int i=0; i<11; i++){
        hold_flag=TRUE;

        *(baseaddr_p + 2)=arrayB[i];
        setBit(setReg, 1);

        while(hold_flag){}

        //*(baseaddr_p + 12)=0;
    }


    cleanup_platform();
    return 0;

}
//--------------------------------------------------------------------------------------
 void myIsr(void *CallbackRef) {

	 if(*(baseaddr_p + 6) == 1){
		 clearBit(setReg,1);
	 }

	 if(*(baseaddr_p + 7)==1){
		 *(baseaddr_p + 12)=1;

		 hold_flag=FALSE;
	 }

 }
 //--------------------------------------------------------------------------------------
//-----debug print reg values-----------------------------------------------------------
void debug_print(void){
	xil_printf("start of debug print\n\n\r");
	print("MicoBlaze_1\n\r");
	xil_printf("Read from register 0 set reg: 0x%08x \n\r", *(baseaddr_p + 0));
	xil_printf("Read from register 1 uP0 data: 0x%08x \n\r", *(baseaddr_p + 1));
	xil_printf("Read from register 2 up1 data: 0x%08x \n\r", *(baseaddr_p + 2));
	xil_printf("Read from register 3 NC: 0x%08x \n\r", *(baseaddr_p + 3));
	xil_printf("Read from register 4 NC: 0x%08x \n\r", *(baseaddr_p + 4));
	xil_printf("Read from register 5 isMatch: 0x%08x \n\r", *(baseaddr_p + 5));
	xil_printf("Read from register 6 data_read: 0x%08x \n\r", *(baseaddr_p + 6));
	xil_printf("Read from register 7 Done: 0x%08x \n\r", *(baseaddr_p + 7));
	xil_printf("Read from register 10 start: 0x%08x \n\r", *(baseaddr_p + 10));
	xil_printf("Read from register 11 ackA: 0x%08x \n\r", *(baseaddr_p + 11));
	xil_printf("Read from register 12 ackB: 0x%08x \n\r", *(baseaddr_p + 12));
	xil_printf("Read from register 14 reset: 0x%08x \n\r", *(baseaddr_p + 14));
	xil_printf("End of debug print\n\n\r");
}
//--------------------------------------------------------------------------------------
//-----enable interupt------------------------------------------------------------------
void enable_ISR(void){
	// Connect ISR to the interrupt controller
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT, myIsr, NULL);
	Xil_ExceptionEnable();

	// Enable MicroBlaze interrupts globally
	microblaze_enable_interrupts();
}
//-----end enable interupt--------------------------------------------------------------
//--------------------------------------------------------------------------------------
 //-----set register---------------------------------------------------------------------
  void setBit(unsigned int *setReg, int bitNumber){
 	unsigned int value = *setReg;// Read the current value

 	value |= (1 << bitNumber);// Set the desired bit
 	*setReg = value;// Write the updated value back
  }
  //-----end set register-----------------------------------------------------------------
  //--------------------------------------------------------------------------------------
  void clearBit(unsigned int *setReg, int bitNumber) {
      unsigned int value = *setReg;// Read the current value

      // Clear the desired bit
      value &= ~(1 << bitNumber);

      // Write the updated value back
      *setReg = value;
  }

//-----end debug print reg values-------------------------------------------------------
//--------------------------------------------------------------------------------------

