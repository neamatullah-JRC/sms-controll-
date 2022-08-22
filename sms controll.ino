#include <LiquidCrystal.h>  // Include the lcd library
#include <SoftwareSerial.h> // Library for using serial communication

const byte rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);  // initialize the library with the numbers of the interface pins

SoftwareSerial gsm(9, 10);    // Pins 9 (RX), 10 (TX) are used as used as software serial pins

String incomingData = "";     // for storing incoming serial data
unsigned short ledPin = 8;
unsigned short lightOut = 11; // Initialized a pin for relay module
unsigned short fanOut = 12;
unsigned short tvOut = 13;

void setup() {
  Serial.begin(9600); // baudrate for serial monitor
  gsm.begin(9600);    // baudrate for GSM shield

  incomingData.reserve(200);

  lcd.begin(16, 2);

  
   pinMode(ledPin, OUTPUT);
  pinMode(lightOut, OUTPUT);
  pinMode(fanOut, OUTPUT);
  pinMode(tvOut, OUTPUT);

 
  digitalWrite(lightOut, LOW);
  digitalWrite(fanOut, LOW);
  digitalWrite(tvOut, LOW);

  
  lcd.print("GSM Control Home");
  lcd.setCursor(0, 1);
  lcd.print("   Automation   ");
  delay(2000);
  showInitializingMsg();
  lcd.clear();
  lcd.print("System Ready");
  delay(1000);

 
  gsm.println("AT+CMGF=1");
  delay(200);

 
  gsm.println("AT+CNMI=2,2,0,0,0");
  delay(200);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Light  Fan Motor");
  lcd.setCursor(0, 1);
  lcd.print("OFF    OFF  OFF");
}

void loop() {
  


  lcd.setCursor(0, 0);
  lcd.print("Light  Fan Motor");
  //lcd.setCursor(0, 1);
  //lcd.print("OFF    OFF  OFF");
  
//sensorState = analogRead(sensor);

//lcd.clear();
//lcd.print(sensorState); 
//delay(500);
/*
//if (sensorState <= 700) {
  lcd.clear();
   lcd.print("SMS Sending ....."); 
    digitalWrite(ledPin, HIGH);
   delay(500);
   sendMessage("Laser Sensor Active"); 
delay(10);
   
  sendMessage1("Laser Sensor Active"); 
   
  } else {
   
   digitalWrite(ledPin, LOW);
  }

*/

  //Function for receiving sms
  receiveSMS();

 if (incomingData.indexOf("On") >= 0) {
   // digitalWrite(lightOut, HIGH);
  //digitalWrite(fanOut, HIGH);
  digitalWrite(tvOut, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("ON     ");
//lcd.setCursor(8, 1);
//    lcd.print("ON   ");
  //   lcd.setCursor(13, 1);
  //  lcd.print("ON  ");
    
   sendMessage("All Load is ON");

} else if (incomingData.indexOf("Off") >= 0) {
   // digitalWrite(lightOut, LOW);
  //digitalWrite(fanOut, LOW);
  digitalWrite(tvOut, LOW);
    lcd.setCursor(0, 1);
    lcd.print("OFF    ");
//lcd.setCursor(8, 1);
//    lcd.print("OFF  ");
//lcd.setCursor(13, 1);
 //   lcd.print("OFF ");
    
    sendMessage("All Load is OFF");

    
} else if (incomingData.indexOf("light on") >= 0) {
    digitalWrite(lightOut, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("ON     ");
    sendMessage("Light is ON");
    sendMessage1("Light is ON");

  } else if (incomingData.indexOf("light off") >= 0) {
    digitalWrite(lightOut, LOW);
    lcd.setCursor(0, 1);
    lcd.print("OFF    ");
    sendMessage("Light is OFF");
     sendMessage1("Light is OFF");
    

  } else if (incomingData.indexOf("fan on") >= 0) {
    digitalWrite(fanOut, HIGH);
    lcd.setCursor(8, 1);
    lcd.print("ON   ");
    sendMessage("Insect Killer is ON");
    sendMessage1("Insect Killer is ON");

  } else if (incomingData.indexOf("fan off") >= 0) {
    digitalWrite(fanOut, LOW);
    lcd.setCursor(8, 1);
    lcd.print("OFF  ");
    sendMessage("Insect Killer is OFF");
    sendMessage1("Insect Killer is OFF");

  } else if (incomingData.indexOf("mot on") >= 0) {
    digitalWrite(tvOut, HIGH);
    lcd.setCursor(13, 1);
    lcd.print("ON  ");
    sendMessage("Motor is ON");
    sendMessage1("Motor is ON");

  } else if (incomingData.indexOf("mot off") >= 0) {
    digitalWrite(tvOut, LOW);
    lcd.setCursor(13, 1);
    lcd.print("OFF ");
    sendMessage("Motor is OFF");
     sendMessage1("Motor is OFF");
  }

  // clear the string:
  incomingData = "";
  //delay(500);
}

/*
   Function for loading animation
*/
void showInitializingMsg() {
  String msg = "Initializing";
  // Here i'm using 16x2 display. So, characters in every line is 16
  unsigned int restOfCellInLine = (16 - msg.length());
  lcd.clear();
  lcd.print(msg);

  for (int i = 0; i < restOfCellInLine; i++) {
    for (int j = 0; j < restOfCellInLine; j++) {
      lcd.print(".");
      delay(1000);
    }
    lcd.clear();
    lcd.print(msg);
  }
}

/*
   Function for receiving sms
*/
void receiveSMS() {
  while (gsm.available()) {
    incomingData = gsm.readStringUntil('\0'); // Get the data from the serial port.
    incomingData.toLowerCase();
    Serial.print(incomingData);
  }
}

/*
   Function for sending sms
*/
void sendMessage(String msg) {
  gsm.println("AT+CMGF=1");    // Set the GSM Module in Text Mode
  delay(1000);
  gsm.println("AT+CMGS=\"+8801650093726\""); // Replace it with your mobile number
  delay(1000);
  gsm.println(msg);       // The SMS text you want to send
  delay(1000);
  gsm.println((char)26);  // ASCII code of CTRL+Z
  delay(1000);
  gsm.println();
  delay(1000);
   
}

void sendMessage1(String msg) {
  gsm.println("AT+CMGF=1");    // Set the GSM Module in Text Mode
  delay(1000);
  gsm.println("AT+CMGS=\"+8801650093726\""); // Replace it with your mobile number
  delay(1000);
  gsm.println(msg);       // The SMS text you want to send
  delay(1000);
  gsm.println((char)26);  // ASCII code of CTRL+Z
  delay(1000);
  gsm.println();
  delay(1000);
  
}
