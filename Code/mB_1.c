//MicroBlaze_1
#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "xbasic_types.h"


//Base Address of the RTL_MULTIPLIER
Xuint32 *baseaddr_p = (Xuint32 *) XPAR_DWC_V1_1_0_S00_AXI_BASEADDR;

int main()
{
    init_platform();

    for(int i=0; i<9999999; i++){}

    print("===================================================\n\r");
    print("MicoBlaze_1\n\r");

	xil_printf("bass address is: 0x%08x \n\r", (Xuint32 *) XPAR_DWC_V1_1_0_S00_AXI_BASEADDR);
	xil_printf("Performing a test of the DWC... \n\r");
	// Write dwc reg 1
	*(baseaddr_p + 1) = 0x00000003;


	print("===================================================\n\r");


    cleanup_platform();
    return 0;
}
