`timescale 1ns / 1ps

module dwc1(
    input clk, reset,
    input [31:0] data_set,
    input [31:0] data_a, data_b,

    output [31:0] isMatch,
    output logic interupt_match
);

localparam logic [2:0] S0= 3'b000, S1= 3'b001, S2=3'b010, S3=3'b011;
logic [2:0] current_state;
logic [2:0] next_state;

reg [31:0]isMatch_reg;
assign isMatch = isMatch_reg;

always@(posedge clk)
    begin
        if(reset)
            current_state<=S0;
        else
            current_state<=next_state;
    end

always@(posedge clk)
    begin
        //zero conditions
        interupt_match<=0;
        
        case(current_state)
            S0:begin
                if(data_set === 3)
                    next_state<=S1;
                else
                    next_state<=S0;
            end

            S1:begin
                if(data_a == data_b)
                    begin
                        isMatch_reg<=1;
                        next_state<=S2;
                    end
                else
                    begin
                        isMatch_reg<=0;
                        next_state<=S2;
                    end
            end

            S2:begin
                interupt_match<=1;
                next_state<=S3;
            end

            S3:begin
                next_state<=S3;
            end
            default: next_state<=S0; 
        endcase
    end
endmodule