#include <DHT.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <OneWire.h>
#include <DallasTemperature.h>

 
#define REPORTING_PERIOD_MS 1000

#include <SPI.h>


uint32_t tsLastReport = 0;

#define DHTPIN 2

const int oneWireBus = 4; 

OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);

#define DHTTYPE DHT11

DHT dht(DHTPIN,DHTTYPE);


float humidityData;
float temperatureData;
float tempC;
float tempF;


const char* ssid = "Suveen";
const char* password = "12345678";

char server[] = "50.18.240.111";  // Local machine IP if you are testing locally
                                           // Instance or server IP address or Domain name if you want access from anywhere

WiFiClient client;    

void setup()
{
 Serial.begin(115200);
  
  dht.begin();
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 sensors.begin();
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
//  server.begin();
  Serial.println("Server started");
  Serial.print(WiFi.localIP());
  delay(25000);
  Serial.println("connecting...");
 }
void loop()
{ 
  
  humidityData = dht.readHumidity();
  temperatureData = dht.readTemperature(); 
  sensors.requestTemperatures(); 
  tempC = sensors.getTempCByIndex(0);
  tempF = sensors.getTempFByIndex(0);
 

 
  Sending_To_phpmyadmindatabase(); 
  delay(30000); // interval
 }

 void Sending_To_phpmyadmindatabase()   //CONNECTING WITH MYSQL
 {
   if (client.connect(server, 80)) {
    Serial.println("connected");
    // Make a HTTP request:
    Serial.print("GET /nodemcu/index/upload.php?humidity=");
    client.print("GET /nodemcu/index/upload.php?humidity=");     //YOUR URL
    Serial.println(humidityData);
    client.print(humidityData);
    client.print("&temperature=");
    Serial.println("&temperature=");
    client.print(temperatureData);
    Serial.println(temperatureData);
    client.print("&DtempC=");
    Serial.println("&DtempC=");
    client.print(tempC);
    Serial.println(tempC);
       client.print("&DtempF=");
    Serial.println("&DtempF=");
    client.print(tempF);
    Serial.println(tempF);
    
    client.print(" ");   
   //SPACE BEFORE HTTP/1.1
    client.print("HTTP/1.1");
    client.println();
    client.println("Host: 50.18.240.111"); // Local machine IP if you are testing locally
                                            // Instance or server IP address or Domain name if you want access from anywhere
    client.println("Connection: close");
    client.println();
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
 }




 
