#include <Pushbutton.h>

#include "HX711.h"
#include "waage_pinout.h"

HX711 scale;

Pushbutton tareButton(TARE_BTN_PIN);


void setup() {
  Serial.begin(57600);
  Serial.println("Initializing the scale");

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
            
  scale.set_scale(-471.497);

  Serial.println("Readings:");
}

double getTareValue(long reading) {
  return reading / ( KNOWN_WEIGHT * NUM_OF_OBJECTS );
}

void recalibrate() {
  if (scale.is_ready()) {
    // clear old tare value
    scale.set_scale();
    Serial.println("Tare... remove any weights from the scale. Then push the button.");
    tareButton.waitForButton();
    scale.tare();

    // calculate new tare value
    Serial.println("Tare done...");
    Serial.print("Place ");
    Serial.print(NUM_OF_OBJECTS);
    Serial.println(" known known objects on the scale... then press the button");
    tareButton.waitForButton();
    double tareValue = getTareValue(scale.get_units(10));
    scale.set_scale(tareValue);
    Serial.println(tareValue);

    Serial.println("calibration is finished. Objects can be removed");
  } 
  else {
    Serial.println("HX711 not found.");
  }
}

void loop() {
  Serial.print("one reading:\t");
  Serial.print(scale.get_units(), 1);
  Serial.print("\t| average:\t");
  Serial.println(scale.get_units(10), 5);
  
  if(tareButton.getSingleDebouncedPress())

  delay(5000);
}