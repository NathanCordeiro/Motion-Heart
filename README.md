# Motion-Heart

This project creates an animated ASCII art heart that "beats" in your terminal window. The animation runs indefinitely and changes color to add a visual effect.

## Requirements

- Windows operating system
- C compiler (e.g., GCC, MinGW)

## How to Run

1. Make sure you have a C compiler installed on your system.
2. Save the code provided in the `heart.c` file.
3. Open a terminal or command prompt.
4. Navigate to the directory where the `heart.c` file is saved.
5. Compile the code using the following command:
   ```bash
   gcc -o heart heart.c -lm -lwinmm

## Code Explanation
The code uses ASCII characters to render a heart shape that "beats" by changing its size and position within the terminal. It leverages trigonometric functions to create a smooth animation. Here's a brief overview of the key components:

- Color Change: Sets the terminal color to red using the system("color 04"); command.
- Cursor and Screen Management: Hides the cursor and clears the screen to provide a clean animation space.
- Animation Loop: Continuously updates the frame to create the beating heart effect using mathematical calculations.
- Z-Buffer: Ensures that the heart shape is correctly rendered based on its depth.
