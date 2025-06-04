#include "AnalogClock.hpp"
#include <cmath>
#include <cstdio>

Color DARK_GREY = {45, 45, 45, 255};
Color LIGHT_GREY = {229, 229, 229, 255};

void AnalogClock::Draw() const
{
    DrawFace();
    DrawHourMarks();
    DrawHourNumbers();
    DrawMinuteHand(minute);
    DrawHourHand(hour, minute);
    DrawSecondHand(second);
    DrawCircleV(position, 15, DARK_GREY);
}

void AnalogClock::Update()
{
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);

    hour = now -> tm_hour % 12; // Convert to 12-hour format
    minute = now -> tm_min;
    second = now -> tm_sec;
}

void AnalogClock::DrawFace() const
{
    DrawCircleV(position, size, DARK_GREY);
    DrawCircleV(position, size - 30, LIGHT_GREY);
    DrawCircleV(position, size - 40, RAYWHITE);
}

void AnalogClock::DrawHourMarks() const
{
    float rectWidth = 10;
    float rectHeight = size;

    Rectangle rect = {position.x, position.y, rectWidth, rectHeight};
    for (int i = 0; i < 12; i++) {
        DrawRectanglePro(rect, {rectWidth / 2, rectHeight}, i * 30, DARK_GREY);
    }
    DrawCircleV(position, size - 50, RAYWHITE);
}

void AnalogClock::DrawMinuteHand(int minute) const
{
    float handWidth = 10;
    float handLength = size * 0.7;
    int angle = minute * 6; // Each minute is 6 degrees

    DrawHand(handWidth, handLength, angle, DARK_GREY, 0);
}

void AnalogClock::DrawHourHand(int hour, int minute) const
{
    float handWidth = 15;
    float handLength = size * 0.6;
    int angle = (hour % 12) * 30 + (minute / 2); // Each hour is 30 degrees, plus a fraction for minutes

    DrawHand(handWidth, handLength, angle, DARK_GREY, 0);
}

void AnalogClock::DrawSecondHand(int second) const
{
    float handWidth = 5;
    float handLength = size * 1.05;
    int angle = second * 6; // Each second is 6 degrees
    DrawHand(handWidth, handLength, angle, RED, 55);
}

void AnalogClock::DrawHand(float handWidth, float handLength, int angle, Color color, int offset) const
{
    Rectangle handRect = Rectangle{position.x, position.y, handWidth, handLength};
    DrawRectanglePro(handRect, {handWidth / 2, handLength - offset}, angle, color);
}

void AnalogClock::DrawHourNumbers() const
{
    int fontSize = 32;
    float radius = size - 65;

    for (int i = 1; i <= 12; ++i) {
        float angle = (i - 3) * (2 * PI / 12); // -3 to make 12 at the top
        float x = position.x + radius * cosf(angle);
        float y = position.y + radius * sinf(angle);

        // Convert number to string
        char buf[3];
        snprintf(buf, sizeof(buf), "%d", i);

        // Center the text
        int textWidth = MeasureText(buf, fontSize);
        int textHeight = fontSize;

        DrawText(buf, x - textWidth / 2, y - textHeight / 2, fontSize, DARK_GREY);
    }
}