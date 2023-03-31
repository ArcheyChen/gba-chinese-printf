#include <gba_base.h>


struct Cord{
	u16 x,y;
};

#define RGB(r,g,b) ((r)+(g<<5)+(b<<10))
void Clear(u16 x, u16 y, u16 w, u16 h, u16 c);
void ClearWithBG(u16* pbg,u16 x, u16 y, u16 w, u16 h);
void DrawPic(u16 *GFX, u16 x, u16 y, u16 w, u16 h, u8 isTrans, u16 tcolor);
void printf_zh(const char *format, ...);
void printf_zh_color(u16 color,const char *format, ...);