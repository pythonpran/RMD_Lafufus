// motor controller pinout
int enA = 3;
int in1 = 4;
int in2 = 5;
int in3 = 6;
int in4 = 7;
int enB = 9;

// left motor
int state_1 = LOW;
int state_2 = HIGH;
// right motor
int state_3 = HIGH;
int state_4 = LOW;

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
  return j;
}

void debuggingFunction(int x_pos, int y_pos, int hypotenuse, float theta, float x, float y, int left_power, int right_power){
  Serial.print("x_pos: "); Serial.println(x_pos);
  Serial.print("y_pos: "); Serial.println(y_pos);
  Serial.print("hypotenuse: "); Serial.println(hypotenuse);
  Serial.print("theta: "); Serial.println(theta);
  Serial.print("x: "); Serial.println(x);
  Serial.print("y: "); Serial.println(y);
  Serial.print("left_power: "); Serial.println(left_power);
  Serial.print("right_power: "); Serial.println(right_power);
  Serial.println("States and the Power (1 - 4)" + String(state_1) + " " + String(state_2) + " " + String(state_3) + " " + String(state_4));
  delay(1000);
}


void setup() {
  Serial.begin(19200);
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
  Serial.println("start");
  joystickInputs joystick = getInputs();

  // Adjusting Velocity Range of Both Motors to be in between -512 to 512
  long x_pos = joystick.x_pos - 512;
  x_pos = -x_pos;
  long y_pos = joystick.y_pos - 512;

  // error removal: removes small deviations in x and y axis
  if(abs(x_pos) < 10){
    x_pos = 0;
  }
  if(abs(y_pos) < 10){
    y_pos = 0;
  }

  Serial.println(x_pos);
  Serial.println(y_pos);

  // hypotenuse of the x and y position on the joystick
  int hypotenuse = sqrt(sq(x_pos) + sq(y_pos));


  // taking the rectangle boundary of the joystick and converting it to circular boundary
  hypotenuse = min(511, hypotenuse);

  // angle of the right triangle formed by x and y position
  float theta;
  if(x_pos == 0 & y_pos == 0){
    theta = 0;
  }else{
    theta = atan2((y_pos * 1.0),(x_pos * 1.0));
  }
  Serial.println(theta);
  // This is finding the amount of x state (turning) and the amount of y state (forward and backward) in the system
  // i.e. allows for interpolation by using a percentage of the states based on the angle in the unit circle
  float x = cos(theta) / (abs(sin(theta)) + abs(cos(theta)));
  float y = sin(theta) / (abs(sin(theta)) + abs(cos(theta)));

  // applying both states and scaling to match power applied
  int left_power = round( (y + x) * (hypotenuse / 2) );
  int right_power = round( (y - x) * (hypotenuse / 2) );

  // setting direction based on power assigned
  if(left_power > 0){
    state_1 = LOW;
  }else{
    state_1 = HIGH;
  }
  state_2 = !state_1;

  if(right_power > 0){
    state_3 = HIGH;
  }else{
    state_3 = LOW;
  }
  state_4 = !state_3;


  digitalWrite(in1, state_1);
  digitalWrite(in2, state_2);
  digitalWrite(in3, state_3);
  digitalWrite(in4, state_4);
  analogWrite(enA, abs(left_power)); // takes a value from 0 to 255
  analogWrite(enB, abs(right_power));

  // debuggingFunction(x_pos, y_pos, hypotenuse, theta, x, y, left_power, right_power);

}
