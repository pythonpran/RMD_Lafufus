// motor controller pinout
int enA = 4;
int in1 = 5;
int in2 = 6;
int in3 = 7;
int in4 = 8;
int enB = 10;

// joystick pinout
int joystick_x = A0;
int joystick_y = A1;

void setup() {
  // put your setup code here, to run once:
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(joystick_x, INPUT);
  pinMode(joystick_y, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  // digitalWrite(in1, LOW);
  // digitalWrite(in2, HIGH);
  // digitalWrite(in3, LOW);
  // digitalWrite(in4, HIGH);
  // analogWrite(enA, 150); // takes a value from 0 to 255
  // analogWrite(enB, 150);
  // delay(20);

int x_pos = analogRead(joystick_x);
int y_pos = analogRead(joystick_y);

// Testing inputs from joystick
Serial.print("X Pos: ");
Serial.println(x_pos);

Serial.print("Y Pos: ");
Serial.println(y_pos);


}
