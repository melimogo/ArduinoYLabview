#include <LiquidCrystal.h> //invocar libreria

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);// 
int temperatura = 0;
int pinTemp = 0;
int pinLed = 13;
float t = 0;

//meli, masmi ♥

void setup() 
   {
       Serial.begin(9600);
       pinMode(pinLed,OUTPUT);
       pinMode(pinTemp,INPUT);
       lcd.begin(16, 2);           // Fijamos el numero de caracteres y filas 
       //lcd.print(" <3 Sebis y Melii");  // Aqi va el mensaje
   }

void loop()
   {
       //lcd.clear();
       lcd.setCursor(6, 1);
       temperatura = analogRead(pinTemp);
       t = (temperatura * 100.0 * 5.0 ) / 1024;
       Serial.println(t);
       String s = String(t) ;
       lcd.print(s) ;
       if(t > 25){
          digitalWrite(pinLed,HIGH);
          delay(500);
       }else{
          digitalWrite(pinLed,LOW);
          delay(500);
       }
       //lcd.setCursor(6, 1);    // Ponte en la line 1, posicion 6
   }
String reloj()
   {
       int n = millis() / 1000 ;       // Lo pasamos a segundos
       int segundos = n % 60  ;
       int minutos =  n / 60  ;

       String S = String(minutos) + ":" + String(segundos);
       return (S);
   }
