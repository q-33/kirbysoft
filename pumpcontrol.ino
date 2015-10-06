//////////////////////
//  KIRBYSOFT v0.6  //
//////////////////////

/*
NOTES
Need to add:
-Flow sensors
-If/then for temp / pump controls
-Temp sensors 6,7,8
*/
 
//Define the reference voltage (use multimeter on 3.3v)
#define aref_voltage 3.3 //Not yet calibrated
 
//Relay pins
#define RELAY1 2 //Pump1 Normal to FAU
#define RELAY2 3 //Pump1 High to FAU
#define RELAY3 4 //Pump2 Normal to H2O exchange
#define RELAY4 5 //Pump3 Normal to slab
#define RELAY5 6 //Pump3 High to slab
//#define RELAY6 7 //EMPTY
//#define RELAY7 8 //EMPTY
//#define RELAY8 9 //EMPTY

//Temperature thresholds for pumps
#define thresh1 80 //Threshold for normal to FAU
#define thresh2 79 //Threshold for high to FAU
#define thresh3 78 //Threshold for normal to H2O
#define thresh4 77 //Threshold for normal to slab
#define thresh5 76 //Threshold for high to slab
 
//TMP36 pins
int tempPin1 = 0; //Panel supply
int tempPin2 = 1; //East panel return
int tempPin3 = 2; //West panel return
int tempPin4 = 3; //H2O supply
int tempPin5 = 4; //H2O return
//int tempPin6 = 5; //H2O main
//int tempPin7 = 6; //FAU supply
//int tempPin8 = 7; //FAU return
 
//Initialize temperature readings
int tempReading1;
int tempReading2;
int tempReading3;
int tempReading4;
int tempReading5;
int tempReading6;
int tempReading7;
int tempReading8;
 
void setup()
{
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  pinMode(RELAY3, OUTPUT);
  pinMode(RELAY4, OUTPUT);
  pinMode(RELAY5, OUTPUT);
//  pinMode(RELAY6, OUTPUT);
//  pinMode(RELAY7, OUTPUT);
//  pinMode(RELAY8, OUTPUT);
 
  Serial.begin(9600);
 
  analogReference(EXTERNAL); //IMPORTANT! USE FOR REFERENCE VOLTAGE!
}
 
