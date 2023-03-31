#include <gba_base.h>



void Clear(u16 x, u16 y, u16 w, u16 h, u16 c);
void ClearWithBG(u16* pbg,u16 x, u16 y, u16 w, u16 h);
void DrawPic(u16 *GFX, u16 x, u16 y, u16 w, u16 h, u8 isTrans, u16 tcolor);
void DrawHZText12(char *str, u16 len, u16 x, u16 y, u16 c);
void DEBUG_printf(const char *format, ...);
void ShowbootProgress(char *str);