1. Aim
To develop a smart load monitoring system using an HX711 weight sensor that measures material weight in real-time and provides alerts via cloud services when weight crosses predefined thresholds.
2. Problem Statement
Manual monitoring of load weight in warehouses is inefficient and prone to delays or human error. A real-time automated system is needed to measure the weight of materials and send alerts when overloading or depletion occurs, helping ensure timely action and safety.
3. Scope of the Solution
- Monitor weight using HX711 + Load Cell continuously.
- Notify warehouse staff via cloud-based alerts (e.g., using ThingSpeak or MQTT).
- Simulate the circuit and logic on Wokwi.
- Scalable for multiple sensors.
- Can be integrated with inventory or logistics software.
4. Required Components
**Hardware:**
- HX711 Weight Sensor Module
- Load Cell
- ESP32 or Arduino UNO (ESP32 preferred for Wi-Fi)
- Breadboard & jumper wires

**Software:**
- Arduino IDE
- Wokwi (for simulation)
- ThingSpeak / Blynk / MQTT for cloud alerts
- GitHub (for code + documentation)

**Cloud Environment:**
- ThingSpeak
5. Arduino Code
```cpp
#include "HX711.h"

#define DT 4
#define SCK 5

HX711 scale;

float upperThreshold = 1000.0;
float lowerThreshold = 100.0;

void setup() {
  Serial.begin(115200);
  scale.begin(DT, SCK);
  Serial.println("Initializing scale...");
  scale.set_scale(2280.f);
  scale.tare();
  Serial.println("Scale ready.");
}

void loop() {
  if (scale.is_ready()) {
    float weight = scale.get_units(5);
    Serial.print("Weight: ");
    Serial.print(weight);
    Serial.println(" grams");

    if (weight > upperThreshold) {
      Serial.println("⚠️ ALERT: Overload detected!");
    } else if (weight < lowerThreshold) {
      Serial.println("⚠️ ALERT: Material depleted!");
    } else {
      Serial.println("✅ Weight is normal.");
    }

    Serial.println("------------------------");
    delay(2000);
  } else {
    Serial.println("❌ HX711 not connected.");
    delay(1000);
  }
