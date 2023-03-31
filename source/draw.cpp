#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <cstring>
#include <gba_base.h>
#include <gba_dma.h>


#include "hzk12.h"
#include "asc126.h"
#include "draw.h"

#include "ezkernel.h"


extern u8 pReadCache [MAX_pReadCache_size]EWRAM_BSS;
//******************************************************************************
void IWRAM_CODE Clear(u16 x, u16 y, u16 w, u16 h, u16 c)
{
	u16 *p = VideoBuffer;
	u16 yi,ww,hh;
    

    hh = (y+h>160)?160:(y+h);
    ww  = (x+w>240)?(240-x):w;

	//u16 tmp[240];
	for(u32 i=0;i<240;i++)
		((u16*)pReadCache)[i] = c;

	for(yi=y; yi < hh; yi++)
		dmaCopy(pReadCache,p+yi*240+x,ww*2);         
}
//******************************************************************************
void IWRAM_CODE ClearWithBG(u16* pbg,u16 x, u16 y, u16 w, u16 h)
{
	u16 *p = VideoBuffer;;
	u16 yi,ww,hh;
    
    hh = (y+h>160)?160:(y+h);
    ww  = (x+w>240)?(240-x):w;

	for(yi=y; yi < hh; yi++)
		dmaCopy(pbg+yi*240+x,p+yi*240+x,ww*2);       
}
//******************************************************************************
void IWRAM_CODE DrawPic(u16 *GFX, u16 x, u16 y, u16 w, u16 h, u8 isTrans, u16 tcolor)
{
	u16 *p = VideoBuffer;
	u16 c;
	u16 xi,yi,ww,hh;

  hh = (y+h>160)?160:(y+h);
  ww  = (x+w>240)?(240-x):w;	
	
	if(isTrans)
	{
		for(yi=y; yi < hh; yi++)
			for(xi=x;xi<x+ww;xi++)
			{
				c = GFX[(yi-y)*w+(xi-x)];
				if(c!=tcolor)
					p[yi*240+xi] = c;
			}
	}
	else
	{
		for(yi=y; yi < hh; yi++)
			dmaCopy(GFX+(yi-y)*w,p+yi*240+x,w*2); 
	}
}
//---------------------------------------------------------------------------------

Cord DrawHZText12(char *str, u16 len, u16 x, u16 y, u16 color)
{
	u32 i,l,hi=0;
	u32 location;
	u8 cc,c1,c2;
	u16 *vram;
	vram = VideoBuffer;
	u16 yy;


	if(len==0)
		l=strlen(str);
	else
		if(len>strlen(str))
			l=strlen(str);
		else
			l=len;

	if((u16)(len*6)>(u16)(240-x))
		len=(240-x)/6;
    while(hi<l)
    {
		c1 = str[hi];
    	hi++;
    	if(c1<0x80)  //ASCII
    	{
			yy = 240*y;
    		location = c1*12;
    		for(i=0;i<12;i++)//字符的高是12，所以画12次
			{
				cc = ASC_DATA[location+i];
				if(cc & 0x01)	//如果这个字符在第i位是1，那么把对应内存的位置填上color
					vram[x+7+yy]=color;
				if(cc & 0x02)
					vram[x+6+yy]=color;
				if(cc & 0x04)
					vram[x+5+yy]=color;
				if(cc & 0x08)
					vram[x+4+yy]=color;
				if(cc & 0x10)
					vram[x+3+yy]=color;
				if(cc & 0x20)
					vram[x+2+yy]=color;
				if(cc & 0x40)
					vram[x+1+yy]=color;
				if(cc & 0x80)
					vram[x+yy]=color;
				yy+=240;
			}		
    		x+=6;
    		continue;
    	}
		else	//Double-byte
		{	
    		c2 = str[hi];
    		hi++;
    		if(c1<0xb0)
    			location = ((c1-0xa1)*94+(c2-0xa1))*24;
    		else
    			location = (9*94+(c1-0xb0)*94+(c2-0xa1))*24;

			yy = 240*y;
			for(i=0;i<12;i++)
			{				
				cc = acHZK12[location+i*2];
				if(cc & 0x01)
					vram[x+7+yy]=color;
				if(cc & 0x02)
					vram[x+6+yy]=color;
				if(cc & 0x04)
					vram[x+5+yy]=color;
				if(cc & 0x08)
					vram[x+4+yy]=color;
				if(cc & 0x10)
					vram[x+3+yy]=color;
				if(cc & 0x20)
					vram[x+2+yy]=color;
				if(cc & 0x40)
					vram[x+1+yy]=color;
				if(cc & 0x80)
					vram[x+yy]=color;
								
				cc = acHZK12[location+i*2+1];
				if(cc & 0x01)
					vram[x+15+yy]=color;
				if(cc & 0x02)
					vram[x+14+yy]=color;
				if(cc & 0x04)
					vram[x+13+yy]=color;
				if(cc & 0x08)
					vram[x+12+yy]=color;
				if(cc & 0x10)
					vram[x+11+yy]=color;
				if(cc & 0x20)
					vram[x+10+yy]=color;
				if(cc & 0x40)
					vram[x+9+yy]=color;
				if(cc & 0x80)
					vram[x+8+yy]=color;
				yy+=240;
			}
			x+=12;
		}
	}
	Cord cord;
	cord.x = x;
	cord.y = y;
	return cord;
}
//---------------------------------------------------------------------------------
void printf_zh(const char *format, ...)
{
	static int current_y = 1;
    static char str[128];
    va_list va;

    va_start(va, format);
    vsprintf(str, format, va);
    va_end(va);

    DrawHZText12(str,0,0,current_y, RGB(31,31,31));
    

    current_y += 12;//英文字库结构  12*8 ，高12，宽6 ，前6bit，中文则是宽12
    if(current_y>150) 
    {
    	current_y=1;
    }
}
//---------------------------------------------------------------------------------
void ShowbootProgress(char *str)
{
	u8 str_len = strlen(str); 	
	Clear(60,160-15,120,15,gl_color_cheat_black);	
	DrawHZText12(str,0,(240-str_len*6)/2,160-15,gl_color_text);	
}
