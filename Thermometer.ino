// Benötigte Libraries werden importiert
#include <SPI.h>
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Hier wird der Eingangs-Pin deklariert, an dem das Sensor-Modul angeschlossen ist
#define KY001_Signal_PIN 4

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

OneWire oneWire(KY001_Signal_PIN); 
DallasTemperature sensors(&oneWire);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  // Initialisierung Serielle Ausgabe
  Serial.begin(9600);
  Serial.println("start thermometer");

  // initialisation of sensor
  sensors.begin();

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.clearDisplay();
  display.display();
}

void loop() {
  // start temperature measurement
  sensors.requestTemperatures();
  // ... und gemessene Temperatur ausgeben
  //Serial.println(sensors.getTempCByIndex(0));

  display.clearDisplay();
  display.setCursor(40,15);             // Start at top-left corner
  display.setTextSize(2);             // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.println(sensors.getTempCByIndex(0));

  display.display();

  delay(1000); // 5s Pause bis zur nächsten Messung
}
 
