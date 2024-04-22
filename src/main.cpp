#include <Arduino.h>
#include <esp32_can.h>

const char separator = ',';

void setup()
{
  Serial.begin(115200);

  CAN0.setCANPins(GPIO_NUM_4, GPIO_NUM_5);
  CAN0.setListenOnlyMode(true);
  CAN0.begin(CAN_BPS_500K);
  CAN0.watchFor();

  Serial.println("\n\n--- CAN logger v1.0 ---");
}

void loop()
{
  CAN_FRAME can_message;

  if (CAN0.read(can_message))
  {
    Serial.print(can_message.id, DEC);

    for (int i = 0; i < can_message.length; i++)
    {
      Serial.print(separator);
      Serial.print(can_message.data.byte[i], DEC);
    }

    Serial.println();
  }
}