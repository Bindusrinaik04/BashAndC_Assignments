# README

## Overview

Question 3 - This README summarizes the key points and discussions related to the C program that performs directory listing, filtering, and counting operations using pipes and child processes.

## Program Structure

The program is designed to achieve the following tasks:

1. Parse command-line arguments to specify the directory path (defaulting to the current directory if not provided).

2. Open the specified directory using the `opendir` function from the `<dirent.h>` library.

3. Create a series of pipes for inter-process communication between child processes.

4. Use `fork` and `exec` to create child processes for different operations:
   - Child 1 (ls): Lists files in the specified directory.
   - Child 2 (grep): Filters files matching the pattern "^A.*\.txt$".
   - Child 3 (wc): Counts the lines (files) from the filtered output.

5. Redirect the standard input and output of child processes using `dup2` to connect the pipes appropriately.

6. In the parent process, read the output of the last child process (wc) and print the file count.

7. Use `waitpid` to ensure all child processes have finished execution before the parent process exits.

## Issues and Debugging

During the development and testing of the program, some common issues were encountered:

1. Ensure the provided directory path exists and contains files matching the grep pattern.

2. Check for proper error handling, especially after system calls like `pipe`, `fork`, and `execlp`. Error messages and `perror` can help identify issues.

3. Debugging can be enhanced by adding print statements at key points in the code to trace the program's execution.

4. Make sure to properly close file descriptors and pipes in both child and parent processes.

5. Be cautious with `dup2` to redirect standard input and output; it should be used before executing `execlp`.

6. Use `exit` to terminate child processes after executing the desired command.

7. Use `waitpid` to ensure that child processes have completed before the parent process finishes.

## Example Code

An example C program that implements these concepts is provided in the previous messages. It's recommended to carefully review and understand the code for better clarity.

For any further assistance or questions, please feel free to reach out.



## Bash Script: Kill CPU-Intensive Processes

### Script Name: `cpu_intensive.sh`

#### Overview

This Bash script allows you to find and terminate CPU-intensive processes based on a specified CPU usage threshold. It uses the `ps` command to list processes, sorts them by CPU usage, and kills processes exceeding the threshold.

#### Usage

1. Make the script executable:

   ```bash
   chmod +x cpu_intensive.sh

###Overview

This Bash script converts numbers from one base to another. It supports conversions between decimal, binary, octal, and hexadecimal bases.
###Notes

    The script performs base conversions by using bc, a command-line calculator.

    Ensure bc is installed on your system.

    Customize the script to support additional bases or error handling if needed.

Feel free to modify and use these scripts as needed. For further assistance or questions, please reach out.
