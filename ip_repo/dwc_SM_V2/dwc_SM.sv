`timescale 1ns / 1ps

module dwc_SM(
    input clk,reset,
    input [31:0] data_a, data_b, //32bit data in from mBlaze
    input [1:0] data_set,       //when mb loads data its flag


    output isMatch,         //compare flag 
    output logic interupt_prompt  
);

reg isMatch_reg;
assign isMatch = isMatch_reg; 

typedef enum logic { S0, S1, S2, S3 } state_type;   //update for 2bit hamming codes
state_type current_state, next_state;

always_ff @(posedge clk)
    begin
        if(reset)
            current_state<= S0;
        else
            current_state<= next_state;
    end

always_comb(
    begin
        //zero state
        interupt_prompt=0; //mB interupt to trigger check of comparision
        isMatch=0;        

        case(current_state)
            S0:begin
                //check till data is loaded
                if(data_set == 2'b11)
                    next_state= S1;
                    data_set= '0; //reset set register
                else
                    next_state= S0;
            end

            S1:begin
                //compare state 
                if(data_a == data_b)
                    isMatch=1;
                else
                    isMatch=0;
                next_state= S2;
            end

            S2:begin
                //interupt mb to read registers
                interupt_prompt=1;

                next_state= S0;
            end

            default: next_state= S0;
        endcase
    end
)
endmodule
