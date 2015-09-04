// An Arduino Micro sketch which prevents a computer from going to sleep.
// Christoph B. Wurzinger

void setup(){
  Mouse.begin();
}

void loop(){
  // Move the cursor
  Mouse.move(1,0);
  delay(10);
  // Undo cursor movement
  Mouse.move(-1,0);
  // wait
  delay(1000);
}

