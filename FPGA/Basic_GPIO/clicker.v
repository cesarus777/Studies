module clicker (
    input but, clk,
	 
	 output q
);

wire sw_down;

button_debouncer  debouncer(.clk_i(clk), .rst_i(),	.sw_i(but), .sw_state_o(), .sw_down_o(sw_down), .sw_up_o());	

counter #(.W(16)) count(.clk(sw_down), .q(q));

endmodule 