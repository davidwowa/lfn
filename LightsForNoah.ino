/*
  Night lamp for Noah

  Created 20.12.2017
  Modified 21.12.2017
  by David Zakrevskyy

  Update 27.09.2018 -> longer working time
  Update 28.09.2018 -> refactoring and stop function

  1.8e+6 = 30 min
  2.7e+6 = 45 min
  3.6e+6 = 60 min
*/

#include <Stepper.h>

const int stepsPerRevolution = 30;
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

long time1 = 60 * 150;
long time2 = 120 * 150;
long time3 = 180 * 150;

// test
//long time1 = 150;
//long time2 = 300;
//long time3 = 450; // = 20 sec -> 3 * 50 = 150 = 60 Sec

//int speed1 = 150;
//int speed2 = 350;

int run_state = 1;

int current_speed = 150;
long current_time = time1;
int current_light = 1;

int init_delay = 50;

int time_state = 0;
int light_state = 0;
int speed_state = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("init step motor");
  myStepper.setSpeed(current_speed);

  Serial.println("init leds for controll unit");
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(12, OUTPUT);

  Serial.println("init leds for lamp");
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);

  Serial.println("init pins for buttons");
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);

  Serial.println("init done");

  Serial.println("start test");

  digitalWrite(7, LOW);
  digitalWrite(12, LOW);
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);

  digitalWrite(5, HIGH);
  delay(init_delay);
  digitalWrite(5, LOW);

  digitalWrite(6, HIGH);
  delay(init_delay);
  digitalWrite(6, LOW);

  digitalWrite(7, HIGH);
  delay(init_delay);
  digitalWrite(7, LOW);
  digitalWrite(12, HIGH);
  delay(init_delay);
  digitalWrite(12, LOW);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(init_delay);
  digitalWrite(LED_BUILTIN, LOW);

  digitalWrite(5, HIGH);
  delay(init_delay);
  digitalWrite(5, LOW);

  digitalWrite(6, HIGH);
  delay(init_delay);
  digitalWrite(6, LOW);

  digitalWrite(5, HIGH);
  delay(init_delay);
  digitalWrite(5, LOW);

  digitalWrite(6, HIGH);
  delay(init_delay);
  digitalWrite(6, LOW);

  Serial.println("test end turn all leds off");
  digitalWrite(7, LOW);
  digitalWrite(12, LOW);
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
}

void loop() {

  // start and restart
  if (digitalRead(4) == HIGH) {
    if (run_state == 0) {
      run_state = 1;
      current_time = time1;
      lightON();
      motor(current_speed);
    } else if (run_state == 1) {
      run_state = 0;
      current_time = 0;
      lightOFF();
      littleLightOFF();
      motor(0);
    }
    delay(500);
  }

  // change light state
  if (digitalRead(3) == HIGH) {
    Serial.println("set light");
    if (light_state == 0) {
      light_state = 1;
      lightON();
    } else if (light_state == 1) {
      light_state = 0;
      lightOFF();
    }
    delay(500);
  }

  // change time state
  if (digitalRead(2) == HIGH) {
    Serial.println("set time");
    if (time_state == 0) {
      time_state = 1;
      current_time = time1;
      digitalWrite(7, HIGH);
      digitalWrite(12, LOW);
    }
    else if (time_state == 1) {
      time_state = 2;
      current_time = time2;
      digitalWrite(7, LOW);
      digitalWrite(12, HIGH);
    }
    else if (time_state == 2) {
      time_state = 0;
      current_time = time3;
      digitalWrite(7, HIGH);
      digitalWrite(12, HIGH);
    }
    delay(500);
  }

  // run...
  if (current_time > 0) {
    Serial.print(current_time);
    Serial.println(" s ");
    current_time--;
    myStepper.step(stepsPerRevolution);
  }
}

void littleLightOFF() {
  Serial.println("Litte LEDs OFF");
  digitalWrite(7, LOW);
  digitalWrite(12, LOW);
}

void lightON() {
  Serial.println("Big LEDs ON");
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
}

void lightOFF() {
  Serial.println("Big LEDs OFF");
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
}

void motor(int speed) {
  Serial.print("Set motor speed to ");
  Serial.println(speed);
  myStepper.setSpeed(speed);
}
