`timescale 1ns / 1ps

module dwc_V3_05(
    input clk,reset,
    input logic [31:0]data_a, data_b, //32bit data in from mBlaze
    input logic [31:0]data_set,       //when mb loads data its flag
    input logic [31:0]ackA,   
    input logic [31:0]ackB, 
    input logic [31:0]start,         
    
    output logic [31:0]isMatch,     //compare flag 
    output logic [31:0]done,        //comparitor finished

    output logic [31:0]data_read,    

    output logic interupt_prompt  //promt MB to check regs
);

reg [31:0]isMatch_reg;
assign isMatch = isMatch_reg; 

reg [31:0] done_reg;
assign done = done_reg;

reg[31:0]data_read_reg;
assign data_read = data_read_reg;

logic readyA;
logic readyB;

typedef enum logic [3:0]{ S0, S1, S2, S3 } state_type;   //update for 2bit hamming codes
state_type current_state, next_state;

always_ff @(posedge clk)
    begin
        if(reset)begin
                current_state<= S0;
            end
        else
            current_state<= next_state;
    end

always @(clk)
    begin
        interupt_prompt<=0;
        data_read_reg<=0;
        readyA<=0;
        readyB<=0;
        
        case(current_state)
            S0:begin

                isMatch_reg<='0;
                done_reg<='0;
                  
                if(data_set==3)begin
                    next_state<=S1;
                    data_read_reg<=1;
                end
                else
                    next_state<=S0;
            end
            S1:begin
                data_read_reg<=1;
                interupt_prompt<=1;
                
                if(start)begin
                    next_state<=S2;
                end
                else
                    next_state<=S1;
            end    
            S2:begin
                if(data_a == data_b)begin
                    isMatch_reg<='1;
                    done_reg<=1;
                end
                else 
                    begin
                        isMatch_reg<='0;
                        done_reg<=1;
                    end
                next_state<=S3;
            end
            S3:begin
                interupt_prompt<=1;
                done_reg<=1;

                if(ackA)
                    readyA<=1;
                if(ackB)
                    readyB<=1;
                
                if(readyA && readyB)begin
                    next_state<=S0;
                end 
                else
                    next_state<=S3;
            end

            default: next_state= S0;
        endcase
    end
endmodule
