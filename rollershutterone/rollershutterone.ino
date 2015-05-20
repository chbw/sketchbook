typedef enum {STOP, PAUSE, UP_STEP, UP_CONT, DN_STEP, DN_CONT} shutter_state_t;

typedef struct {
  shutter_state_t state;
  unsigned long timestamp;
  uint8_t btn_up;
  uint8_t btn_up_prev;
  uint8_t btn_dn;
  uint8_t btn_dn_prev;
  int driver_up;
  int driver_dn;
  int button_up;
  int button_dn;
} shutter_t;

shutter_t s1_;


const unsigned long TIME_PAUSE_MS = 400;
const unsigned long TIME_STEP_MS = 400;
const unsigned long TIME_CONT_MS = 30000;

void setup(){
  unsigned long now = millis();

  s1_.state = STOP;
  s1_.timestamp = now;
  s1_.btn_up = LOW;
  s1_.btn_up_prev = LOW;
  s1_.btn_dn = LOW;
  s1_.btn_dn_prev = LOW;
  s1_.driver_up = 2;
  s1_.driver_dn = 3;
  s1_.button_up = 4;
  s1_.button_dn = 5;
  pinMode(s1_.driver_up,OUTPUT);
  pinMode(s1_.driver_dn,OUTPUT);
  pinMode(s1_.button_up,INPUT);
  pinMode(s1_.button_dn,INPUT);

}


void loop(){
  unsigned long now = millis();
  
  s1_.btn_dn_prev = s1_.btn_dn;
  s1_.btn_up_prev = s1_.btn_up;
  s1_.btn_up = digitalRead(s1_.button_up);
  s1_.btn_dn = digitalRead(s1_.button_dn);
  
  switch(s1_.state) {
    case PAUSE:
      digitalWrite(s1_.driver_up, LOW);
      digitalWrite(s1_.driver_dn, LOW);
      if(now > s1_.timestamp + TIME_PAUSE_MS) {
        s1_.state = STOP;
      }
      break;
      
    case STOP:
      digitalWrite(s1_.driver_up, LOW);
      digitalWrite(s1_.driver_dn, LOW);
      if(s1_.btn_up && (!s1_.btn_up_prev)){
        s1_.state = UP_STEP;
        s1_.timestamp = now;
      }
      if(s1_.btn_dn && (!s1_.btn_dn_prev)){
        s1_.state = DN_STEP;
        s1_.timestamp = now;
      }
      break;
      
    case UP_STEP:
      digitalWrite(s1_.driver_up, HIGH);
      digitalWrite(s1_.driver_dn, LOW);
      if(!s1_.btn_up){
        s1_.state = PAUSE;
        s1_.timestamp = now;
      }
      if(now > s1_.timestamp + TIME_STEP_MS){
        s1_.state = UP_CONT;
      }
      break;
      
    case UP_CONT:
      digitalWrite(s1_.driver_up, HIGH);
      digitalWrite(s1_.driver_dn, LOW);
      if(now > s1_.timestamp + TIME_CONT_MS) {
        s1_.state = PAUSE;
        s1_.timestamp = now;
      }
      if(s1_.btn_up && (!s1_.btn_up_prev)){
        s1_.state = PAUSE;
        s1_.timestamp = now;
      }
      if(s1_.btn_dn && (!s1_.btn_dn_prev)){
        s1_.state = PAUSE;
        s1_.timestamp = now;
      }
      break;
      
    case DN_STEP:
      digitalWrite(s1_.driver_up, LOW);
      digitalWrite(s1_.driver_dn, HIGH);
      if(!s1_.btn_dn){
        s1_.state = PAUSE;
        s1_.timestamp = now;
      }
      if(now > s1_.timestamp + TIME_STEP_MS){
        s1_.state = DN_CONT;
     }
     break;
      
    case DN_CONT:
      digitalWrite(s1_.driver_up, LOW);
      digitalWrite(s1_.driver_dn, HIGH);
      if(now > s1_.timestamp + TIME_CONT_MS) {
        s1_.state = PAUSE;
        s1_.timestamp = now;
      }
      if(s1_.btn_up && (!s1_.btn_up_prev)){
        s1_.state = PAUSE;
        s1_.timestamp = now;
      }
      if(s1_.btn_dn && (!s1_.btn_dn_prev)){
        s1_.state = PAUSE;
        s1_.timestamp = now;
      }
      break;
  }
}

