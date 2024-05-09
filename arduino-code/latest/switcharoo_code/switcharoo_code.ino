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
void hoMaharaja();

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


//************************************
//Main Program
//************************************


void setup() {
  
  // put your setup code here, to run once:
  Serial.println(" switcharoo coming to life ... ");
  Serial.begin(9600);
  //Attach Servo motors
  AttachServos();
  AttachButton_Lights();
  //Set Initial Positions
  InitialPosition();

  Serial.println(" All components successfully initialized - switcharoo alive");
}

/*servo motor behavior
        //void moveToCoordinates(int leftRight, int upDown, int frontBack)
        //left 90 -> 180,  right -> 90 -> 0
        //up 90->0 , down 90 -> 180
        //front 90 ->0, back 90 -> 180
*/

//wrapper method to just show movement and give a green signal
void hoMaharaja(){
    moveToCoordinates(60, 80, -1); //Do nothing with the pieces. Show arm movement
    shortDelay();
    moveToCoordinates(80, 90, -1); //Do nothing with the pieces. Show arm movement
    longDelay();
    showGreenSignal();
}

void loop() {
  // put your main code here, to run repeatedly:  
    // read the state of the pushbutton value:
    switchState = digitalRead(switchButtonPin);
    //  Serial.println( switchState );
  
    if (switchState == HIGH){
      counter++;
      shortDelay();
      isPressed=true;
    }

    if (isPressed){ 
      // Serial.println( counter ); 
      if (counter == 1){
        hoMaharaja();
      }else if (counter == 2){
        hoMaharaja();        
      }else if (counter == 3){
        //First identify the object to be bad
        moveToCoordinates(60, 80, -1); //Do nothing with the pieces. Show arm movement
        shortDelay();
        moveToCoordinates(80, 90, -1); //Do nothing with the pieces. Show arm movement
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
           
        //Move piece 2 (back of face)
          //prepare claw position and pickup from source
          clawOpen();
          rotate(170);
          moveToCoordinates(-1, -1, 100); 
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
          moveToCoordinates(147, -1, -1); 
          moveToCoordinates(-1, 71, -1); 
          moveToCoordinates(-1, -1, 71); 

          clawOpen();

        //Reset arm to move it out of the way 
        moveToCoordinates(-1, -1, 110); 
        moveToCoordinates(-1, 90, -1); 
        
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

}