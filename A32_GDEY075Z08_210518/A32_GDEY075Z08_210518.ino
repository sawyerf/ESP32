#include "Ap_29demo.h"
//IO settings
int BUSY_Pin = 1;
int RES_Pin = 19;
int DC_Pin = 20;
int CS_Pin = 18;
int SCK_Pin = 23;
int SDI_Pin = 22;
int PWR_Pin = 14;

#define EPD_W21_MOSI_0 digitalWrite(SDI_Pin, LOW)
#define EPD_W21_MOSI_1 digitalWrite(SDI_Pin, HIGH)

#define EPD_W21_CLK_0 digitalWrite(SCK_Pin, LOW)
#define EPD_W21_CLK_1 digitalWrite(SCK_Pin, HIGH)

#define EPD_W21_CS_0 digitalWrite(CS_Pin, LOW)
#define EPD_W21_CS_1 digitalWrite(CS_Pin, HIGH)

#define EPD_W21_DC_0 digitalWrite(DC_Pin, LOW)
#define EPD_W21_DC_1 digitalWrite(DC_Pin, HIGH)
#define EPD_W21_RST_0 digitalWrite(RES_Pin, LOW)
#define EPD_W21_RST_1 digitalWrite(RES_Pin, HIGH)
#define isEPD_W21_BUSY digitalRead(BUSY_Pin)
////////FUNCTION//////
void driver_delay_us(unsigned int xus);
void driver_delay_xms(unsigned long xms);
void DELAY_S(unsigned int delaytime);
void SPI_Delay(unsigned char xrate);
void SPI_Write(unsigned char value);
void EPD_W21_WriteDATA(unsigned char command);
void EPD_W21_WriteCMD(unsigned char command);
//EPD
void EPD_W21_Init(void);
void EPD_init(void);
void PIC_display1(void);
void EPD_sleep(void);
void EPD_refresh(void);
void lcd_chkstatus(void);
void PIC_display_Clean(void);
unsigned char HRES, VRES_byte1, VRES_byte2;

void setup() {
  Serial.begin(9600);
  Serial.println("setup");
  pinMode(BUSY_Pin, INPUT);
  pinMode(RES_Pin, OUTPUT);
  pinMode(DC_Pin, OUTPUT);
  pinMode(CS_Pin, OUTPUT);
  pinMode(SCK_Pin, OUTPUT);
  pinMode(SDI_Pin, OUTPUT);
  pinMode(PWR_Pin, OUTPUT);
  // led
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("setup done");
}


//Tips//
/*When the electronic paper is refreshed in full screen, the picture flicker is a normal phenomenon, and the main function is to clear the display afterimage in the previous picture.
  When the local refresh is performed, the screen does not flash.*/
/*When you need to transplant the driver, you only need to change the corresponding IO. The BUSY pin is the input mode and the others are the output mode. */


void loop() {
  //PICTURE1

  digitalWrite(PWR_Pin, HIGH);
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  Serial.println("start");
  Serial.print("busy: ");
  Serial.println(isEPD_W21_BUSY);
  EPD_init();  //EPD init
  PIC_display1();
  EPD_refresh();  //EPD_refresh
  EPD_sleep();    //EPD_sleep,Sleep instruction is necessary, please do not delete!!!
  delay(3000);

  //PICTURE Clean
  EPD_init();  //EPD init
  PIC_display_Clean();
  EPD_refresh();                   //EPD_refresh
  EPD_sleep();                     //EPD_sleep,Sleep instruction is necessary, please do not delete!!!
  digitalWrite(LED_BUILTIN, LOW);  // turn the LED off by making the voltage LOW
  while (1)
    ;
}




///////////////////EXTERNAL FUNCTION////////////////////////////////////////////////////////////////////////
/////////////////////delay//////////////////////////////////////
void driver_delay_us(unsigned int xus)  //1us
{
  for (; xus > 1; xus--)
    ;
}
void driver_delay_xms(unsigned long xms)  //1ms
{
  unsigned long i = 0, j = 0;

  for (j = 0; j < xms; j++) {
    for (i = 0; i < 256; i++)
      ;
  }
}
void DELAY_S(unsigned int delaytime) {
  int i, j, k;
  for (i = 0; i < delaytime; i++) {
    for (j = 0; j < 4000; j++) {
      for (k = 0; k < 222; k++)
        ;
    }
  }
}
//////////////////////SPI///////////////////////////////////
void SPI_Delay(unsigned char xrate) {
  unsigned char i;
  while (xrate) {
    for (i = 0; i < 2; i++)
      ;
    xrate--;
  }
}


