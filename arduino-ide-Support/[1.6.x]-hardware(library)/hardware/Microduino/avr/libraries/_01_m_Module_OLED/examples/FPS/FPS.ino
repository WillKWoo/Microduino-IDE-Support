/*

  FPS.pde
  
  >>> Before compiling: Please remove comment from the constructor of the 
  >>> connected graphics display (see below).
  
  Universal 8bit Graphics Library, http://code.google.com/p/u8glib/
  
  Copyright (c) 2012, olikraus@gmail.com
  All rights reserved.

  Redistribution and use in source and binary forms, with or without modification, 
  are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice, this list 
    of conditions and the following disclaimer.
    
  * Redistributions in binary form must reproduce the above copyright notice, this 
    list of conditions and the following disclaimer in the documentation and/or other 
    materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND 
  CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  

  ST7920_192X32, SPI:    FPS: Box=7.6   @=9.8                iFPS: Box=11.4  @=14.7
  ST7920_192X32, 8Bit:   FPS: Box=6.2   @=7.5                iFPS: Box=9.3 @=11.2
  DOGM128 SW SPI:         FPS: Box=5.1   @=5.9  Pix=2.6               iFPS: Box=10.2 @=11.8 Pix=5.2
  DOGM128 HW SPI:         FPS: Box=5.5   @=6.3               iFPS: Box=11.0 @=12.6
  DOGXL160 SW SPI:         FPS: Box=1.7   @=1.9               iFPS: Box=6.9 @=7.7
  DOGXL160 HW SPI:         FPS: Box=1.8   @=2.1               
  
  NHD27OLED_BW, SW SPI: FPS: Box=3.0  @=3.7
  NHD27OLED_BW, HW SPI: FPS: Box=3.5  @=4.5
  NHD27OLED_2X_BW, SW SPI: FPS: Box=3.8  @=4.9
  NHD27OLED_2X_BW, HW SPI: FPS: Box=4.6  @=6.4
  
  30 Sep 2012
  NHD27OLED_BW, SW SPI: FPS: Clip=9.2 Box=3.9  @=4.4		NEW_CODE
  NHD27OLED_BW, SW SPI: FPS: Clip=9.2 Box=3.6  @=4.5
  NHD27OLED_BW, HW SPI: FPS: Clip=16.3 Box=4.7  @=5.6
  NHD27OLED_2X_BW, SW SPI: FPS: Clip=9.7 Box=4.5  @=5.8
  NHD27OLED_2X_BW, SW SPI: FPS: Clip=18.0 Box=5.8  @=7.9

  1 Oct 2012
  ST7920_192X32, 8Bit:   FPS: Box=7.2   @=10.0                
  DOGM128 SW SPI:         FPS: Box=5.2   @=6.6  Pix=2.6               
  DOGM128 HW SPI:         FPS: Clip=33.2 Box=5.5   @=7.1
  DOGXL160 SW SPI:         FPS: Box=1.7   @=2.0
  DOGXL160 HW SPI:         FPS: Box=1.8   @=2.2

  DOGXL160 GR SW SPI:         FPS: Box=1.1   @=1.3

  1 Mar 2013
  ST7920_192X32_1X, SPI:    FPS: Clip=10.3 Box=5.5  @=7.2 Pix=3.9
  ST7920_192X32_4X, SPI:    FPS: Clip=10.9 Box=6.7  @=8.8 Pix=7.4
  ST7920_192X32_1X, 8Bit:    FPS: Clip=14.2 Box=6.1  @=8.4 Pix=4.2
  ST7920_192X32_4X, 8Bit:    FPS: Clip=14.2 Box=7.8  @=10.7 Pix=8.7
  ST7920_192X32_1X, HW SPI:    FPS: Clip=14.2 Box=6.3  @=8.7 Pix=4.3
  ST7920_192X32_4X, HW SPI:    FPS: Clip=15.3 Box=8.0  @=11.2 Pix=9.0

  2 Jun 2013
  U8GLIB_DOGM128 SW SPI:		FPS: Clip=23.9 Box=4.5  @=6.6 Pix=2.1
  U8GLIB_DOGM128_2X SW SPI:	FPS: Clip=28.5 Box=6.6  @=9.7 Pix=3.9
  U8GLIB_DOGM128_2X HW SPI:	FPS: Clip=40.8 Box=7.1  @=10.8 Pix=4.1
  
  3 Jun 2013
  U8GLIB_ST7920_192X32_1X -Os	SW SPI	FPS: Clip=11.0 Box=5.4  @=7.1 Pix=3.9	Size=11828
  U8GLIB_ST7920_192X32_1X -O3	SW SPI	FPS: Clip=10.9 Box=5.6  @=7.5 Pix=4.0	Size=13800
  U8GLIB_ST7920_192X32_1X -Os	SW SPI	FPS: Clip=16.8 Box=6.7  @=9.6 Pix=4.5	Size=11858	(new seq data output)
  U8GLIB_ST7920_192X32_1X -Os	HW SPI	FPS: Clip=25.7 Box=7.5  @=11.3 Pix=4.8	(new seq data output)
  
  6 Jun 2013
  U8GLIB_DOGS102 u8g(13, 11, 10, 9);    STD SW SPI	FPS: Clip=9.5 Box=7.6  @=8.2 Pix=6.2	Size=15652
  U8GLIB_DOGS102 u8g(13, 11, 10, 9);    SW SPI	        FPS: Clip=19.1 Box=12.8  @=14.0 Pix=9.2	Size=15532


  12 Jun 2013
  SSD1351_128X128_332	SW SPI Clip=1.3 Box=0.7  @=0.9 Pix=0.4
  SSD1351_128X128_332	HW SPI Clip=3.6 Box=1.1  @=1.5 Pix=0.5

  24 Jun 2013
  Uno SSD1351_128X128_332				SW SPI Clip=1.4 Box=0.8  @=0.9 Pix=0.4
  
  Uno SSD1351_128X128_332					HW SPI Clip=4.4 Box=1.2  @=1.6 Pix=0.5
  Uno SSD1351_128X128_HICOLOR			HW SPI Clip=3.7 Box=0.8  @=1.0 Pix=0.3

  Mega2560 SSD1351_128X128_332			HW SPI Clip=4.4 Box=1.2  @=1.6 Pix=0.5
  Mega2560 SSD1351_128X128_4X_332			HW SPI Clip=4.6 Box=2.3  @=2.8 Pix=1.5
  Mega2560 SSD1351_128X128_HICOLOR		HW SPI Clip=3.6 Box=0.8  @=1.0 Pix=0.3
  Mega2560 SSD1351_128X128_4X_HICOLOR	HW SPI Clip=4.2 Box=1.7  @=2.1 Pix=1.0

  Due SSD1351_128X128_332					HW SPI Clip=24.6 Box=6.3  @=7.8 Pix=2.8
  Due SSD1351_128X128_4X_332 				HW SPI Clip=28.1 Box=13.0  @=15.1 Pix=8.5
  Due SSD1351_128X128_HICOLOR			HW SPI Clip=20.8 Box=3.4  @=4.5 Pix=1.4
  Due SSD1351_128X128_4X_HICOLOR			HW SPI Clip=26.3 Box=8.9  @=11.1 Pix=4.8

  Due SSD1351_128X128_4X_HICOLOR			SW SPI Clip=0.4 Box=0.4  @=0.4 Pix=0.4
  
  Due DOGS102 u8g(13, 11, 10, 9);    			SW SPI	        FPS: Clip=19.1 Box=13.1  @=14.3 Pix=9.4
  Due DOGS102 u8g(10, 9);    					HW SPI	        FPS: Clip=128.9 Box=30.7  @=40.6 Pix=15.4

  Due NHD27OLED_BW u8g(10, 9)				HW SPI		FPS: Clip=53.0 Box=19.6  @=23.8 Pix=10.6
  Due NHD27OLED_2X_BW u8g(10, 9)			HW SPI		FPS: Clip=57.0 Box=25.3  @=31.7 Pix=18.1
  Due NHD27OLED_GR u8g(10, 9)				HW SPI		FPS: Clip=34.1 Box=11.7  @=13.7 Pix=5.6
  Due NHD27OLED_2X_GR u8g(10, 9)			HW SPI		FPS: Clip=38.1 Box=15.5  @=20.0 Pix=8.8

*/


