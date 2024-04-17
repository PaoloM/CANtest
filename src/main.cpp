#include <Arduino.h>
#include <esp32_can.h>

void setup()
{
  Serial.begin(9600);

  Serial.println("CAN Display - log recorder");
  CAN0.setCANPins(GPIO_NUM_5, GPIO_NUM_4);
  CAN0.setListenOnlyMode(true);
  CAN0.begin(500000);
  CAN0.watchFor();
}

void loop()
{
  CAN_FRAME can_message;

  if (CAN0.read(can_message))
  {
    Serial.print("CAN MSG: 0x");
    Serial.print(can_message.id, HEX);
    Serial.print(" [");
    Serial.print(can_message.length, DEC);
    Serial.print("] <");
    for (int i = 0; i < can_message.length; i++)
    {
      if (i != 0)
        Serial.print(":");
      Serial.print(can_message.data.byte[i], HEX);
    }
    Serial.println(">");
  }
}