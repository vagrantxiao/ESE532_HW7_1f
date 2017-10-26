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
  unsigned char Input_y[OUTPUT_FRAME_WIDTH];
  unsigned Input_ymx, Input_yxm, Input_new;


  for (int Y = 0; Y < OUTPUT_FRAME_HEIGHT; Y++)
  {
    for (int X = 0; X < OUTPUT_FRAME_WIDTH; X++)
    {
#pragma HLS PIPELINE
      Input_ymx = Input_y[X];
      Input_yxm = Input_new;
      Input_new = Input[OUTPUT_FRAME_WIDTH * Y + X];
      int Average = 0;
      if (Y > 0 && X > 0)
        Average = (Input_ymx + Input_yxm) / 2;
      else if (Y > 0)
        Average = Input_ymx;
      else if (X > 0)
        Average = Input_yxm;

      unsigned char Diff = Input_new - Average;
      Output[Y * OUTPUT_FRAME_WIDTH + X] = Diff;

      Input_y[X] = Input_new;
    }
  }
}