#include "U8glib.h"

// setup u8g object, please remove comment from one of the following constructor calls
// IMPORTANT NOTE: The following list is incomplete. The complete list of supported 
// devices with all constructor calls is here: http://code.google.com/p/u8glib/wiki/device

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);	// I2C / TWI 

#define SECONDS 10
uint8_t flip_color = 0;
uint8_t draw_color = 1;

void draw_set_screen(void) {
  // graphic commands to redraw the complete screen should be placed here  
  if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    if ( flip_color == 0 ) 
      u8g.setHiColorByRGB(0,0,0);
    else
      u8g.setHiColorByRGB(255,255,255);
  }
  else {
    u8g.setColorIndex(flip_color);
  }
  u8g.drawBox( 0, 0, u8g.getWidth(), u8g.getHeight() );
}

void draw_clip_test(void) {
  u8g_uint_t i, j, k;
  char buf[3] = "AB";
  k = 0;
  if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255,255,255);
  }
  else {
    u8g.setColorIndex(draw_color);
  }
  u8g.setFont(u8g_font_6x10);
  
  for( i = 0; i  < 6; i++ ) {
    for( j = 1; j  < 8; j++ ) {
      u8g.drawHLine(i-3, k, j);
      u8g.drawHLine(i-3+10, k, j);
      
      u8g.drawVLine(k+20, i-3, j);
      u8g.drawVLine(k+20, i-3+10, j);
      
      k++;
    }
  }
  u8g.drawStr(0-3, 50, buf);
  u8g.drawStr180(0+3, 50, buf);
  
  u8g.drawStr(u8g.getWidth()-3, 40, buf);
  u8g.drawStr180(u8g.getWidth()+3, 40, buf);

  u8g.drawStr90(u8g.getWidth()-10, 0-3, buf);
  u8g.drawStr270(u8g.getWidth()-10, 3, buf);

  u8g.drawStr90(u8g.getWidth()-20, u8g.getHeight()-3, buf);
  u8g.drawStr270(u8g.getWidth()-20, u8g.getHeight()+3, buf);
  
}

