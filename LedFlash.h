/*
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *      
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *      
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *      MA 02110-1301, USA.
 */

/*  * * * * * * * * * * * * * * * * * * * * * * * * * * * 
By AWI () 2015
 Class inspired by "Bounce2" library. 
 Main code by Thomas O Fredericks (tof@t-o-f.info)
 Previous contributions by Eric Lowry, Jim Schimpf and Tom Harkaway
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* assign an output to pin and perform actions
on, off, flash, timer 
update should be called as often as possible, only once per loop
depends on millis() function, so avoid sleep...
*/

#ifndef LedFlash_h
#define LedFlash_h

#include <inttypes.h>

#define F_OFF  	0              // flash status values, local in class
#define F_ON   	1
#define F_FLASH 2

class LedFlash
{
public:
  // Create an instance of LedFlash
  LedFlash() ;					// default flash period (ms)

  // Attach to a pin and set initial state
  void attach(int pin) ;
	// Sets the led flash period
  void period(unsigned long flash_freq);
	// Sets the led to flash, optional argument for period in seconds (then to off)
  void flash(int duration = 0) ;	
	// Sets the led to continuous on, optional argument for period in seconds (then to off)
  void on(int duration = 0) ;
	// Sets the led to continuous off
  void off(void) ;
	// Sets the Led to perform current (or future) action for x seconds
  void timer(int Seconds) ;
  
	// Updates the led
	// Returns true if On, false if Off
  bool update(void);
	
protected:
  unsigned long  _flash_freq, _lastUpdate, _flashTime;  // period, counters ()
  uint8_t _curState, _flash_stat ; 
  bool _flashTimer; // status flags
  uint8_t _pin;
};
#endif
