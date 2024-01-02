//MicroBlaze_1

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "xbasic_types.h"


//Base Address of the dwc_V2
Xuint32 *baseaddr_p = (Xuint32 *) XPAR_MYDWC_V2_0_S00_AXI_BASEADDR;

volatile unsigned int *setReg = (unsigned int *)XPAR_MYDWC_V2_0_S00_AXI_BASEADDR;	//set register

int main()
{
    init_platform();

    //print("===================================================\n\r");
    //print("MicoBlaze_1\n\r");
    //print("===================================================\n\r");

	*(baseaddr_p + 2) = 0x00000005;
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
