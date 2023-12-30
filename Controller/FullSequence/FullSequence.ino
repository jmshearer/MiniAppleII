#include <st7789v2.h>
#include "SPI.h"
#include "graphics.h"

st7789v2 lcd;

int lastRandomNumber=0;

void setup() {  
  lcd.SetRotate(270);
  lcd.Init();
  lcd.SetBacklight(100);
  lcd.Clear(BLACK);
  lcd.DrawString_EN(80, 20, "Apple ][", &Font16, BLACK, GREEN);
  delay(2500);
  lcd.DrawString_EN(80, 20, "        ", &Font16, BLACK, GREEN);  
  randomSeed(analogRead(0));  
}

void loop() {     

  //Come up with a random action that is different than the previous one
  int randomNumber;
  do {
    randomNumber = random(1, 5); 
  } while (randomNumber == lastRandomNumber);
  lastRandomNumber = randomNumber;    


  //Perform the action.  Note that each action should return the screen to black
  switch(randomNumber){
    case 1:
      showAbout();
      break;
    case 2:
      showOregon();
      break;
    case 3:
      showCat();
      break;
    case 4:
      showLOGO();
      break;
  }  
}


//LOGO simulator
void showLOGO() {  
  lcd.Clear(BLACK);
  int shape = random(1,3);  
  TypeCommandWait(20,"]BRUN LOGO",0);
  lcd.DrawString_EN(10, 20,"             ", &Font16, BLACK, GREEN);
    
  switch(shape){
    case 1:
      TypeCommandWait(150,"?TO STAR",0);
      TypeCommandWait(170,">REPEAT 5 [",0);
      TypeCommandWait(190, ">FD 5 RT 144",0);      
      TypeCommandWait(210,">]",0);  
      
      lcd.DrawString_EN(10, 210,"             ", &Font16, BLACK, GREEN);
      lcd.DrawString_EN(10, 190,">]           ", &Font16, BLACK, GREEN);
      lcd.DrawString_EN(10, 170,">FD 5 RT 144 ", &Font16, BLACK, GREEN);
      lcd.DrawString_EN(10, 150,">REPEAT 5[   ", &Font16, BLACK, GREEN);  
      TypeCommandWait(210,">END",0);  
      
      lcd.DrawString_EN(10, 210,"             ", &Font16, BLACK, GREEN);
      lcd.DrawString_EN(10, 190,"STAR DEFINED ", &Font16, BLACK, GREEN);      
      lcd.DrawString_EN(10, 170,">END         ", &Font16, BLACK, GREEN);      
      lcd.DrawString_EN(10, 150,">]           ", &Font16, BLACK, GREEN);      
      TypeCommandWait(210,"?STAR",0);    

      lcd.DrawString_EN(10, 150,">END         ", &Font16, BLACK, GREEN);      
      lcd.DrawString_EN(10, 170,"STAR DEFINED ", &Font16, BLACK, GREEN);      
      lcd.DrawString_EN(10, 190,"?STAR        ", &Font16, BLACK, GREEN);
      lcd.DrawString_EN(10, 210,"             ", &Font16, BLACK, GREEN);  
        
      logoPlot(5, 144, 50);      

      TypeCommandWait(210,"?",3);
      TypeCommandWait(210,"?BYE",0);

      break;
    case 2:
      TypeCommandWait(150,"?REPEAT 4 [FD 5 RT 90]",0);            
      
      logoPlot(4, 90, 50);

      TypeCommandWait(190,"?",3);
      TypeCommandWait(190,"?BYE",0);
      break;
  }  
  lcd.Clear(BLACK);
}

