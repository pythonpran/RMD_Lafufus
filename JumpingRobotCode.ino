#include <IRremote.hpp>

// ---------- IR ----------
#define IR_PIN 7

// IR button codes
const uint32_t BTN_MOTOR_IDLE  = 0xF30CFF00;
const uint32_t BTN_MOTOR_RUN   = 0xE718FF00;
const uint32_t BTN_STEPPER_360 = 0xA15EFF00;
const uint32_t BTN_DISENGAGE   = 0xF708FF00;

// ---------- DC MOTOR (XY-160D) ----------
const int MOTOR_IN1 = 8;
const int MOTOR_IN2 = 9;
const int MOTOR_ENA = 10;   // PWM speed control

const int MOTOR_SPEED = 200; // 0–255

// ---------- STEPPER (A4988, NEMA 11) ----------
const int STEPPER_DIR_PIN  = 3;
const int STEPPER_STEP_PIN = 4;

const int baseStepsPerRev  = 200;  // 1.8° motor
const int microstepSetting = 1;    // set to 2/4/8/16 if MS pins used
const int stepsPerRev      = baseStepsPerRev * microstepSetting;

const unsigned int stepDelayMicros = 800;

// ---------- STATE ----------
String motorStatus   = "Idle";
String engagerStatus = "Disengaged";
uint32_t buttonVal   = 0;

// ---------- STEPPER FUNCTIONS ----------
void stepperMoveSteps(int direction, int steps) {
  digitalWrite(STEPPER_DIR_PIN, (direction >= 0) ? HIGH : LOW);

  for (int i = 0; i < steps; i++) {
    digitalWrite(STEPPER_STEP_PIN, HIGH);
    delayMicroseconds(stepDelayMicros);
    digitalWrite(STEPPER_STEP_PIN, LOW);
    delayMicroseconds(stepDelayMicros);
  }
}

void rotateStepper360() {
  Serial.print("Stepper: 360 deg (");
  Serial.print(stepsPerRev);
  Serial.println(" steps)");
  stepperMoveSteps(+1, stepsPerRev);
  Serial.println("Stepper: done");
}

// ---------- MOTOR FUNCTIONS ----------
void motorStop() {
  digitalWrite(MOTOR_IN1, LOW);
  digitalWrite(MOTOR_IN2, LOW);
  analogWrite(MOTOR_ENA, 0);
}

void motorRunForward() {
  digitalWrite(MOTOR_IN1, HIGH);
  digitalWrite(MOTOR_IN2, LOW);
  analogWrite(MOTOR_ENA, MOTOR_SPEED);
}

void setup() {
  Serial.begin(9600);

  // IR
  IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);

  // DC motor
  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_IN2, OUTPUT);
  pinMode(MOTOR_ENA, OUTPUT);
  motorStop();

  // Stepper
  pinMode(STEPPER_DIR_PIN, OUTPUT);
  pinMode(STEPPER_STEP_PIN, OUTPUT);
  digitalWrite(STEPPER_DIR_PIN, LOW);
  digitalWrite(STEPPER_STEP_PIN, LOW);

  Serial.println("System ready");
}

void loop() {
  if (IrReceiver.decode()) {
    buttonVal = IrReceiver.decodedIRData.decodedRawData;

    Serial.print("IR Code: 0x");
    Serial.println(buttonVal, HEX);

    if (buttonVal == BTN_MOTOR_IDLE) {
      motorStatus = "Idle";
      motorStop();
    }
    else if (buttonVal == BTN_MOTOR_RUN) {
      motorStatus = "Run";
      motorRunForward();
    }
    else if (buttonVal == BTN_STEPPER_360) {
      engagerStatus = "Engaged";
      rotateStepper360();
    }
    else if (buttonVal == BTN_DISENGAGE) {
      engagerStatus = "Disengaged";
    }

    IrReceiver.resume();
  }

  Serial.println("Motor Status: " + motorStatus);
  Serial.println("Engager Status: " + engagerStatus);
  Serial.println("-------------------------");
  delay(500);
}
