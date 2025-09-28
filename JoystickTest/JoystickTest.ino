// joystick pinout
int joystick_x = A0;
int joystick_y = A1;

struct joystickInputs {
  int x_pos;
  int y_pos;
};

joystickInputs getInputs() {
  joystickInputs j;
  j.x_pos = analogRead(joystick_x);
  j.y_pos = analogRead(joystick_y);

  // Testing inputs from joystick
  Serial.print("X Pos: ");
  Serial.println(j.x_pos);

  Serial.print("Y Pos: ");
  Serial.println(j.y_pos);
  delay(100);

  return j;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(joystick_x, INPUT);
  pinMode(joystick_y, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  joystickInputs joystick = getInputs();
}
