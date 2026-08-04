#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

#define RED 12

char buffer[4096] = {0};
int pos = 0;
HANDLE hOut;

void save_file(const char *filename) {
    FILE *f = fopen(filename, "w");
    if (f) {
        for (int i = 0; i < pos; i++) {
            if (buffer[i] == '\r') buffer[i] = '\n';
        }
        fwrite(buffer, 1, pos, f);
        fclose(f);
    }
}

int main(int argc, char *argv[]) {
    const char *filename = (argc > 1) ? argv[1] : NULL;
    
    if (filename) {
        FILE *f = fopen(filename, "r");
        if (f) {
            pos = fread(buffer, 1, sizeof(buffer)-1, f);
            fclose(f);
        }
    }

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleOutputCP(437);
    
    while(1) {
        SetConsoleCursorPosition(hOut, (COORD){0, 0});
        SetConsoleTextAttribute(hOut, RED);
        
        for (int i = 0; i < pos; i++) {
            putchar(buffer[i] == '\r' ? '\n' : buffer[i]);
        }
        printf(" ");
        fflush(stdout);
        
        int c = _getch();
        if (c == 4 || c == 27) break; // Ctrl+D or Esc
        
        if (c == 8 || c == 127) { // Backspace
            if (pos > 0) pos--;
        } else if (c == 0 || c == 224) {
            _getch(); // Ignore arrow keys
        } else if (pos < sizeof(buffer)-1 && c >= 32) {
            buffer[pos++] = (char)c;
        }
    }

    SetConsoleTextAttribute(hOut, 7);
    printf("\n");
    
    if (filename) save_file(filename);
    
    return 0;
}
