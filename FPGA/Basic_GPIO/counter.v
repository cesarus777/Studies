module counter #(parameter W = 16)(
    input clk,

    output [W - 1:0]q
);

/*
*   Write your code for counter of W bit width here
*/

assign q = cnt;

reg [W - 1:0]cnt = 0;

always @(posedge clk) begin
	cnt <= cnt + 1;
end

endmodule
