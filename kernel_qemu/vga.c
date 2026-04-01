#include "libc.h"
#include <stdint.h>
#include <stddef.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_ADDR 0xB8000

static uint16_t *vga_buffer = (uint16_t*)VGA_ADDR;
static uint8_t term_col = 0;
static uint8_t term_row = 0;
static uint8_t term_color = 0x0F;

void vga_set_cursor(int x, int y) {
    uint16_t pos = y * VGA_WIDTH + x;
    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t)(pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}

void vga_clear() {
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        vga_buffer[i] = ((uint16_t)term_color << 8) | ' ';
    }
    term_col = 0;
    term_row = 0;
    vga_set_cursor(0, 0);
}

void vga_scroll() {
    for (int i = 0; i < (VGA_HEIGHT - 1) * VGA_WIDTH; i++) {
        vga_buffer[i] = vga_buffer[i + VGA_WIDTH];
    }
    for (int i = (VGA_HEIGHT - 1) * VGA_WIDTH; i < VGA_HEIGHT * VGA_WIDTH; i++) {
        vga_buffer[i] = ((uint16_t)term_color << 8) | ' ';
    }
}

void vga_print_char(char c) {
    if (c == '\n') {
        term_col = 0;
        if (++term_row == VGA_HEIGHT) { term_row--; vga_scroll(); }
    } else if (c == '\b') {
        if (term_col > 0) {
            term_col--;
            vga_buffer[term_row * VGA_WIDTH + term_col] = ((uint16_t)term_color << 8) | ' ';
        } else if (term_row > 0) {
            term_row--;
            term_col = VGA_WIDTH - 1;
            vga_buffer[term_row * VGA_WIDTH + term_col] = ((uint16_t)term_color << 8) | ' ';
        }
    } else if (c == '\r') {
        term_col = 0;
    } else {
        size_t index = term_row * VGA_WIDTH + term_col;
        vga_buffer[index] = ((uint16_t)term_color << 8) | (uint8_t)c;
        if (++term_col == VGA_WIDTH) {
            term_col = 0;
            if (++term_row == VGA_HEIGHT) { term_row--; vga_scroll(); }
        }
    }
    vga_set_cursor(term_col, term_row);
}

void vga_print_str(const char *s) {
    for (int i = 0; s[i] != '\0'; i++) vga_print_char(s[i]);
}
