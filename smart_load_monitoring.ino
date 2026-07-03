#include "HX711.h"

// Define HX711 pins for ESP32
#define DT 4   // Data pin (DOUT)
#define SCK 5  // Clock pin (SCK)

HX711 scale;

// Weight thresholds (in grams)
float upperThreshold = 1000.0;
float lowerThreshold = 100.0;

void setup() {
  Serial.begin(115200);
  scale.begin(DT, SCK);

  Serial.println("Initializing the HX711 scale...");

  scale.set_scale(2280.f); // Default calibration factor (adjust if needed)
  scale.tare();            // Set current weight to zero

  Serial.println("Scale is ready!");
}

void loop() {
  if (scale.is_ready()) {
    float weight = scale.get_units(5); // Get average of 5 readings

    Serial.print("Weight: ");
    Serial.print(weight);
    Serial.println(" grams");

    // Alert logic
    if (weight > upperThreshold) {
      Serial.println("⚠️ ALERT: Overload detected!");
    } else if (weight < lowerThreshold) {
      Serial.println("⚠️ ALERT: Material depleted!");
    } else {
      Serial.println("✅ Weight is within normal range.");
    }

    Serial.println("------------------------");
    delay(2000);
  } else {
    Serial.println("❌ ERROR: HX711 not connected.");
    delay(1000);
  }
}
