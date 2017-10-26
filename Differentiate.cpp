#include "Pipeline.h"

void Differentiate_SW(const unsigned char * Input, unsigned char * Output)
{
  for (int Y = 0; Y < OUTPUT_FRAME_HEIGHT; Y++)
    for (int X = 0; X < OUTPUT_FRAME_WIDTH; X++)
    {
      int Average = 0;
      if (Y > 0 && X > 0)
        Average = (Input[OUTPUT_FRAME_WIDTH * (Y - 1) + X] + Input[OUTPUT_FRAME_WIDTH * Y + X - 1]) / 2;
      else if (Y > 0)
        Average = Input[OUTPUT_FRAME_WIDTH * (Y - 1) + X];
      else if (X > 0)
        Average = Input[OUTPUT_FRAME_WIDTH * Y + X - 1];

      unsigned char Diff = Input[OUTPUT_FRAME_WIDTH * Y + X] - Average;

      Output[Y * OUTPUT_FRAME_WIDTH + X] = Diff;
    }
}

#pragma SDS data copy(Input[0:OUTPUT_FRAME_HEIGHT * OUTPUT_FRAME_WIDTH], Output[0:OUTPUT_FRAME_HEIGHT * OUTPUT_FRAME_WIDTH])
#pragma SDS data access_pattern(Input:SEQUENTIAL, Output:SEQUENTIAL)
void Differentiate_HW(const unsigned char Input[FRAMES * INPUT_FRAME_SIZE], unsigned char Output[FRAMES * INPUT_FRAME_SIZE])
{
  unsigned char Input_ym[OUTPUT_FRAME_WIDTH];
  unsigned char Input_y[OUTPUT_FRAME_WIDTH];

  for (int Y = 0; Y < OUTPUT_FRAME_HEIGHT; Y++)
  {
    for (int X = 0; X < OUTPUT_FRAME_WIDTH; X++)
    {
      Input_y[X] =  Input[OUTPUT_FRAME_WIDTH * Y + X];
      int Average = 0;
      if (Y > 0 && X > 0)
        Average = (Input_ym[X] + Input_y[X-1]) / 2;
      else if (Y > 0)
        Average = Input_ym[X];
      else if (X > 0)
        Average = Input_y[X-1];

      unsigned char Diff = Input_y[X] - Average;
      Output[Y * OUTPUT_FRAME_WIDTH + X] = Diff;
      Input_ym[X] = Input_y[X];
    }
  }
}


