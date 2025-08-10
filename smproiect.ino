#include <Wire.h>
#include <Servo.h>

#define SD2403_ADDRESS 0x32

Servo myservo;

uint8_t bcdToDec(uint8_t val) {
  return (val / 16 * 10) + (val % 16);
}

void readTime(uint8_t& hour, uint8_t& minute, uint8_t& second) {
  Wire.beginTransmission(SD2403_ADDRESS);
  Wire.write(0x00);
  Wire.endTransmission();

  Wire.requestFrom(SD2403_ADDRESS, 3);
  if (Wire.available() >= 3) {
    second = bcdToDec(Wire.read());
    minute = bcdToDec(Wire.read());
    hour   = bcdToDec(Wire.read());
  }
}

void setup() {
  Wire.begin();
  Serial.begin(9600);
  // Servo-ul nu este atașat la pornire
}

bool triggered = false;

void loop() {
  uint8_t h, m, s;
  readTime(h, m, s);

  Serial.print("Ora RTC: ");
  Serial.print(h);
  Serial.print(":");
  Serial.print(m);
  Serial.print(":");
  Serial.println(s);

  if (h == 18 && m == 11 && s == 0 && !triggered) {
    myservo.attach(9);

    // Deplasare de la 0 la 110°
    for (int pos = 0; pos <= 110; pos++) {
      myservo.write(pos);
      delay(15);
    }

    delay(3000); // 🔹 Așteaptă 3 secunde la 110°

    // Revenire la 0°
    for (int pos = 110; pos >= 0; pos--) {
      myservo.write(pos);
      delay(15);
    }

    myservo.detach(); // Oprește semnalul PWM
    triggered = true;
  }

  if (s != 0) {
    triggered = false;
  }

  delay(500);
}
