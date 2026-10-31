/*
  Smart Water Irrigation System using ESP32
  Soil sensor OUT -> GPIO 34
  Relay IN       -> GPIO 26

  IMPORTANT:
  - Calibrate SOIL_DRY and SOIL_WET for your sensor.
  - This example assumes a higher ADC reading means drier soil.
  - Use a separate suitable power supply for the pump.
*/

const int SOIL_SENSOR_PIN = 34;
const int RELAY_PIN = 26;

// Example values only: measure your sensor in dry and wet soil.
const int SOIL_DRY = 3000;
const int SOIL_WET = 1200;
const int MOISTURE_THRESHOLD = 35;

int readMoisturePercent() {
  int raw = analogRead(SOIL_SENSOR_PIN);

  // Assumes higher raw reading means drier soil.
  int percent = map(raw, SOIL_DRY, SOIL_WET, 0, 100);
  percent = constrain(percent, 0, 100);

  Serial.print("Raw sensor value: ");
  Serial.println(raw);
  return percent;
}

void setPump(bool on) {
  // Active-LOW relay: LOW = ON, HIGH = OFF.
  digitalWrite(RELAY_PIN, on ? LOW : HIGH);
}

void setup() {
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);
  setPump(false); // Pump OFF at startup.
}

void loop() {
  int moisture = readMoisturePercent();

  Serial.print("Soil moisture: ");
  Serial.print(moisture);
  Serial.println("%");

  if (moisture < MOISTURE_THRESHOLD) {
    setPump(true);
    Serial.println("Soil is dry - Pump ON");
  } else {
    setPump(false);
    Serial.println("Soil moisture is sufficient - Pump OFF");
  }

  Serial.println("-----------------------");
  delay(2000);
}
