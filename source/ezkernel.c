#include <gba_video.h>
#include <gba_interrupt.h>
#include <gba_systemcalls.h>
#include <gba_input.h>
#include <stdio.h>
#include <stdlib.h>
#include <gba_base.h>
#include <gba_dma.h>
#include <string.h>
#include <stdarg.h>
#include <gba_timers.h>

#include "draw.h"
#include "ezkernel.h"
#include "images/splash.h"


u8 pReadCache [MAX_pReadCache_size]EWRAM_BSS;


u32 game_total_SD;
u32 game_total_NOR;
u32 folder_total;

u32 gl_currentpage;
u32 gl_norOffset;
u16 gl_select_lang;
u16 gl_engine_sel;

u16 gl_show_Thumbnail;
u16 gl_ingame_RTC_open_status;


u8 __attribute__((aligned(4)))GAMECODE[4];

u8 dwName;

u16 gl_reset_on;
u16 gl_rts_on;
u16 gl_sleep_on;
u16 gl_cheat_on;

//----------------------------------------
u16 gl_color_selected 		= RGB(00,20,26);
u16 gl_color_text 				= RGB(31,31,31);
u16 gl_color_selectBG_sd 	= RGB(00,00,31);
u16 gl_color_selectBG_nor = RGB(10,10,10);
u16 gl_color_MENU_btn			= RGB(20,20,20);
u16 gl_color_cheat_count  = RGB(00,31,00);
u16 gl_color_cheat_black  = RGB(00,00,00);
u16 gl_color_NORFULL      = RGB(31,00,00);
u16 gl_color_btn_clean    = RGB(00,00,31);
//******************************************************************************
void delay(u32 R0)
{
  int volatile i;

  for ( i = R0; i; --i );
  return;
}
//---------------------------------------------------------------------------------
void wait_btn()
{
	while(1)
	{
		scanKeys();
		u16 keys = keysUp();
		if (keys & KEY_B) {
			break;
		}
	}
	//while(*(vu16*)0x04000130 == 0x3FF );
	//while(*(vu16*)0x04000130 != 0x3FF );
}
//---------------------------------------------------------------------------------

int main(void) {

	irqInit();
	irqEnable(IRQ_VBLANK);

	REG_IME = 1;

	SetMode (MODE_3 | BG2_ENABLE );
	
	DrawPic((u16*)gImage_splash, 0, 0, 240, 160, 0, 0, 1);	

	DrawHZText12("≤‚ ‘“ªœ¬",0,2,20, gl_color_text,1);

	VBlankIntrWait();	
	while(1);
}
//---------------------------------------------------------------