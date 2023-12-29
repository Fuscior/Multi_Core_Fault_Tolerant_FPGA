//07-11-2023
//simple module to create a AXI per

module adder_32bit(
    input logic [31:0] A,
    input logic [31:0] B,

    output logic [31:0] result
);

always_comb
    begin
        result= A + B;
    end;
    
endmodule
