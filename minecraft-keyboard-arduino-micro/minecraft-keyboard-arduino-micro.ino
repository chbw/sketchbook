// An Arduino Micro sketch which allows to controll your favourite Game
// by the push of a button. Created beacause some people are not capable of
// pressing the 'w' button on the keyboard.
// 
// Daniel Kreimer & Benjamin L. Witzerstorfer & Simon Hacker

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


