#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#define RED "\033[91m"
#define RESET "\033[0m"

struct termios orig_termios;

void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode() {
    struct termios raw;
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disableRawMode);
    raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main(int argc, char *argv[]) {
    if (argc > 2) return 1;
    
    char buffer[1024] = {0};
    int pos = 0;
    char c;
    
    if (argc == 2) {
        FILE *f = fopen(argv[1], "r");
        if (f) {
            fread(buffer, 1, sizeof(buffer)-1, f);
            fclose(f);
            for (char *p = buffer; *p; p++) if (*p == '\n') *p = '\r';
            pos = strlen(buffer);
        }
    }
    
    enableRawMode();
    
    while(1) {
        write(STDOUT_FILENO, "\x1b[H\x1b[J", 7);
        printf(RED);
        fwrite(buffer, 1, pos, stdout);
        fflush(stdout);
        
        read(STDIN_FILENO, &c, 1);
        
        if (c == 4) break;
        
        if (c == 127 && pos > 0) {
            pos--;
        } else if (pos < sizeof(buffer)-1) {
            if (c == '\n') c = '\r';
            buffer[pos++] = c;
        }
    }
    
    disableRawMode();
    
    if (argc == 2) {
        for (int i = 0; i < pos; i++) if (buffer[i] == '\r') buffer[i] = '\n';
        FILE *f = fopen(argv[1], "w");
        if (f) {
            fwrite(buffer, 1, pos, f);
            fclose(f);
        }
    }
    
    return 0;
}
