//https://www.instructables.com/id/How-to-use-the-L293D-Motor-Driver-Arduino-Tutorial/

const int motorPin1  = 5;  // Pin 14 of L293
const int motorPin2  = 6;  // Pin 10 of L293

void setup() {
  // put your setup code here, to run once:
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);

  //This code  will turn Motor A clockwise for 2 sec.
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  /*delay(2000); 
  //This code will turn Motor A counter-clockwise for 2 sec.
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  delay(2000);
  
  //This code will turn Motor B clockwise for 2 sec.
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  delay(2000); 
  //This code will turn Motor B counter-clockwise for 2 sec.
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  delay(2000);    
  
  //And this code will stop motors
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);*/
}

void loop() {
  // put your main code here, to run repeatedly:

}
