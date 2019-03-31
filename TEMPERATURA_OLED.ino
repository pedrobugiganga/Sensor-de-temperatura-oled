#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Definicao de pinos interface SPI
#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

#define entrada_sensor A0
#define saida_fan 2
int sensor_temp;
int i =0;
float temp;

#define SSD1306_LCDHEIGHT 64
#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif


void setup()   
{
  display.clearDisplay();
  Serial.begin(9600);
   pinMode(entrada_sensor, INPUT);
   pinMode(saida_fan, OUTPUT);
  // Inicializa o display
  display.begin(SSD1306_SWITCHCAPVCC);
  display.clearDisplay();
   display.setTextColor(WHITE);

  display.println("    LAB DOS FUNDOS");
  display.display();
  delay(2000);
  display.clearDisplay();


  for(i=0; i<display.width(); i+=4) {
    display.drawLine(0, display.height()-1, i, 0, WHITE);
    display.display();
    delay(1);
  }
  for(i=display.height()-1; i>=0; i-=4) {
    display.drawLine(0, display.height()-1, display.width()-1, i, WHITE);
    display.display();
    delay(1);
  }
  delay(500);

  display.clearDisplay();

  for(i=display.width()-1; i>=0; i-=4) {
    display.drawLine(display.width()-1, display.height()-1, i, 0, WHITE);
    display.display();
    delay(1);
  }
  for(i=display.height()-1; i>=0; i-=4) {
    display.drawLine(display.width()-1, display.height()-1, 0, i, WHITE);
    display.display();
    delay(1);
  }
  delay(1000);
  display.clearDisplay();
}

void loop() 
{
  float tempM[100]; // medição média
  int j=0 ;
  for(j =0; j<100; j++){
   sensor_temp = analogRead(entrada_sensor);
   tempM [j] = (sensor_temp * (5.0/1023.0))*100;
   temp=temp+tempM[j];
  }

float temp_result = temp / 100;
temp = 0;
  
  display.clearDisplay();

  display.setTextSize(2);
  display.setCursor(0,0);
  display.println("   TEMP   ");
  display.setCursor(25,25);
  display.print(temp_result);
  display.println("C");
  display.display();
  delay(1000);

}
