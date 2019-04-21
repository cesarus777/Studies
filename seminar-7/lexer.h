#pragma once

enum cmd_kind { MOVI, OP, IO };

enum operation { ADD, SUB, MUL, DIV };

enum stream { IN, OUT };

struct command {
  enum cmd_kind kind;
  union {
    enum operation op;
    enum stream io;
  } type;
  union {
    int imm;
    char regs[2];
  } data;
};

enum { ICAP = 10 };

struct cmd_array {
  struct cmd *cmds;
  int size, capacity;
};

struct command lex_analysis_one (int mode, char *str);
