#include <Arduino.h>
#include <esp32_can.h>

void setup()
{
  Serial.begin(9600);

  Serial.println("\n\nCAN Display - log recorder");
  CAN0.setCANPins(GPIO_NUM_4, GPIO_NUM_5);
  CAN0.setListenOnlyMode(true);
  CAN0.begin(CAN_BPS_500K);
  CAN0.watchFor();
}

void loop()
{
  CAN_FRAME can_message;

  if (CAN0.read(can_message))
  {
    Serial.print("CAN MSG: 0x");
    Serial.print(can_message.id, HEX);
    Serial.print(" ");
    Serial.print("[");
    Serial.print(can_message.length, DEC);
    Serial.print("] <");
    for (int i = 0; i < can_message.length; i++)
    {
      if (i != 0)
        Serial.print(":");
      Serial.print(can_message.data.byte[i], HEX);
      Serial.print(" "); // maybe replace with \t for .tsv files
    }
    Serial.println(">");
  }
}