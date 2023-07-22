#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // LCD Display (RS,EN,D4,D5,D6,D7)
#include <SoftwareSerial.h>
 
SoftwareSerial mySerial(6,13);

#define flamePin 10 // Flame Sensor Connected To Arduino
#define buzzerPin 9 //Buzzer Connected To Arduino
#define redledPin 7
#define greenledPin 8

void setup() {
 Serial.begin(9600);
 lcd.begin(16, 2);
 mySerial.begin(9600); // Setting the baud rate of GSM Module

 pinMode(buzzerPin,OUTPUT);
 pinMode(flamePin,INPUT);
 pinMode(redledPin,OUTPUT);
 pinMode(greenledPin,OUTPUT);
  lcd.setCursor(0, 0);
  lcd.print("Calibrating");
    for(int i = 0; i <15; i++){
      if (i==4)
      {
         lcd.setCursor(0, 1);
         lcd.print(".");
        }
       else  lcd.print(".");
      delay(500);
      }
    lcd.setCursor(11, 1);
    lcd.print("Done");
    delay(1000);
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Sensor Active");
    delay(1500);
    lcd.clear();

}


void loop() {
 
int Flame = digitalRead(flamePin);

  if (Flame == LOW)
  {
     SendMessage();
     digitalWrite(buzzerPin,HIGH);
     digitalWrite(redledPin,HIGH);
     digitalWrite(greenledPin,LOW);
     lcd.setCursor(0, 0);
     lcd.print(" Flame : ");
     lcd.print("Flame");
     lcd.setCursor(0, 1);
     lcd.print("  is Detected");
     Serial.print(Flame);
     Serial.print("\t");
     Serial.print("Flame is Detected");
     Serial.println("I am in send");
     }
     
     
    
  
  else if (Flame == HIGH)
      {
     digitalWrite(buzzerPin,LOW);
     digitalWrite(redledPin,LOW);
     digitalWrite(greenledPin,HIGH);
     lcd.setCursor(0, 0);
     lcd.print("Flame : ");
     lcd.print("No Flame");
     Serial.print(Flame);
     Serial.print("\t");
     Serial.println("No Flame"); 
  
 
  delay(300);
  lcd.clear();
}
}
void SendMessage(){
     Serial.println("I am in send");
     mySerial.println("AT+CMGF=1"); //Sets the GSM Module in Text Mode
     delay( 1000);
     mySerial.println("AT+CMGS=\"+918700943235\"\r"); // Replace x with mobile number
     delay(1000);
     mySerial.println("FIRE DETECTED!!");// The SMS text you want to send
     delay(1000);
     mySerial.println((char)26);// ASCII code of CTRL+Z}}
     delay(1000);
     }
