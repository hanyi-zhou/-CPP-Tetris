#include <iostream>
using namespace std;

#include <ncurses.h>
#include <unistd.h>

wstring tetromino[7];
int nFieldWidth = 12;
int nFieldHeight = 18;
unsigned char *pField = nullptr;  // dynamically allocate memory for play field

int nScreenWidth = 80;
int nScreenHeight = 30;

int Rotate(int px, int py, int r)
{
    switch (r % 4)
    {
        case 0: return py * 4 + px;          // 0 degree
        case 1: return 12 + py - (px * 4);   // 90 degrees
        case 2: return 15 - (py * 4) - px;   // 180 degrees
        case 3: return 3 - py + (px * 4);    // 270 degrees
    }
    return 0;
}

int main()
{
    // Create assets
    tetromino[0].append(L"..X.");
    tetromino[0].append(L"..X.");
    tetromino[0].append(L"..X.");
    tetromino[0].append(L"..X.");

    tetromino[1].append(L"..X.");
    tetromino[1].append(L".XX.");
    tetromino[1].append(L".X..");
    tetromino[1].append(L"....");

    tetromino[2].append(L".X..");
    tetromino[2].append(L".XX.");
    tetromino[2].append(L"..X.");
    tetromino[2].append(L"....");

    tetromino[3].append(L"....");
    tetromino[3].append(L".XX.");
    tetromino[3].append(L".XX.");
    tetromino[3].append(L"....");

    tetromino[4].append(L"..X.");
    tetromino[4].append(L".XX.");
    tetromino[4].append(L"..X.");
    tetromino[4].append(L"....");

    tetromino[5].append(L"....");
    tetromino[5].append(L".XX.");
    tetromino[5].append(L"..X.");
    tetromino[5].append(L"..X.");

    tetromino[6].append(L"....");
    tetromino[6].append(L".XX.");
    tetromino[6].append(L".X..");
    tetromino[6].append(L".X..");

    pField = new unsigned char[nFieldWidth*nFieldHeight]; // create play field buffer
    for (int x = 0; x < nFieldWidth; x++) // Board Boundary
        for (int y = 0; y < nFieldHeight; y++)
            pField[y*nFieldWidth + x] = (x == 0 || x == nFieldWidth - 1 || y == nFieldHeight - 1) ? 9 : 0;

    // Initialize the ncurses library
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    timeout(0);

    // Create a screen buffer
    int nScreenWidth = nFieldWidth + 4;  // Add borders
    int nScreenHeight = nFieldHeight + 2; // Add borders and bottom status bar
    wchar_t *screen = new wchar_t[nScreenWidth * nScreenHeight];
    for (int i = 0; i < nScreenWidth * nScreenHeight; ++i) screen[i] = L' ';

    bool bGameOver = false;

    // Main game loop
    while (!bGameOver) {
        // Draw the field
        for (int x = 0; x < nFieldWidth; x++)
            for (int y = 0; y < nFieldHeight; y++)
                screen[(y + 2) * nScreenWidth + (x + 2)] = L" ABCDEFG=#"[pField[y * nFieldWidth + x]];

        // Display the frame
        clear();
        for (int y = 0; y < nScreenHeight; ++y) {
            for (int x = 0; x < nScreenWidth; ++x) {
                mvaddch(y, x, screen[y * nScreenWidth + x]);
            }
        }
        refresh();

        // Wait for a short period (simulate frame rate)
        struct timespec ts;
        ts.tv_sec = 0;
        ts.tv_nsec = 100000000; // 100 milliseconds
        nanosleep(&ts, NULL);
    }

    // End the ncurses library
    endwin();

    // Free memory
    delete[] screen;

    return 0;
}