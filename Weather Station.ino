#include <SoftwareSerial.h>
#include "Arduino.h"

//BMP280 Declerations
#include <Adafruit_BMP280.h>
Adafruit_BMP280 airPressureSensor;

//CCS811 declarations
#include "SparkFunCCS811.h"
#define CCS811_ADDR 0x5A
CCS811 mySensor(CCS811_ADDR);
int co2value = 0;   //eCO2 (Equivalent calculated carbon-dioxide) 400 - 8192 ppm
int tvocValue = 0;  //TVOC (Total Volatile Organic Compound) 0 - 1187 ppb
//Alcohols, Aldehydes, Ketones, Organic Acids, Amines, Aliphatic and Aromatic Hydricarbons

//DHT declarations
#include <DHT.h>;
#define DHTPIN 6                   // DHT sensor pin
#define DHTTYPE  DHT22
DHT dht(DHTPIN, DHTTYPE);
float humidity;
float temperature;

//LCD declarations
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
const unsigned long lcdInterval = 500;
unsigned long lcdPreviousTime = 0;

//PLX-DAQ (Excel) declarations
const unsigned long excelInterval = 5000;
unsigned long excelPreviousTime = 0;

//RTC (ZS-042) declarations
#include <DS3231.h>
DS3231  rtc(SDA, SCL);

//SD card module declaratinos
#include <SPI.h>
#include <SD.h>
File myFile;
const unsigned long sdInterval = 3000;
unsigned long sdPreviousTime = 0;

//Dust sensor declarations
SoftwareSerial dustSensor(13, 12);
int pm1 = 0;
int pm2_5 = 0;
int pm10 = 0;


void setup() {
  Serial.begin(9600);
  delay(50);

  //PLX-DAQ (Excel) Setup
  Serial.println("CLEARDATA");
  Serial.print("LABEL,Date (MM:DD:YYYY), Time (hh:mm:ss),Temperature (C),Humidity (%),PM1 (ppm),PM2.5 (ppm),PM10 (ppm),CO2 (ppm), TVOC (ppb), AirPressure (mb)");
  Serial.println();

  //RTC (ZS-042) Setup
  rtc.begin();
  // The following lines can be uncommented to set the date and time
  //        rtc.setDOW(WEDNESDAY);     // Set Day-of-Week to SUNDAY
  //        rtc.setTime(01, 46, 10);     // Set the time to HH:MM:SS (24hr format)
  //        rtc.setDate(29, 01, 2020);   // Set the date to DD, MM, YYYY

  //SD card module Setup
  //  while (!Serial) {
  //  }
  //  if (!SD.begin(53)) {
  //    while (1);
  //  }

  //BMP280 Setup
  airPressureSensor.begin(0x76);

  //CCS811 Setup
  Wire.begin();
  CCS811Core::status returnCode = mySensor.begin();

  //DHT Setup
  dht.begin();

  //LCD Setup
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("    Deokgye     ");
  delay(50);
  lcd.setCursor(0, 1);
  lcd.print("   Elementary   ");
  delay(2000);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("TEMP");
  lcd.setCursor(0, 1);
  lcd.print("HUMI");
  lcd.setCursor(5, 0);
  lcd.print("BARO");
  lcd.setCursor(10, 0);
  lcd.print("DUST");

  lcd.setCursor(5, 1);
  lcd.print("CO2");
  lcd.setCursor(9, 1);
  lcd.print("TVOC");
  lcd.setCursor(15, 1);
  lcd.print("E");
  lcd.setCursor(14, 1);
  lcd.print("S");
  delay(6000);
  lcd.clear();

  //Dust sensor setup
  dustSensor.begin(9600);
}


