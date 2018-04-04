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

#ifndef MY_DISPLAY_H
  #define MY_DISPLAY_H

#include <Arduino.h>
#include <SSD1306.h>

  class MyDisplay{
    public:
      MyDisplay();
      ~MyDisplay();
      void begin();
      void showNolaLogo(); 
      void showDeadlocksLogo();
      void clearMyDisplay();
      void updateMyDisplay(int16_t, int16_t, String);
  };
   
#endif // MY_DISPLAY_H
