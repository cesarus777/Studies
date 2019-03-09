module sign_ext(
    input [11:0]imm,

    output [31:0]ext_imm
);

/*
*   Problem 4:
*   Describe sign extension logic.
*/

wire msb = imm[11];

wire [19:0]ext = {20{msb}};

wire [31:0]ext_imm = {ext, imm};

endmodule
