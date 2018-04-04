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
#include "MyNetwork.h"
#include "MyLed.h"
#include "MyButtons.h"
#include "MyDisplay.h"

// Initialize instance of MyNetwork() class
MyNetwork mynetwork;
// Initialize instance of MyLed() class
MyLed myled;
// Initialize instance of MyDisplay() class
MyDisplay mydisp;

void setup() {
  mydisp.showDeadlocksLogo();
  mydisp.showNolaLogo();
}

void loop() {

  // show menus

   // void MQTT_connect();

  myled.rainbow();

  if (mynetwork.MyNetStatus() != 3) {
    if(!mynetwork.WiFiScanned)
    {
      mydisp.clearMyDisplay();
      mydisp.updateMyDisplay(0, 0, "Scanning WiFi");

      mynetwork.WiFiCount = WiFi.scanNetworks();
    
      if (mynetwork.WiFiCount == 0) {
        mydisp.clearMyDisplay();
        mydisp.updateMyDisplay(0, 0, "No Networks Found");
      } else {
        mynetwork.WiFiScanned = true;
        mynetwork.DisplayUpdate = true;
      }
    }
    else
    {
      if (digitalRead(UP) == LOW) {
        mynetwork.WiFiIndex--;
        mynetwork.DisplayUpdate = true;
        if (mynetwork.WiFiIndex < 0) {
          mynetwork.WiFiIndex = 0;
        }
      }
      if (digitalRead(ESC) == LOW) {
        mynetwork.WiFiScanned = false;
        mynetwork.WiFiIndex = 0;
        mynetwork.DisplayUpdate = true;
      }
      if (digitalRead(ENTER) == LOW) {

        WiFi.disconnect();
        char ssid[] = "";
        WiFi.SSID(mynetwork.WiFiIndex).toCharArray(ssid, (WiFi.SSID(mynetwork.WiFiIndex).length() +1));
        
        WiFi.begin(ssid);

        while ((mynetwork.MyNetStatus() != 3) && (digitalRead(ESC) != LOW)) {
          mydisp.clearMyDisplay();
          mydisp.updateMyDisplay(0, 0, "Connecting to " + String(ssid));
          mydisp.updateMyDisplay(0, 10, mynetwork.GetWiFiStatus(WiFi.status()));
          delay(500);
        }
        
        if (mynetwork.MyNetStatus() == 3) {
          mydisp.clearMyDisplay();
          mydisp.updateMyDisplay(0, 0, "Connected");
          mydisp.updateMyDisplay(0, 10, "IP: " + String(WiFi.localIP()[0]) + "." + String(WiFi.localIP()[1]) + "." + String(WiFi.localIP()[2]) + "." + String(WiFi.localIP()[3]));
          delay(500);
        }

        if (digitalRead(ESC) == LOW) {
          mynetwork.WiFiScanned = 0;
          mynetwork.WiFiIndex = 0;
          mynetwork.DisplayUpdate = true;
        }
        
      }
      if (digitalRead(DOWN) == LOW) {
        mynetwork.WiFiIndex++;
        mynetwork.DisplayUpdate = true;
        if (mynetwork.WiFiIndex > mynetwork.WiFiCount - 1) {
          mynetwork.WiFiIndex = mynetwork.WiFiCount - 1;
        }
      }

      if (mynetwork.DisplayUpdate) {     
        mydisp.clearMyDisplay();
        mydisp.updateMyDisplay(0, 0, "Networks: " + String(mynetwork.WiFiCount));
        mydisp.updateMyDisplay(0, 10, String(mynetwork.WiFiIndex + 1) + ": " + WiFi.SSID(mynetwork.WiFiIndex));
        mydisp.updateMyDisplay(0, 20, "Channel: " + String(WiFi.channel(mynetwork.WiFiIndex)));
        mydisp.updateMyDisplay(0, 30, "Strength: " + String(WiFi.RSSI(mynetwork.WiFiIndex)));
        mydisp.updateMyDisplay(0, 40, "Encryption: " + mynetwork.GetWiFiEncryption(WiFi.encryptionType(mynetwork.WiFiIndex)));
        mynetwork.DisplayUpdate = false;
        delay(200);
      }
    }
  }
  else {
    if (digitalRead(ESC) == LOW) {
      WiFi.disconnect();
      //WiFiScanned = false;
      mynetwork.WiFiScanned = false;
      mynetwork.WiFiIndex = 0;
      mynetwork.DisplayUpdate = true;
    }  
  }
}
/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 by Daniel Eichhorn
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */
