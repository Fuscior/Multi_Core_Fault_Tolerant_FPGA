`timescale 1ns / 1ps

module dwc_SM_tb();

localparam period=40.0;

logic clk, reset;
logic [31:0] data_a, data_b;
logic [1:0] data_set;

logic isMatch;
logic interupt_prompt;

dwc_SM U1(.*);


initial 
    begin
        repeat(2) @(negedge clk)
        @(negedge clk)
        data_a=5;
        @(negedge clk)
        data_b=5;
        @(negedge clk)
        data_set=3;
       
        
        @(negedge clk)
        @(negedge clk)
        @(negedge clk)
        @(negedge clk)
        @(negedge clk)
        @(negedge clk)
        @(negedge clk)
        @(negedge clk)
        @(negedge clk)

        $finish;
    end


initial 
    begin
        clk=1'b0;
        forever
        #(period/2) clk= ~clk;
    end
endmodule