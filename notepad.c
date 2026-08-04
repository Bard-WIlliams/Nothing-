#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

#define RED FOREGROUND_RED | FOREGROUND_INTENSITY

HANDLE hOut;
WORD orig_attrs;

void restoreConsole() {
    SetConsoleTextAttribute(hOut, orig_attrs);
}

int main(int argc, char *argv[]) {
    if (argc > 2) return 1;
    
    char buffer[1024] = {0};
    int pos = 0;
    char c;
    
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hOut, &csbi);
    orig_attrs = csbi.wAttributes;
    atexit(restoreConsole);
    
    if (argc == 2) {
        FILE *f = fopen(argv[1], "r");
        if (f) {
            fread(buffer, 1, sizeof(buffer)-1, f);
            fclose(f);
            pos = strlen(buffer);
        }
    }
    
    while(1) {
        COORD coord = {0, 0};
        SetConsoleCursorPosition(hOut, coord);
        DWORD written;
        FillConsoleOutputCharacterA(hOut, ' ', 80*25, coord, &written);
        
        SetConsoleTextAttribute(hOut, RED);
        fwrite(buffer, 1, pos, stdout);
        fflush(stdout);
        
        if (_kbhit()) {
            c = _getch();
            if (c == 4 || c == 27) break;
            if (c == 8 && pos > 0) {
                pos--;
            } else if (pos < sizeof(buffer)-1 && c >= 32 && c <= 126) {
                buffer[pos++] = c;
            }
        }
        Sleep(10);
    }
    
    if (argc == 2) {
        FILE *f = fopen(argv[1], "w");
        if (f) {
            fwrite(buffer, 1, pos, f);
            fclose(f);
        }
    }
    
    return 0;
}
