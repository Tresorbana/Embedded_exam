#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHT_PIN  2
#define DHT_TYPE DHT11

DHT dht(DHT_PIN, DHT_TYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

String name = "Bana Emmy Tresor";
int scrollPos = 0;
unsigned long lastScroll = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  dht.begin();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(name);
  lcd.setCursor(0, 1);
  lcd.print("Temp: --.- C");
}

void loop() {
  float temp = dht.readTemperature();

  // Row 2: temperature
  lcd.setCursor(0, 1);
  lcd.print("Temp:");
  lcd.print(temp);
  lcd.print((char)223);
  lcd.print("C   ");

  // Send raw value to PC
  Serial.println(temp);

  // Row 1: scroll name if longer than 16 chars
  if (name.length() > 16) {
    if (millis() - lastScroll > 300) {
      String text = name + "    ";
      lcd.setCursor(0, 0);
      for (int i = 0; i < 16; i++) {
        lcd.print(text[(scrollPos + i) % text.length()]);
      }
      scrollPos++;
      if (scrollPos >= text.length()) scrollPos = 0;
      lastScroll = millis();
    }
  } else {
    lcd.setCursor(0, 0);
    lcd.print(name);
  }

  delay(1000);
}
