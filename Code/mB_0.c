//MicroBlaze_0

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "xbasic_types.h"
#include "xil_exception.h"	//isr


//Base Address of the dwc_V2
Xuint32 *baseaddr_p = (Xuint32 *) XPAR_DWC1_0_S00_AXI_BASEADDR;

volatile unsigned int *setReg = (unsigned int *)XPAR_DWC1_0_S00_AXI_BASEADDR;	//set register

void myIsr(void *CallbackRef);
void enable_ISR(void);
void reset_dwc(void);

int main()
{
    init_platform();
    enable_ISR();	//initilise ISR
    print("===================================================\n\r");
    print("MicoBlaze_0\n\r");

	xil_printf("bass address is: 0x%08x \n\r", (Xuint32 *) XPAR_DWC1_0_S00_AXI_BASEADDR);

	reset_dwc();

	// Write inputs to register data_a
	*(baseaddr_p + 1) = 0x00000005;
	setBit(setReg, 0);

	xil_printf("Wrote to register 0: 0x%08x \n\r", *(baseaddr_p + 1));
	// Read multiplier output from register 1


	print("MicoBlaze_0\n\r");
	xil_printf("Read from register 0 set reg: 0x%08x \n\r", *(baseaddr_p + 0));
	xil_printf("Read from register 1 uP0: 0x%08x \n\r", *(baseaddr_p + 1));
	xil_printf("Read from register 2 up1: 0x%08x \n\r", *(baseaddr_p + 2));
	xil_printf("Read from register 3 isMatch: 0x%08x \n\r", *(baseaddr_p + 3));
	xil_printf("Read from register 4 reset: 0x%08x \n\r", *(baseaddr_p + 4));
	xil_printf("Read from register 5 unused: 0x%08x \n\r", *(baseaddr_p + 5));
	xil_printf("End of test\n\n\r");


	print("===================================================\n\r");

    cleanup_platform();
    return 0;
}

/*
 * 	      case ( axi_araddr[ADDR_LSB+OPT_MEM_ADDR_BITS:ADDR_LSB] )
	        4'h0   : reg_data_out <= slv_reg0; //data_set
	        4'h1   : reg_data_out <= slv_reg1; //data_a
	        4'h2   : reg_data_out <= slv_reg2; //data_b
	        4'h3   : reg_data_out <= isMatch_flag; //isMatch
	        4'h4   : reg_data_out <= slv_reg4; //reset
	        4'h5   : reg_data_out <= slv_reg5;
	        4'h6   : reg_data_out <= slv_reg6;
	        4'h7   : reg_data_out <= slv_reg7;
	        4'h8   : reg_data_out <= slv_reg8;
	        4'h9   : reg_data_out <= slv_reg9;
	        default : reg_data_out <= 0;
	      endcase
 */

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
     // ISR code
     xil_printf("Interrupt occurred!\n");
     xil_printf("Read from register 5 isMatch in ISR: 0x%08x \n\r", *(baseaddr_p + 3));
     *(baseaddr_p + 0) = 0x00000000;
 }

 void reset_dwc(void){	//toggle reset
	 *(baseaddr_p + 4) = 0x00000001;
	 *(baseaddr_p + 4) = 0x00000000;
 }

