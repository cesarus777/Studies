/*
*   Introduction to FPGA and Verilog
*
*   Viktor Prutyanov, 2019
*
*   Problem set #00
*/

module pset00_invertor(
/*
*   Problem 2/5:
*   describe ports here
*/
	input wire in,
	output wire out

);

/*
*   Problem 2/5:
*   write NOT logic here
*/
assign out = ~in;

endmodule
