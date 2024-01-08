`timescale 1ns / 1ps

module dwc_SM(
    input clk,reset,
    input [31:0] data_a, data_b, //32bit data in from mBlaze
    input logic [1:0] data_set,       //when mb loads data its flag

    output [31:0] isMatch,         //compare flag 
    output logic interupt_prompt  
);

reg [31:0] isMatch_reg;
reg [1:0] data_set_reg;
assign isMatch = isMatch_reg; 


typedef enum logic [3:0]{ S0, S1, S2, S3 } state_type;   //update for 2bit hamming codes
state_type current_state, next_state;

always_ff @(posedge clk)
    begin
        if(reset)begin
                current_state<= S0;
                isMatch_reg<=0;
                //data_set_reg<=0;
                
            end
        else
            current_state<= next_state;
    end

always @(posedge clk) 
    begin
        //zero state
        interupt_prompt<=0; //mB interupt to trigger check of comparision  
        //isMatch_reg=0;  

        case(current_state)
            S0:begin
            //assign data_set_reg = data_set;
                //check till data is loaded
                if(data_set == 2'b11)
                    begin
                        next_state<= S1;
                        //data_set_reg=0; //reset set register
                    end
                else
                    next_state<= S0;
            end

            S1:begin
                //compare state 
                if(data_a == data_b)
                    isMatch_reg<= 1;
                else
                    isMatch_reg<= 0;
                next_state<= S2;
            end

            S2:begin
                //interupt mb to read registers
                interupt_prompt<=1;

                next_state<= S3;
            end
            
            S3:
                //holding state till reset
                next_state<=S3;

            default: next_state<= S0;
        endcase
    end
endmodule
