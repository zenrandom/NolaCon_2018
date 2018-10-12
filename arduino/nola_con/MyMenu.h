/*!
 * @file MyMenu.h
 *  ____  _____      _    ____    _  ___     ____ ____  
 * |  _ \| ____|_   / \  |  _ \ _/ |/ _ \ _ / ___| ___| 
 * | | | |  _| (_) / _ \ | | | (_) | | | (_) |   |___ \ 
 * | |_| | |___ _ / ___ \| |_| |_| | |_| |_| |___ ___) |
 * |____/|_____(_)_/   \_\____/(_)_|\___/(_)\____|____/ 
 *                                                    
 *                                                    
 * Author : @theDevilsVoice @p0lr_ @mzbat
 * Date   : May 15, 2018
 * Version: 0.5
 */

#ifndef MY_MENU_H
#define MY_MENU_H

class MyMenu{
  public:
    const String myHandle = "@zenrandom";
    String myText; 
    int page;  // page number
    int inv;   // which menu item to invert
    int total; //total menu items on page
    int ledpattern;

    void show_menu();
};

#endif // MY_MENU_H
