#include "stdarg.h"

void putchar(char c) {
    volatile char *video = (volatile char*) 0xB8000;
    static int offset = 0;  // Позиция в видеопамяти
    video[offset] = c;  // Символ
    video[offset + 1] = 0x07;  // Атрибут (белый текст на черном фоне)
    offset += 2;  // Переход к следующему символу
}


void printf(const char *format, ...) {
    va_list args;
    va_start(args, format);

    for (const char *p = format; *p != '\0'; p++) {
        if (*p == '%' && *(p + 1) == 'c') {
            // Обработка символа
            char c = (char) va_arg(args, int);
            putchar(c);
            p++;  // Пропустить следующий символ формата
        } else if (*p == '%' && *(p + 1) == 's') {
            // Обработка строки
            const char *str = va_arg(args, const char *);
            while (*str) {
                putchar(*str++);
            }
            p++;  // Пропустить следующий символ формата
        } else {
            putchar(*p);
        }
    }

    va_end(args);
}


void kernel_main(){
    const char *msg = "Test message.";
    printf(msg);
    while(1){

    }
}

