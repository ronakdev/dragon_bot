/* Copyright (c) <2016> <mmg005@eng.ucsd.edu >
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of
* this software and associated documentation files (the "Software"), to deal in 
* the Software without restriction, including without limitation the rights to use,
* copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the
* Software, and to permit persons to whom the Software is furnished to do so, 
* subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all 
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
* PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
* HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
* OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "RGBLED.h"

// Constructor to save pins
RGBLED::RGBLED(int red, int green, int blue, bool common_anode):
     red_pin(red),
     green_pin(green),
     blue_pin(blue),
     common_anode(common_anode)
{
}

void RGBLED::set(int red, int green, int blue)
{
  //set LED color
  if (common_anode) {
    analogWrite(red_pin, 255-red);
    analogWrite(green_pin, 255-green);
    analogWrite(blue_pin, 255-blue);
  }
  else {
    analogWrite(red_pin, red);
    analogWrite(green_pin,  green);
    analogWrite(blue_pin, blue);

  }

  this->prev_red = red;
  this->prev_green = green;
  this->prev_blue = blue;

}

// Fade in a specific amount of time and steps
void RGBLED::fade(int red, int green, int blue, int step, int period)
{
  int diff_red = red - prev_red;
  int diff_green = green - prev_green;
  int diff_blue = blue - prev_blue;

  // Calculate increments
  int step_red = diff_red / step;
  int step_green = diff_green / step;
  int step_blue = diff_blue / step;

  for ( int i = step - 1; i >=0 ; i--) {
    // set the color
    this->set(
      red - i * step_red,
      green - i * step_green,
      blue - i * step_blue
    );

    // delay
    delay(period/step);

  }

}

void RGBLED::setup()
{
  this->set(255, 0, 0);
}

void RGBLED::loop()
{
  static unsigned long timer;
  static int state; // 0 for R, 1 for G, 2 for B
  unsigned long delay_time = 2000;

  if (millis() - timer > delay_time)
  {
    if (state == 0)
    {
      this->set(0, 255, 0);
      state = 1;
    }
    else if (state == 1)
    {
      this->set(0, 0, 255);
      state = 2;
    }
    else if (state == 2)
    {
      this->set(255, 0, 0);
      state = 0;
    }
    timer = millis();
  }
}

