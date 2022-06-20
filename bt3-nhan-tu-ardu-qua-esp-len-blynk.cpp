#define BLYNK_TEMPLATE_ID "TMPLjw14UP6r"
#define BLYNK_DEVICE_NAME "autonomous vehicle monitoring on blynk"
#define BLYNK_AUTH_TOKEN "YNKiHmPxWv2UIMysAf898THdUaBiJog8"
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>
SoftwareSerial s(D5,D6);
char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "Xom Tro 2";
char pass[] = "Thao270296";


int  point,zone = 0;
String zone1;
BlynkTimer timer;
BLYNK_WRITE(V0)
{
    int pinValueA = param.asInt(); 
    if (pinValueA == 1)
    {
        
        s.write(1);
    }
    else
    {
        s.write(0);
    }
}


BLYNK_WRITE(V1)
{
    int pinValueB = param.asInt(); 
    if (pinValueB == 1)
    {
        s.write(2);
    }
    else
    {
        s.write(0);
    }  
}


BLYNK_CONNECTED()
{
    Blynk.syncVirtual(V0);
    Blynk.syncVirtual(V1);
    Blynk.syncVirtual(V2);
    Blynk.syncVirtual(V3);
}

/*send zone to cloud*/
void myTimerEvent()
{
    Blynk.virtualWrite(V2, zone);
    Blynk.virtualWrite(V3, point);
}



void setup()
{
    pinMode(D5, INPUT);
    pinMode(D6, OUTPUT);
    s.begin(9600);
    Serial.begin(9600);

    Blynk.begin(auth, ssid, pass);
    timer.setInterval(100L, myTimerEvent);
}

void loop()
{
    while(s.available()==0)
    {
        Blynk.run();
        timer.run();
    }

    zone = s.read();
    Serial.println(zone);
    point = zone * 20;
}
