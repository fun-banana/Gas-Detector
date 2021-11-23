#ifndef BITMAP_H
#define BITMAP_H

/******************************************
PURPOSE:    Provides a function that allows to print 24bit bmp images onto the TFT9341 screen
            (only canon bmp images are allowed - bottom-top ordered)
Created by: Daniel Rossinsky
DATE:       3/6/2018
*******************************************/

#include <stdint.h>

namespace bmp {
  enum BMPStatus : uint8_t
  {
    FILE_NOT_FOUND,
    NOT_24_BIT,
    COMPRESSED,
    GOOD_BMP,
    BAD_BMP,
    BAD_ID,
    BAD_XY
  };

  BMPStatus draw(char* file_name, uint16_t x, uint16_t y);
}

#endif 
