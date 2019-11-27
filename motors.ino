
const int mot_2_a = 4;
const int mot_2_b = 5;

const int mot_3_a = 6;
const int mot_3_b = 7;

void motor_setup() {

  pinMode(mot_2_a, OUTPUT);
  pinMode(mot_2_b, OUTPUT);

  pinMode(mot_3_a, OUTPUT);
  pinMode(mot_3_b, OUTPUT);

}

void motor_stop() {

  Serial.println("MOTOR STOP");
  
  digitalWrite(mot_2_a, LOW);
  digitalWrite(mot_2_b, LOW);

  digitalWrite(mot_3_a, LOW);
  digitalWrite(mot_3_b, LOW);
}

void motor_up(int side) {

  Serial.println("MOTOR UP");
  
  digitalWrite(mot_2_a, (side == SIDE_BOTH || side == SIDE_LEFT) ? HIGH : LOW);
  digitalWrite(mot_2_b, LOW);

  digitalWrite(mot_3_a, (side == SIDE_BOTH || side == SIDE_RIGHT) ? HIGH : LOW);
  digitalWrite(mot_3_b, LOW);
}


void motor_down(int side) {

  Serial.println("MOTOR DOWN");
  
  digitalWrite(mot_2_a, LOW);
  digitalWrite(mot_2_b, (side == SIDE_BOTH || side == SIDE_LEFT) ? HIGH : LOW);

  digitalWrite(mot_3_a, LOW);
  digitalWrite(mot_3_b,  (side == SIDE_BOTH || side == SIDE_RIGHT) ? HIGH : LOW);
}

void motor_test() {

  motor_up(SIDE_BOTH);

  delay(1000);

  motor_down(SIDE_BOTH);

  delay(1000);
}
