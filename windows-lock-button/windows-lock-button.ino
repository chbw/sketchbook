// An Arduino Micro sketch which allows to lock a Windows-Computer by the push
// of a button. Created because some seemingly some people around me are not
// able to remember the keyboard shortcut.
//
// Christoph B. Wurzinger

const int port_num = 2;

void setup() {
  pinMode(2, INPUT_PULLUP);
  Keyboard.begin();
}


void loop() {
  // wait for falling edge on pin 9
  while(digitalRead(port_num));
  
  // send keystroke
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('l');
 
  delay(100);
  Keyboard.releaseAll();
  
  // repeat after 1s
  delay(1000);
}


