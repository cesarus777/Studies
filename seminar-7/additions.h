#pragma once

enum
{
  ENCODER = 1, DECODER
};

void codec_init (int *mode, int *file_flag, const int argc, char **argv);

void files_open (FILE ** input, FILE ** output, char **argv);
