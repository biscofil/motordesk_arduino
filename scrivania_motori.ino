
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
