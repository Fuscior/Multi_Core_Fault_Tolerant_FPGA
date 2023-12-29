module interupt_test(
    input clk,
    output logic count_interupt
);

logic [31:0] tick_count;

always @(posedge clk)
    begin
        if(tick_count == 1000000000)
            tick_count<='0;

        else
            tick_count<= tick_count +1;
    end

    assign count_interupt= (tick_count == 1000000000)?1: 1'b0;
endmodule