// Created by: Ryan Sunderhaus

// Completed xx/xx/2016

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
//-----------------------//

//----------Globals----------//
byte move_x, move_y = 0;
int move_speed = 10;
byte buttons;
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
}
//-------------------------//


void loop() {
  moveMouse();
  
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
}

//--
void moveMouse() {
  if (hasCommand()) {
    
    //Horizontal movement
    if (digitalRead(left) && !digitalRead(right)) move_x = -1;
    else if (digitalRead(right) && !digitalRead(left)) move_x = 1;
    else move_x = 0;
    
    //Vertical movement
    if (digitalRead(up) && !digitalRead(down)) move_y = -1;
    else if (digitalRead(down) && !digitalRead(up)) move_y = 1;
    else move_y = 0;
    
    //Buttons
    if (digitalRead(left_click)) buttons |= (1 << 1);
    if (digitalRead(right_click)) buttons |= (1 << 2);
    
    mouseCommand(buttons, move_x*move_speed, move_y*move_speed);
  }
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
  Serial.write((byte)0x00);
  Serial.write((byte)0x00);
  Serial.write((byte)0x00);
}
