/*////////////////////
//  KIRBYSOFT v0.7  //
////////////////////*/

/*Include Dallas DS18b20 temperature sensors */
#include <OneWire.h>
#include <DallasTemperature.h>

/*Include libraries for Adafruit RA8875 */
#include <SPI.h>
#include "Adafruit_GFX.h"
#include "Adafruit_RA8875.h"

/* Pins for RA8875 */
// Connect SCLK to UNO Digital #13 (Hardware SPI clock)
// Connect MISO to UNO Digital #12 (Hardware SPI MISO)
// Connect MOSI to UNO Digital #11 (Hardware SPI MOSI)
#define RA8875_INT 3
#define RA8875_CS 10
#define RA8875_RESET 9

Adafruit_RA8875 tft = Adafruit_RA8875(RA8875_CS, RA8875_RESET);
// tsPoint_t       _tsLCDPoints[3]; 
// tsPoint_t       _tsTSPoints[3]; 
// tsMatrix_t      _tsMatrix;
uint16_t tx, ty;

#define textSetCursorX_1 10
#define textSetCursorY_1 10
#define textSetCursorX_2 10
#define textSetCursorY_2 35

/* Define oneWire data pins for temperature sensors */
#define ONE_WIRE_BUS 5

/* Setup oneWire instance to communicate with any oneWire devices */
OneWire oneWire(ONE_WIRE_BUS);

/* Pass our oneWire reference to Dallas Temperature. */
DallasTemperature sensors(&oneWire);
 
/* Define the reference voltage (use multimeter on 3.3v) */
//#define aref_voltage 3.3 //Not yet calibrated
 
/* Relay pins */
//#define RELAY1 22 //Pump1 Normal to FAU
//#define RELAY2 23 //Pump1 High to FAU
//#define RELAY3 24 //Pump2 Normal to H2O exchange
//#define RELAY4 25 //Pump3 Normal to slab
//#define RELAY5 26 //Pump3 High to slab
//#define RELAY6 27 //EMPTY
//#define RELAY7 28 //EMPTY
//#define RELAY8 29 //EMPTY

/* Temperature thresholds for pumps */
#define thresh1 80 //Threshold for normal to FAU
#define thresh2 79 //Threshold for high to FAU
#define thresh3 78 //Threshold for normal to H2O
//#define thresh4 77 //Threshold for normal to slab
//#define thresh5 76 //Threshold for high to slab
 
/* TMP36 pins */
//int tempPin1 = 30; //Panel supply
//int tempPin2 = 31; //East panel return
//int tempPin3 = 32; //West panel return
//int tempPin4 = 33; //H2O supply
//int tempPin5 = 34; //H2O return
//int tempPin6 = 35; //H2O main
//int tempPin7 = 36; //FAU supply
//int tempPin8 = 37; //FAU return
 
/* Initialize temperature readings */
//int tempReading1;
//int tempReading2;
//int tempReading3;
//int tempReading4;
//int tempReading5;
//int tempReading6;
//int tempReading7;
//int tempReading8;
 
void setup() {
  Serial.begin(9600);

  // Start the temperature sensors
  sensors.begin();

  // Start the relays
  //pinMode(RELAY1, OUTPUT);
  //pinMode(RELAY2, OUTPUT);
  //pinMode(RELAY3, OUTPUT);
  //pinMode(RELAY4, OUTPUT);
  //pinMode(RELAY5, OUTPUT);
  //pinMode(RELAY6, OUTPUT);
  //pinMode(RELAY7, OUTPUT);
  //pinMode(RELAY8, OUTPUT);

  /* Start the screen */
    Serial.println("RA8875 start");
  if (!tft.begin(RA8875_800x480)) {
    Serial.println("RA8875 Not Found!");
    while (1);
  }

  Serial.println("Found RA8875");

  tft.displayOn(true);
  tft.GPIOX(true);      // Enable TFT - display enable tied to GPIOX
  tft.PWM1config(true, RA8875_PWM_CLK_DIV1024); // PWM output for backlight
  tft.PWM1out(255);
  tft.fillScreen(RA8875_BLACK);

  /* Switch to text mode */  
  // tft.textMode();

 /*Analog reference voltage calibration */
 //analogReference(EXTERNAL); //IMPORTANT! USE FOR REFERENCE VOLTAGE! 
}
 
