#include <Adafruit_NeoPixel.h>
#include <RCSwitch.h>

#define PIN 6 // Pin to which the Neopixel is connected
#define NUM_LEDS 3 // Number of Neopixel LEDs

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

RCSwitch mySwitch = RCSwitch();

void setup() {
  Serial.begin(9600);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  mySwitch.enableReceive(0); // Receiver on interrupt 0
}

void loop() {
  if (mySwitch.available()) {
    unsigned long receivedValue = mySwitch.getReceivedValue();
    
    if (receivedValue == 0) {
      Serial.println("Unknown encoding");
    } else {
      Serial.print("Received RF signal: ");
      Serial.println(receivedValue);

      if (receivedValue == 7474698) { // Replace XXXX with the actual code for Green signal
        setGreen();
      } else if (receivedValue == 7474702) { // Replace YYYY with the actual code for Red signal
        setYellow();
        delay(2000); // Wait for 2 seconds (2000 milliseconds)
        setRed();
      }
    }

    mySwitch.resetAvailable();
  }
}

void setRed() {
  strip.setPixelColor(0, 0, 0, 0); // Red
  strip.setPixelColor(1, 0, 0, 0); // Red
  strip.setPixelColor(2, 255, 0, 0); // Red
  strip.show();
}

void setYellow() {
  strip.setPixelColor(0, 0, 0, 0); // Yellow
  strip.setPixelColor(1, 255, 150, 0); // Yellow
  strip.setPixelColor(2, 0, 0, 0); // Yellow
  strip.show();
}

void setGreen() {
  strip.setPixelColor(0, 0, 255, 0); // Green
  strip.setPixelColor(1, 0, 0, 0); // Green
  strip.setPixelColor(2, 0, 0, 0); // Green
  strip.show();
}
