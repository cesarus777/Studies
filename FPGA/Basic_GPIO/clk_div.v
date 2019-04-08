module clk_div #(parameter X = 12)(
	input clk,

	output clk_out

);

reg [X-1:0]q = 0;

assign clk_out = (q == 1);

always @(posedge clk) begin
		q <= q + 1;
end

endmodule
