const int mot_1_a = 2;
const int mot_1_b = 3;

const int mot_2_a = 4;
const int mot_2_b = 5;

const int mot_3_a = 6;
const int mot_3_b = 7;

const int mot_4_a = 8;
const int mot_4_b = 9;

void motor_setup() {

  pinMode(mot_1_a, OUTPUT);
  pinMode(mot_1_b, OUTPUT);

  pinMode(mot_2_a, OUTPUT);
  pinMode(mot_2_b, OUTPUT);

  pinMode(mot_3_a, OUTPUT);
  pinMode(mot_3_b, OUTPUT);

  pinMode(mot_4_a, OUTPUT);
  pinMode(mot_4_b, OUTPUT);

}


void motor_up() {

  digitalWrite(mot_2_a, HIGH);
  digitalWrite(mot_2_b, LOW);
  digitalWrite(mot_3_a, HIGH);
  digitalWrite(mot_3_b, LOW);

  delay(1000);

  digitalWrite(mot_2_a, LOW);
  digitalWrite(mot_2_b, LOW);
  digitalWrite(mot_3_a, LOW);
  digitalWrite(mot_3_b, LOW);
}



void motor_down() {

  digitalWrite(mot_2_a, LOW);
  digitalWrite(mot_2_b, HIGH);
  digitalWrite(mot_3_a, LOW);
  digitalWrite(mot_3_b, HIGH);

  delay(1000);

  digitalWrite(mot_2_a, LOW);
  digitalWrite(mot_2_b, LOW);
  digitalWrite(mot_3_a, LOW);
  digitalWrite(mot_3_b, LOW);

}

void motor_test() {

  motor_up();

  delay(1000);

  motor_down();

  delay(1000);
}