//logoPlot is used by showLOGO and it more-or-less behaves very similar to the original LOGO software
void logoPlot(int n, float angleIncrement, int length){
  float angle = 0;
  int x =105;
  int y = 80;  
  int xEnd;
  int yEnd;
  for (int i = 0; i < n; i++) {
    // Calculate end point of each line based on angle
    xEnd = x + round(length * cos(radians(angle)));
    yEnd = y + round(length * sin(radians(angle)));

    // Draw the line
    lcd.DrawLine(x, y, xEnd, yEnd, GREEN, DOT_PIXEL_2X2, LINE_STYLE_SOLID);
    delay(100);

    // Update the angle for the next line
    angle += angleIncrement;
    x = xEnd;
    y = yEnd;
  }

  xEnd=xEnd-4;
  yEnd=yEnd+2;

  //Create a "turtle" (poor substitution, but it gets the idea across)
  lcd.DrawLine(xEnd, yEnd, xEnd+8, yEnd, GREEN, DOT_PIXEL_1X1, LINE_STYLE_SOLID);  
  lcd.DrawLine(xEnd, yEnd, xEnd+4, yEnd-8, GREEN, DOT_PIXEL_1X1, LINE_STYLE_SOLID);  
  lcd.DrawLine(xEnd+8, yEnd, xEnd+4, yEnd-8, GREEN, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
}

//Show the Oregon Trail artwork
void showOregon(){
  lcd.Clear(BLACK);    
  TypeCommandWait(20,"]BRUN OREGON",0);
  delay(1500);
  lcd.DrawString_EN(10, 40, "              " , &Font16, BLACK, GREEN);

  lcd.DrawImage(oregon1, 0, 0, 260, 240);   
  delay(2000);
  lcd.DrawImage(oregon2, 0, 0, 260, 240);   
  delay(2000);
  lcd.DrawImage(oregon3, 0, 0, 260, 240);   
  delay(2000);
  lcd.DrawImage(oregon4, 0, 0, 260, 240);   
  delay(2000);
  lcd.DrawImage(oregon5, 0, 0, 260, 240);   
  delay(2000);

  if(random(1,4)==1){
    lcd.DrawImage(oregon7, 0, 0, 260, 240);     
  } else {
    lcd.DrawImage(oregon6, 0, 0, 260, 240);   
  }
  delay(2000);
  lcd.Clear(BLACK);
  lcd.DrawString_EN(10, 20, "]BRUN OREGON", &Font16, BLACK, GREEN);
  TypeCommandWait(40,"]",2);
  TypeCommandWait(40,"]HOME",0);
}

//Show a simple ASCII-art cat
void showCat() {  
  lcd.Clear(BLACK);
  TypeCommandWait(20,"]LOAD CAT.BAS",0);
  TypeCommandWait(40,"]RUN",0);

  delay(500);
  
  lcd.DrawString_EN(30, 60,  "   |\__/,|    (`)", &Font16, BLACK, GREEN);
  lcd.DrawString_EN(30, 80,  "   |o o  |__ _) )", &Font16, BLACK, GREEN);
  lcd.DrawString_EN(30, 100, " _.( T   )  `  /", &Font16, BLACK, GREEN);
  lcd.DrawString_EN(30, 120, "((_ `^--' /_<  \\", &Font16, BLACK, GREEN);
  lcd.DrawString_EN(30, 140, "`` `-'(((/  (((/", &Font16, BLACK, GREEN);  

  delay(1500);

  TypeCommandWait(180,"]",3);
  
  TypeCommandWait(180,"]HOME",0);    
}


//Show an "About" screen
void showAbout() {  
  lcd.Clear(BLACK);    
  TypeCommandWait(20,"]LOAD ABOUT.BAS",0);
  TypeCommandWait(40,"]RUN",0);

  delay(500);
  
  lcd.DrawString_EN(30, 80,  " Mini Apple II", &Font16, BLACK, GREEN);
  lcd.DrawString_EN(30, 100,  "(C) Shearer ", &Font16, BLACK, GREEN);
  lcd.DrawString_EN(30, 120, "", &Font16, BLACK, GREEN);
  lcd.DrawString_EN(30, 140, "       2023", &Font16, BLACK, GREEN);  
  delay(1500);

  TypeCommandWait(180,"]",3);
  
  TypeCommandWait(180,"]HOME",0);    
}

//Pretend to "type" a command and then wait for sec
void TypeCommandWait(int y, String cmd, int sec) {
  String temp;
  
  for (int i = 1; i <= cmd.length(); i++) {
    // Get the substring from the start to the current position
    temp = cmd.substring(0, i) + char(176);
    // Display the substring on the LCD
    lcd.DrawString_EN(10, y, temp.c_str(), &Font16, BLACK, GREEN);
    // Delay for a random time between 150ms and 200ms to simulate variable typing speed
    delay(random(150, 201));    
  }

  //Add the blinking cursor
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