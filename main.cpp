#include <Arduino.h> 
#include <Wire.h>
#include <Adafruit_Sensor.h> 
#include <Adafruit_BME280.h>
#include <SPI.h> 
#include <Adafruit_GFX.h> 
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_MOSI 11 
#define OLED_CLK 13 
#define OLED_DC 9 
#define OLED_CS 10 
#define OLED_RST 8 

Adafruit_SSD1306 display( 
SCREEN_WIDTH, 
SCREEN_HEIGHT, 
OLED_MOSI, 
OLED_CLK, 
OLED_DC, 
OLED_RST, 
OLED_CS 
);  
Adafruit_BME280 bme; 
float temperature;
float Humidity;
float pressure;
void setup(){
  Serial.begin(9600); 
  Serial.println("Program Started"); 

  Wire.begin(); 
  Serial.println("I2C Started");

 if (bme.begin(0x76)){ 
    Serial.println("BME280 Found at 0x76"); 
  }
 else if(bme.begin(0x077))
 { 
    Serial.println("BME280 Found at 0x77");
  }
  else
  {
   Serial.println("BME280 Not found");
  }  
display.begin(SSD1306_SWITCHCAPVCC);
display.clearDisplay();// Clear Display 
display.setTextSize(1); // Set Text Size 
display.setTextColor(SSD1306_WHITE); // Set Text Color 
display.display(); // Update Display 
}

void loop(){
temperature = bme.readTemperature(); 
Serial.print("Temperature: "); 
Serial.print(temperature); 
Serial.println(" C");

Humidity = bme.readHumidity();
Serial.print("Humidity: "); 
Serial.print(Humidity); 
Serial.println(" %");

pressure = bme.readPressure() / 100.0F; 
Serial.print("Pressure: "); 
Serial.print(pressure); 
Serial.println(" hPa");

display.clearDisplay(); // Clear the display
display.setCursor(0,0); // Move the cursor to the top-left corner

display.print("Temp:"); // Display "Temp"
display.print(temperature);
display.println(" C");

display.print("Hum:"); // Display "Hum"
display.print(Humidity);
display.println(" %");

display.print("Pres:"); // Display "Pres"
display.print(pressure);
display.println(" hpa");

display.display(); // Update the display
delay(1000);// Wait one second 
}