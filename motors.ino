
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


void motor_up(int side) {

  if (side == SIDE_BOTH || side == SIDE_LEFT) {
    digitalWrite(mot_2_a, HIGH);
    digitalWrite(mot_2_b, LOW);
  }
  if (side == SIDE_BOTH || side == SIDE_RIGHT) {
    digitalWrite(mot_3_a, HIGH);
    digitalWrite(mot_3_b, LOW);
  }

  delay(1000);

  digitalWrite(mot_2_a, LOW);
  digitalWrite(mot_2_b, LOW);
  digitalWrite(mot_3_a, LOW);
  digitalWrite(mot_3_b, LOW);
}



void motor_down(int side) {

  if (side == SIDE_BOTH || side == SIDE_LEFT) {
    digitalWrite(mot_2_a, LOW);
    digitalWrite(mot_2_b, HIGH);
  }
  if (side == SIDE_BOTH || side == SIDE_RIGHT) {
    digitalWrite(mot_3_a, LOW);
    digitalWrite(mot_3_b, HIGH);
  }

  delay(1000);

  digitalWrite(mot_2_a, LOW);
  digitalWrite(mot_2_b, LOW);
  digitalWrite(mot_3_a, LOW);
  digitalWrite(mot_3_b, LOW);

}

void motor_test() {

  motor_up(SIDE_BOTH);

  delay(1000);

  motor_down(SIDE_BOTH);

  delay(1000);
}
