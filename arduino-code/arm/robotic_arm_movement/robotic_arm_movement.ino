#include<Servo.h>

//************************************
//user defined function declarations
//************************************
void moveLeft(Servo s, int degrees); 
void moveRight(Servo s, int degrees); 
void moveUp(Servo s, int degrees); 
void moveDown(Servo s, int degrees); 


//************************************
//user defined variables
//************************************
//up/down
Servo sMotor1;
int servoPin1=3;

//left/right
Servo sMotor2;
int servoPin2=4;

//wrist
Servo sMotor3;
int servoPin3=5;

//claw
Servo sMotor4;
int servoPin4=6;

int BUTTON_PIN=2;
int counter=0;
int buttonState;  // variable for reading the pushbutton status
bool isPressed=false;

//************************************
//user defined function definitions
//************************************

void moveLeft(Servo s, int degrees){
  Serial.println("Moving Left by .. " + degrees);
  s.write(degrees);
}

void moveRight(Servo s, int degrees){
  Serial.println("Moving Right by .. " + degrees);
  s.write(degrees);
}

void moveUp(Servo s, int degrees){
  Serial.println("Moving Up by .. " + degrees);
  s.write(degrees);
}

void moveDown(Servo s, int degrees){
  Serial.println("Moving Down by .. " + degrees);
  s.write(degrees);
}



//************************************
//Main Program
//************************************


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  //Attach Servo motors
  sMotor1.attach(servoPin1);
  sMotor2.attach(servoPin2);
  sMotor3.attach(servoPin3);
  sMotor4.attach(servoPin4);
  
  // initialize the pushbutton pin as an input:
  pinMode(BUTTON_PIN, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:  
  
  // read the state of the pushbutton value:
  buttonState = digitalRead(BUTTON_PIN);
  //  Serial.println( buttonState );
  
  if (buttonState == HIGH){
    counter++;
    delay(300);
    isPressed=true;
  }
  //  Serial.println( "Press Count : " + press ); 
  //delay(300);
  if (isPressed){ 
    Serial.println( counter ); 
    if (counter == 1){
      moveLeft(sMotor1,10);
      moveRight(sMotor2,10);
      moveUp(sMotor3,10);
      moveDown(sMotor4,10);
    }else if (counter == 2){
      moveLeft(sMotor1,40);
      moveRight(sMotor2,40);
      moveUp(sMotor3,40);
      moveDown(sMotor4,40);
    }else if (counter == 3){
      moveLeft(sMotor1,90);
      moveRight(sMotor2,90);
      moveUp(sMotor3,90);
      moveDown(sMotor4,90);
    }else if (counter >= 4){
      moveLeft(sMotor1,0);
      moveRight(sMotor2,0);
      moveUp(sMotor3,0);
      moveDown(sMotor4,0);
      counter=0;
    }
    isPressed=false;
  }
}

