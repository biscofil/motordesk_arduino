
const int SIDE_BOTH = 0;
const int SIDE_LEFT = 1;
const int SIDE_RIGHT = 2;

const int DELAY_TIMEOUT = 1000;

int loops_without_requests = 0;
// DEBUG int count_without_requests = 0;

void resetRequestDelayCount() {

  loops_without_requests = 0;

  // DEBUG Serial.println("TIMEOUT RESET");
}

void setAsReady() {

  digitalWrite(LED_BUILTIN, HIGH);
}

void setup() {

  // DEBUG Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);

  digitalWrite(LED_BUILTIN, LOW);

  ethernet_setup();

  motor_setup();
}

void loop() {

  loops_without_requests ++;
  // DEBUG count_without_requests ++;

  ethernet_loop();

  if (loops_without_requests > DELAY_TIMEOUT) {

    // DEBUG Serial.println("TIMEOUT REACHED");

    motor_stop();

    resetRequestDelayCount();

  }

  delay(1); // necessary for my system
}
