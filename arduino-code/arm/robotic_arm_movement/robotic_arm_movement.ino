#include<Servo.h>

//************************************
//user defined function declarations
//************************************
void moveLeftRight(int degree); 
void moveUpDown(int degree); 
void clawOpen(); 
void clawClose(); 
void rotate(int degree);
void shortDelay();
void longDelay();

//************************************
//user defined variables
//************************************

//left/right
Servo sLeftRight;
int sLeftRightPin=4;

//up/down
Servo sUpDown;
int sUpDownPin=5;


//wrist
Servo sWrist;
int sWristPin=6;

//claw
Servo sClaw;
int sClawPin=7;

//switch to control the flow
int switchButtonPin=2;

int counter=0;
int switchState;  // variable for reading the pushbutton status
bool isPressed=false;

bool isGoalAchieved=false;


//************************************
//user defined function definitions
//************************************

/* 
This function is hardcoded to always close the claw.
Claw close is the neutral position for servo motor with default angle of 93
*/
void clawClose(){
  Serial.println("Closing the claw");
  sClaw.write(95);
}

/* This function is hardcoded to always open the claw.*/
void clawOpen(){
  Serial.println(" Opening the claw ");
  sClaw.write(65);
}


void moveLeftRight(int degree){
  Serial.println("Moving Left/Right by .. " + degree);
  sLeftRight.write(degree);
}


void moveUpDown(int degree){
  Serial.println("Moving Up by .. " + degree);
  sUpDown.write(degree);
}

void rotate(int degree){
  Serial.println("Rotating by .. " + degree);
  sWrist.write(degree);
}

void shortDelay(){
  delay(300);
}

void longDelay(){
  delay(5000);
}

//************************************
//Main Program
//************************************


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  //Attach Servo motors
  sUpDown.attach(sUpDownPin);
  // sLeftRight.attach(sLeftRightPin);
   sWrist.attach(sWristPin);
  //sClaw.attach(sClawPin);

  
    // initialize the pushbutton pin as an input:
  // pinMode(switchButtonPin, INPUT);

  Serial.println(" All components successfully initialized");
}

void loop() {
  // put your main code here, to run repeatedly:  

  
  if(isGoalAchieved == false){

    Serial.println(sClaw.read());
    Serial.println(sUpDown.read());
    // longDelay();
    // clawOpen();
    // longDelay();
    // clawClose();
    longDelay();
    moveUpDown(120);
    longDelay();
    moveUpDown(80);
    longDelay();
  // sClaw.write(0);
  // delay(3000);

  // Serial.println(sClaw.read());
  // delay(3000);

  // sClaw.write(180);
  // delay(3000);
  
  // sClaw.write(90);
  // delay(3000);
    
    //counter = counter+1;
    // delay(3000);
    // clawClose(sClaw);
    // delay(3000);
    // clawOpen(sClaw);
    // delay(3000);


    // delay(3000);
    // clawClose(sClaw);
    // delay(3000);
    // clawOpen(sClaw);
    // delay(3000);


    // delay(3000);
    // clawClose(sClaw);
    // delay(3000);
    // clawOpen(sClaw);
    // delay(3000);


    // delay(3000);
    // clawClose(sClaw);
    // delay(3000);
    // clawOpen(sClaw);
    // delay(3000);
    isGoalAchieved=true;
     
    // Serial.println("Finished working on motor .. counter = " + counter);
  }else{
    isGoalAchieved=true;
    Serial.println("Finished working on motor .. Goal achieved - XXX");
  }

  
  // // read the state of the pushbutton value:
  // switchState = digitalRead(switchButtonPin);
  // //  Serial.println( switchState );
  
  // if (switchState == HIGH){
  //   counter++;
  //   delay(300);
  //   isPressed=true;
  // }
  // //  Serial.println( "Press Count : " + press ); 
  // //delay(300);
  // if (isPressed){ 
  //   Serial.println( counter ); 
  //   if (counter == 1){
  //     moveLeft(sUpDown,10);
  //     moveRight(sLeftRight,10);
  //     moveUp(wristMotor,10);
  //     moveDown(sClaw,10);
  //   }else if (counter == 2){
  //     moveLeft(sUpDown,40);
  //     moveRight(sLeftRight,40);
  //     moveUp(wristMotor,40);
  //     moveDown(sClaw,40);
  //   }else if (counter == 3){
  //     moveLeft(sUpDown,90);
  //     moveRight(sLeftRight,90);
  //     moveUp(wristMotor,90);
  //     moveDown(sClaw,90);
  //   }else if (counter >= 4){
  //     moveLeft(sUpDown,0);
  //     moveRight(sLeftRight,0);
  //     moveUp(wristMotor,0);
  //     moveDown(sClaw,0);
  //     counter=0;
  //   }
  //   isPressed=false;
  // }
}

