`timescale 1ns / 1ps


module add_one(
    input S_AXI_ACLK,
    input slv_reg_wren,
    input [2:0] axi_awaddr,
    input [31:0] S_AXI_WDATA,
    input S_AXI_ARESETN,
    input isSet,
    output reg [31:0] result,result1,result2
    );
      
  always @( posedge S_AXI_ACLK )
    begin
        if ( S_AXI_ARESETN == 1'b0 )
            begin
                result <= 4'b0;
                result1 <=4'b0;
                result2 <=4'b0;
            end
        else 
            begin
                if (isSet)
                    begin
                        result<='1;
                        result1<='1;
                        result2<='1;
                    end
                
                else if(!isSet)
                    begin
                        result<='0;
                        result1<='0;
                        result2<='0;
                    end

            end
          //if (slv_reg_wren && (axi_awaddr == 3'h0))
             // result <= S_AXI_WDATA + 1;
    end
endmodule

