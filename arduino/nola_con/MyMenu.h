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
#ifndef MY_MENU_H
#define MY_MENU_H

#include <Arduino.h>

/* 
 * menu 
 * 
 * 0. bling
 *   0.0 
 *   0.1 cybercop
 *   0.3 rainbow
 *   0.4 chase
 * 1. games
 *    1.1 snake
 *    1.2 pong
 * 2. network   
 *   2.1 wifi scanner
 *   2.2 mqtt connect
*/

class MyMenu{
  public:
    //MyMenu();
    //~MyMenu();

    const String myHandle = "@nola_con";
    String myText; 
    int page;  // page number
    int inv;   // which menu item to invert
    int total; //total menu items on page
    int ledpattern;
    
};

#endif //MY_MENU_H

