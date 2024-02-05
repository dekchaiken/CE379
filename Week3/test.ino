#define BUTTON_PIN 4
#define LDR_PIN A0
#define LED_PIN 2
// Pins for RGB LED
#define RED_PIN 15
#define GREEN_PIN 12
#define BLUE_PIN 13
#define NUM_COLORS 5
#define MAX_CHAR_LEN 20
#define RGB 3
#define BAUD_RATE 115200

char COLOR_NAMES[NUM_COLORS][MAX_CHAR_LEN] = {"red", "yellow", "green", "blue", "white"};
unsigned int COLORS[NUM_COLORS][RGB] = {
    {1023, 0, 0},      // Red
    {1023, 1023, 0},   // Yellow
    {0, 1023, 0},      // Green
    {0, 0, 1023},      // Blue
    {1023, 1023, 1023} // White
};

int state = 0;

void setup()
{
    Serial.begin(BAUD_RATE);
    pinMode(LED_PIN, OUTPUT); // single-color LED
    pinMode(RED_PIN, OUTPUT);
    pinMode(GREEN_PIN, OUTPUT);
    pinMode(BLUE_PIN, OUTPUT);
    pinMode(BUTTON_PIN, INPUT_PULLUP); // Button pin as input with pull-up resistor
    Serial.println("\nReady");
}

void loop()
{
    // Check for button press
    if (digitalRead(BUTTON_PIN) == LOW)
    {
        // Button is pressed, change color
        if (state >= NUM_COLORS)
        {
            state = 0;
        }
        Serial.println(COLOR_NAMES[state]);
        analogWrite(RED_PIN, COLORS[state][0]);
        analogWrite(GREEN_PIN, COLORS[state][1]);
        analogWrite(BLUE_PIN, COLORS[state][2]);
        state++;
        delay(1000);
    }
    // Add additional code for other functionalities (e.g., LDR readings)
}
