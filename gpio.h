/**
 * Constants for gpio registers
 * (Offsets from the gpio base address) 
 */
#define GPFSEL 0x00 //GPIO Function Select                  Read/Write access
#define GPSET  0x1C //GPIO Set Pin Output  (HIGH),          Write 1 bit
#define GPCLR  0x28 //GPIO Clear Pin Output  (LOW),         Write 1 bit
#define GPLEV  0x34 //GPIO Pin Level,                       Read access 
#define GPEDS  0x40 //GPIO Pin Event Detect Status          Read/Write 1 bit to clear
#define GPREN  0x4C //GPIO Pin Rising Edge Detect Enable    Read/Write access 
#define GPFEN  0x58 //GPIO Pin Falling Edge Detect Enable   Read/Write access 
#define GPHEN  0x64 //GPIO Pin High Detect Enable           Read/Write access 
#define GPLEN  0x70 //GPIO Pin Low Detect Enable            Read/Write access 
#define GPAREN 0x7C //GPIO Pin Async. Rising Edge Detect    Read/Write access
#define GPAFEN 0x88 //GPIO Pin Async. Falling Edge Detect   Read/Write access 
#define GPPULL 0xe4 //GPIO_PUP_PDN_CNTRL_REG Pull-up/-down  Read/Write access


#define PIN_COUNT 58  //RPi 4

//Pin functions for the GPFSEL-register
#define INPUT 0
#define OUTPUT 1
#define ALTERNATE_FUNCTION_0 4
#define ALTERNATE_FUNCTION_1 5
#define ALTERNATE_FUNCTION_2 6
#define ALTERNATE_FUNCTION_3 7
#define ALTERNATE_FUNCTION_4 3
#define ALTERNATE_FUNCTION_5 2 


//Return values of functions
#define NO_ACCESS -13 //if mapping /dev/gpiomem fails 
#define SUCCESS 0
#define EVENT_OCCURED 1
#define NO_EVENT 0
//Level of a pin
#define LOW 0
#define HIGH 1

//Direction of pull-up/pull-down-register
#define  NONE 0
#define  UP 1
#define  DOWN 2


/**
 * Maps the GPIO device (/dev/gpiomem) of the Raspberry Pi 4
 * into the user programs' memory space. 
 * Returns 0 for success, NO_ACCESS if user has no permission for 
 * reading/writing to/from the /dev/gpiomem file. 
 * [In Ubuntu Mate 20.04.1, MATE 1.24.0 for Raspberry Pi 4B
 * /dev/gpiomem belongs to a group 'dialout' which has read/write access. 
 * After adding the username to this group in the /etc/group file 
 * (dialout:x:20:myname) mapping should succeed.]
 */
int init_gpio(void); 

/**
 * Used for testing purposes instead of init_gpio();
 */
int test_init(void);


/**
 * Unmaps the GPIO device of the Raspbery Pi.
 */
int close_gpio(void);


/**
 * Returns gpio base addresss.
 * Requires initializiation with init_gpio()
 */
long long gpio_base(void);

/**
 * All functions take a pin number.
 * It's up to the user to provide a valid number
 * in the range from 0 to PIN_COUNT-1.
 * Invalid numbers can cause  errors and crashes.
 */
 
 
/**
 * Set gpio function for a pin
 */
void input(int pin);  // GPFSEL INPUT
void output(int pin); // GPFSEL OUTPUT
void alt0(int pin);   // GPFSEL ALTERNATE_FUNCTION_0
void alt1(int pin);   // GPFSEL ALTERNATE_FUNCTION_1
void alt2(int pin);   // GPFSEL ALTERNATE_FUNCTION_2
void alt3(int pin);   // GPFSEL ALTERNATE_FUNCTION_3
void alt4(int pin);   // GPFSEL ALTERNATE_FUNCTION_4
void alt5(int pin);   // GPFSEL ALTERNATE_FUNCTION_5

/**
 * Set output pin to low or high
 */
void low(int pin);  //GPCLR
void high(int pin); //GPSET


/**
 * Getter functions for readable gpio registers
 */
int function(int pin);                  //GPFSEL   
int level(int pin);                     //GPLEV
int rising_edge_detect(int pin);        //GPREN
int falling_edge_detect(int pin);       //GPFEN
int high_detect(int pin);               //GPHEN
int low_detect(int pin);                //GPLEN
int async_rising_edge_detect(int pin);  //GPAREN 
int async_falling_edge_detect(int pin); //GPAFEN
int pull_direction(int pin);            //GPPULL

/**
 * Set functions for pullup-pull-down register
 */
void pull_up(int pin);   //GPPULL PULL_UP
void pull_down(int pin); //GPPULL PULL_DOWN
void no_pull(int pin);	 //GPPULL NO_PULL

/**
 *  Returns EVENT_OCCURED if an event had occured, otherwise NO_EVENT.
 *  Does not clear the event in the GPEDS register.
 */
int event(int pin); //GPEDS

/**
 * Clears an event.
 */
void clear_event(int pin);

/**
 * Returns EVENT_OCCURED if an event had occured, otherwise NO_EVENT.
 * If there was an event, the GPEDS register entry for the pin is 
 * immediatly cleared.
 * This function is faster than 
 *   int e = event(pin);
 *   if(e==EVENT_OCCURED){ 
 *       clear_event(pin);
 *   }
 *   return e;
 */
int get_event_and_clear(int pin); 


/**
 * Enable/disable gpio 'detect'registers
 * Activation of one of these event detection registers can cause crashes in 
 * case of an event:
 * "The GPIO peripheral has four dedicated interrupt lines. 
 * These lines are triggered by the setting of bits in the event detect
 * status register."
 * BCM2711 ARM Peripherals manual, p.64 
 */
void enable_rising_edge_detect(int pin);       // GPREN 
void enable_falling_edge_detect(int pin);      // GPFEN 
void enable_high_detect(int pin);			   // GPHEN 
void enable_low_detect(int pin);               // GPLEN 
void enable_async_rising_edge_detect(int pin); // GPAREN 
void enable_async_falling_edge_detect(int pin);// GPAFEN  

/**
 * It is recommended to disable the 'detect' registers as soon as they are
 * no longer needed.
 */
void disable_rising_edge_detect(int pin);       // GPREN 
void disable_falling_edge_detect(int pin);      // GPFEN 
void disable_high_detect(int pin);              // GPHEN 
void disable_low_detect(int pin);               // GPLEN 
void disable_async_rising_edge_detect(int pin); // GPAREN 
void disable_async_falling_edge_detect(int pin);// GPAFEN  


