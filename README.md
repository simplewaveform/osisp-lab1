# File System Scanner: `dirwalk`

## Overview
`dirwalk` is a command-line utility designed to scan a file system and display information about files, directories, and symbolic links based on specified options. The program is POSIX-compliant, ensuring portability across Unix-like systems.

## Features
- Recursively scans directories.
- Filters output by file type (symbolic links, directories, or regular files).
- Sorts output according to the system's locale settings.
- Supports flexible command-line options.

## Requirements
- **Operating System**: Linux/Unix
- **Compiler**: `gcc` or any POSIX-compliant compiler
- **Utilities**: `make` (optional), `git` (optional)

## Installation

1. **Clone the Repository** (if using Git):
   ```bash
   git clone <repository-url>
   cd <project-directory>
   ```

2. **Compile the Program**:
   ```bash
   gcc -o dirwalk dirwalk.c
   ```

3. **Run the Program**:
   ```bash
   ./dirwalk [directory] [options]
   ```

   Examples:
   - Scan the current directory:
     ```bash
     ./dirwalk
     ```
   - Scan a specific directory and display only symbolic links:
     ```bash
     ./dirwalk /path/to/dir -l
     ```
   - Scan the current directory, display only files, and sort the output:
     ```bash
     ./dirwalk -f -s
     ```

## Command-Line Options
- `-l`: Display only symbolic links.
- `-d`: Display only directories.
- `-f`: Display only regular files.
- `-s`: Sort the output according to the system's locale (LC_COLLATE).

If none of the `-l`, `-d`, or `-f` options are specified, the program will display all file types (directories, files, and symbolic links).

## Project Structure
- `dirwalk.c`: Source code for the `dirwalk` utility.
- `README.md`: Documentation (this file).

## Usage Examples

1. **Display All Files and Directories in the Current Directory**:
   ```bash
   ./dirwalk
   ```

2. **Display Only Directories in a Specified Directory**:
   ```bash
   ./dirwalk /path/to/dir -d
   ```

3. **Display Only Files with Sorted Output**:
   ```bash
   ./dirwalk -f -s
   ```

4. **Display Only Symbolic Links in the Current Directory**:
   ```bash
   ./dirwalk -l
   ```


## Notes
- The program uses POSIX-compliant functions (`opendir`, `readdir`, `lstat`, etc.) to ensure compatibility across Unix-like systems.
- Sorting (`-s`) is locale-aware, meaning it respects the system's language and regional settings.
- macOS-Specific Behavior
The sorting feature (-s) relies on the system's implementation of strcoll. On macOS, this has the following behavior:
Cyrillic Sorting:
Cyrillic characters are sorted by their Unicode code points (similar to the C locale).
This means that sorting may not follow language-specific rules for Cyrillic text.

Recommendation:
For correct locale-aware sorting (e.g., Russian alphabetical order), it is recommended to use Linux.

## License
This project is open-source and available under the [MIT License](LICENSE).
