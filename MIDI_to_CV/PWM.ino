/**********************************************************
 * Setup for the fast PWM
 *
 * http://r6500.blogspot.de/2014/12/fast-pwm-on-arduino-leonardo.html
 *
 * ... with timers 1:
 * On pins 9 and 10 with frequencies up to 62kHz
 *
 * ... with timer 4:
 * Onr pins 6 with frequencies up to 187kHz
 *
 **********************************************************
 * Do not use analogWrite to pins 6, 9 or 10.
 *
 * Those functions will probably conflict with the
 * servo library and the MSTIMER2 library.
 *
 **********************************************************
 * Timer 4 uses a PLL as input so that its clock frequency
 * can be up to 96MHz on standard Arduino Leonardo.
 * We limit imput frequency to 48MHz to generate 187.5kHz PWM
 * If needed, we can double that up to 375kHz
 *
 **********************************************************/

// Frequency modes for TIMER1
#define PWM62k   1   //62500 Hz
#define PWM8k    2   // 7812 Hz
#define PWM1k    3   //  976 Hz
#define PWM244   4   //  244 Hz
#define PWM61    5   //   61 Hz

// Configure the PWM clock
// The argument is one of the 5 previously defined modes
void pwm91011configure(int mode)
{
  // TCCR1A configuration
  //  00 : Channel A disabled D9
  //  00 : Channel B disabled D10
  //  00 : Channel C disabled D11
  //  01 : Fast PWM 8 bit
  TCCR1A = 1;
  // TCCR1B configuration
  // Clock mode and Fast PWM 8 bit
  TCCR1B = mode | 0x08;
  // TCCR1C configuration
  TCCR1C = 0;
}

// Set PWM to pin 09 - Values are between 0 and 255
void pwmSet9(int value)
{
  OCR1A = value; // Set PWM value
  DDRB |= 1 << 5; // Set Output Mode B5
  TCCR1A |= 0x80; // Activate channel
}

// Set PWM to pin 10 - Values are between 0 and 255
void pwmSet10(int value)
{
  OCR1B = value; // Set PWM value
  DDRB |= 1 << 6; // Set Output Mode B6
  TCCR1A |= 0x20; // Activate channel
}

// Change PWM on pin 09 - Values are between 0 and 255
void setPWM9(int value)
{
  OCR1A = value; // Set PWM value
}

// Change PWM on pin 10 - Values are between 0 and 255
void setPWM10(int value)
{
  OCR1B = value; // Set PWM value
}

//************************************************************
// Frequency modes for TIMER4
#define PWM187k 1   // 187500 Hz
#define PWM94k  2   //  93750 Hz
#define PWM47k  3   //  46875 Hz
#define PWM23k  4   //  23437 Hz
#define PWM12k  5   //  11719 Hz
#define PWM6k   6   //   5859 Hz
#define PWM3k   7   //   2930 Hz


// Configure the PWM clock
// The argument is one of the 7 previously defined modes
void pwm613configure(int mode)
{
  // TCCR4A configuration
  TCCR4A = 0;
  // TCCR4B configuration
  TCCR4B = mode;
  // TCCR4C configuration
  TCCR4C = 0;
  // TCCR4D configuration
  TCCR4D = 0;
  // PLL Configuration
  // Use 96MHz / 2 = 48MHz
  PLLFRQ = (PLLFRQ & 0xCF) | 0x30;
  // PLLFRQ=(PLLFRQ&0xCF)|0x10; // Will double all frequencies
  // Terminal count for Timer 4 PWM
  OCR4C = 255;
}

// Set PWM to pin 06 - Values are between 0 and 255
void pwmSet6(int value) 
{
  OCR4D = value; // Set PWM value
  DDRD |= 1 << 7; // Set Output Mode D7
  TCCR4C |= 0x09; // Activate channel D
}

// Set PWM to pin 05 - Values are between 255 and 0!
void pwmSet5(int value)
{
  OCR4A = 255 - value; // Set the negativ PWM value
  DDRC |= 1 << 6; // Set Output Mode C6
  TCCR4A = 0x42; // Activate the complementary channel A
}

// Change PWM to pin 06 - Values are between 0 and 255
void setPWM6(int value)
{
  OCR4D = value; // Set PWM value
}

// Change PWM to pin 05 - Values are between 255 and 0 !!complementary!!
void setPWM5(int value)
{
  OCR4A = 255 - value; // Set PWM value
}

//************************************************************
// Setup for fast PWM:
void PWMsetup()
{
  // Configure Timer 1 (Pins 9 and 10)
  pwm91011configure(PWM62k);

  // Configure Timer 4 (Pins 6)
  pwm613configure(PWM187k);

  // Prepare pin 06, 09 and 10 for the fast PWM and set them to 0
  pwmSet9(0);
  pwmSet10(0);
  pwmSet6(0);
  pwmSet5(0);
}

