#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHT_PIN  2
#define DHT_TYPE DHT11

DHT dht(DHT_PIN, DHT_TYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

const String CANDIDATE_NAME = "Bana Emmy Tresor";

int scrollPos = 0;
unsigned long lastScroll = 0;
const int SCROLL_DELAY = 400;
bool needsScroll = false;
String scrollText = "";

void setup() {
  Serial.begin(9600);
  Wire.begin();
  dht.begin();

  lcd.init();
  lcd.backlight();

  needsScroll = (CANDIDATE_NAME.length() > 16);

  if (needsScroll) {
    scrollText = CANDIDATE_NAME + "                ";
  }

  lcd.setCursor(0, 0);
  if (!needsScroll) {
    lcd.print(CANDIDATE_NAME);
  }

  lcd.setCursor(0, 1);
  lcd.print("Temp: --.- C");
}

void loop() {
  float temp = dht.readTemperature();
  float hum  = dht.readHumidity();

  // Row 1: name (scroll if longer than 16 chars)
  unsigned long now = millis();
  if (needsScroll && (now - lastScroll >= SCROLL_DELAY)) {
    lastScroll = now;
    lcd.setCursor(0, 0);
    String window = (scrollText + scrollText).substring(scrollPos, scrollPos + 16);
    lcd.print(window);
    scrollPos = (scrollPos + 1) % scrollText.length();
  } else if (!needsScroll) {
    lcd.setCursor(0, 0);
    lcd.print(CANDIDATE_NAME);
  }

  // Row 2: temperature
  lcd.setCursor(0, 1);
  if (!isnan(temp)) {
    lcd.print("Temp: ");
    lcd.print(temp, 1);
    lcd.print((char)223);
    lcd.print("C   ");

    Serial.print("TEMP:");
    Serial.println(temp, 2);
  } else {
    lcd.print("Sensor error    ");
    Serial.println("TEMP:ERROR");
  }

  delay(2000);
}
