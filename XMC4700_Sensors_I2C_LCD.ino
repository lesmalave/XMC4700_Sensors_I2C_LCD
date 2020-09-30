#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#include "utility.h"

// Set the LCD address to 0x27 for a 20 chars and 4 line display
LiquidCrystal_I2C lcd(0x27, 20, 04);

#define DHTPIN 2      // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11 // DHT 11
DHT dht(DHTPIN, DHTTYPE);

// The analog pins that connect to the sensors
#define MQ7pin A0     // analog 0
#define MQ135pin A1   // analog 1
#define Luxpin A2

// Pin donde se conectan los leds
int Led1 = 24;
int Led2 = 25;
int Led3 = 3;
int Led4 = 4;

void setup()
{

  Serial.begin(115200);
  lcd.begin();
  dht.begin();

  // Turn on the blacklight and print a message.
  lcd.backlight();
  lcd.setCursor(2, 0);
  lcd.print("Infineon XMC4700");
  lcd.setCursor(1, 1);
  lcd.print("Enviroment Sensors");
  lcd.setCursor(0, 2);
  lcd.print("DHT-11 & Quality Air");
  delay(3000);

  // Configuramos como salidas los pines donde se conectan los led
  pinMode(Led1, OUTPUT);
  pinMode(Led2, OUTPUT);
  pinMode(Led3, OUTPUT);
  pinMode(Led4, OUTPUT);
}

void loop()
{
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f))
  {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  analogRead(MQ7pin);
  delay(20);
  int MQ7Reading = analogRead(MQ7pin);

  analogRead(MQ135pin);
  delay(20);
  int MQ135Reading = analogRead(MQ135pin);

  analogRead(Luxpin);
  delay(20);
  int LuxReading = analogRead(Luxpin);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));

  lcd.clear();
  delay(500);
  lcd.setCursor(0, 0);
  lcd.print("Temperature: ");
  lcd.print(t);
  lcd.print(" *C");
  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(h);
  lcd.print("%");
  lcd.setCursor(0, 2);
  lcd.print("Heat Index: ");
  lcd.print(hic);
  lcd.print(" *C");
  delay(4000);
  lcd.clear();
  delay(500);
  lcd.setCursor(0,0);
  lcd.print("Carbon monoxide: ");
  lcd.print(MQ7Reading);
  lcd.setCursor(0,1);
  lcd.print("Air Quality: ");
  lcd.print(MQ135Reading);
  lcd.setCursor(0,2);
  lcd.print("Lux: ");
  lcd.print(LuxReading);
  delay(4000);

  

}
