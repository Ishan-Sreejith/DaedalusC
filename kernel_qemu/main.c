#include "daedalus.h"
#include "libc.h"

extern void gdt_install(void);
extern void idt_install(void);
extern void pic_remap(void);
extern void keyboard_install(void);
extern void vga_clear(void);
extern void vga_print_str(const char *s);
extern char *fgets(char *str, int n, void *stream);

void kernel_main(void) {
    /* Initialize GDT & IDT */
    gdt_install();
    idt_install();
    pic_remap();
    keyboard_install();
    
    /* Re-enable interrupts */
    __asm__("sti");

    /* Initialize basic VGA */
    vga_clear();
    
    /* Splash Banner */
    vga_print_str("\n\n"
        "  ____                _       _\n"
        " |  _ \\  __ _  ___  __| | __ _| |_   _ ___\n"
        " | | | |/ _` |/ _ \\/ _` |/ _` | | | | / __|\n"
        " | |_| | (_| |  __/ (_| | (_| | | |_| \\__ \\\n"
        " |____/ \\__,_|\\___|\\__,_|\\__,_|_|\\__,_|___/\n"
        "  Daedalus OS x86  ·  Bare-Metal (v2.2)\n"
        "  ──────────────────────────────────────────\n\n");

    /* Init Filesystem & Shell */
    FSNode     *fs = fs_init();
    ShellState *s = shell_init(fs);

    vga_print_str("✓ Filesystem initialized\n");
    vga_print_str("✓ Global Descriptor Table loaded\n");
    vga_print_str("✓ Interrupt Descriptor Table loaded\n");
    vga_print_str("✓ Keyboard controller ready\n");
    vga_print_str("✓ VGA text mode initialized\n\n");

    vga_print_str("DaedalusC is ready for commands.\n");
    vga_print_str("For interactive shell, type commands below:\n");
    vga_print_str("Available: help, ls, cd, pwd, cat, echo, mkdir, etc.\n\n");

    /* Main REPL loop */
    char line[MAX_LINE];
    while (1) {
        shell_prompt(s);
        /* Use keyboard-based input (fgets will use keyboard_install's interrupt handler) */
        if (fgets(line, MAX_LINE, NULL)) {
            shell_execute(s, line, 0);
        }
    }
}