void loop() {
  //DHT Loop
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();

  //BMP Loop
  float Pa = airPressureSensor.readPressure();
  float airPressure = (Pa / 100); // converts Pascals to Millibar (mb)

  //CCS811 Loop
  if (mySensor.dataAvailable()) {
    mySensor.readAlgorithmResults();
    co2value = mySensor.getCO2();
    tvocValue = mySensor.getTVOC();
  }

  //Dust sensor loop
  int index = 0;
  char value;
  char previousValue;

  while (dustSensor.available()) {
    value = dustSensor.read();
    if ((index == 0 && value != 0x42) || (index == 1 && value != 0x4d)) {
      break;
    }

    if (index == 4 || index == 6 || index == 8 || index == 10 || index == 12 || index == 14) {
      previousValue = value;
    }
    else if (index == 5) {
      pm1 = 256 * previousValue + value;
    }
    else if (index == 7) {
      pm2_5 = 256 * previousValue + value;
    }
    else if (index == 9) {
      pm10 = 256 * previousValue + value;
    } else if (index > 15) {
      break;
    }
    index++;
  }
  while (dustSensor.available()) dustSensor.read();



  //======================  Serial Monitor (PLX-DAQ) loop =========================
  unsigned long excelCurrentTime = millis();
  if (excelCurrentTime - excelPreviousTime >= excelInterval) {
    Serial.print("DATA,");
    Serial.print(rtc.getDateStr()); // Send date
    Serial.print(",");
    Serial.print(rtc.getTimeStr()); // Send time
    Serial.print(",");
    Serial.print(temperature);
    Serial.print(",");
    Serial.print(humidity);
    Serial.print(",");
    Serial.print(pm1);
    Serial.print(",");
    Serial.print(pm2_5);
    Serial.print(",");
    Serial.print(pm10);
    Serial.print(",");
    Serial.print(co2value);
    Serial.print(",");
    Serial.print(tvocValue);
    Serial.print(",");
    Serial.print(round(airPressure)); //unis in millibar (mb)
    lcd.setCursor(15, 1);
    lcd.print("E");
    delay(500);
    lcd.setCursor(15, 1);
    lcd.print("  ");

    excelPreviousTime = excelCurrentTime;
    Serial.println();
  }

  //=============================  LCD Printing ======================================
  unsigned long lcdCurrentTime = millis();
  if (lcdCurrentTime - lcdPreviousTime >= lcdInterval) {
    lcd.setCursor(0, 0);
    lcd.print(temperature, 1);
    //  lcd.print("C");

    lcd.setCursor(0, 1);
    lcd.print(humidity, 1);
    //  lcd.print("%");

    lcd.setCursor(5, 0);
    lcd.print(round(airPressure));
    lcd.print("   ");

    lcd.setCursor(10, 0);
    lcd.print(pm2_5);
    lcd.print("   ");

    lcd.setCursor(5, 1);
    lcd.print(co2value);
    lcd.print("   ");

    lcd.setCursor(9, 1);
    lcd.print(tvocValue);
    lcd.print("   ");

    lcdPreviousTime = lcdCurrentTime;
  }


  //=============================  SD card module ======================================
  myFile = SD.open("AQSdata2.txt", FILE_WRITE);
  if (myFile) {
    unsigned long sdCurrentTime = millis();
    if (sdCurrentTime - sdPreviousTime >= sdInterval) {
      myFile.print(rtc.getDateStr()); // Send date
      myFile.print(",");
      myFile.print(rtc.getTimeStr()); // Send time
      myFile.print(",");
      myFile.print(temperature);
      myFile.print(",");
      myFile.print(humidity);
      myFile.print(",");
      myFile.print(pm1);
      myFile.print(",");
      myFile.print(pm2_5);
      myFile.print(",");
      myFile.print(pm10);
      myFile.print(",");
      myFile.print(co2value);
      myFile.print(",");
      myFile.print(tvocValue);
      myFile.print(",");
      myFile.print(airPressure);

      sdPreviousTime = sdCurrentTime;
      myFile.println();
      lcd.setCursor(14, 1);
      lcd.print("S");
      delay(500);
      lcd.setCursor(14, 1);
      lcd.print(" ");
    }
    myFile.close();
  }
}
