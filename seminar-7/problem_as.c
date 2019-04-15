#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "additions.h"
#include "codecs.h"

int
main (int argc, char **argv)
{
  if (argc < 2)
    {
      fprintf (stderr, "Usage: %s <programm>\n", argv[0]);
      abort ();
    }

  int mode = 0, file_flag = 0;
  codec_init (&mode, &file_flag, argc, argv);

  if (file_flag == 0)
    {
      codec_one (&mode, argv[2]);
      switch (mode)
	{
	case 0:
	  fprintf (stderr, "Usage: %s <programm>\n", argv[0]);
	  fprintf (stderr, "Register input error\n");
	  abort ();
	  break;
	case -1:
	  fprintf (stderr, "Usage: %s <programm>\n", argv[0]);
	  fprintf (stderr, "Error: unknown instruction\n");
	  abort ();
	  break;
	case -2:
	  fprintf (stderr, "Usage: %s <programm>\n", argv[0]);
	  fprintf (stderr, "Incorrect instruction\n");
	  abort ();
	  break;
	}
      return 0;
    }

  if (file_flag == 1)
    {
      FILE *input = NULL, *output = NULL;
      files_open (&input, &output, argv);
      assert (input != NULL);
      assert (output != NULL);
      codec_file (&mode, input, output);
      switch (mode)
	{
	case 0:
	  fprintf (stderr, "Usage: %s <programm>\n", argv[0]);
	  fprintf (stderr, "File read error\n");
	  abort ();
	  break;
	case -1:
	  fprintf (stderr, "Usage: %s <programm>\n", argv[0]);
	  fprintf (stderr, "Data format error\n");
	  abort ();
	  break;
	}

      fclose (input);
      fclose (output);
    }
}
