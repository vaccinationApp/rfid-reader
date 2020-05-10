
#include <SoftwareSerial.h>
#include <Rfid134.h>

// implement a notification class,
// its member methods will get called 
//
class RfidNotify
{
public:
  static void OnError(Rfid134_Error errorCode)
  {
    // see Rfid134_Error for code meaning
    Serial.println();
    Serial.print("Com Error ");
    Serial.println(errorCode);
  }

  static void OnPacketRead(const Rfid134Reading& reading)
  {
    char temp[8];

    Serial.print("TAG: ");

    // since print doesn't support leading zero's, use sprintf
    sprintf(temp, "%03u", reading.country);
    Serial.print(temp);   

    Serial.print(" ");
    
    // since print doesn't support leading zero's, use sprintf
    // since sprintf with AVR doesn't support uint64_t (llu/lli), use /% trick to
    // break it up into equal sized leading zero pieces
    sprintf(temp, "%06lu", static_cast<uint32_t>(reading.id / 1000000));
    Serial.print(temp); 
    sprintf(temp, "%06lu", static_cast<uint32_t>(reading.id % 1000000));
    Serial.print(temp); 

    Serial.print(" ");
    if (reading.isData)
    {
        Serial.print("data");
    }
    if (reading.isAnimal)
    {
        Serial.print("animal");
    }
    Serial.println();
  }

};

Rfid134<HardwareSerial, RfidNotify> rfid(Serial1);


void setup() 
{
  Serial.begin(115200);

  Serial.println("initializing...");
  
  rfid.begin();
 
  Serial.println("starting...");
}

void loop() 
{
  rfid.loop();
}
