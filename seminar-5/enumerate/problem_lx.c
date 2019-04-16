#include <ctype.h>
#include <stdlib.h>

#include "problem_lx.h"

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

void
larr_realloc_check (struct lex_array_t *larr)
{
  if ((larr->capacity - larr->size) == 1)
    {
      struct lexem_t *r = (struct lexem_t *) realloc (larr->lexems,
						      (larr->size +
						       ICAP) *
						      sizeof (struct
							      lexem_t));
      assert (r != NULL);
      larr->capacity += ICAP;
    }
}

struct lex_array_t
lex_string (const char *str)
{
  assert (str != NULL);

  struct lex_array_t larr = { malloc (ICAP * sizeof (struct lexem_t)),
    0,
    ICAP
  };

  assert (larr.lexems != NULL);

  // TODO:
  // for each char in str
  //   if char reminds space, skip it
  //   if char reminds number, lex number
  //   if char reminds brace, lex brace
  //   if char reminds operation, lex operation
  //   otherwise free lex array, return NULL

  for (int i = 0; str[i] != '\0'; ++i)
    {

      larr_realloc_check (&larr);

      if (isspace (str[i]))
	continue;

      if (islbrace (str[i]))
	{
	  struct lexem_t l = { BRACE, LBRAC };
	  larr.lexems[larr.size] = l;
	  ++larr.size;
	  continue;
	}

      if (isrbrace (str[i]))
	{
	  struct lexem_t l = { BRACE, RBRAC };
	  larr.lexems[larr.size] = l;
	  ++larr.size;
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
	  if (str[i] == '+')
	    {
	      struct lexem_t l = {
		OP, ADD
	      };
	      larr.lexems[larr.size] = l;
	      ++larr.size;
	      continue;
	    }
	  if (str[i] == '-')
	    {
	      struct lexem_t m = {
		OP, SUB
	      };
	      larr.lexems[larr.size] = m;
	      ++larr.size;
	      continue;
	    }
	  if (str[i] == '*')
	    {
	      struct lexem_t n = {
		OP, MUL
	      };
	      larr.lexems[larr.size] = n;
	      ++larr.size;
	      continue;
	    }
	  if (str[i] == '/')
	    {
	      struct lexem_t k = {
		OP, DIV
	      };
	      larr.lexems[larr.size] = k;
	      ++larr.size;
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
	  int read = (int) strtol((str + i), &strp, 10);
    struct lexem_t l = {NUM, read};
    larr.lexems[larr.size] = l;
    ++larr.size;
    i = strp - str;

// previous realisation of number reading
#if 0
	  while (isdigit (str[i]))
	    {
	      read = 10 * read + ((int) (str[i] - '0'));
	      if (!isdigit (str[i + 1]))
		{
		  struct lexem_t l = {
		    NUM, read
		  };
		  larr.lexems[larr.size] = l;
		  ++larr.size;
		  break;
		}
	      ++i;
	    }
#endif

	  continue;
	}

      struct lex_array_t l = {
	NULL, 0, 0
      };
      larr = l;
      break;
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
