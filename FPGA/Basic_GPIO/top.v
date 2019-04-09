module top (
    input CLK, BUT,

    output DS_EN1, DS_EN2, DS_EN3, DS_EN4, DS_EN5, DS_EN6, DS_EN7, DS_EN8,
    output DS_A, DS_B, DS_C, DS_D, DS_E, DS_F, DS_G
);

wire [7:0]anodes;
assign {DS_EN1, DS_EN2, DS_EN3, DS_EN4, DS_EN5, DS_EN6, DS_EN7, DS_EN8} = ~anodes;

wire [6:0]segments;
assign {DS_A, DS_B, DS_C, DS_D, DS_E, DS_F, DS_G} = ~segments;

wire [15:0]data; /* Data bus */
wire clk1, clk2; /* Clocks */

wire [15:0]click_data;
wire clk3;

/*
*   Instantiate hex display driver, 16-bit counter and two clock dividers here
*/

clk_div #(.X(12)) clk_div1(.clk(CLK), .clk_out(clk1));
clk_div #(.X(22)) clk_div2(.clk(CLK), .clk_out(clk2));
clk_div #(.X(12)) clk_div3(.clk(CLK), .clk_out(clk3));

counter #(.W(16)) counter(.clk(clk2), .q(data));

clicker clicker(.but(BUT), .clk(clk3), .q(click_data));

hex_display hex_display(.clk(clk1), .data(data), .cdata(click_data), .anodes(anodes), .segments(segments));

endmodule
