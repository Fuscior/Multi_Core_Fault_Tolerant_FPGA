`timescale 1ns / 1ps

module dwc_V3_03(
    input clk,reset,
    input logic [31:0]data_a, data_b, //32bit data in from mBlaze
    input logic [31:0]data_set,       //when mb loads data its flag
    input logic [31:0]ack,          
    
    output logic [31:0]isMatch,     //compare flag 
    output logic [31:0]done,        //comparitor finished     

    output logic interupt_prompt  //promt MB to check regs
);

reg [31:0]isMatch_reg;
assign isMatch = isMatch_reg; 

reg [31:0] done_reg;
assign done = done_reg;

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
        
        case(current_state)
            S0:begin
                isMatch_reg<='0;
                done_reg<='0;
                if(!ack)
                    if(data_set==3)
                        next_state<=S1;
                else
                    next_state<=S0;
            end
            S1:begin
                if(data_a == data_b)begin
                    isMatch_reg<='1;     //is match
                    
                    done_reg<='1;
                    interupt_prompt<=1;
                end
                else
                    begin
                        isMatch_reg<='0;    //no match
                        
                        done_reg<='1;
                        interupt_prompt<=1;
                    end

                next_state<=S2;
            end    
            S2:begin
                interupt_prompt<=0;
                if(ack && (data_set==0) )begin
                    done_reg<='0;
                    next_state<=S0; //next data set
                end
                else
                    next_state<=S2;
            end 

            default: next_state= S0;
        endcase
    end
endmodule
