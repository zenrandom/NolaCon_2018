/*
 *  ____  _____      _    ____    _  ___     ____ ____  
 * |  _ \| ____|_   / \  |  _ \ _/ |/ _ \ _ / ___| ___| 
 * | | | |  _| (_) / _ \ | | | (_) | | | (_) |   |___ \ 
 * | |_| | |___ _ / ___ \| |_| |_| | |_| |_| |___ ___) |
 * |____/|_____(_)_/   \_\____/(_)_|\___/(_)\____|____/ 
 *                                                    
 *                                                    
 * Author : @theDevilsVoice @p0lr_ @mzbat
 * Date   : March 31, 2018
 * Version: 0.4
 */
#include "MyDisplay.h"

SSD1306 display(0x3c, D2, D1);

// class constructor
MyDisplay::MyDisplay() {
  display.init();
  display.flipScreenVertically();
}

//<<destructor>>
MyDisplay::~MyDisplay(){/*nothing to destruct*/}

void MyDisplay::begin(){
  Serial.println( "Called MyDisplay::begin" );
}


/* https://learn.adafruit.com/monochrome-oled-breakouts/arduino-library-and-examples
 *  http://en.radzio.dxp.pl/bitmap_converter/
 */
void MyDisplay::showNolaLogo(){
  Serial.println( "Called MyDisplay::showNolaLogo" );
  
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_16);
  String Msg = "display @nola_con logo";
  display.drawString(0, 0, Msg);
  display.display();
  delay(500);
}

void MyDisplay::showDeadlocksLogo(){
  Serial.println( "Called MyDisplay::showDeadlocksLogo" );

  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 0, "DE:AD:10:C5");
  display.display();
  delay(500);
}

void MyDisplay::clearMyDisplay(){
  display.clear();
}

void MyDisplay::updateMyDisplay(int16_t x, int16_t y, String text){
  Serial.println( "Called MyDisplay::showDeadlocksLogo" );

  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_16);
  display.drawString(x,y,text);
  display.display();
}

