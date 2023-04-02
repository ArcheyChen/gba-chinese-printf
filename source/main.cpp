#include <gba_video.h>
#include <gba_interrupt.h>
#include <gba_systemcalls.h>
#include <gba_timers.h>
#include <gba_input.h>
#include <stdio.h>
#include <stdlib.h>
#include <gba_base.h>
#include <gba_dma.h>
#include <string.h>
#include <stdarg.h>
#include <gba_timers.h>

#include "font.h"
// #include "images/splash.h"




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

int main(void) {
	
	irqInit();
	irqEnable(IRQ_VBLANK);

	
	SetMode (MODE_3 | BG2_ENABLE );

	REG_IME = 1;
	
	// DrawPic((u16*)gImage_splash, 0, 0, 240, 160, 0, 0);	
	char txt[] = "君不见，黄河之水天上来，奔流到海不复回。"
"君不见，高堂明镜悲白发，朝如青丝暮成雪。"
""
"人生得意须尽欢，莫使金樽空对月。"
""
"天生我材必有用，千金散尽还复来。"
""
"烹羊宰牛且为乐，会须一饮三百杯。"
""
"岑夫子，丹丘生，将进酒，杯莫停。"
""
"与君歌一曲，请君为我倾耳听。"
""
"钟鼓馔玉不足贵，但愿长醉不愿醒。"
""
"古来圣贤皆寂寞，惟有饮者留其名。"
""
"陈王昔时宴平乐，斗酒十千恣欢谑。"
""
"主人何为言少钱，径须沽取对君酌。"
""
"五花马，千金裘，呼儿将出换美酒，与尔同销万古愁。";
	fbInit();
	fbDrawUtf8String(txt,gl_color_cheat_count);

	clearConsole();
	printf_zh_color(gl_color_MENU_btn,"请看古文：\n%s",txt);
	// printf_zh_color(gl_color_MENU_btn,"测试\n");
	
	
	VBlankIntrWait();	
	while(1);
}
//---------------------------------------------------------------