#include<Servo.h>



//************************************
//user defined function declarations
//************************************
void moveLeftRight(int degree); 
void moveUpDown(int degree); 
void moveFrontBack(int degree); 
void clawOpen(); 
void clawClose(); 
void rotate(int degree);
void moveServo(Servo s, int degree);
void shortDelay();
void longDelay();

//************************************
//user defined variables
//************************************

//left/right
Servo sLeftRight;
int sLeftRightPin=4;

//front-back
Servo sFrontBack;
int sFrontBackPin=5;

//up/down
Servo sUpDown;
int sUpDownPin=6;


//wrist
Servo sWrist;
int sWristPin=7;

//claw
Servo sClaw;
int sClawPin=8;

//switch to control the flow
int switchButtonPin=2;
int greenLightPin=13;
int redLightPin=12;

int counter=0;
int switchState;  // variable for reading the pushbutton status
bool isPressed=false;
bool isGoalAchieved=false;

//Constants
int SHORT_DELAY=300;
int LONG_DELAY=5000;
int INITIAL_POS=90;
int SERVO_SPEED_DELAY=150; //15ms delay to control servo speed

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
  moveServo(sLeftRight, degree);
}

void moveFrontBack(int degree){
  Serial.println("Moving Front/Back by .. " + degree);
  moveServo(sFrontBack, degree);
}

void moveUpDown(int degree){
  Serial.println("Moving Up by .. " + degree);
  moveServo(sUpDown, degree);
}

void rotate(int degree){
  Serial.println("Rotating by .. " + degree);
    moveServo(sWrist, degree);
}

void shortDelay(){
  delay(SHORT_DELAY);
}

void longDelay(){
  delay(LONG_DELAY);
}

void AttachServos(){
  sLeftRight.attach(sLeftRightPin);
  sFrontBack.attach(sFrontBackPin);
  sUpDown.attach(sUpDownPin);
  sWrist.attach(sWristPin);
  sClaw.attach(sClawPin);
}

void AttachButton_Lights(){
  // initialize the pushbutton pin as an input:
  pinMode(switchButtonPin, INPUT);  
  //Init lights as output
  pinMode(greenLightPin, OUTPUT);
  pinMode(redLightPin, OUTPUT);
}

void InitialPosition(){
  sLeftRight.write(INITIAL_POS);
  sFrontBack.write(INITIAL_POS);
  sUpDown.write(INITIAL_POS);
  sWrist.write(INITIAL_POS);
  sClaw.write(INITIAL_POS);
}

void moveServo(Servo s, int degree){
  int pos = s.read();
 if (pos < degree){
    for(pos = pos; pos < degree; pos += 1)  // goes from 0 degrees to 180 degrees 
    {                                  // in steps of 1 degree 
      s.write(pos);              // tell servo to go to position in variable 'pos' 
      delay(SERVO_SPEED_DELAY);                       // waits 15ms for the servo to reach the position 
    } 
  }else
  {
    for(pos = pos; pos>degree; pos-=1)     // goes from 180 degrees to 0 degrees 
    {                                
      s.write(pos);              // tell servo to go to position in variable 'pos' 
      delay(SERVO_SPEED_DELAY);                       // waits 15ms for the servo to reach the position 
    }
  }
}

void readInitialPosition(){
  //Read Initial Positions
    Serial.println(sLeftRight.read());
    Serial.println(sUpDown.read());
    Serial.println(sFrontBack.read());
    Serial.println(sWrist.read());
    Serial.println(sClaw.read());
    
}

void showGreenSignal(){
  //Light HIGH
  digitalWrite(greenLightPin, HIGH);
  Serial.println( "lights ON ");
  longDelay();
  digitalWrite(greenLightPin, LOW);
}

void showRedSignal(){
  //Light HIGH
  digitalWrite(redLightPin, HIGH);
  Serial.println( "Red lights ON ");
  delay(5000);
  digitalWrite(greenLightPin, LOW);
  shortDelay();
}

void moveToCoordinates(int leftRight, int upDown, int frontBack) {
  // Move motors to specified angles for reaching coordinates
  moveLeftRight(leftRight);
  moveUpDown(upDown);
  moveFrontBack(frontBack);
  delay(1000);  // Adjust delay as needed for movement completion
}

void runDemo(){
    //Move all 10 to 170 and get back to 90 degree one by one
    moveLeftRight(10);
    shortDelay();
    moveLeftRight(170);
    shortDelay();
    moveLeftRight(80);

    moveFrontBack(85);
    shortDelay();
    moveFrontBack(95);
    shortDelay();
    moveFrontBack(90);

    moveUpDown(75);
    shortDelay();
    moveUpDown(110);
    shortDelay();
    moveUpDown(90);

    rotate(45);
    shortDelay();
    rotate(135);
    shortDelay();
    rotate(90);
}


//************************************
//Main Program
//************************************


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //Attach Servo motors
  AttachServos();
  AttachButton_Lights();
  //Set Initial Positions
  InitialPosition();

  Serial.println(" All components successfully initialized");
}

void loop() {
  // put your main code here, to run repeatedly:  

  ////####### Uncomment this to run Demo mode ######
  //if(isGoalAchieved == false){
      // readInitialPosition();
      // runDemo();
  //   isGoalAchieved=true;
  //   // Serial.println("Finished working on motor .. counter = " + counter);
  // }else{
  //   isGoalAchieved=true;
  //   Serial.println("Finished working on motor .. Goal achieved - XXX");
  //   longDelay();
  // }
  ////####### End Demo ##########################


    // read the state of the pushbutton value:
    switchState = digitalRead(switchButtonPin);
    //  Serial.println( switchState );
  
    if (switchState == HIGH){
      counter++;
      shortDelay();
      isPressed=true;
    }

    if (isPressed){ 
      Serial.println( counter ); 
     
      if (counter == 1){
        longDelay();
        showGreenSignal();
      }else if (counter == 2){
        longDelay();
        showGreenSignal();
      }else if (counter == 3){
        longDelay();
        showRedSignal();
        //Start Desmantle work
        clawOpen();
        moveToCoordinates(100, 125, 95); //Grab First piece
        clawClose();
        moveToCoordinates(20, 35, 95); //take it to drop point
        clawOpen();
        //Start Assemble work

        longDelay();
        showGreenSignal();

      }else if (counter >= 4){
        //Reset
        counter=0;
      }
      isPressed=false;
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

