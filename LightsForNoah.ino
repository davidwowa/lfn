/*
  Night lamp for Noah

  Created 20.12.2017
  Modified 21.12.2017
  by David Zakrevskyy

  1.8e+6 = 30 min
  2.7e+6 = 45 min
  3.6e+6 = 60 min
*/

#include <Stepper.h>

const int stepsPerRevolution = 30;
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

int time1 = 30 * 60;
int time2 = 45 * 60;
int time3 = 60 * 60;

// for test
//int time1 = 20;
//int time2 = 30;
//int time3 = 40;

int speed1 = 100;
int speed2 = 300;
int speed3 = 600;

int current_speed = speed1;
int current_time = time1;
int current_light = 0;

int init_delay = 50;

int time_button = 0;
int light_button = 0;
int speed_button = 0;

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
  if (current_time >= 0) {
    Serial.print(current_time);
    Serial.println(" s ");
    current_time--;

    int current_light_button = digitalRead(3);
    int current_speed_button = digitalRead(4);

    // light
    if (current_light_button == HIGH) {
      Serial.println("set light");
      if (light_button == 0) {
        light_button = 1;
      }
      else if (light_button == 1) {
        light_button = 2;
      }
      else if (light_button == 2) {
        light_button = 0;
      } else {
        Serial.println("error on light button");
        digitalWrite(LED_BUILTIN, HIGH);
        delay(init_delay);
        digitalWrite(LED_BUILTIN, LOW);
      }
    }

    if (light_button == 0) {
      digitalWrite(5, HIGH);
      digitalWrite(6, HIGH);
    }
    else if (light_button == 1) {
      digitalWrite(5, HIGH);
      digitalWrite(6, LOW);
    }
    else if (light_button == 2) {
      digitalWrite(5, LOW);
      digitalWrite(6, HIGH);
    } else {
      Serial.println("error on light setting");
      digitalWrite(LED_BUILTIN, HIGH);
      delay(init_delay);
      digitalWrite(LED_BUILTIN, LOW);
    }

    // speed
    if (current_speed_button == HIGH) {
      Serial.println("set speed");
      if (speed_button == 0) {
        speed_button = 1;
      }
      else if (speed_button == 1) {
        speed_button = 2;
      }
      else if (speed_button == 2) {
        speed_button = 0;
      } else {
        Serial.println("error on speed button");
        digitalWrite(LED_BUILTIN, HIGH);
        delay(init_delay);
        digitalWrite(LED_BUILTIN, LOW);
      }
    }

    if (speed_button == 0) {
      myStepper.setSpeed(speed1);
    }
    else if (speed_button == 1) {
      myStepper.setSpeed(speed2);
    }
    else if (speed_button == 2) {
      myStepper.setSpeed(speed3);
    } else {
      Serial.println("error on speed setting");
      digitalWrite(LED_BUILTIN, HIGH);
      delay(init_delay);
      digitalWrite(LED_BUILTIN, LOW);
    }
    myStepper.step(stepsPerRevolution);
  } else {
    digitalWrite(7, LOW);
    digitalWrite(12, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    myStepper.setSpeed(0);
  }

  int current_time_button = digitalRead(2);
  // time
  if (current_time_button == HIGH) {
    Serial.println("set time");
    if (time_button == 0) {
      time_button = 1;
      current_time = time2;
    }
    else if (time_button == 1) {
      time_button = 2;
      current_time = time3;
    }
    else if (time_button == 2) {
      time_button = 0;
      current_time = time1;
    } else {
      Serial.println("error on time button");
      current_time = 0;
      digitalWrite(LED_BUILTIN, HIGH);
      delay(init_delay);
      digitalWrite(LED_BUILTIN, LOW);
    }
  }

  if (time_button == 0) {
    digitalWrite(7, LOW);
    digitalWrite(12, LOW);
  }
  else if (time_button == 1) {
    digitalWrite(7, LOW);
    digitalWrite(12, HIGH);
  }
  else if (time_button == 2) {
    digitalWrite(7, HIGH);
    digitalWrite(12, LOW);
  }
  else {
    Serial.println("error on time set");
    digitalWrite(LED_BUILTIN, HIGH);
    delay(init_delay);
    digitalWrite(LED_BUILTIN, LOW);
  }
}
