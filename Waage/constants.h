#define KNOWN_WEIGHT 1
#define NUM_OF_OBJECTS 20
#define OBJECT_NAME "ball"
#define OBJECT_NAMES "balls"
#define NAME(count) (count != 1) ? OBJECT_NAMES : OBJECT_NAME;

// hx711 wiring
#define LOADCELL_DOUT_PIN 2
#define LOADCELL_SCK_PIN 3

#define TARE_BTN_PIN 4

// LCD displax
#define I2C_ADDRESS 0x27
#define COLUMNS 16
#define ROWS 2
