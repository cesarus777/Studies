module fib_counter #(parameter W = 16)(
    input clk, rst,

    output [W - 1:0]out
);

assign out = x3;

reg [W - 1:0]x1;
reg [W - 1:0]x2;
reg [W - 1:0]x3;

initial begin
  x1 <= 0;
  x2 <= 1;
  x3 <= 0;
end

always @(posedge clk or posedge rst) begin
  if (rst) begin
    x3 <= 0;
  end
  else begin
    x3 <= x2 + x1;
  end
end

always @(negedge clk or posedge rst) begin
  if (rst) begin
    x1 <= 0;
    x2 <= 1;
  end
  else begin
    x2 <= x3;
    x1 <= x2;
  end
end

endmodule
