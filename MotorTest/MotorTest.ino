// motor controller pinout
int enA = 3;
int in1 = 4;
int in2 = 5;
int in3 = 6;
int in4 = 7;
int enB = 9;


void setup() {
  // put your setup code here, to run once:
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enB, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enA, 150);  // takes a value from 0 to 255
  analogWrite(enB, 150);

}
