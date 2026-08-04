# Neon Red Notepad

A minimal terminal-based notepad application written in C with a neon red theme.

## Features

- Simple text editing interface
- Neon red color scheme for text display
- File loading and saving capabilities
- Basic editing (typing and backspace)
- Exit with Ctrl+D

## Requirements

- Linux/Unix system with terminal support
- GCC compiler
- Standard C libraries

## Compilation

```bash
gcc -o notepad.exe notepad.c
```

## Usage

```bash
./notepad.exe [filename]
```

- If filename is provided, loads existing content or creates new file
- If no filename, starts with empty buffer
- Type text directly into the interface
- Use backspace to delete characters
- Press Ctrl+D to save and exit

## Controls

- Normal typing: Adds text to buffer
- Backspace/Delete: Removes previous character
- Ctrl+D: Saves file and exits program

## Technical Details

- Uses raw terminal mode for immediate input handling
- ANSI escape codes for color formatting
- Basic character buffer for text storage
- Converts between newline and carriage return for display

## Note on .exe extension

The `notepad.exe` file created is a Linux executable binary (ELF format). The `.exe` extension is used here only as a filename convention requested by the user. To run this on Windows as a true `.exe`, you would need to cross-compile using MinGW or similar tools.
