/*

This file contains all functions related to controlling LED Matrix. Based on bartoszbielawski's LEDMatrixDriver library

*/

// Define CS pin 
const uint8_t LEDMATRIX_CS_PIN = 15;

// Number of 8x8 segments you are connecting
const int LEDMATRIX_SEGMENTS = 4;
const int LEDMATRIX_WIDTH    = LEDMATRIX_SEGMENTS * 8;

// The LEDMatrixDriver class instance
LEDMatrixDriver lmd(LEDMATRIX_SEGMENTS, LEDMATRIX_CS_PIN);

// Marquee speed (lower nubmers = faster)
const int ANIM_DELAY = 30;

int x=0, y=0;   // start top left

/**
 * This draws a sprite to the given position using the width and height supplied (usually 8x8)
 */
void drawSprite( byte* sprite, int x, int y, int width, int height )
{
  // The mask is used to get the column bit from the sprite row
  byte mask = B10000000;

  for( int iy = 0; iy < height; iy++ )
  {
    for( int ix = 0; ix < width; ix++ )
    {
      lmd.setPixel(x + ix, y + iy, (bool)(sprite[iy] & mask ));

      // shift the mask by one pixel to the right
      mask = mask >> 1;
    }

    // reset column mask
    mask = B10000000;
  }
}

void writeToMatrix(String msg, int len){
  char buf[100];
  // Draw the text to the current position
  msg.toCharArray(buf, len+1);
  for(int i=0;i<len;i++){
    int c = (int)buf[i] - 32;
    if( x + i * 8  > LEDMATRIX_WIDTH )return;
    if( 8 + x + i * 8 > 0 ) drawSprite(font[c], x+i * 8, y, 8, 8);
  }
  // In case you wonder why we don't have to call lmd.clear() in every loop: The font has a opaque (black) background...


}
