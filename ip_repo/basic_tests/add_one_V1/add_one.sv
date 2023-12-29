`timescale 1ns / 1ps


module add_one(
    input S_AXI_ACLK,
    input slv_reg_wren,
    input [2:0] axi_awaddr,
    input [31:0] S_AXI_WDATA,
    input S_AXI_ARESETN,
    output reg [31:0] result
    );
      
  always @( posedge S_AXI_ACLK )
  begin
    if ( S_AXI_ARESETN == 1'b0 )
    result <= 4'b0;
    else 
      if (slv_reg_wren && (axi_awaddr == 3'h0))
          result <= S_AXI_WDATA + 1;
      end
endmodule

