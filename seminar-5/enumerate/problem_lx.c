#include <ctype.h>
#include <stdlib.h>

#include "problem_lx.h"
#include "symbol_check.h"

void
larr_realloc_check (struct lex_array_t *larr)
{
  if ((larr->capacity - larr->size) == 1)
    {
      struct lexem_t *r = (struct lexem_t *) realloc (larr->lexems,
						      (larr->size + ICAP) * sizeof (struct lexem_t));

      assert (r != NULL);
      larr->lexems = r;
      larr->capacity += ICAP;
    }
}

void
push_back_lexem (struct lex_array_t *larr, struct lexem_t l)
{
  larr->lexems[larr->size] = l;
  ++larr->size;
  larr_realloc_check (larr);
}

struct lex_array_t
lex_string (const char *str)
{
  assert (str != NULL);

  struct lex_array_t larr = { malloc (ICAP * sizeof (struct lexem_t)),
    0, ICAP };

  assert (larr.lexems != NULL);

  int lbn = 0, rbn = 0;

  for (int i = 0; str[i] != '\0'; ++i)
    {
      if (isspace (str[i]))
    	  continue;

      if (islbrace (str[i]))
	      {
	        struct lexem_t l = { BRACE, LBRAC };
	        push_back_lexem (&larr, l);
	        ++lbn;
	        continue;
      	}

      if (isrbrace (str[i]))
	      {
	        struct lexem_t l = { BRACE, RBRAC };
	        push_back_lexem (&larr, l);
	        ++rbn;
	        continue;
      	}

      if (!isalnum (str[i]))
	      {
	        if (larr.lexems[larr.size - 1].kind == OP)
	          {
	             free (larr.lexems);
	             struct lex_array_t l = { NULL, 0, 0 };
	             return l;
	          }
	        if (isplus (str[i]))
	          {
	            struct lexem_t l = { OP, ADD };
	            push_back_lexem (&larr, l);
	            continue;
	          }
      	  if (isminus (str[i]))
	          {
	            struct lexem_t m = { OP, SUB };
	            push_back_lexem (&larr, m);
	            continue;
	          }
	        if (ismul (str[i]))
	          {
	            struct lexem_t n = { OP, MUL };
	            push_back_lexem (&larr, n);
	            continue;
	          }
	        if (isdiv (str[i]))
	          {
	            struct lexem_t k = {	OP, DIV };
	            push_back_lexem (&larr, k);
	            continue;
	          }

	        free (larr.lexems);
	        struct lex_array_t l = { NULL, 0, 0 };
	        return l;
	      }

      if (isdigit (str[i]))
	      {
	        if (larr.lexems[larr.size - 1].kind == NUM)
	          {
	            free (larr.lexems);
	            struct lex_array_t l = { NULL, 0, 0 };
	            return l;
	          }
	        char *strp;
	        int read = (int) strtol ((str + i), &strp, 10);
	        struct lexem_t l = { NUM, read };
	        i = strp - str - 1;
	        push_back_lexem (&larr, l);

	        continue;
	      }

      struct lex_array_t l = { NULL, 0, 0 };
      larr = l;
      break;
    }

  if (lbn != rbn)
    {
      struct lex_array_t l = { NULL, 0, 0 };
      larr = l;
    }

  return larr;
}

static void
print_op (enum operation_t opcode)
{
  switch (opcode)
    {
    case ADD:
      printf ("PLUS ");
      break;
    case SUB:
      printf ("MINUS ");
      break;
    case MUL:
      printf ("MUL ");
      break;
    case DIV:
      printf ("DIV ");
      break;
    default:
      assert (0 && "unknown opcode");
    }
}

static void
print_brace (enum braces_t bracetype)
{
  switch (bracetype)
    {
    case LBRAC:
      printf ("LBRAC ");
      break;
    case RBRAC:
      printf ("RBRAC ");
      break;
    default:
      assert (0 && "unknown bracket");
    }
}

static void
print_num (int n)
{
  printf ("NUMBER:%d ", n);
}

void
print_lexem (struct lexem_t lxm)
{
  switch (lxm.kind)
    {
    case OP:
      print_op (lxm.lex.op);
      break;
    case BRACE:
      print_brace (lxm.lex.b);
      break;
    case NUM:
      print_num (lxm.lex.num);
      break;
    default:
      assert (0 && "unknown lexem");
    }
}

void
dump_lexarray (struct lex_array_t pl)
{
  int i;
  assert (pl.lexems != NULL);
  for (i = 0; i < pl.size; ++i)
    print_lexem (pl.lexems[i]);
  printf ("\n");
}
