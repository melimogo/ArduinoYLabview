#include <Keypad.h>
#define s0 0
#define s1 1
#define s2 2
#define s3 3
#define s4 4

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
const String psw = "0258";   
char keys[ROWS][COLS] = {
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'*','0','#', 'D'}
};
char num[10]={'0','1','2','3','4','5','6','7','8','9'};
byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {9, 8, 7, 6}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

String password= "";
char key;
int estado=s0;
//char clave[5];
int cont=0;

void setup(){
  Serial.begin(9600);
  pinMode(13,OUTPUT);
}


void loop(){
  char key = keypad.getKey();
  Serial.println(key);
  
  if (key != NO_KEY){
      switch(estado){
        case s0:
          if(key == '*'){
            estado = s1;
          }
        break;
        case s1:
        if (Number(key)== true){
          password = password + String(key);
          cont=cont+1;
          estado = s2;
        }           
        break;
        case s2:
        if (Number(key)==true){
          password = password + String(key);
          cont=cont+1;
          estado = s3;
        }          
        break;
        case s3:
        if (Number(key)==true){
          password = password + String(key);
          cont=cont+1;
          estado = s4;
        }          
        break;
        case s4:
        if (Number(key)!=true){
          password = password + String(key);
           Serial.println(password);  
           if (password.equals(psw))
           {
              Serial.println("BIENVENIDOS BB's");
              digitalWrite(13,HIGH);
           }            
        }
       break;      

    }
  }
}

boolean Number(key){
  int b = 0;
  for i=0;i<11;i++{
    if (key != num(i)){
                 
    }else{
      b=1;      
    }
  }
  return true;
  cont=0;
  estado = s0;
  password = "";     
}


