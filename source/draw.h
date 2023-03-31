#include <gba_base.h>


struct Cord{
	u16 x,y;
};
void Clear(u16 x, u16 y, u16 w, u16 h, u16 c);
void ClearWithBG(u16* pbg,u16 x, u16 y, u16 w, u16 h);
void DrawPic(u16 *GFX, u16 x, u16 y, u16 w, u16 h, u8 isTrans, u16 tcolor);
Cord DrawHZText12(char *str, u16 len, u16 x, u16 y, u16 c);
void printf_zh(const char *format, ...);
void ShowbootProgress(char *str);