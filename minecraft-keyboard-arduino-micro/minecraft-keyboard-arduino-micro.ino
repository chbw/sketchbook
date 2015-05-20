const int port_num = 2;

void setup() {
  pinMode(2, INPUT_PULLUP);
  Keyboard.begin();
}


void loop() {
  // wait for falling edge on pin 9
  while(digitalRead(port_num));
  
  // send keystroke
  Keyboard.press('w');

  delay(50);
  
  Keyboard.releaseAll();
      
  // wait for rising edge on pin 9
  while(!digitalRead(port_num));

  delay(50);
}


