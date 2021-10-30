#include <Blynk.h>
#include <BlynkSimpleEsp8266.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include<ESP8266WiFi.h>

#define BLYNK_PRINT Serial
OneWire pin_DS18B20 (D1);
DallasTemperature DS18B20(&pin_DS18B20);
BlynkTimer timer;
const int GSR = A0;
int sensorValue=0;
int gsr_average=0;

const char*auth="TnSJYg8-fbpKFpahvaXghq7pDF6ykHWY";
const char*ssid="KANTOR L-16";
const char*pass="1234567890";

WiFiClient client;

void sendSensor(){
  DS18B20.requestTemperatures();
  Serial.print("Suhu Celsius: ");
  Serial.println(DS18B20.getTempCByIndex(0));
  Blynk.virtualWrite(V5,DS18B20.getTempCByIndex(0));
  long sum=0;
  for(int i=0;i<10;i++){
    sensorValue=analogRead(GSR);
    sum += sensorValue;
    delay(5);
  }
  gsr_average = sum/10;
  Serial.print("gsr_average =");
  Serial.println(gsr_average);
  Blynk.virtualWrite(V3,gsr_average);
}
void setup() {
  Serial.begin(9600);
  pinMode(GSR,INPUT);
  Blynk.begin(auth,ssid,pass);
  DS18B20.begin();
  delay(10);
  timer.setInterval(1000L,sendSensor);

  Serial.print("Menghubungkan ke : ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);
  while (WiFi.status()!=WL_CONNECTED){
    delay(500);
    Serial.print("....");
  }
  Serial.print("\n");
  Serial.print("IP address : ");
  Serial.print(WiFi.localIP());
  Serial.print("\n");
  Serial.print("MAC : ");
  Serial.println(WiFi.macAddress());
  Serial.println("");
  Serial.print("Terhubung dengan : ");
  Serial.print(ssid);
}

void loop() {
  Blynk.run();
  timer.run();
  
}
