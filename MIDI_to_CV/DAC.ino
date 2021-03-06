/****************************************************
 * Setup for the Digital Analog Converter (DAC)
 *****************************************************/

const int dacChipSelectPin = 18;      // set pin 18 (A0) as the chip select for the DAC

// Setup for the DAC:
void DACsetup()
{
  pinMode (dacChipSelectPin, OUTPUT);
  // set the ChipSelectPins high initially:
  digitalWrite(dacChipSelectPin, HIGH);
  // initialise SPI:
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);         // Not strictly needed but just to be sure.
  SPI.setDataMode(SPI_MODE0);        // Not strictly needed but just to be sure.
  setDac(0, 0);   // set DAC 1 to zero
  setDac(0, 1);   // set DAC 2 to zero
}


// Function to set the DAC
// Accepts the value to be sent and the channel of the DAC to be used.
void setDac(int value, int channel)
{
  byte dacRegister = 0b00110000;                        // Sets default DAC registers B00110000, 1st bit choses DAC, A=0 B=1, 2nd Bit bypasses input Buffer, 3rd bit sets output gain to 1x, 4th bit controls active low shutdown. LSB are insignifigant here.
  int dacSecondaryByteMask = 0b0000000011111111;        // Isolates the last 8 bits of the 12 bit value, B0000000011111111.
  byte dacPrimaryByte = (value >> 8) | dacRegister;     //Value is a maximum 12 Bit value, it is shifted to the right by 8 bytes to get the first 4 MSB out of the value for entry into th Primary Byte, then ORed with the dacRegister
  byte dacSecondaryByte = value & dacSecondaryByteMask; // compares the 12 bit value to isolate the 8 LSB and reduce it to a single byte.
  // Sets the MSB in the primaryByte to determine the DAC to be set, DAC A=0, DAC B=1
  switch (channel){
    case 0:
      dacPrimaryByte &= ~(1 << 7);
      break;
    case 1:
      dacPrimaryByte |= (1 << 7);
      break;
  }
  noInterrupts();                       // disable interupts to prepare to send data to the DAC
  digitalWrite(dacChipSelectPin, LOW);  // take the Chip Select pin low to select the DAC:
  SPI.transfer(dacPrimaryByte);         // send in the Primary Byte:
  SPI.transfer(dacSecondaryByte);       // send in the Secondary Byte
  digitalWrite(dacChipSelectPin, HIGH); // take the Chip Select pin high to de-select the DAC:
  interrupts();                         // Enable interupts
}

