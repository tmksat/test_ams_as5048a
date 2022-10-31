#include <SPI.h>

// led
#define LED 25
#define LEDON digitalWrite(LED, HIGH)
#define LEDOFF digitalWrite(LED, LOW)
volatile bool led_status = true;

// spi0
#define SPI0_CS 17


// AS5048
volatile int g_angle = 0;

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
  SPI.transfer(0xff);
  SPI.transfer(0xff);
  SPI.transfer(0xff);
  SPI.transfer(0xff);
  digitalWrite(SPI0_CS, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:

  // read angle value from as5048 via spi0

  // led blink 
  led_status = !led_status;
  digitalWrite(LED, led_status);

  // print angle value to serial console
  Serial.print("{angle:");
  Serial.print(g_angle, DEC);
  Serial.println("}");


  // loop delay
  delay(1000);
}