void loop() {
  
  tft.fillScreen(RA8875_BLACK);
  
//TEMPERATURE SENSOR READINGS

  // call sensors.requestTemperatures() to issue a global temperature 
  // request to all devices on the bus
  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.println("DONE");
  
  // After we got the temperatures, we can print them here.
  // We use the function ByIndex, and as an example get the temperature from the first sensor only.
  float panelsupplyF = sensors.getTempFByIndex(0) ;
  float panelreturnF = sensors.getTempFByIndex(1) ;
  float fauF = sensors.getTempFByIndex(2) ;
  Serial.print("Temperature for the Panel Supply is: ");
  Serial.println(panelsupplyF);
  Serial.print("Temperature for the Panel Return is: ");
  Serial.println(panelreturnF);
  Serial.print("Temperature for the FAU is: ");
  Serial.println(fauF);

 if (panelsupplyF >= thresh1) {
  char string[15] ;
  char stringOne[15] ;
  tft.textMode() ;
  tft.textTransparent(RA8875_RED) ;
  tft.textSetCursor(textSetCursorX_1, textSetCursorY_1) ;
  tft.textEnlarge(1);
  tft.textWrite("Panel supply: ") ;
  sprintf (string, "%d", panelsupplyF ) ;
  tft.textWrite(string) ;
 }
 else {
  char string[15] ;
  char stringOne[15] ;
  tft.textMode() ;
  tft.textTransparent(RA8875_WHITE) ;
  tft.textSetCursor(textSetCursorX_1, textSetCursorY_1) ;
  tft.textEnlarge(1);
  tft.textWrite("Panel supply: ") ;
  sprintf (string, "%d", panelsupplyF ) ;
  tft.textWrite(string) ;
 }


 if (panelreturnF >= thresh2) {
  char string[15] ;
  char stringOne[15] ;
  tft.textMode() ;
  tft.textTransparent(RA8875_RED) ;
  tft.textSetCursor(textSetCursorX_2, textSetCursorY_2) ;
  tft.textEnlarge(1);
  tft.textWrite("Panel return: ") ;
  sprintf (string, "%d", panelreturnF) ;
  tft.textWrite(string) ;
 }
 else {
  char string[15] ;
  char stringOne[15] ;
  tft.textMode() ;
  tft.textTransparent(RA8875_WHITE) ;
  tft.textSetCursor(textSetCursorX_2, textSetCursorY_2) ;
  tft.textEnlarge(1);
  tft.textWrite("Panel return: ") ;
  sprintf (string, "%d", panelreturnF) ;
  tft.textWrite(string) ;
 }

 /*
 //East Panel Return
 tempReading2 = analogRead(tempPin2);
 float voltage2 = tempReading2 * aref_voltage;
 voltage2 /= 1024.0;
 float temperature2C = (voltage2 - 0.5) * 100 ;
 float temperature2F = (temperature2C * 9.0 / 5.0) + 32.0;
 Serial.print("East Panel Return: "); Serial.print(temperature2F); Serial.println(" degrees F");
 
 //West Panel Return
 tempReading3 = analogRead(tempPin3);
 float voltage3 = tempReading3 * aref_voltage;
 voltage3 /= 1024.0;
 float temperature3C = (voltage3 - 0.5) * 100 ; 
 float temperature3F = (temperature3C * 9.0 / 5.0) + 32.0;
 Serial.print("West Panel Return: "); Serial.print(temperature3F); Serial.println(" degrees F");
 
 //H2O Supply
 tempReading4 = analogRead(tempPin4);
 float voltage4 = tempReading4 * aref_voltage;
 voltage4 /= 1024.0;
 float temperature4C = (voltage4 - 0.5) * 100 ; 
 float temperature4F = (temperature4C * 9.0 / 5.0) + 32.0;
 Serial.print("H2O Supply: "); Serial.print(temperature4F); Serial.println(" degrees F");
 
 //H2O Return
 tempReading5 = analogRead(tempPin5);
 float voltage5 = tempReading5 * aref_voltage;
 voltage5 /= 1024.0;
 float temperature5C = (voltage5 - 0.5) * 100 ; 
 float temperature5F = (temperature5C * 9.0 / 5.0) + 32.0;
 Serial.print("H2O Return: "); Serial.print(temperature5F); Serial.println(" degrees F");
 
  //H2O Main
 tempReading6 = analogRead(tempPin5); //CHANGE TO CORRECT PIN!
 float voltage6 = tempReading6 * aref_voltage;
 voltage6 /= 1024.0;
 float temperature6C = (voltage6 - 0.5) * 100 ; 
 float temperature6F = (temperature6C * 9.0 / 5.0) + 32.0;
 Serial.print("H2O Main: "); Serial.print(temperature6F); Serial.println(" degrees F");
 
  //FAU Supply
 tempReading7 = analogRead(tempPin5); //CHANGE TO CORRENT PIN!
 float voltage7 = tempReading7 * aref_voltage;
 voltage7 /= 1024.0;
 float temperature7C = (voltage7 - 0.5) * 100 ; 
 float temperature7F = (temperature7C * 9.0 / 5.0) + 32.0;
 Serial.print("FAU Supply: "); Serial.print(temperature7F); Serial.println(" degrees F");
 
  //FAU Return
 tempReading8 = analogRead(tempPin5); //CHANGE TO CORRENT PIN!
 float voltage8 = tempReading8 * aref_voltage;
 voltage8 /= 1024.0;
 float temperature8C = (voltage8 - 0.5) * 100 ; 
 float temperature8F = (temperature8C * 9.0 / 5.0) + 32.0;
 Serial.print("FAU Return: "); Serial.print(temperature8F); Serial.println(" degrees F");
 
//RELAY CONTROL
 //PUMP1 - NORMAL TO FAU
 
 if (temperature1F >= thresh1) {
   digitalWrite(RELAY1, HIGH);
    Serial.println("PUMP TO FAU ON NORMAL");
 }
 else {
   digitalWrite(RELAY1, LOW);
     Serial.println("pump to fau off normal");
 }
  
 //PUMP1 - HIGH TO FAU
  if (temperature2F >= thresh2) {
   digitalWrite(RELAY2, HIGH);
     Serial.println("PUMP TO FAU ON HIGH");
 }
 else {
   digitalWrite(RELAY2, LOW);
     Serial.println("pump to fau off high");
 }
  
 //PUMP2 - NORMAL TO H2O EXCHANGE
 
  if (temperature3F >= thresh3) {
   digitalWrite(RELAY3, HIGH);
     Serial.println("PUMP TO H2O EXCHANGE ON");
 }
 else {
   digitalWrite(RELAY3, LOW);
     Serial.println("pump to h2o exchange off");
 }
 
 //PUMP3 - NORMAL TO SLAB
  if (temperature4F >= thresh4) {
   digitalWrite(RELAY4, HIGH);
     Serial.println("PUMP TO SLAB ON NORMAL");
 }
 else {
   digitalWrite(RELAY4, LOW);
     Serial.println("pump to slab off normal");
 }
  
 //PUMP3 - HIGH TO SLAB
  if (temperature5F >= thresh5) {
   digitalWrite(RELAY5, HIGH);
     Serial.println("PUMP TO SLAB ON HIGH");
 }
 else {
   digitalWrite(RELAY5, LOW);
     Serial.println("pump to slab off high");
 }
*/
  delay(1000);
}
