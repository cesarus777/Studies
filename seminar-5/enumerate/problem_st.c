#include <assert.h>

#include "problem_lx.h"
#include "problem_st.h"

int pars_expr(struct lex_array_t, int*); 

int pars_term(struct lex_array_t lex_str, int *n)
{
  if((lex_str.lexems[*n].kind == BRACE) &&
     (lex_str.lexems[*n].lex.b == LBRAC))
  {
    *n += 1;
    int res = pars_expr(lex_str, n);
    return res;
  }

  else if(lex_str.lexems[*n].kind == NUM)
  {
    int res = lex_str.lexems[*n].lex.num;
    *n += 1;
    return res;
  }
}

int pars_mult(struct lex_array_t lex_str, int *n)
{
  int a = pars_term(lex_str, n);
  if(lex_str.lexems[*n].kind == BRACE) 
    return a;
  assert(lex_str.lexems[*n].kind == OP);
  enum operation_t md = lex_str.lexems[*n].lex.op;
  if ((md != MUL) && (md != DIV))
    return a;

  *n += 1;
  int b = pars_mult(lex_str, n);

  if(md == MUL)
    return a * b;
  else
    return a / b;
}

int pars_expr(struct lex_array_t lex_str, int *n)
{
  int a = pars_mult(lex_str, n);
  if(lex_str.lexems[*n].kind == BRACE) 
  {
    assert(lex_str.lexems[*n].lex.b = RBRAC);
    *n += 1; 
    return a;
  }
  if(*n == lex_str.size)
    return a;
  enum operation_t as = lex_str.lexems[*n].lex.op;
  assert((as != ADD) || (as != SUB));
  *n += 1;
  int b = pars_expr(lex_str, n);

  if(as == ADD)
    return a + b;
  else
    return a - b;

}

int pars(struct lex_array_t lex_str)
{
  int i = 0;
  return pars_expr(lex_str, &i);
}
