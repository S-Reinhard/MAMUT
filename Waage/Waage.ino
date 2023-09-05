#include <LiquidCrystal_I2C.h>

#include <Pushbutton.h>

#include "HX711.h"
#include "constants.h"

HX711 scale;

Pushbutton calBtn(CAL_BTN_PIN);
Pushbutton tareBtn(TARE_BTN_PIN);
LiquidCrystal_I2C lcd(I2C_ADDRESS, COLUMNS, RISING);

void setup() {
  Serial.begin(57600);

  lcd.init();
  lcd.backlight();
  
  resetLCD();
  lcd.print("init scale");
  
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(3922.67993);
  scale.tare();

  resetLCD();
}

void resetLCD() {
  lcd.clear();
  lcd.setCursor(0,0);
}

double getTareValue(double reading) {
  return reading / ( KNOWN_WEIGHT_PER_UNIT * NUM_OF_CAL_OBJECTS );
}

void printCountedObjects(int amount) {
  resetLCD();
  lcd.print("counted:");
  lcd.setCursor(0,1);
  lcd.print(amount);
  lcd.print(" ");
  lcd.print(NAME(amount));
  
}

void printRemoveObjects() {
  resetLCD();
  lcd.print("remove ");
  lcd.print(OBJECT_NAMES);
  lcd.setCursor(0, 1);
  lcd.print("then press tare");
}

void printPlaceObjects() {
  resetLCD();
  lcd.print("Place ");
  lcd.print(NUM_OF_CAL_OBJECTS);
  lcd.print(" ");
  lcd.print(NAME(NUM_OF_CAL_OBJECTS));
  lcd.setCursor(0, 1);
  lcd.print("then press tare");
}

void recalibrate() {
  Serial.println("Recalibrate");
  if (!scale.is_ready()) {
    // clear old tare value
    scale.set_scale();
    printRemoveObjects();
    calBtn.waitForButton();
    scale.tare();

    // calculate new tare value
    printPlaceObjects();
    calBtn.waitForButton();
    resetLCD();
    lcd.print("wait...");
    double tareValue = getTareValue(scale.get_units(1000));
    scale.set_scale(tareValue);
    Serial.println(tareValue, 5);

    resetLCD();
    lcd.println(tareValue);
    lcd.setCursor(0,1);
    lcd.println("finished");
  } else {
    resetLCD();
    Serial.println("HX711 not found.");
  }
}

void loop() {
  //get the absolute load on the scale
  double load = abs(scale.get_units(10000)); //10000 because the lcd display does not work properly other wise. at least for me

  // print the rounded value 
  printCountedObjects((int) (0.5 + load));

  //recalibrate the scale if cal button is pressed
  if(!calBtn.isPressed()) {
    recalibrate();
  }

  if(!tareBtn.isPressed()) {
    scale.tare();
    Serial.println("tare");
  }

    scale.power_down();
    delay(1000);
    scale.power_up();
}
