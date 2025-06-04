#include <raylib.h>
#include "AnalogClock.hpp"

int main() 
{
    const int WINDOW_WIDTH = 600;
    const int WINDOW_HEIGHT = 600;
    Color LIGHT_BLUE = {225, 239, 240, 255};

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Analog Clock");
    SetTargetFPS(15); // Set the target frames per second

    AnalogClock clock {250, {300, 300}};

    // Main loop
    while(WindowShouldClose() == false) {
        // Event handling

        // Update
        clock.Update();

        // Draw
        BeginDrawing();
        ClearBackground(LIGHT_BLUE);
        clock.Draw();
        EndDrawing();
    }


    CloseWindow();
}