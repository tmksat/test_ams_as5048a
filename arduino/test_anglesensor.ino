#include <SPI.h>

// led
#define LED 25
#define LEDON digitalWrite(LED, HIGH)
#define LEDOFF digitalWrite(LED, LOW)
volatile bool led_status = true;

// spi0
#define SPI0_CS 17


// AS5048
volatile uint16_t g_angle = 0x0000;
#define CMD_ANGLE (uint16_t)0x3FFF // RW=0(read) | Parity(Even)=0 | adr=0x3fff


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("AS5048 test board:");

  // led (gp25)
  pinMode(LED, OUTPUT);
  
  //spi0 settings
  SPI.setRX(16);
  // SPI.setCS(17);
  pinMode(SPI0_CS, OUTPUT);
  SPI.setSCK(18);
  SPI.setTX(19);
  // SPI.setBitOrder(MSBFIRST);
  // SPI.setClockDivider(SPI_CLOCK_DIV128);
  // SPI.setClockDivider(SPI_HOWMANY);
  // SPI.setDataMode(SPI_MODE0);
  SPI.begin();
  // spi0 software reset
  digitalWrite(SPI0_CS, LOW);
  SPI.transfer(0x00);
  SPI.transfer(0x00);
  SPI.transfer(0x00);
  SPI.transfer(0x00);
  digitalWrite(SPI0_CS, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:

  // read angle value from as5048 via spi0
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE1));
  digitalWrite(SPI0_CS, LOW);
  uint16_t res = SPI.transfer16((uint16_t)CMD_ANGLE);
  digitalWrite(SPI0_CS, HIGH);
  SPI.endTransaction();
  g_angle = (res & 0x3fff); // mask lower 14bit

  // led blink 
  led_status = !led_status;
  digitalWrite(LED, led_status);

  // print angle value to serial console
  Serial.print("{angle:");
  Serial.print(g_angle);
  Serial.println("}");

  // loop delay
  delay(25);
}
