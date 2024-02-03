//Include the library files
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
BlynkTimer timer;
bool pirbutton = 0;

//Define the relay pins
#define relay1 D1
#define relay2 D2
#define PIR D3
#define flame D0 


//Define Blynk
#define BLYNK_TEMPLATE_ID "TMPLzHpuA7y2"
#define BLYNK_DEVICE_NAME "PROYEK 2"
#define BLYNK_AUTH_TOKEN "LqGCakSlVRp4RZkdhPtWbfnh5s7RHGgb"
char auth[] = BLYNK_AUTH_TOKEN ;
char ssid[] = "Ditoo";//Enter your WIFI name
char pass[] = "";//Enter your WIFI password


//Get buttons pir values
BLYNK_WRITE(V3) {
  pirbutton = param.asInt();
}

//Get the button1 values
BLYNK_WRITE(V0) {
  bool value1 = param.asInt();
  // Check these values and turn the relay1 ON and OFF
  if (value1 == 1) {
    digitalWrite(relay1, LOW);
    Blynk.logEvent("r1on", "Lampu Kamar Tidur Menyala");
  } else {
    digitalWrite(relay1, HIGH);
    Blynk.logEvent("r1off", "Lampu Kamar Tidur Mati");
  }
}

//PirSensor
//Get the PIR sensor values
void pirsensor() 
{
  bool value = digitalRead(PIR);
  if (pirbutton == 1) {
    if (value == 0) {
      digitalWrite(relay2, HIGH);
      Serial.println("PIR nonaktif ");
    } else if (value == 1) {
      digitalWrite(relay2, LOW);
      Serial.println("PIR aktif ");      
    }
  }else{
    digitalWrite(relay2, HIGH);
  }
}

//FlameSensor
void flamesensor()
{
 bool value = digitalRead(flame);
 if (value == 0) {
      Serial.println("Flame Sensor Nonaktif");
    } else if (value == 1) {
      digitalWrite(relay1, HIGH);
      digitalWrite(relay2, HIGH);
      Serial.println("Flame Sensor Aktif");
      Blynk.logEvent("fire", "Ada Kebakaran !!!");
  }
}

void setup() {

  Serial.begin(9600) ;
  //Set the relay pins as output pins
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(PIR, INPUT);
  pinMode(flame, INPUT);
  
  // Turn OFF the relay
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);

  //Initialize the Blynk library
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);

  //Call the functions
  timer.setInterval(1000L, pirsensor);
  timer.setInterval(1000L, flamesensor);
}

void loop() {
  //Run the Blynk library
  Blynk.run();
  timer.run();
}
