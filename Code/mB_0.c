//MicroBlaze_0

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

    print("===================================================\n\r");
    print("MicoBlaze_0\n\r");


	xil_printf("bass address is: 0x%08x \n\r", (Xuint32 *) XPAR_DWC_V1_1_0_S00_AXI_BASEADDR);
	xil_printf("Performing a test of the DWC... \n\r");
	// Write multiplier inputs to register 0
	*(baseaddr_p + 0) = 0x00000003;
	xil_printf("Wrote to register 0: 0x%08x \n\r", *(baseaddr_p + 0));
	// Read multiplier output from register 1


	for(int i=0; i<99999999; i++){}
	print("MicoBlaze_0\n\r");
	xil_printf("Read from register 0: 0x%08x \n\r", *(baseaddr_p + 0));
	xil_printf("Read from register 1: 0x%08x \n\r", *(baseaddr_p + 1));
	xil_printf("Read from register 3: 0x%08x \n\r", *(baseaddr_p + 3));
	xil_printf("End of test\n\n\r");


	print("===================================================\n\r");
    cleanup_platform();
    return 0;
}