void draw_char(void) {
  char buf[2] = "@";
  u8g_uint_t i, j;
  // graphic commands to redraw the complete screen should be placed here  
  if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255,255,255);
  }
  else {
    u8g.setColorIndex(draw_color);
  }
  u8g.setFont(u8g_font_6x10);
  j = 8;
  for(;;) {
    i = 0;
    for(;;) {
      u8g.drawStr( i, j, buf);
      i += 8;
      if ( i > u8g.getWidth() )
        break;
    }
    j += 8;
    if ( j > u8g.getHeight() )
      break;
  }
  
}

void draw_pixel(void) {
  u8g_uint_t x, y, w2, h2;
  if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255,255,255);
  }
  else {
    u8g.setColorIndex(draw_color);
  }
  w2 = u8g.getWidth();
  h2 = u8g.getHeight();
  w2 /= 2;
  h2 /= 2;
  for( y = 0; y < h2; y++ ) {
    for( x = 0; x < w2; x++ ) {
      if ( (x + y) & 1 ) {
        u8g.drawPixel(x,y);
        u8g.drawPixel(x,y+h2);
        u8g.drawPixel(x+w2,y);
        u8g.drawPixel(x+w2,y+h2);
      }
    }
  }
}

// returns unadjusted FPS
uint16_t picture_loop_with_fps(void (*draw_fn)(void)) {
  uint16_t FPS10 = 0;
  uint32_t time;
  
  time = millis() + SECONDS*1000;
  
  // picture loop
  do {
    u8g.firstPage();  
    do {
      draw_fn();
    } while( u8g.nextPage() );
    FPS10++;
    flip_color = flip_color ^ 1;
  } while( millis() < time );
  return FPS10;  
}

const char *convert_FPS(uint16_t fps) {
  static char buf[6];
  strcpy(buf, u8g_u8toa( (uint8_t)(fps/10), 3));
  buf[3] =  '.';
  buf[4] = (fps % 10) + '0';
  buf[5] = '\0';
  return buf;
}

void show_result(const char *s, uint16_t fps) {
  // assign default color value
  if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255,255,255);
  }
  else {
    u8g.setColorIndex(draw_color);
  }
  u8g.setFont(u8g_font_8x13B);
  u8g.firstPage();  
  do {
    u8g.drawStr(0,12, s);
    u8g.drawStr(0,24, convert_FPS(fps));
  } while( u8g.nextPage() );
}

void setup(void) {
  // flip screen, if required
  // u8g.setRot180();
  
  // assign default color value
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) 
    draw_color = 255;     // white
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT )
    draw_color = 3;         // max intensity
  else if ( u8g.getMode() == U8G_MODE_BW )
    draw_color = 1;         // pixel on
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255,255,255);
  }
}

void loop(void) {
  uint16_t fps;
  fps = picture_loop_with_fps(draw_clip_test);
  show_result("draw clip test", fps);
  delay(5000);
  fps = picture_loop_with_fps(draw_set_screen);
  show_result("clear screen", fps);
  delay(5000);
  fps = picture_loop_with_fps(draw_char);
  show_result("draw @", fps);
  delay(5000);  
  fps = picture_loop_with_fps(draw_pixel);
  show_result("draw pixel", fps);
  delay(5000);
}

