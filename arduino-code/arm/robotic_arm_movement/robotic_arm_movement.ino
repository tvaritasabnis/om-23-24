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
//Shoulder Servo Motors and their corresponding pin location 
Servo shoulderMotor1;
Servo shoulderMotor2;
int shoulderPin1=3;
int shoulderPin2=4;

//Shoulder Arm Motors and their corresponding pin location 
Servo armMotor1;
Servo armMotor2;
int armPin1=5;
int armPin2=6;

//Shoulder wrist Motors and their corresponding pin location 
Servo wristMotor1;
Servo wristMotor2;
int wristPin1=7;
int wristPin2=8;

//Shoulder claw Motors and their corresponding pin location 
Servo clawMotor1;
Servo clawMotor2;
int clawPin1=9;
int clawPin2=10;



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





void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  //Attach Servo motors
  shoulderMotor1.attach(shoulderPin1);
  shoulderMotor2.attach(shoulderPin2);

  armMotor1.attach(armPin1);
  armMotor2.attach(armPin2);

  wristMotor1.attach(wristPin1);
  wristMotor2.attach(wristPin2);
  
  clawMotor1.attach(clawPin1);
  clawMotor2.attach(clawPin2);

}

void loop() {
  // put your main code here, to run repeatedly:  
  moveLeft(shoulderMotor1,10);
  moveRight(shoulderMotor2,20);
  
  moveUp(armMotor1,30);
  moveDown(armMotor1,40);
  
  moveLeft(wristMotor1,50);
  moveRight(wristMotor2,60);
  
  moveUp(clawMotor1,70);
  moveDown(clawMotor1,80);
  
}

