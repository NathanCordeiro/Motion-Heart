/// Heart For Your Lover

#include <stdio.h>
#include <math.h>
#include <windows.h>

int main() {
    system("color 04");
    float t = 0;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    // Clear screen and hide cursor
    system("cls");

    // Hide cursor
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 100;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    // Get initial buffer size
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    int initialWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int initialHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    // Create output buffer - one extra character per line for \r
    char* outputBuffer = malloc((initialWidth + 1) * initialHeight);
    if (!outputBuffer) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    while(1) {
        // Get current terminal size
        GetConsoleScreenBufferInfo(hConsole, &csbi);
        int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        int height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

        // Ensure minimum size
        if (width < 10 || height < 5) {
            COORD pos = {0, 0};
            SetConsoleCursorPosition(hConsole, pos);
            printf("Terminal too small!");
            Sleep(100);
            continue;
        }

        // Create z-buffer
        float* zb = calloc(width * height, sizeof(float));
        if (!zb) {
            printf("Memory allocation failed!\n");
            return 1;
        }

        float maxz = 0;
        float c = cos(t * 0.3f);
        float s = sin(t * 0.3f);

        for(float y = -0.5f; y <= 0.5f; y += 0.008f) {
            float beat = sin(t * 1.5f + y * 1.5f);
            float beatAmplitude = beat * beat * beat * 0.5f + 0.5f;
            float r = 0.3f + 0.04f * pow(beatAmplitude, 4);

            for(float x = -0.5f; x <= 0.5f; x += 0.008f) {
                float z = -x * x - pow(0.8f * y - fabs(x) * 2/3, 2) + r * r;
                if(z < 0)
                    continue;

                z = sqrt(z) / (1.8f - y);
                for(float tz = -z; tz <= z; tz += z/8) {
                    float nx = x * c - tz * s;
                    float nz = x * s + tz * c;
                    float p = 1.15f + nz / 2.2f;

                    int vx = lroundf((nx * p + 0.5f) * (width - 20) + 10);
                    int vy = lroundf((-y * p + 0.5f) * (height - 4) + 2);

                    if(vx >= 0 && vx < width && vy >= 0 && vy < height) {
                        int idx = vx + vy * width;
                        if(zb[idx] <= nz) {
                            zb[idx] = nz;
                            if(maxz <= nz)
                                maxz = nz;
                        }
                    }
                }
            }
        }

        // Move cursor to home position
        COORD pos = {0, 0};
        SetConsoleCursorPosition(hConsole, pos);

        // Build and display frame line by line
        for(int y = 0; y < height; y++) {
            for(int x = 0; x < width; x++) {
                int idx = x + y * width;
                putchar(" .,-~:;=!*#$@@"[lroundf(zb[idx] / maxz * 13)]);
            }
            // Use \r to prevent scrolling
            if(y < height - 1) {
                putchar('\r');
                putchar('\n');
            }
        }

        // Free z-buffer
        free(zb);

        // Update animation time
        t += 0.002f;
        Sleep(5);
    }

    free(outputBuffer);
    return 0;
}
