// Code provided by Adafruit at https://learn.adafruit.com/introducing-bluefruit-ez-key-diy-bluetooth-hid-keyboard/sending-keys-via-serial#raw-hid-mouse-reports
// Sends proper serial codes to Bluefruit for mouse commands based on x, y, and buttons

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

