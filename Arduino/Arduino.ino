// Created by: Ryan Sunderhaus

// Completed xx/xx/2016
// To do:
// -Set speed
// -Fix buttons
// -Scrolling
// -Make code look nice

//----------PINS---------//
const byte rx_pin = 0;
const byte tx_pin = 1;
const byte left = 9;
const byte up = 3;
const byte right = 4;
const byte down = 5;
const byte left_click = 7;
const byte right_click = 8;
const byte dial = A0;
const byte test_led = 13;
//-----------------------//

//----------Globals----------//
int move_speed = 10;
//---------------------------//

//----------Setup----------//
void setup() {
  Serial.begin(9600);
  pinMode(left, INPUT);
  pinMode(up, INPUT);
  pinMode(right, INPUT);
  pinMode(down, INPUT);
  pinMode(left_click, INPUT);
  pinMode(right_click, INPUT);
  pinMode(test_led, OUTPUT);
}
//-------------------------//


void loop() {
  byte move_x, move_y = 0;
  byte buttons = 0;
  
  move_x = setMoveX();
  move_y = setMoveY();
  buttons = setButtons();
  
  if (hasCommand()) {    
    mouseCommand(buttons, move_x, move_y);
  }
}

//--
byte setButtons() {
  byte buttons = 0;
  if (digitalRead(left_click)) buttons = 0x1;
  else if (digitalRead(right_click)) buttons = 0x2;
  else buttons = 0x0;
  return buttons;
}

//--Determine y movement direction
byte setMoveY() {
    byte y = 0;
  if (digitalRead(up) && !digitalRead(down)) y = -1;
  else if (digitalRead(down) && !digitalRead(up)) y = 1;
  else y = 0;
  return y*setMoveSpeed();
}

//--Determine x movement direction
byte setMoveX() {
  byte x = 0;
  if (digitalRead(left) && !digitalRead(right)) x = -1;
  else if (digitalRead(right) && !digitalRead(left)) x = 1;
  else x = 0;
  return x*setMoveSpeed();
}

//--Sets speed of mouse movements based on dial
byte setMoveSpeed() {
  return analogRead(dial)/100;
}

//--Returns true if any button is pressed, there is a command from the mouse
boolean hasCommand() {
  return digitalRead(left) || digitalRead(right) || digitalRead(up) || digitalRead(down) || digitalRead(left_click) || digitalRead(right_click);
}

//--Sends proper serial codes to Bluefruit for mouse commands based on x, y, and buttons
void mouseCommand(uint8_t buttons, uint8_t x, uint8_t y) {
  Serial.write(0xFD);
  Serial.write((byte)0x00);
  Serial.write((byte)0x03);
  Serial.write(buttons);
  Serial.write(x);
  Serial.write(y);
  Serial.write((byte)0x00); //v scroll control??
  Serial.write((byte)0x00); //h
  Serial.write((byte)0x00);
}


/*------UNUSED-------/*



boolean released(byte button) {
  boolean pressed, released = false;
  if (digitalRead(button)) pressed = true;
  if (pressed && !digitalRead(button)) {
    released = true;
    pressed = false;
  }
  return released;
}



/*if (digitalRead(down) == HIGH) mouseCommand(0, 0, 10);
  else if (digitalRead(right) == HIGH) mouseCommand(0, 10, 0);
  else if (digitalRead(up) == HIGH) mouseCommand(0, 0, -10);
  //mouseCommand(0,0,0);*/
  
  /*move_x = 0;
  move_y = 0;
  if (digitalRead(left) == HIGH) move_x = -10;
  if (digitalRead(right) == HIGH) move_x = 10;
  if (digitalRead(up) == HIGH) move_y = -10;
  if (digitalRead(down) == HIGH) move_y = 10;
  
  
  mouseCommand(buttons, move_x, move_y);*/
  
  //Serial.println(analogRead(dial));
  
  
  
  
  
   //"Lets go" of button commands when buttons are released
  /*if(released(left_click) || released(right_click)) {
    mouseCommand(0,0,0);
    digitalWrite(test_led, HIGH);
  } else digitalWrite(test_led, LOW);*/