void loop() {
 
 Serial.println("*************************************");
 Serial.println("*     WELCOME TO KIRBYSOFT v0.6     *");
 Serial.println("*************************************");
 
 delay(2000);
 
 Serial.println("Hello, Kirby! Let me check the sensors...");
 
 delay(3000);
 
//TEMPERATURE SENSOR READINGS
 //Panel Supply 
 tempReading1 = analogRead(tempPin1);
 float voltage1 = tempReading1 * aref_voltage;
 voltage1 /= 1024.0;
 float temperature1C = (voltage1 - 0.5) * 100 ;
 float temperature1F = (temperature1C * 9.0 / 5.0) + 32.0;
 Serial.print("Panel Supply: "); Serial.print(temperature1F); Serial.println(" degrees F");
 delay(1000);
 
 //East Panel Return
 tempReading2 = analogRead(tempPin2);
 float voltage2 = tempReading2 * aref_voltage;
 voltage2 /= 1024.0;
 float temperature2C = (voltage2 - 0.5) * 100 ;
 float temperature2F = (temperature2C * 9.0 / 5.0) + 32.0;
 Serial.print("East Panel Return: "); Serial.print(temperature2F); Serial.println(" degrees F");
 delay(1000);
 
 //West Panel Return
 tempReading3 = analogRead(tempPin3);
 float voltage3 = tempReading3 * aref_voltage;
 voltage3 /= 1024.0;
 float temperature3C = (voltage3 - 0.5) * 100 ; 
 float temperature3F = (temperature3C * 9.0 / 5.0) + 32.0;
 Serial.print("West Panel Return: "); Serial.print(temperature3F); Serial.println(" degrees F");
 delay(1000);
 
 //H2O Supply
 tempReading4 = analogRead(tempPin4);
 float voltage4 = tempReading4 * aref_voltage;
 voltage4 /= 1024.0;
 float temperature4C = (voltage4 - 0.5) * 100 ; 
 float temperature4F = (temperature4C * 9.0 / 5.0) + 32.0;
 Serial.print("H2O Supply: "); Serial.print(temperature4F); Serial.println(" degrees F");
 delay(1000);
 
 //H2O Return
 tempReading5 = analogRead(tempPin5);
 float voltage5 = tempReading5 * aref_voltage;
 voltage5 /= 1024.0;
 float temperature5C = (voltage5 - 0.5) * 100 ; 
 float temperature5F = (temperature5C * 9.0 / 5.0) + 32.0;
 Serial.print("H2O Return: "); Serial.print(temperature5F); Serial.println(" degrees F");
 delay(500);
 
  //H2O Main
 tempReading6 = analogRead(tempPin5); //CHANGE TO CORRECT PIN!
 float voltage6 = tempReading6 * aref_voltage;
 voltage6 /= 1024.0;
 float temperature6C = (voltage6 - 0.5) * 100 ; 
 float temperature6F = (temperature6C * 9.0 / 5.0) + 32.0;
 Serial.print("H2O Main: "); Serial.print(temperature6F); Serial.println(" degrees F");
 delay(500);
 
  //FAU Supply
 tempReading7 = analogRead(tempPin5); //CHANGE TO CORRENT PIN!
 float voltage7 = tempReading7 * aref_voltage;
 voltage7 /= 1024.0;
 float temperature7C = (voltage7 - 0.5) * 100 ; 
 float temperature7F = (temperature7C * 9.0 / 5.0) + 32.0;
 Serial.print("FAU Supply: "); Serial.print(temperature7F); Serial.println(" degrees F");
 delay(500);
 
  //FAU Return
 tempReading8 = analogRead(tempPin5); //CHANGE TO CORRENT PIN!
 float voltage8 = tempReading8 * aref_voltage;
 voltage8 /= 1024.0;
 float temperature8C = (voltage8 - 0.5) * 100 ; 
 float temperature8F = (temperature8C * 9.0 / 5.0) + 32.0;
 Serial.print("FAU Return: "); Serial.print(temperature8F); Serial.println(" degrees F");
 delay(500);
 
 Serial.println("Done.");
 delay(3000);

 Serial.println("Now, let me adjust the pumps...");
 delay(3000);
 
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
 
 delay(1000);
 
 //PUMP1 - HIGH TO FAU
  if (temperature2F >= thresh2) {
   digitalWrite(RELAY2, HIGH);
     Serial.println("PUMP TO FAU ON HIGH");
 }
 else {
   digitalWrite(RELAY2, LOW);
     Serial.println("pump to fau off high");
 }
 
  delay(1000);
 
 //PUMP2 - NORMAL TO H2O EXCHANGE
 
  if (temperature3F >= thresh3) {
   digitalWrite(RELAY3, HIGH);
     Serial.println("PUMP TO H2O EXCHANGE ON");
 }
 else {
   digitalWrite(RELAY3, LOW);
     Serial.println("pump to h2o exchange off");
 }

  delay(1000);
 
 //PUMP3 - NORMAL TO SLAB
  if (temperature4F >= thresh4) {
   digitalWrite(RELAY4, HIGH);
     Serial.println("PUMP TO SLAB ON NORMAL");
 }
 else {
   digitalWrite(RELAY4, LOW);
     Serial.println("pump to slab off normal");
 }
 
  delay(1000);
 
 //PUMP3 - HIGH TO SLAB
  if (temperature5F >= thresh5) {
   digitalWrite(RELAY5, HIGH);
     Serial.println("PUMP TO SLAB ON HIGH");
 }
 else {
   digitalWrite(RELAY5, LOW);
     Serial.println("pump to slab off high");
 }
 
  delay(1000);
  
  Serial.println("Done.");
  delay(3000);
 
//Kill time between runs
 Serial.println("Give me a moment to catch my breath.");
 delay(5000);
 Serial.println("Restarting in...");
 delay(500);
 Serial.println("5");
 delay(1000);
 Serial.println("4");
 delay(1000);
 Serial.println("3");
 delay(1000);
 Serial.println("2");
 delay(1000);
 Serial.println("1");
 delay(1000);
 Serial.println("restart");
 delay(500);
}
