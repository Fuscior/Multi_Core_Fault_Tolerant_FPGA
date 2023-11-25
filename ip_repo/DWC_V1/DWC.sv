module DWC(
    input clk,
    input [15:0] a,
    input [15:0] b,
    output [31:0] isMatch
);

reg [31:0] isMatch_reg;
assign isMatch = productReg;

always @(posedge clk) 
    begin
        if(a == b)
            isMatch_reg <= 1
        else
            isMatch <=0
    end
endmodule
