#define KNOWN_WEIGHT_PER_UNIT 1 // the weight of one ball is defined as one ball so 1. If you have a test weight of 50g and want to measure in g insert 50.
#define NUM_OF_CAL_OBJECTS 25   // since balls tend to have slightly diffent mass from each other putting 25 balls on the scale and dividing the result by 25 is a good way to estimate the weight of one single mass. If you know the exact weight of your calibration object in the unit you desire you can insert 1.
#define OBJECT_NAME "ball"      // This is used to print messages (Singular)
#define OBJECT_NAMES "balls"    // This is used to print messages, too (Plural)
#define NAME(count) (count != 1) ? (OBJECT_NAMES) : (OBJECT_NAME) // this determins when to use Singular and When to use Plural

// hx711 wiring
#define LOADCELL_DOUT_PIN 2
#define LOADCELL_SCK_PIN 3

// buttons
#define CAL_BTN_PIN 4
#define TARE_BTN_PIN 7

// LCD displax
#define I2C_ADDRESS 0x27
#define COLUMNS 16
#define ROWS 2
