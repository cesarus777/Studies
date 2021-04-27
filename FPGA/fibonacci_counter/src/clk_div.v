module clk_div #(parameter X = 12)(
	input clk,

	output clk_out

);

reg [X-1:0]cnt = 0;

assign clk_out = (cnt == 0);

always @(posedge clk) begin
		cnt <= cnt + 1;
end

endmodule



module clk_runtime_div #(parameter W = 8)(
  input clk,
  input [W-1:0]div,

  output clk_out

);

reg [W-1:0]cnt = 0;

assign clk_out = (cnt <= 0);

always @(posedge clk) begin
    cnt <= cnt + 1;
    if(cnt >= div)
      cnt <= 0;
end

endmodule

