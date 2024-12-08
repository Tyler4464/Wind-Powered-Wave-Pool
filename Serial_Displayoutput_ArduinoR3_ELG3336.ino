#include <Adafruit_GFX.h>      // Include core graphics library
#include <Adafruit_SSD1306.h>  // Include Adafruit SSD1306 OLED display library

// Ultrasonic sensor pins
#define trigPin 12
#define echoPin 11

// Variables to store duration and distance
long duration;
int distance;

// OLED display specifications
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1          // Reset pin (not used, set to -1)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  // Set up pin modes for the ultrasonic sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Initialize the OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64 screen
    Serial.println("OLED initialization failed");
    while (true);  // Stop if display fails
  }
  display.clearDisplay();
  display.setTextColor(WHITE);

  // Initialize serial communication for output to Serial Monitor
  Serial.begin(9600);
  delay(1000);  // Small delay for stable startup
}

void loop() {
  // Send a pulse to the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echoPin and calculate the duration of the pulse
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in cm (speed of sound = 343 m/s or 0.034 cm/µs)
  distance = duration * 0.034 / 2;

  // Output the distance to the Serial Monitor
  Serial.print("Distance = ");
  Serial.print(distance);
  Serial.println(" cm");

  // Display the distance on the OLED screen
  display.clearDisplay();  // Clear the screen buffer

  // Display the numeric distance value
  display.setTextSize(3);   // Large text size
  display.setCursor(10, 20);
  display.print(distance);

  // Display the unit "CM"
  display.setTextSize(3);
  display.setCursor(70, 20);
  display.print("CM");

  display.display();  // Render the display buffer to the screen

  // Small delay before repeating
  delay(500);
}
