
const int SIDE_BOTH = 0;
const int SIDE_LEFT = 1;
const int SIDE_RIGHT = 2;

void setAsReady(){
  
  digitalWrite(LED_BUILTIN, HIGH);
}

void setup() {

  pinMode(LED_BUILTIN, OUTPUT);

  digitalWrite(LED_BUILTIN, LOW);

  ethernet_setup();

  motor_setup();
}

void loop() {

  ethernet_loop();
}
