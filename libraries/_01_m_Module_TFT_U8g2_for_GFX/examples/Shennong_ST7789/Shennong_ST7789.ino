#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_TFT.h>
#include <U8g2_for_Adafruit_GFX.h>

//#define BOARD_TYPE JOYPAD_ESP
//#define BOARD_TYPE MICROBIT_ESP

#define NORMAL    0       //Cube-S2 + ST7735
#define JOYPAD_ESP    1   //ESP32 + ST7789
#define MICROBIT_ESP  2   //ESP32 + ST7789

#if BOARD_TYPE == MICROBIT_ESP
#define TFT_CLK   18
#define TFT_MOSI  23
#define TFT_MISO  -1
#define TFT_CS    25
#define TFT_DC    26   //0
#define TFT_RST   -1   //15
#define TFT_BL    5
#define SPI_PORT  SPI
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS,  TFT_DC, TFT_RST);
#elif BOARD_TYPE == JOYPAD_ESP
#define TFT_CLK   14
#define TFT_MOSI  13
#define TFT_MISO  -1
#define TFT_CS    4
#define TFT_DC    15  //0
#define TFT_RST   -1   //15
#define TFT_BL    2
#define SPI_PORT  TFTSPI
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST);
#else
#define TFT_CLK   D13
#define TFT_MOSI  D11
#define TFT_MISO  -1
#define TFT_CS     D5
#define TFT_RST    -1  // you can also connect this to the Arduino reset
#define TFT_DC     D4
#define TFT_BL     D6
#define SPI_PORT  SPI
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
#endif

U8G2_FOR_ADAFRUIT_GFX u8g2;


// To read the short story with all glyphs you need at least a font with _gb2312b postfix
// However, a font with _gb2312b postfix is very large and will not always fit on
// the target controller. For testing you can use _chinese1 extenstion, but then
// many gylphs are skipped and not visible.
//
// wqy fonts are available in different sizes, here are only wqy12, wqy14 and wqy16 listed

//#define FONT u8g2_font_wqy12_t_chinese1
//#define FONT u8g2_font_wqy12_t_gb2312b

//#define FONT u8g2_font_wqy14_t_chinese1
//#define FONT u8g2_font_wqy14_t_gb2312b

//#define FONT u8g2_font_wqy16_t_chinese1
#define FONT u8g2_font_wqy16_t_gb2312b

// The next two macros define the scroll speed of the short story
#define SCROLL_DELTA 4
#define SCROLL_DELAY 100


// Chinese Short Story
// The Farmer God Shen Nong Tastes All the Plants
// Please excause wrong line breaks

const char c_str[] =
  "Shen Nong\n\n"
  "神农一生下来就是\n"
  "个水晶肚子，五脏\n"
  "六腑全都能看得一\n"
  "清二楚。那时侯，\n"
  "人们经常因为乱吃\n"
  "东西而生病，甚至\n"
  "丧命。神农决心尝\n"
  "遍所有的东西，好\n"
  "吃的放在身边左边\n"
  "的袋子里，给人吃\n"
  "；\n"
  "不好吃的就放在身\n"
  "子右边的袋子里，\n"
  "作药用。\n"
  "第一次，神农尝了\n"
  "一片小嫩叶。这叶\n"
  "片一落进肚里，就\n"
  "上上下下地把里面\n"
  "各器官擦洗得清清\n"
  "爽爽，\n"
  "象巡查似的，\n"
  "神农把它叫做\n"
  "“查”，\n"
  "就是后人所称的\n"
  "“茶”。\n"
  "神农将它放进右边\n"
  "袋子里。第二次，\n"
  "神农尝了朵蝴蝶样\n"
  "的淡红小花，甜津\n"
  "津的，香味扑鼻，\n"
  "这是“甘草”。他把\n"
  "它放进了左边袋子\n"
  "里。就这样，神农\n"
  "辛苦地尝遍百草，\n"
  "每次中毒，都靠茶\n"
  "来解救。后来，\n"
  "他左边的袋子里花\n"
  "草根叶有四万七千\n"
  "种，右边有三十九\n"
  "万八千种。\n"
  "但有一天，神农尝\n"
  "到了“断肠草”，这\n"
  "种毒草太厉害了，\n"
  "他还来不及吃茶解\n"
  "毒就死了。\n"
  "他是为了拯救人们\n"
  "而牺牲的，人们称\n"
  "他为“药王菩萨”，\n"
  "人间以这个神话故\n"
  "事永远地纪念他。\n";


