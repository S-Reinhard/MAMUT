#include <LiquidCrystal_I2C.h>

#include <Pushbutton.h>

#include "HX711.h"
#include "constants.h"

HX711 scale;

Pushbutton tareButton(TARE_BTN_PIN);
LiquidCrystal_I2C lcd(I2C_ADDRESS, COLUMNS, RISING);


  void setup() {
  Serial.begin(57600);

  lcd.init();
  lcd.backlight();
  //lcd.autoscroll();
  lcd.setCursor(0, 0);

    lcd.println("Initializing the scale");

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  scale.set_scale(24753);

  lcd.clear();
  lcd.setCursor(0, 0);
}

double getTareValue(long reading) {
  return reading / (KNOWN_WEIGHT * NUM_OF_OBJECTS);
}

void printRemoveObjects() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("remove ");
  lcd.print(OBJECT_NAMES);
  lcd.setCursor(0, 1);
  lcd.print("then press tare");
}

void printPlaceObjects() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Place ");
  lcd.print(NUM_OF_OBJECTS);
  lcd.print(" ");
  lcd.print(OBJECT_NAMES);
  lcd.setCursor(0, 1);
  lcd.print("then press tare");
}

void recalibrate() {
  if (scale.is_ready()) {
    // clear old tare value
    scale.set_scale();
    printRemoveObjects();
    tareButton.waitForButton();
    scale.tare();

    // calculate new tare value
    printPlaceObjects();
    tareButton.waitForButton();
    double tareValue = getTareValue(scale.get_units(10));
    scale.set_scale(tareValue);

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.println(tareValue);
    lcd.setCursor(0,1);
    lcd.println("finished");
  } else {
    lcd.clear();
    lcd.setCursor(0,0);
    Serial.println("HX711 not found.");
  }
}

void loop() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("counted ");
  lcd.setCursor(0,1);
  lcd.print(scale.get_units(10), 1);

  if (tareButton.getSingleDebouncedPress()) {
    recalibrate();
  }
    scale.power_down();
    delay(5000);
    scale.power_up();
}