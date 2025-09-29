int enA = 3;
int in1 = 4;
int in2 = 5;
int in3 = 6;
int in4 = 7;
int enB = 9;
float pi = 3.14159265358979;


  //int theta = 720;
  float wheelBase = .2;
  float timeConstant = 0.00313266666; //units (m/s)/PWM
  float radius = .5;
  int baseSpeed = 150;

  

void driveCircle(float radius)
{

  float speedRatio = (wheelBase+radius)/(radius);

  int leftSpeed = (int)baseSpeed;
  int rightSpeed = (int)(baseSpeed * speedRatio);

  float time = (2*pi*(radius+(wheelBase/2)) / (timeConstant*rightSpeed));

  analogWrite(enA, abs(baseSpeed));
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enB, abs(rightSpeed));
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  Serial.println(leftSpeed);
  Serial.println(rightSpeed);

  delay(time*1000);

  analogWrite(enA, 0);
  analogWrite(enB, 0);
}

void setup() {
  // put yur setup code here, to run once:
  
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enB, OUTPUT);

  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
  driveCircle(radius);
  while(true);

}