char buf[48];      // there are at most 8 chinese glyphs per line, max buf size is 8*3 = 24

uint8_t total_lines;    // the total number of lines in the story
uint8_t i;        // loop variable for the lines
uint8_t line_cnt;   // number of lines to draw, usually equal to lines_per_draw
uint8_t start_line;   // topmost visible line, derived from top_window_pos
uint8_t lines_per_draw; // how many lines to draw on the screen, derived from font and display height
uint16_t glyph_height;  // height of the glyphs
uint16_t glyph_width;

uint16_t top_window_pos;    // defines the display position in pixel within the text
uint16_t total_height;      // total height in pixel, derived from font height and total_lines
uint16_t top_offset;     // offset between the first visible line and the display


uint8_t u8x8_GetStringLineCnt(const char *str)
{
  char e;
  uint8_t line_cnt = 1;
  if ( str == NULL )
    return 0;
  for (;;)
  {
    e = *str;
    if ( e == '\0' )
      break;
    str++;
    if ( e == '\n' )
      line_cnt++;
  }
  return line_cnt;
}

/*
    Assumes strings, separated by '\n' in "str".
    Returns the string at index "line_idx". First strng has line_idx = 0
    Example:
      Returns "xyz" for line_idx = 1 with str = "abc\nxyz"
    Support both UTF8 and normal strings.
*/
const char *u8x8_GetStringLineStart(uint8_t line_idx, const char *str )
{
  char e;
  uint8_t line_cnt = 1;

  if ( line_idx == 0 )
    return str;

  for (;;)
  {
    e = *str;
    if ( e == '\0' )
      break;
    str++;
    if ( e == '\n' )
    {
      if ( line_cnt == line_idx )
        return str;
      line_cnt++;
    }
  }
  return NULL;  /* line not found */
}

/* copy until first '\n' or '\0' in str */
/* Important: There is no string overflow check, ensure */
/* that the destination buffer is large enough */
void u8x8_CopyStringLine(char *dest, uint8_t line_idx, const char *str)
{
  if ( dest == NULL )
    return;
  str = u8x8_GetStringLineStart( line_idx, str );
  if ( str != NULL )
  {
    for (;;)
    {
      if ( *str == '\n' || *str == '\0' )
        break;
      *dest = *str;
      dest++;
      str++;
    }
  }
  *dest = '\0';
}


void setup() {
#ifdef ESP32
  tft.begin(SPI_DEFAULT_FREQ, SPI_PORT);
#else
  tft.begin(SPI_DEFAULT_FREQ);
#endif
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);
  u8g2.begin(tft);                 // connect u8g2 procedures to Adafruit GFX

  u8g2.setFont(FONT);
  u8g2.setForegroundColor(TFT_WHITE);      // apply Adafruit GFX color

  /* calculate the length of the text in lines */
  total_lines = u8x8_GetStringLineCnt(c_str);

  /* get the height of the glyphs */
  //glyph_height = u8g2.getMaxCharHeight();
  glyph_height = u8g2.u8g2.font_info.max_char_height;
  glyph_width = u8g2.u8g2.font_info.max_char_width;

  /* calculate the height of the text in pixel */
  total_height = (uint16_t)total_lines * (uint16_t)glyph_height;


  /* calculate how many lines must be drawn on the screen */
  lines_per_draw = tft.height() / glyph_height;
  lines_per_draw += 2;

  /* start at the top of the text */
  top_window_pos = 0;

}

void loop() {
  start_line = top_window_pos / glyph_height;
  top_offset = top_window_pos % glyph_height;

  line_cnt = total_lines - start_line;
  if ( line_cnt > lines_per_draw )
    line_cnt = lines_per_draw;

  //tft.clearDisplay();                               // clear the graphcis buffer

  for ( i = 0; i < line_cnt; i++ )
  {
    /* copy a line of the text to the local buffer */
    u8x8_CopyStringLine(buf, i + start_line, c_str);

    /* draw the content of the local buffer */
    tft.fillRect(0, i * glyph_height - top_offset, line_cnt * glyph_width, glyph_height, TFT_BLACK);
    u8g2.drawUTF8(0, i * glyph_height - top_offset + glyph_height, buf);


  }

  //tft.display();                                    // make everything visible
  delay(SCROLL_DELAY);
  top_window_pos += SCROLL_DELTA;
}
