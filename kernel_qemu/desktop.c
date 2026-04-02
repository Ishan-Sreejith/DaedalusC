#include "libc.h"
#include <stdint.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_ADDR 0xB8000

static uint16_t *vga_buffer = (uint16_t*)VGA_ADDR;

void desktop_clear(uint8_t color) {
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        vga_buffer[i] = ((uint16_t)color << 8) | ' ';
    }
}

void desktop_draw_window(int x, int y, int w, int h, uint8_t color, const char *title) {
    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            int px = x + i;
            int py = y + j;
            if (px < 0 || px >= VGA_WIDTH || py < 0 || py >= VGA_HEIGHT) continue;
            char ch = ' ';
            uint8_t border = color;
            if (j == 0 || j == h-1 || i == 0 || i == w-1) border = 0x1F; // blue border
            if (j == 0 && i > 1 && i < w-2 && title && i-2 < (int)strlen(title)) ch = title[i-2];
            vga_buffer[py * VGA_WIDTH + px] = ((uint16_t)border << 8) | ch;
        }
    }
}

void desktop_draw_icon(int x, int y, char c, uint8_t color) {
    if (x >= 0 && x < VGA_WIDTH && y >= 0 && y < VGA_HEIGHT)
        vga_buffer[y * VGA_WIDTH + x] = ((uint16_t)color << 8) | c;
}

void desktop_demo() {
    desktop_clear(0x1A); // teal background
    desktop_draw_window(10, 5, 30, 10, 0x2E, "Welcome");
    desktop_draw_icon(15, 8, '\x01', 0x1E); // smiley
    desktop_draw_icon(17, 8, '\x03', 0x1E); // heart
    desktop_draw_icon(19, 8, '\x04', 0x1E); // diamond
    printf("\n  Daedalus Desktop Demo - Press any key to exit\n");
    extern char kbd_getchar(void);
    kbd_getchar();
}

