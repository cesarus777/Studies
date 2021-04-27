module counter #(parameter W = 16)(
    input clk, rst,

    output [W - 1:0]out
);

assign out = cnt;

reg [W - 1:0]cnt;

initial begin
  cnt <= 0;
end

always @(posedge clk or posedge rst) begin
  if (rst)
    cnt <= 0;
  else
    cnt <= cnt + 1;
end

endmodule
