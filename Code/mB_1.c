//MicroBlaze_1

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "xbasic_types.h"
#include "xil_exception.h"	//isr

//Base Address of the dwc_V2
Xuint32 *baseaddr_p = (Xuint32 *) XPAR_DWC1_0_S00_AXI_BASEADDR;

volatile unsigned int *setReg = (unsigned int *)XPAR_DWC1_0_S00_AXI_BASEADDR;

void enable_ISR(void);
void myIsr(void *CallbackRef);

int main()
{
    init_platform();


	*(baseaddr_p + 2) = 0x00000004;
	setBit(setReg, 1);


    cleanup_platform();
    return 0;
}

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
void myIsr(void *CallbackRef) {

    //xil_printf("Interrupt occurred!\n");
    //xil_printf("Read from register 5 isMatch in ISR: 0x%08x \n\r", *(baseaddr_p + 3));
}
