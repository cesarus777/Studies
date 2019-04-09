module clicker (
    input but, clk,
	 
	 output q
);

assign q = cnt;

reg [15:0]cnt = 0;

reg [3:0]buff = 0;

reg prev = 0;

always @(posedge clk) begin
    if (but != prev)
	     buff <= buff + 1;
	 if (buff == 10)
	     buff <= 0;
	 if (buff == 10)
     	  prev = ~prev;
	 if (buff == 10)
	     cnt <= cnt + 1;
end

endmodule 