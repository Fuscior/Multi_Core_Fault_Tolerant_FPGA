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

volatile unsigned int matchCheck=0;

void debug_print(void);
void enable_ISR(void);
void myIsr(void *CallbackRef);

bool hold_flag=TRUE;

int arrayA[11]={1, 2, 3 , 4 ,5 ,6, 7,  8, 9 ,10};
int arrayB[11]={1, 0, 3 , 0 ,5 ,0, 7,  0, 9 ,0};
int matched[11];

int main()
{
    init_platform();
    enable_ISR();

	print("=======================================================\n\r");
	print("Hello World uP0\n\r");
	print("=======================================================\n\r");


    for(int i=0; i<11; i++){
        hold_flag=TRUE;

        *(baseaddr_p + 1)=arrayA[i];
        print("first value \n\r");
        setBit(setReg, 0);
        debug_print();


        print("mb 0 \n\r");
        debug_print();

        while(hold_flag){
        	print("in hold loop\n\r");
        }

		*(baseaddr_p + 11)=0;
		*(baseaddr_p + 12)=0;

        matched[i]=matchCheck;
    }

	print("=======================================================\n\r");

	for(int x=0; x<15; x++){
		xil_printf("matched array: 0x%08x \n\r", matched[x]);
	}



    cleanup_platform();
    return 0;
}
//--------------------------------------------------------------------------------------
 void myIsr(void *CallbackRef) {
     // ISR code
	 print("=======================================================\n\r");
     xil_printf("Interrupt occurred!\n\r");
     print("=======================================================\n\r");

     if(*(baseaddr_p + 6) == 1){	//data read in
    	 print("data_read area");
    	 clearBit(setReg,0);

    	 debug_print();
     }
     else{
		 xil_printf("Read from register 5 isMatch: 0x%08x \n\r", *(baseaddr_p + 5));

		 debug_print();
		 if(*(baseaddr_p + 7)==1){	//done
			 matchCheck=*(baseaddr_p + 5);
			 *(baseaddr_p + 11)=1;

			 hold_flag=FALSE;	//leave hold loop
		 }
     }

     if(*(baseaddr_p + 0)==0){
    	 *(baseaddr_p + 10)=1;
    	 *(baseaddr_p + 10)=0;
     }

 }
 //--------------------------------------------------------------------------------------
//-----debug print reg values-----------------------------------------------------------
void debug_print(void){
	xil_printf("start of debug print\n\n\r");
	print("MicoBlaze_0\n\r");
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
 	// Read the current value
 	unsigned int value = *setReg;

 	// Set the desired bit
 	value |= (1 << bitNumber);

 	// Write the updated value back
 	*setReg = value;
  }
  //-----end set register-----------------------------------------------------------------
  //--------------------------------------------------------------------------------------
  void clearBit(unsigned int *setReg, int bitNumber) {
      // Read the current value
      unsigned int value = *setReg;

      // Clear the desired bit
      value &= ~(1 << bitNumber);

      // Write the updated value back
      *setReg = value;
  }

//-----end debug print reg values-------------------------------------------------------
//--------------------------------------------------------------------------------------

/*
* 	        4'h0   : reg_data_out <= slv_reg0; //.data_set(slv_reg0);
	        4'h1   : reg_data_out <= slv_reg1; //.data_a(slv_reg1);
	        4'h2   : reg_data_out <= slv_reg2; //.data_b(slv_reg2);
	        4'h3   : reg_data_out <= slv_reg3;
	        4'h4   : reg_data_out <= slv_reg4;
	        4'h5   : reg_data_out <= isMatch_inter;    //.isMatch(isMatch_inter),
	        4'h6   : reg_data_out <= data_read_inter;  //.data_read(data_read_inter),
	        4'h7   : reg_data_out <= done_inter;       //.done(done_inter),
	        4'h8   : reg_data_out <= slv_reg8;
	        4'h9   : reg_data_out <= slv_reg9;
	        4'hA   : reg_data_out <= slv_reg10;    //.start(slv_reg10),
	        4'hB   : reg_data_out <= slv_reg11;    //.ackA(slv_reg11),
	        4'hC   : reg_data_out <= slv_reg12;    //.ackB(slv_reg12),
	        4'hD   : reg_data_out <= slv_reg13;
	        4'hE   : reg_data_out <= slv_reg14;    //.reset(slv_reg14);
	        default : reg_data_out <= 0;
 */
