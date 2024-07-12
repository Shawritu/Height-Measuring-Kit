#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <MPU6050_light.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define trigPin 9
#define echoPin 8
#define OLED_RESET 4
 // Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);
 
 
MPU6050 mpu(Wire);
unsigned long timer = 0;
 
void setup() {
Serial.begin (9600);
Serial.begin(115200);                           // Ensure serial monitor set to this value also    
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))  // Address 0x3C for most of these displays, if doesn't work try 0x3D 
  { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);                                      // Don't proceed, loop forever
  } 
  display.setTextSize(2);             
  display.setTextColor(SSD1306_WHITE);            // Draw white text
  display.clearDisplay();                         
  Wire.begin();
  mpu.begin();
  display.println(F("DONT MOVE...."));
  display.display();        
  mpu.calcGyroOffsets();                          // This does the calibration
  display.setTextSize(2);          
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //initialize with the I2C addr 0x3C (128x64)
display.clearDisplay();
 
}
 
void loop() { 
float distance_cm;
float distance_in;
float duration;
 mpu.update();  
  if((millis()-timer)>10)                         // print data every 10ms
float duration;
digitalWrite(trigPin, LOW); //PULSE |---|
delayMicroseconds(1);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
 
duration= pulseIn(echoPin, HIGH);
 
distance_cm = (duration/2) / 29.1;
distance_in = (duration/2) / 73.914;
 

display.clearDisplay();                       // clear screen
    display.setCursor(10,25);
    display.setTextSize(1);                         
    display.print("ANGLE: ");
    display.println(mpu.getAngleX());
   
    display.display();                            // display data
    timer = millis();
    
display.setCursor(2,10); //oled display
display.setTextSize(1);
display.setTextColor(WHITE);
display.println("HIGHT:");

display.setCursor(10,38); //oled display
display.setTextSize(1);
display.setTextColor(WHITE);
 display.println("DIST:");
 display.setCursor(93,23);
 display.setTextSize(1);
 display.println("*");

 
display.setCursor(43,38); //oled display
display.setTextSize(1);
display.setTextColor(WHITE);
display.println(distance_cm-3);
display.setCursor(99,38);
display.setTextSize(1);
display.println("CM");

display.setCursor(40,10); //oled display
display.setTextSize(1);
display.setTextColor(WHITE);
display.println(tan(mpu.getAngleX()*(3.14/180))*(distance_cm-2)+1);
display.setCursor(99,10);
display.setTextSize(1);
display.println("H-CM");
display.display();

 
delay(50);
display.clearDisplay();
 
Serial.println(distance_cm);
Serial.println(distance_in);
}
