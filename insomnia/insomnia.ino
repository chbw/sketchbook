// An Arduino Micro sketch which prevents a computer (and its display) from going to sleep.
// This can be useful when running a presentation/slideshow/etc on somebody elses computer
// where one can not modify the power saving settings.
//
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

