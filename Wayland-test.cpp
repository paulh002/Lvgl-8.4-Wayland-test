#include "lvgl.h"
#include "lv_drivers/wayland/wayland.h"
#include <time.h>
#include <unistd.h>

const int screenWidth = 800;
const int screenHeight = 480;
const int topHeight = 35;
const int tunerHeight = 100;
const int barHeight = 110; // 90;

lv_obj_t *scr, *label_status, *bar_view;

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