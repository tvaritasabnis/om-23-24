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
int LONG_DELAY=1000;
int INITIAL_POS=90;
int SERVO_SPEED_DELAY=70; //delay to control servo speed

//************************************
//user defined function definitions
//************************************

/* 
This function is hardcoded to always close the claw.
Claw close is the neutral position for servo motor with default angle of 93
*/
void clawClose(){
  Serial.println("Closing the claw");
  moveServo(sClaw, 90);
  longDelay();
}

/* This function is hardcoded to always open the claw.*/
void clawOpen(){
  Serial.println(" Opening the claw ");
  moveServo(sClaw, 50);
  shortDelay();
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
void lightBlinkDelay(){
  delay(1000);
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
  moveServo(sLeftRight, INITIAL_POS);
  moveServo(sFrontBack, 95);
  moveServo(sUpDown, 85);
  moveServo(sWrist, 85);
  moveServo(sClaw, 50);
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
  Serial.println( "Green lights ON ");
  digitalWrite(greenLightPin, HIGH);
  lightBlinkDelay();
  digitalWrite(greenLightPin, LOW);
  lightBlinkDelay();
  // digitalWrite(greenLightPin, HIGH);
  // lightBlinkDelay();
  // digitalWrite(greenLightPin, LOW);
  // lightBlinkDelay();
  // digitalWrite(greenLightPin, HIGH);
  // lightBlinkDelay();
  // digitalWrite(greenLightPin, LOW);
  // lightBlinkDelay();
  digitalWrite(greenLightPin, HIGH);
  longDelay();
  digitalWrite(greenLightPin, LOW);
  lightBlinkDelay();
}

void showRedSignal(){
  //Light HIGH
  Serial.println( "Red lights ON ");
  digitalWrite(redLightPin, HIGH);
  lightBlinkDelay();
  digitalWrite(redLightPin, LOW);
  lightBlinkDelay();
  // digitalWrite(redLightPin, HIGH);
  // lightBlinkDelay();
  // digitalWrite(redLightPin, LOW);
  // lightBlinkDelay();
  // digitalWrite(redLightPin, HIGH);
  // lightBlinkDelay();
  // digitalWrite(redLightPin, LOW);
  // lightBlinkDelay();
  digitalWrite(redLightPin, HIGH);
  longDelay();
  digitalWrite(redLightPin, LOW);
  lightBlinkDelay();
  }

void moveToCoordinates(int leftRight, int upDown, int frontBack) {
  // Move motors to specified angles for reaching coordinates
  if (leftRight != -1) moveLeftRight(leftRight);
  shortDelay();
  if (upDown != -1) moveUpDown(upDown);
  shortDelay();
  if (frontBack != -1) moveFrontBack(frontBack);
  shortDelay();
  //delay(500);  // Adjust delay as needed for movement completion
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

/*servo motor behavior
        //void moveToCoordinates(int leftRight, int upDown, int frontBack)
        //left 90 -> 180,  right -> 90 -> 0
        //up 90->0 , down 90 -> 180
        //front 90 ->0, back 90 -> 180
*/
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
      // counter=3; //temp code
      shortDelay();
      isPressed=true;
    }

    if (isPressed){ 

      // Serial.println( counter ); 
      if (counter == 1){
        moveToCoordinates(60, 80, -1); //Do nothing with the pieces. Show arm movement
        shortDelay();
        moveToCoordinates(80, 90, -1); //Do nothing with the pieces. Show arm movement
        longDelay();
        showGreenSignal();
      }else if (counter == 2){
        moveToCoordinates(60, 80, -1); //Do nothing with the pieces. Show arm movement
        shortDelay();
        moveToCoordinates(80, 90, -1); //Do nothing with the pieces. Show arm movement
        longDelay();
        showGreenSignal();
        moveToCoordinates(-1, -1, 110); //Do nothing with the pieces. Show arm movement

      }else if (counter == 3){

        //First identify the object to be bad
        moveToCoordinates(100, 80, 100); //Do nothing with the pieces. Show arm movement
        shortDelay();
        moveToCoordinates(90, 90, 90); //Do nothing with the pieces. Show arm movement
        longDelay();
        showRedSignal();
        longDelay();


       //Now start fixing (disassemble and reassemble) the object
       //Move piece 1 (cap piece)
      
          //prepare claw position and pickup from source
          clawOpen();          
          rotate(175);          
          moveToCoordinates(-1, -1, 100); 
          moveToCoordinates(-1, 66, -1); 
          moveToCoordinates(55, -1, -1); 
          moveToCoordinates(-1, -1, 78); 
          clawClose();
  
          // //move piece to destination 
           moveToCoordinates(-1, 60, -1);            
           moveToCoordinates(-1, -1, 95); 
           moveToCoordinates(165, -1, -1); 
          //  rotate(0);
           moveToCoordinates(-1, 110, -1); 
          //  moveToCoordinates(-1, -1, 80); 
           clawOpen();
           moveToCoordinates(-1, -1, 110); //dont go 
           moveToCoordinates(-1, 85, -1); 
           moveToCoordinates(-1, -1, 83); 
           moveToCoordinates(-1, 105, -1); 
           
           //move the claw out of the way 
           moveToCoordinates(-1, 90, -1); 
           moveToCoordinates(-1, -1, 120); 
           
        //InitialPosition(); // consider removing this - to optimize the code

        //Move piece 2 (back of face)
          //prepare claw position and pickup from source
          clawOpen();
          rotate(170);
          moveToCoordinates(-1, -1, 100); 
          //moveToCoordinates(-1, 90, -1); 
          moveToCoordinates(34, -1, -1); 
          moveToCoordinates(-1, 100, -1); 
          moveToCoordinates(-1, -1, 83); 
          clawClose();

          //move piece to destination 
          moveToCoordinates(-1, -1, 115); 
          moveToCoordinates(-1, 80, -1); 
          rotate(0);
          moveToCoordinates(175, -1, -1); 
          moveToCoordinates(-1, 73, -1); 
          moveToCoordinates(-1, -1, 80); 
          clawOpen();

        //Reset arm to move it out of the way 
        moveToCoordinates(-1, -1, 117); 
        moveToCoordinates(-1, 113, -1); 
        moveToCoordinates(110, -1, -1); 
        //rotate(90);
        // InitialPosition();
      
      //Move front face piece # 3 
          //prepare claw position and pickup from source
          clawOpen();          
          rotate(175);
          
          moveToCoordinates(-1, -1, 110); 
          moveToCoordinates(-1, 84, -1);  
          moveToCoordinates(60, -1, -1); 
          moveToCoordinates(-1, -1, 87); 
          moveToCoordinates(-1, 103, -1);
          clawClose();

          //move piece to destination 
          moveToCoordinates(-1, -1, 110); 
          moveToCoordinates(-1, 90, -1); 
          rotate(0);
          moveToCoordinates(142, -1, -1); 
          moveToCoordinates(-1, 71, -1); 
          moveToCoordinates(-1, -1, 71); 

          clawOpen();

        //Reset arm to move it out of the way 
        moveToCoordinates(-1, -1, 110); 
        moveToCoordinates(-1, 90, -1); 
        // moveToCoordinates(90, -1, -1); 
        // rotate(90);

        // InitialPosition();

        //Go back to initial position 
        longDelay();
        InitialPosition();
        //mark the object to be good
        showGreenSignal();
       
      } else if (counter >= 4){
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