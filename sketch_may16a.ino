#include "DHT.h"
#define DHTPIN 2     // what digital pin we're connected to
#define DHTTYPE DHT11   // DHT 11

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
String commandString = "";

int relay1 = 13;
int led2Pin = 12;
int relay2 = 11;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  
  delay(2000);

  float humidity = dht.readHumidity();

  float temperature = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(temperature)){  
    Serial.println("Failed to read from DHT sensor!");
    TurnFirstLedOnly(led2Pin , relay1, relay2);
    return;
  }

  if(temperature >= 30){
     Serial.println("Temperature over 30: Turning On AirConditioner");
     TurnFirstLedOnly(relay1 , led2Pin, relay2);
  }

  if(temperature < 30){
     Serial.println("Temperature less than 30: Turning On ElectricFan");
     TurnFirstLedOnly(relay2 , led2Pin, relay1);
  }

  // Compute heat index in Celsius (isFahreheit = false)
  float heat_index = dht.computeHeatIndex(temperature, humidity, false);

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" *C ");
  Serial.print("Heat index: ");
  Serial.print(heat_index);
  Serial.print(" *C ");
  Serial.println();

}

void TurnFirstLedOnly(int first , int off1, int off2)
{
  digitalWrite(first, HIGH);
  digitalWrite(off1, LOW);
  digitalWrite(off2, LOW);
}

