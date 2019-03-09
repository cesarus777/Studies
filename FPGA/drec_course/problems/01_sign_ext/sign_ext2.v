module sign_ext2(
    input [11:0]imm,

    output [31:0]ext_imm
);

/*
*   Problem 5:
*   Describe sign extension logic using ternary operator.
*/

wire msb = imm[11] ? 1 : 0;

wire [19:0]ext = {20{msb}};

assign ext_imm = {ext, imm};

endmodule
