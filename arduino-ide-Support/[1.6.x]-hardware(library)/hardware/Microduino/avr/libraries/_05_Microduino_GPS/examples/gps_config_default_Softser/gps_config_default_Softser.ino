//This example is for Microduino/mCookie Core/CoreUSB/Core+/CoreRF
//More information please visit https://wiki.microduino.cn/index.php/MCookie-GPS

#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); // RX, TX
Adafruit_GPS GPS(&mySerial);

void setup()
{
  Serial.begin(115200);

  GPS.begin(38400);  //9600/19200/38400/57600/115200
  GPS.set_config(CONFIG_DEFAULT);  //CONFIG_DEFAULT/CONFIG_SAVE
}

void loop() // run over and over again
{
  if (mySerial.available()) {
    char c = mySerial.read();
    Serial.write(c);
  }
}
