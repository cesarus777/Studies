#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "additions.h"

//-----------------------------------------------------------------------------
//
// this file contains functions with analysis command line arguments
//
//-----------------------------------------------------------------------------

//function that defines codec mode
int
check_mode (char **argv)
{
  char *tmp = argv[1];

  if (tmp[0] == '-')
    {
      switch (tmp[1])
	{
	case ('c'):
	  return ENCODER;
	  break;
	case ('d'):
	  return DECODER;
	  break;
	}
    }

  fprintf (stderr, "Usage: %s <programm>\n", argv[0]);
  fprintf (stderr, "Unknown codec mode\n");
  abort ();
  return 0;
}

//function that defines files' usage
int
check_file (const int argc)
{
  if (argc < 3)
    return -1;
  if (argc == 6)
    return 1;
  return 0;
}

//function with start initialization of codec
void
codec_init (int *mode, int *file_flag, const int argc, char **argv)
{

  *mode = check_mode (argv);
  assert (*mode);

  *file_flag = check_file (argc);

  if ((*file_flag == 0) && (argc != 3))
    {
      fprintf (stderr, "Usage: %s <programm>\n", argv[0]);
      fprintf (stderr, "Incorrect argument format\n");
      abort ();
    }

  if (*file_flag == -1)
    {
      fprintf (stderr, "Usage: %s <programm>\n", argv[0]);
      fprintf (stderr, "No arguments were inputed\n");
      abort ();
    }
}

//function that opens input and output files
void
files_open (FILE ** input, FILE ** output, char **argv)
{
  if (strcmp (argv[2], "-f") == 0)
    {
      *input = fopen (argv[3], "r");
      if (strcmp (argv[4], "-o") == 0)
	*output = fopen (argv[5], "w");
      return;
    }
  if (strcmp (argv[4], "-f") == 0)
    {
      *input = fopen (argv[5], "r");
      if (strcmp (argv[2], "-o") == 0)
	*output = fopen (argv[3], "w");
      return;
    }
}
