module top (
  input CLK, BUT, RST,
  input DP1, DP2, DP3, DP4, DP5, DP6, DP7, DP8,

  output DS_EN1, DS_EN2, DS_EN3, DS_EN4, DS_EN5, DS_EN6, DS_EN7, DS_EN8,
  output DS_A, DS_B, DS_C, DS_D, DS_E, DS_F, DS_G
);

//wire [3:0] left_anodes;
//wire [3:0]right_anodes;
wire [7:0]anodes;
assign { DS_EN5, DS_EN6, DS_EN7, DS_EN8,
         DS_EN1, DS_EN2, DS_EN3, DS_EN4 } = ~anodes;

wire [6:0]segments;
assign {DS_A, DS_B, DS_C, DS_D, DS_E, DS_F, DS_G} = ~segments;

wire [31:0]data;

wire display_clk, slow_clk, fast_clk;

clk_div #(.X(12)) clk_div1(.clk(CLK), .clk_out(display_clk));
clk_div #(.X(24)) clk_div2(.clk(CLK), .clk_out(slow_clk));
clk_div #(.X(20)) clk_div3(.clk(CLK), .clk_out(fast_clk));

//counter #(.W(16)) counter(.clk(clk3), .q(data[15:0]));

//wire click_clk;
//clicker clicker(.but(BUT), .rst(RST), .clk(CLK), .out(click_clk));
//counter #(.W(16)) click_counter(.clk(click_clk), .q(data[31:16]));

//counter #(.W(16)) counter(.clk(slow_clk), .q(data[31:16]));
//fib_counter #(.W(16)) fib_counter(.clk(slow_clk), .out(data[15:0]));

wire click_clk, rst_but, en_auto_click;
reg rst, en_auto_click_toggle;
wire [2:0]click_cnt_div;
assign en_auto_click = DP1;
assign click_cnt_div = { DP2, DP3, DP4 };
//clicker clicker(.but(BUT), .clk(CLK), .out(click_clk));
mixed_clicker #(.W(3), .X(20)) clicker(.but(BUT),
                      .clk(CLK),
                      .auto_click(en_auto_click),
                      .div(click_cnt_div),
                      .out(click_clk));

clicker   reset(.but(RST), .clk(CLK), .out(rst_but));

counter #(.W(4)) click_counter(.clk(click_clk), .rst(rst_but), .out(data[31:28]));

fib_counter #(.W(28)) fib_counter(.clk(click_clk), .rst(rst_but), .out(data[27:0]));

always @(posedge CLK or posedge en_auto_click or posedge dis_auto_click) begin
  if(en_auto_click) begin
    en_auto_click_toggle <= 1;
  end else if(dis_auto_click) begin
    en_auto_click_toggle <= 1;
  end else begin
    if(en_auto_click_toggle) begin
      rst <= 1;
      en_auto_click_toggle <= ~en_auto_click_toggle;
    end else begin
      rst <= rst_but;
    end
  end
end

wire dis_auto_click;

assign dis_auto_click = ~en_auto_click;

hex_display hex_display(.clk(display_clk),
                        .data(data),
                        .anodes(anodes),
                        .segments(segments));

endmodule