void SPI_Write(unsigned char value) {
  unsigned char i;
  SPI_Delay(1);
  for (i = 0; i < 8; i++) {
    EPD_W21_CLK_0;
    SPI_Delay(1);
    if (value & 0x80)
      EPD_W21_MOSI_1;
    else
      EPD_W21_MOSI_0;
    value = (value << 1);
    SPI_Delay(1);
    driver_delay_us(1);
    EPD_W21_CLK_1;
    SPI_Delay(1);
  }
}

void EPD_W21_WriteCMD(unsigned char command) {
  SPI_Delay(1);
  EPD_W21_CS_0;
  EPD_W21_DC_0;  // command write
  SPI_Write(command);
  EPD_W21_CS_1;
}
void EPD_W21_WriteDATA(unsigned char command) {
  SPI_Delay(1);
  EPD_W21_CS_0;
  EPD_W21_DC_1;  // command write
  SPI_Write(command);
  EPD_W21_CS_1;
}



/////////////////EPD settings Functions/////////////////////
void EPD_W21_Init(void) {
  EPD_W21_RST_0;  // Module reset
  delay(100);     //At least 10ms
  EPD_W21_RST_1;
  delay(100);
}
void EPD_init(void) {
  unsigned char HRES_byte1 = 0x03;  //800
  unsigned char HRES_byte2 = 0x20;
  unsigned char VRES_byte1 = 0x01;  //480
  unsigned char VRES_byte2 = 0xE0;

  EPD_W21_Init();

  EPD_W21_WriteCMD(0x01);  //POWER SETTING
  EPD_W21_WriteDATA(0x07);
  EPD_W21_WriteDATA(0x07);  //VGH=20V,VGL=-20V
  EPD_W21_WriteDATA(0x3f);  //VDH=15V
  EPD_W21_WriteDATA(0x3f);  //VDL=-15V

  EPD_W21_WriteCMD(0x04);  //Power on
  lcd_chkstatus();         //waiting for the electronic paper IC to release the idle signal

  EPD_W21_WriteCMD(0X00);   //PANNEL SETTING
  EPD_W21_WriteDATA(0x0F);  //KW-3f   KWR-2F BWROTP 0f BWOTP 1f

  EPD_W21_WriteCMD(0x61);         //tres
  EPD_W21_WriteDATA(HRES_byte1);  //source 800
  EPD_W21_WriteDATA(HRES_byte2);
  EPD_W21_WriteDATA(VRES_byte1);  //gate 480
  EPD_W21_WriteDATA(VRES_byte2);

  EPD_W21_WriteCMD(0X15);
  EPD_W21_WriteDATA(0x00);

  EPD_W21_WriteCMD(0X50);  //VCOM AND DATA INTERVAL SETTING
  EPD_W21_WriteDATA(0x11);
  EPD_W21_WriteDATA(0x07);

  EPD_W21_WriteCMD(0X60);  //TCON SETTING
  EPD_W21_WriteDATA(0x22);
}
void EPD_refresh(void) {
  EPD_W21_WriteCMD(0x12);  //DISPLAY REFRESH
  driver_delay_xms(100);   //!!!The delay here is necessary, 200uS at least!!!
  lcd_chkstatus();
}
void EPD_sleep(void) {
  EPD_W21_WriteCMD(0X50);  //VCOM AND DATA INTERVAL SETTING
  EPD_W21_WriteDATA(0x97);

  EPD_W21_WriteCMD(0X02);  //power off
  lcd_chkstatus();
  EPD_W21_WriteCMD(0X07);  //deep sleep
  EPD_W21_WriteDATA(0xA5);
}


void PIC_display1(void) {
  unsigned int i;
  EPD_W21_WriteCMD(0x10);  //Transfer old data
  for (i = 0; i < 48000; i++)
    EPD_W21_WriteDATA(~pgm_read_byte(&gImage_BW[i]));  //BW

  EPD_W21_WriteCMD(0x13);  //Transfer new data
  for (i = 0; i < 48000; i++)
    EPD_W21_WriteDATA(pgm_read_byte(&gImage_R[i]));  //red
}

void PIC_display_Clean(void) {
  unsigned int i;
  EPD_W21_WriteCMD(0x10);  //Transfer old data
  for (i = 0; i < 48000; i++) {
    EPD_W21_WriteDATA(0xff);
  }

  EPD_W21_WriteCMD(0x13);  //Transfer new data
  for (i = 0; i < 48000; i++) {
    EPD_W21_WriteDATA(0x00);
  }
}
void lcd_chkstatus(void) {
  EPD_W21_WriteCMD(0x71);
  // Serial.println("CheckStatus start");
  Serial.print("busy: ");
  Serial.println(isEPD_W21_BUSY);
  while (!isEPD_W21_BUSY)
    ;  //0 is busy
  Serial.print("busyend: ");
  Serial.println(isEPD_W21_BUSY);

  // Serial.println("CheckStatus done");
}
