# IOT-Based-Health-Monitoring-System
To measure body temperature and SpO2 level.

# Components required

1. ESP32
2. MAX30100 Pulse Oximeter
3. DHT11 temperature and humidity sensor
4. DS18B20 body temperature sensor
5. Connecting wires
6. Breadboard

# Connections

MAX30100 is an I2C Sensor, so connect its SDA & SCL pin to GPIO21 & GPIO22.Connect its INT pin to GPIO19 of ESP32. 
The output pin of DHT11 is connected to GPIO18 of ESP32. 
The output pin of DS18B20 is connected to GPIO5 of ESP32.
A 4.7K pull-up resistor is connected between output pin & VCC pin of DS18B20.

