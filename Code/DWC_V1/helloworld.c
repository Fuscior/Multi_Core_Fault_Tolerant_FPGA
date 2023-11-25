/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

//25/11/2023
//DWC basic test
//one 32bit in compare 16 LSB to 16MSB and throw flag
#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "xbasic_types.h"

// we will use the Base Address of the RTL_MULTIPLIER
Xuint32 *baseaddr_p = (Xuint32 *) XPAR_DWC_0_S00_AXI_BASEADDR;

int main()
{
    init_platform();


    	print("Hello World\n\r");

    	xil_printf("bass address is: 0x%08x \n\r", (Xuint32 *) XPAR_DWC_0_S00_AXI_BASEADDR);

    	xil_printf("Performing a test of the DWC Block... \n\r");
    	// Write multiplier inputs to register 0
    	*(baseaddr_p + 0) = 0x00060006;

    	xil_printf("Wrote to register 0: 0x%08x \n\r", *(baseaddr_p + 0));
    	// Read multiplier output from register 1
    	xil_printf("Read from register 1: 0x%08x \n\r", *(baseaddr_p + 1));
    	xil_printf("End of test\n\n\r");

    	for(int i=0; i<9999999; i++){}

    cleanup_platform();
    return 0;
}
