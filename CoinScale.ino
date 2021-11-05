#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);


#include "HX711.h"

#define DOUT 3
#define CLK  2

HX711 scale;

float calibration_factor = 1000; 
float units;
float ounces;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 4);
  lcd.setCursor(0, 0);
  lcd.print("HX711 calibration");
  Serial.println("HX711 calibration sketch");
  Serial.println("Remove all weight from scale");
  Serial.println("After readings begin, place known weight on scale");
  Serial.println("Press + or a to increase calibration factor");
  Serial.println("Press - or z to decrease calibration factor");

  scale.begin(DOUT, CLK);
  scale.set_scale();
  scale.tare();	//Reset the scale to 0

  long zero_factor = scale.read_average(); //Get a baseline reading
  Serial.print("Zero factor: "); //This can be used to remove the need to tare the scale. Useful in permanent scale projects.
  Serial.println(zero_factor);
}

void loop() {
  scale.set_scale(calibration_factor); //Adjust to this calibration factor
  Serial.print("Reading: ");
  units = scale.get_units();
  if (units < 0) {
    units = 0.00;
  }
  ounces = units * 0.035274;
  Serial.print(units);
  Serial.print(" grams"); 
  Serial.print(" calibration_factor: ");
  Serial.print(calibration_factor);
  Serial.println();
  lcd.setCursor(0, 1);
  lcd.print("Grams: ");
  lcd.print(units);
  lcd.setCursor(0, 2);
  lcd.print("Ounce: ");
  lcd.print(ounces);
  lcd.setCursor(0, 3);
  lcd.print("Calbr: ");
  lcd.print(calibration_factor);

  if(Serial.available())
  {
    char temp = Serial.read();
    if(temp == '+' || temp == 'a')
      calibration_factor += 1;
    else if(temp == '-' || temp == 'z')
      calibration_factor -= 1;
  }
}