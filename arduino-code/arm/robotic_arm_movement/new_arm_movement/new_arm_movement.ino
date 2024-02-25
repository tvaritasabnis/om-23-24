#include<Servo.h>


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
  sClaw.write(83);
}

/* This function is hardcoded to always open the claw.*/
void clawOpen(){
  Serial.println(" Opening the claw ");
  sClaw.write(65);
}


void moveLeft(int degree){
  Serial.println("Moving Left .. " + degree);
  int pos = sLeftRight.read();
  pos += degree;
  moveServo(sLeftRight, pos);
}

void moveRight(int degree){
  Serial.println("Moving Right by .. " + degree);
  int pos = sLeftRight.read();
  pos -= degree;
  moveServo(sLeftRight, pos);
}

void moveFront(int degree){
  Serial.println("Moving Front by .. " + degree);
   int pos = sLeftRight.read();
  pos += degree;
  moveServo(sFrontBack, pos);
}

void moveBack(int degree){
  Serial.println("Moving Back by .. " + degree);
   int pos = sLeftRight.read();
  pos -= degree;
  moveServo(sFrontBack, pos);
}

void moveUp(int degree){
  Serial.println("Moving Up by .. " + degree);
  int pos = sLeftRight.read();
  pos += degree;
  moveServo(sUpDown, degree);
}

void moveDown(int degree){
  Serial.println("Moving Down by .. " + degree);
  int pos = sLeftRight.read();
  pos -= degree;
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
  sWrist.write(85);
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

void moveToHome(){
  moveServo(sLeftRight, INITIAL_POS);
  moveServo(sFrontBack, INITIAL_POS);
  moveServo(sUpDown, INITIAL_POS);
  moveServo(sWrist, 85);
  moveServo(sClaw, 85);
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

    // read the state of the pushbutton value:
    switchState = digitalRead(switchButtonPin);
    //  Serial.println( switchState );
  
    if (switchState == HIGH){
      //counter++;
      counter=3; //temp code
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
        //showRedSignal();
        //Start Desmantle work
          clawOpen();
          moveBack(10);
          moveLeft(10);
          moveUp(10);
          moveFront(10);
          clawClose();
          moveBack(10);
          moveRight(40);
          moveFront(10);
          moveDown(20);
          clawOpen();
          moveUp(20);
          moveToHome();
        //Start Assemble work

        longDelay();
        showGreenSignal();

      }else if (counter >= 4){
        //Reset
        counter=0;
      }
      isPressed=false;
    }


}

