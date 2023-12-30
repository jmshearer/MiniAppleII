#include <st7789v2.h>
#include "SPI.h"

st7789v2 lcd;

//Simple "Hello World" application

void setup() {
  // put your setup code here, to run once:
  lcd.SetRotate(270);
  lcd.Init();
  lcd.SetBacklight(100);
  lcd.Clear(BLACK);
  lcd.DrawString_EN(80, 10, "Apple ][", &Font16, BLACK, GREEN);
  delay(2500);
  lcd.DrawString_EN(80, 10, "        ", &Font16, BLACK, GREEN);
}

void loop() {  
  lcd.Clear(BLACK);    
  TypeCommandWait(10,"]print \"Hello!\"",0);
  TypeCommandWait(30,"]RUN",0);
  lcd.DrawString_EN(10, 50,  "Hello!", &Font16, BLACK, GREEN);  

  delay(500);

  TypeCommandWait(70,"]",3);
  
  TypeCommandWait(70,"]HOME",0);    
}

void TypeCommandWait(int y, String cmd, int sec) {
  String temp;
  
  for (int i = 0; i <= cmd.length(); i++) {
    // Get the substring from the start to the current position
    temp = cmd.substring(0, i) + char(176);
    // Display the substring on the LCD
    lcd.DrawString_EN(10, y, temp.c_str(), &Font16, BLACK, GREEN);

    // Delay for a random time between 150ms and 200ms
    delay(random(150, 201));    
  }

  String withCursor = cmd + char(176);
  String withoutCursor = cmd + " ";
  for(int i=0; i <= sec*2; i++){
    lcd.DrawString_EN(10, y, withoutCursor.c_str(), &Font16, BLACK, GREEN);
    delay(500);
    lcd.DrawString_EN(10, y, withCursor.c_str(), &Font16, BLACK, GREEN);
    delay(500);
  }
  lcd.DrawString_EN(10, y, withoutCursor.c_str(), &Font16, BLACK, GREEN);

}