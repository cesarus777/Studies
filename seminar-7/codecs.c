#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "additions.h"
#include "codecs.h"

// array of string with MK commands
char asm_commands[7][7] =
  { "MOVI D", "ADD", "SUB", "MUL", "DIV", "IN", "OUT" };

// function returns 4 bits with registor's information from command in string
// 'str'; 'one_reg' is flag for commands 'IN' and 'OUT' 
unsigned char
read_regs (char *str, int one_reg)
{
  unsigned char res, f = 0;
  for (int i = 0; i < strlen (str); ++i)
    {
      if (isalpha (str[i]) && (!isalpha (str[i + 1])))
	{
	  if (f != 0)
	    {
	      res |= str[i] - 'A';
	      return res;
	    }

	  res |= str[i] - 'A';

	  if (one_reg)
	    return res;
	  f = 1;
	  res = res << 2;
	}
    }
  return 0x10;
}

// function encodes one command from string 'str'
unsigned char
encode_one (char *str)
{
  unsigned char res, rr;
  for (int i = 0; i < 7; ++i)
    {
      if (strstr (str, asm_commands[i]) != NULL)
	{
	  switch (i)
	    {
	    case 0:
	      return read_num (&str[6], 10);
	      break;
	    case 5:
	      res = 0x30 << 2;
	      rr = read_regs (&str[2], 1);
	      if (rr == 0x10)
		return 0xff;
	      res |= rr;
	      return res;
	      break;
	    case 6:
	      res = 0x31 << 2;
	      rr = read_regs (&str[3], 1);
	      if (rr == 0x10)
		return 0xff;
	      res |= rr;
	      return res;
	      break;
	    default:
	      res = (8 | (i - 1)) << 4;
	      rr = read_regs (&str[3], 0);
	      if (rr == 0x10)
		return 0xff;
	      res |= rr;
	      return res;
	      break;
	    }
	}
    }
  return 0xfe;
}

// returns n bit in x
int
read_bit (char x, int n)
{
  return (x >> n) & 0x1;
}

// print num in binary representation
void
bin_print (char x)
{
  for (int i = 7; i >= 0; --i)
    printf ("%d", read_bit (x, i));
  printf ("\n");
}

// function that adds registers from command 'cmd' to the end of string 'res'
// returns adress of 'res'
char *
add_regs (unsigned char cmd, char *res)
{
  for (int i = 2; i > 0; --i)
    {
      int reg = (cmd >> (2 * (i - 1))) & 0x3;
      switch (reg)
	{
	case 0:
	  strcat (res, "A");
	  break;
	case 1:
	  strcat (res, "B");
	  break;
	case 2:
	  strcat (res, "C");
	  break;
	case 3:
	  strcat (res, "D");
	  break;
	}
      if (i - 1)
	strcat (res, ", ");
    }
  return res;
}

// function decodes one command from string 'str' and writes result in string
// 'res'
// returns adress of 'res'
char *
decode_one (char *str, char *res)
{
  if (str[8] != '\0')
    return NULL;

  unsigned char cmd = read_num (str, 2);

  if (read_bit (cmd, 7) == 0)
    {
      strcpy (res, "MOVI D, ");
      char imm[8];
      sprintf (imm, "%d", cmd & 0x7f);
      strcat (res, imm);
      return res;
    }

  if ((cmd >> 3) == 0x18)
    {
      if (read_bit (cmd, 2))
	{
	  strcpy (res, "OUT ");
	}
      else
	{
	  strcpy (res, "IN ");
	}

      int reg = cmd & 0x3;
      switch (reg)
	{
	case 0:
	  strcat (res, "A");
	  return res;
	  break;
	case 1:
	  strcat (res, "B");
	  return res;
	  break;
	case 2:
	  strcat (res, "C");
	  return res;
	  break;
	case 3:
	  strcat (res, "D");
	  return res;
	  break;
	}
    }

  if (read_bit (cmd, 6) == 0)
    {
      switch ((cmd >> 4) & 0x3)
	{
	case 0:
	  strcpy (res, "ADD ");
	  add_regs (cmd, res);
	  return res;
	  break;
	case 1:
	  strcpy (res, "SUB ");
	  add_regs (cmd, res);
	  return res;
	  break;
	case 2:
	  strcpy (res, "MUL ");
	  add_regs (cmd, res);
	  return res;
	  break;
	case 3:
	  strcpy (res, "DIV ");
	  add_regs (cmd, res);
	  return res;
	  break;
	}
    }

  return NULL;
}

// codec for one argument
void
codec_one (int *mode, char *str)
{
  if (*mode == ENCODER)
    {
      unsigned char res = encode_one (str);
      switch (res)
	{
	case 0xff:
	  *mode = 0;
	  return;
	case 0xfe:
	  *mode = -1;
	  return;
	}

      bin_print (res);
    }

  if (*mode == DECODER)
    {
      char res[10], *check = decode_one (str, res);
      if (check == NULL)
	{
	  *mode = -2;
	  return;
	}

      printf ("%s\n", res);
      return;
    }
}

// print num in binary representation in file 'f'
void
bin_fprint (FILE * f, unsigned char x)
{
  for (int i = 7; i >= 0; --i)
    fprintf (f, "%d", read_bit (x, i));
  fprintf (f, "\n");
}

// function encodes file 'input' and write result in file 'output'
void
encode_file (FILE * input, FILE * output)
{
  char str[20], *strx;
  for (;;)
    {
      strx = fgets (str, 16, input);

      if (strx == NULL)
	{
	  if (feof (input) != 0)
	    {
	      printf ("File read successfully\n");
	      break;
	    }
	  else
	    {
	      input = NULL;
	      break;
	    }
	}

      unsigned char res = encode_one (str);
      if (res == 0xff)
	{
	  output = NULL;
	  return;
	}

      printf (".\n");
      bin_fprint (output, res);
    }
}

// function decodes file 'input' and write result in file 'output'
void
decode_file (FILE * input, FILE * output)
{
  char str[16], *strx;
  for (;;)
    {
      strx = fgets (str, 12, input);

      if (strx == NULL)
	{
	  if (feof (input) != 0)
	    {
	      printf ("File read successfully\n");
	      break;
	    }
	  else
	    {
	      input = NULL;
	      break;
	    }
	}

      char res[16], *check = decode_one (str, res);
      if (check == NULL)
	{
	  output = NULL;
	  return;
	}

      printf (".\n");
      fprintf (output, "%s\n", res);
    }
}

// codec for file
void
codec_file (int *mode, FILE * input, FILE * output)
{
  if (*mode == ENCODER)
    encode_file (input, output);

  if (*mode == DECODER)
    decode_file (input, output);

  if (output == NULL)
    {
      *mode = -1;
      return;
    }
  if (input == NULL)
    {
      *mode = 0;
      return;
    }
}
