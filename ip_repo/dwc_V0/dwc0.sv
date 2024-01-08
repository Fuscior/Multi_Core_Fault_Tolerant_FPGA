`timescale 1ns / 1ps

module dwc0(
    input clk, reset,
    input [31:0] data_set,
    input [31:0] data_a, data_b,

    output [31:0] isMatch,
    output logic interupt_match
);

reg isMatch_reg;
assign isMatch = isMatch_reg;

always@(posedge clk)
    begin
        if(data_set == 3)
            begin
                if(data_a == data_b)
                    isMatch_reg= 1;
                else
                    isMatch_reg= 0;
            interupt_match=1;
            end
        else
            interupt_match=0; 
    end
endmodule