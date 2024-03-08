#include <SPI.h>
#include <TFT_eSPI.h>
#include <DHT.h>
#include <DHT_U.h>
#include <UbiConstants.h>
#include <UbiTypes.h>
#include <UbidotsEsp32Mqtt.h>
#define DHTPIN 27
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
TFT_eSPI tft = TFT_eSPI();

RTC_DATA_ATTR char payload = 0; //Graba datos en la memoria RTC de la variable de interes antes 
                                // de definirla en el setup
RTC_DATA_ATTR float t;
RTC_DATA_ATTR float h;
touch_pad_t touchPin;
/****************************************
 * Define Constants
 ****************************************/
const char *UBIDOTS_TOKEN = "BBUS-4A0XexFStypzV1WtTm4rfQydg0Y330";  // Put here your Ubidots TOKEN
const char *WIFI_SSID = "";      // Put here your Wi-Fi SSID
const char *WIFI_PASS = "";      // Put here your Wi-Fi password
const char *DEVICE_LABEL = "esp32";   // Put here your Device label to which data  will be published
const char *VARIABLE_LABEL = "t"; // Put here your Variable label to which data  will be published
const char *HUMEDAD_VARIABLE_LABEL = "h"; 
const int PUBLISH_FREQUENCY = 5000; // Update rate in milliseconds

unsigned long timer;
uint8_t analogPin = 27; // Pin used to read data from GPIO34 ADC_CH6.


/****************************************
 * Auxiliar Functions
 ****************************************/

void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}



void setup() {
  Serial.begin(115200); //init del dht
  delay(1000);




    Serial.println(F("DHTxx test!"));

    dht.begin();
    float h = dht.readHumidity(); //datos del sensor
    float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
      Serial.println(F("Failed to read from DHT sensor!"));
      return;
    }

    Serial.print(h);
    Serial.print(t);
    
  Serial.println("Entrando en modo ahorro");
  delay(1000);
  esp_sleep_enable_touchpad_wakeup(); //Finaliza modo de bajo consumo con un touch pin en esquematico
  Serial.flush(); 
  esp_deep_sleep_start(); //Inicia modo de ahorro, ignora lo demas
    
}



void loop() {
  // subrutina de loop vacia porque el modo deep_sleep solo llega hasta el setup()
  
}
