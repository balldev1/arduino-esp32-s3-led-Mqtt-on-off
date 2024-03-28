#include <Arduino.h>

void setup() {
  for (int pin = 0; pin <= 39; pin++) { // ลูปผ่านทุกขาของ ESP32 (0-39)
    pinMode(pin, OUTPUT); // กำหนดโหมดของขาเป็น OUTPUT
  }
}

void loop() {
  for (int pin = 0; pin <= 39; pin++) { // ลูปผ่านทุกขาของ ESP32 (0-39)
    digitalWrite(pin, HIGH); // ส่งสัญญาณ HIGH ไปยังขาที่ pin
    delay(1000); // รอ 1 วินาที
    digitalWrite(pin, LOW); // ส่งสัญญาณ LOW ไปยังขาที่ pin
  }
}
