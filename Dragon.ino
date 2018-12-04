// Remember to include gadgetron libraries
#include "Dragon.h"

// const vars
const int PASSIVE_STATE = 0;
const int ATTACK_STATE = 1;
const double TAU = 2 * 3.1415;
const double DR = 360.0 / TAU;

// Figure 8
const int DRIVE_8_TIME = 5000; // Don't remember what it was
bool figureState = true;

// Oscillate between these degrees (Amplitude)
const int TAIL_MIN_DEG = 25;
const int TAIL_MAX_DEG = 32;

int tailDeg = TAIL_MIN_DEG;
int tailDir = 1; // when 1, the tail will increase

const int WING_MIN_DEG = 25;
const int WING_MAX_DEG = 32;
int wingDeg = 25;
int wingDir = 1; // when 1  , the wing will increase

// Frequency
const double TAIL_F = TAU * 1 / 3; // 1/3rd "rev" every second
const double WING_F = TAU * 1 / 4;


// Attack variables

const int A_TAIL_DEG = 0; // Set angle to this during attack state
const int A_WING_DEG = 25;
const int ATTACK_SPEED = 500;
const int ATTACK_TIME_OUT = 5000; // 3 Seconds

// Keep track of state
int state = PASSIVE_STATE;
long int last_time;
long int servo_time = 0;
long int animation_time;
long int figure_time;


void setup() {
  Serial.begin( 9600 );
  distanceSensor.setup();
  pincer.setup();
  TailServo.setup();
  HeadServo.setup();
  drive.setup();
  last_time = millis();
}

void idle_Animation() {
  double current_time = ( double ) millis();
  double wing_phase = current_time * WING_F / 1000.0;
  double tail_phase = current_time * TAIL_F / 1000.0;

  int wing_degree = ( int ) A_WING_DEG * sin( wing_phase ) * DR;
  int tail_degree = ( int ) A_TAIL_DEG * sin( tail_phase ) * DR;

  Serial.println("Currently attacking");

  // leftWingPincer.open( wing_degree );
  // rightWingPincer.open( wing_degree );
  TailServo.rotate( tail_degree );
}

void figure8Animation() {
  if (millis() > figure_time + DRIVE_8_TIME) {
    figureState = !figureState;
    figure_time = millis();
  }

  if (figureState) { // true when needing to go right

    drive.spinRight(100);
  } else {

    drive.spinLeft(100);
  }
}

void loop() {
  // Logic State Function
  switch (state) {
    case PASSIVE_STATE:
      if (distanceSensor.get_distance() > 1 && distanceSensor.get_distance() < 10) {
        state = ATTACK_STATE;
        last_time = millis();
        figure_time = millis();
        servo_time = millis();
      }
      break;
    case ATTACK_STATE:
      if (distanceSensor.get_distance() < 1 || distanceSensor.get_distance() > 10 ||
          millis() > last_time + 10000) {
        state = PASSIVE_STATE;
      }
      break;
  }


  // Actual Moving State function
  switch (state) {
    case PASSIVE_STATE:
      // figure 8 code

      figure8Animation();
      break;
    case ATTACK_STATE:
      // move forward code
      drive.forward(ATTACK_SPEED);
      
      // oscillate servo code
      if (millis() > servo_time + 500) {
        servo_time = millis();
        if (tailDeg > TAIL_MAX_DEG) {
          tailDir = -1;
        } else if (tailDeg < TAIL_MIN_DEG) {
          tailDir = 1;
        }
        if (wingDeg > WING_MAX_DEG) {
          wingDir = -1;
        } else if (wingDeg < WING_MIN_DEG) {
          wingDir = 1;
        }

        // actually modify the dirs
        tailDeg += tailDir;
        wingDeg += wingDir;

        TailServo.rotate(tailDeg);
        HeadServo.rotate(tailDeg);
        pincer.open(wingDeg);
        Serial.println("tail deg!");
        Serial.println(tailDeg);
      }

      break;

  }
}
