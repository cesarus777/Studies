#include "symbol_check.h"

int
islbrace (char symbol)
{
  return (symbol == '(') ? 1 : 0;
}

int
isrbrace (char symbol)
{
  return (symbol == ')') ? 1 : 0;
}

int
isplus (char symbol)
{
  return (symbol == '+') ? 1 : 0;
}

int
isminus (char symbol)
{
  return (symbol == '-') ? 1 : 0;
}

int
ismul (char symbol)
{
  return (symbol == '*') ? 1 : 0;
}

int
isdiv (char symbol)
{
  return (symbol == '/') ? 1 : 0;
}
