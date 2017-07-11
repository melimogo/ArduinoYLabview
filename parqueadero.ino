#include<Servo.h>
#include <LiquidCrystal.h>
int pinServo = 22;
Servo servo;

#define UP  0
#define MEDIUM  1
#define BAD  2
int state;
int in1;
int in2;
int pinIN1 = 8;
int pinIN2 = 3;

LiquidCrystal lcd(12,11,10,9,8,7);

int secureStateUP ;
int secureStateMEDIUM;
int secureStateBAD;
int pinSecureStateUP = 6;
int pinSecureStateMEDIUM = 5;
int punSecureStateBAD = 4;
int SecureStateBAD;

int pinPull1=53;
int pinPull2=49;
int pul1;
int pul2;

boolean ending  = false;
int numCars = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pinIN1,INPUT);
  pinMode(pinIN2,INPUT);
  pinMode(pinSecureStateUP,INPUT);
  pinMode(pinSecureStateMEDIUM,INPUT);
  pinMode(punSecureStateBAD,INPUT);

  pinMode(pinPull1,INPUT);
  pinMode(pinPull2,INPUT);
  servo.attach(pinServo);
  moveServo(40);
  delay(500);
  state = MEDIUM;
  lcd.begin(16,2);
  writeLcd();
}

void loop() {
  /*servo.write(20);
  int valor = digitalRead(6);
  Serial.print("value: ");
  Serial.println(valor);
  //40 mitad
  //20 abajo
  //65 arriba
  // put your main code here, to run repeatedly:*/
  in1 = digitalRead(pinIN1);
  in2 = digitalRead(pinIN2);
  pul1 = digitalRead(pinPull1);
  Serial.print("in2: ");
  Serial.println(in1);
  
  //Serial.print("value: ");
  //Serial.println(pul2);
  
  if(pul1 == 1){
      state = BAD;
    }
 
  switch(state){
    case UP:
    if(in1 == 0 && in2 == 1){
      ending = true;
      
    }
    if(ending == true && in1 == 0 && in2 == 0){
      if(closeDoor()== true){
        state = MEDIUM;
        ending = false;
      }
      
    }
    break;
    case MEDIUM:
    if(in1 == 1 && in2 == 0){
      
      if(openDoor() == true){
        state = UP;
      }
    }
    break;
    case BAD:
    error();
    pul2 = digitalRead(pinPull2);
    if(pul2 == 1){
      lcd.clear();
      writeLcd();
      moveServo(40);
      state = MEDIUM;
      writeMessageInSerial("Error Solucionado");
    }
    break;
  }

}



boolean openDoor(){
  moveServo(65);
  delay(300);
  //Serial.println(secureStateUP);
  secureStateUP = digitalRead(pinSecureStateUP);
  Serial.println(secureStateUP);
  if(secureStateUP == 0){
    //Puerta abierta
    writeMessageInSerial("Puerta Abierta");
    lcd.setCursor(2,0);
    lcd.print("Veh. Puerta");  
    return true;
  }else{
    //La puerta no se abrio correctamente
    writeMessageInSerial("La puerta no se abrio correctamente");
    return false;
  }
}
boolean closeDoor(){
  moveServo(40);
  delay(300);
  secureStateMEDIUM = digitalRead(pinSecureStateMEDIUM);
  if(secureStateMEDIUM == 0){
    numCars = numCars + 1;
    lcd.clear();
    writeLcd();
    writeMessageInSerial("Puerta cerrada correctamente");
    //state = MEDIUM;
    return true;
  }else{
    writeMessageInSerial("La puerta no se cerro correctamente");
    return false;
  }
  
}

void error(){
  moveServo(20);
  delay(300);
  SecureStateBAD = digitalRead(punSecureStateBAD);
  if(SecureStateBAD == 0){    
    writeMessageInSerial("Hay un problema mecanico");
    lcd.clear();
    lcd.setCursor(2,0);lcd.print("Falla mecanica");
    writeLcd();
  }
  
}

void writeLcd(){
  lcd.setCursor(0,1);lcd.print("No. Vehiculos");
  lcd.setCursor(14,1);lcd.print(numCars);
}

void moveServo(int angle){
  servo.write(angle);
}
void writeMessageInSerial(String message){
  Serial.println(message);
}
