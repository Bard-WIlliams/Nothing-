# Neon Red Notepad (Windows Version)

A minimal terminal-based notepad application written in C with a neon red theme, designed for Windows.

## Features

- Simple text editing interface
- Neon red color scheme (Windows Console Color 12)
- File loading and saving capabilities
- Basic editing (typing and backspace)
- Exit with Esc or Ctrl+D

## Requirements

- Windows 10/11
- MinGW-w64 (GCC for Windows) or Visual Studio with C support

## Compilation

### Using MinGW (gcc):
```bash
gcc -o notepad.exe notepad.c
```

### Using Visual Studio (cl):
```bash
cl notepad.c
```

## Usage

```bash
notepad.exe [filename]
```

- If filename is provided, loads existing content or creates new file
- If no filename, starts with empty buffer
- Type text directly into the interface
- Use backspace to delete characters
- Press Esc or Ctrl+D to save and exit

## Controls

- **Normal typing**: Adds text to buffer
- **Backspace**: Removes previous character
- **Esc or Ctrl+D**: Saves file (if filename provided) and exits

## Technical Details

- Uses Windows Console API (`windows.h`) for screen management
- Uses `conio.h` for keyboard input (`_getch()`)
- ANSI color code 12 (bright red) for neon red theme
- 4KB buffer for text storage
- Automatically converts line endings on save

## Troubleshooting

If you get "termios.h: No such file or directory":
- This code has been updated for Windows. Make sure you're using the latest `notepad.c` provided here.
- The old Linux version used `termios.h`, but this Windows version uses `windows.h` and `conio.h`.

If the .exe says "doesn't run on your PC":
- Ensure you compiled it on Windows using MinGW or Visual Studio
- Do NOT transfer a Linux-compiled binary to Windows
- Run `gcc -o notepad.exe notepad.c` directly on your Windows machine
