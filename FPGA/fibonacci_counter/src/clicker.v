module clicker (
    input but, clk,

    output out
);

button_debouncer  debouncer(.clk_i(clk), .rst_i(),	.sw_i(but), .sw_state_o(), .sw_down_o(out), .sw_up_o());

endmodule 



module mixed_clicker #(parameter W = 3, X = 22) (
    input clk, rst, but, auto_click,
    input [W - 1:0]div,

    output reg out
);

wire [W - 1:0]cnt;
wire cnt_clk, clk_div;
clk_div #(.X(X)) clk_prediv(.clk(clk), .clk_out(clk_div));
clk_runtime_div #(.W(W)) count_clk(.clk(clk_div), .div(~div), .clk_out(cnt_clk));
counter #(.W(W)) counter(.clk(cnt_clk), .rst(rst), .out(cnt));

wire clk_out, sw_down;

assign clk_out = (cnt == 0);

clicker clicker(but, clk, sw_down);

always @(posedge clk) begin
  if (auto_click) begin
    out <= clk_out;
  end else begin
    out <= sw_down;
  end
end

endmodule
