#include "lvgl.h"
#include "lv_drivers/wayland/wayland.h"
#include <time.h>
#include <unistd.h>
#include <stdio.h>

const int screenWidth = 800;
const int screenHeight = 480;
const int topHeight = 35;
const int tunerHeight = 100;
const int barHeight = 110; // 90;

lv_obj_t *scr, *label_status, *bar_view, *button;
lv_style_t style_btn;

static int counter = 0;

static void button_event_cb(lv_event_t *e)
{
	char str[80];
	lv_obj_t *obj = lv_event_get_target(e);

	sprintf(str, "Hello button pressed %d", counter++);
	lv_label_set_text(label_status, str);
}

int main(int argc, char *argv[])
{
	lv_init();
	lv_wayland_init();
	lv_disp_t *disp = lv_wayland_create_window(screenWidth,
											   screenHeight,
											   "Wayland-lvgl-8.4 test",
											   NULL);
	
	lv_theme_t *th = lv_theme_default_init(NULL, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_CYAN), LV_THEME_DEFAULT_DARK, &lv_font_montserrat_14);
	lv_disp_set_theme(NULL, th);
	scr = lv_scr_act();

	static lv_style_t background_style;

	lv_style_init(&background_style);
	lv_style_set_radius(&background_style, 0);
	lv_style_set_bg_color(&background_style, lv_palette_main(LV_PALETTE_RED));

	lv_obj_t *obj1;
	bar_view = lv_obj_create(lv_scr_act());
	lv_obj_set_style_radius(bar_view, 0, 0);
	lv_obj_set_pos(bar_view, 0, topHeight + tunerHeight);
	lv_obj_set_size(bar_view, LV_HOR_RES - 3, barHeight);

	label_status = lv_label_create(lv_scr_act());
	// lv_obj_add_style(label_status, &LabelTextStyle, 0);
	lv_obj_align(label_status, LV_ALIGN_LEFT_MID, 0, 0);
	lv_label_set_text(label_status, "Hello");

	lv_style_init(&style_btn);
	lv_style_set_radius(&style_btn, 10);
	lv_style_set_bg_color(&style_btn, lv_color_make(0x60, 0x60, 0x60));
	lv_style_set_bg_grad_color(&style_btn, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_btn, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_btn, 255);
	lv_style_set_border_color(&style_btn, lv_color_make(0x9b, 0x36, 0x36)); // lv_color_make(0x2e, 0x44, 0xb2)
	lv_style_set_border_width(&style_btn, 2);
	lv_style_set_border_opa(&style_btn, 255);
	lv_style_set_outline_color(&style_btn, lv_color_black());
	lv_style_set_outline_opa(&style_btn, 255);

	button = lv_btn_create(lv_scr_act());
	lv_obj_add_style(button, &style_btn, 0);
	lv_obj_add_event_cb(button, button_event_cb, LV_EVENT_CLICKED, NULL);
	lv_obj_align(button, LV_ALIGN_CENTER, 0,0);

	while (1)
	{
		/* Periodically call the lv_task handler.
		 * It could be done in a timer interrupt or an OS task too.*/
		// lv_timer_handler();
		lv_wayland_timer_handler();
		usleep(5 * 1000);
	}

	lv_wayland_deinit();
	return 0;
}

uint32_t custom_tick_get(void)
{
	struct timespec period;
	clock_gettime(CLOCK_MONOTONIC, &period);
	uint64_t ticks_ms = period.tv_sec * 1000 + period.tv_nsec / 1000000;

	static uint64_t start_ms = 0;
	if (start_ms == 0)
	{
		start_ms = ticks_ms;
	}

	uint32_t time_ms = ticks_ms - start_ms;
	return time_ms;
}