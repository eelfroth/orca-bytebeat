#include <stdio.h>

int main()
{
    int c;
    
    while (1) {
        c = getc(stdin);

        if (c == EOF) break;
        else if (c >= '0' && c <= '9') c -= '0';
        else if (c >= 'a' && c <= 'z') c -= 'a' - 10;
        else if (c >= 'A' && c <= 'Z') c -= 'A' - 10;
        else continue;

        c = c * 255 / 35;

        putc(c, stdout);
    }
    return 0;
}
