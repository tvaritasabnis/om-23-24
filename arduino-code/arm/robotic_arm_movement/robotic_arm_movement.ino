#include<Servo.h>

//************************************
//user defined function declarations
//************************************
void moveLeft(Servo s, int degrees); 
void moveRight(Servo s, int degrees); 
void moveUp(Servo s, int degrees); 
void moveDown(Servo s, int degrees); 
void clawOpen(Servo s, int degrees); 
void clawClose(Servo s, int degrees); 


//************************************
//user defined variables
//************************************
//up/down
Servo clawUpDown;
int clawUpDownPin=3;

//left/right
Servo clawLeftRight;
int clawLeftRightPin=4;

//wrist
Servo wristMotor;
int wristPin=5;

//claw
Servo claw;
int clawPin=6;

//switch to control the flow
int switchButtonPin=2;

int counter=0;
int switchState;  // variable for reading the pushbutton status
bool isPressed=false;

//************************************
//user defined function definitions
//************************************

/* This function is hardcoded to always close the claw.*/
void clawClose(Servo s, int degrees){
  Serial.println("Closing the claw");
  s.write(0);
}

/* This function is hardcoded to always open the claw.*/
void clawOpen(Servo s, int degrees){
  Serial.println("Opening the claw");
  s.write(180);
}


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
  clawUpDown.attach(clawUpDownPin);
  clawLeftRight.attach(clawLeftRightPin);
  wristMotor.attach(wristPin);
  claw.attach(clawPin);
  
  // initialize the pushbutton pin as an input:
  pinMode(switchButtonPin, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:  
  
  // read the state of the pushbutton value:
  switchState = digitalRead(switchButtonPin);
  //  Serial.println( switchState );
  
  if (switchState == HIGH){
    counter++;
    delay(300);
    isPressed=true;
  }
  //  Serial.println( "Press Count : " + press ); 
  //delay(300);
  if (isPressed){ 
    Serial.println( counter ); 
    if (counter == 1){
      moveLeft(clawUpDown,10);
      moveRight(clawLeftRight,10);
      moveUp(wristMotor,10);
      moveDown(claw,10);
    }else if (counter == 2){
      moveLeft(clawUpDown,40);
      moveRight(clawLeftRight,40);
      moveUp(wristMotor,40);
      moveDown(claw,40);
    }else if (counter == 3){
      moveLeft(clawUpDown,90);
      moveRight(clawLeftRight,90);
      moveUp(wristMotor,90);
      moveDown(claw,90);
    }else if (counter >= 4){
      moveLeft(clawUpDown,0);
      moveRight(clawLeftRight,0);
      moveUp(wristMotor,0);
      moveDown(claw,0);
      counter=0;
    }
    isPressed=false;
  }
}

