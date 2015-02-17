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
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "LedFlash.h"

  // Create an instance of LedFlash
  LedFlash::LedFlash() {
	_flash_freq = 200;				// default flash period (ms)
}

  // Attach to a pin and set initial state
  void LedFlash::attach(int pin) {
	_pin = pin;					// assign pin
	_curState = LOW;
	_flash_stat = F_OFF ;
	digitalWrite(_pin,LOW);	// set Led to low
	_lastUpdate = millis();				// set timer value
	}

	// Sets the led flash period
  void LedFlash::period(unsigned long flash_freq) {
	_flash_freq = flash_freq;
  }	

  // Sets the led to flash
  void LedFlash::flash(int duration) {
	_flash_stat = F_FLASH;
	if (duration != 0){
		_flashTime = duration * 1000 + millis() ;  // set the timer values to milliseconds from now
		_flashTimer = true ;
	}
  }	

  // Sets the led to on
  void LedFlash::on(int duration) {
	_flash_stat = F_ON;
	_curState = HIGH;
	if (duration != 0){
		_flashTime = duration * 1000 + millis() ;  // set the timer values to milliseconds from now
		_flashTimer = true ;
	}
  }	

  // Sets the led to off
  void LedFlash::off(void) {
	_flash_stat = F_OFF;
	_curState = LOW;
  }	

  // Sets the Led to perform current (or future) action for x seconds
  void LedFlash::timer(int Seconds){
	_flashTime = Seconds * 1000 + millis() ;  // set the timer values to milliseconds from now
	_flashTimer = true ;
  }
  
	// Updates the led
	// Returns true if On, false if Off
  bool LedFlash::update(void) {
	if (_flash_stat == F_FLASH){ 		// if flashing change state after xx millis
		if (millis()-_lastUpdate > _flash_freq){
			if (_curState == LOW){		// change state
				_curState = HIGH;
			} else {
				_curState = LOW;
			}
			_lastUpdate = millis();
		}
	}
	if (_flashTimer){					// if timer is on check if expired
		if (millis() > _flashTime){
			_flashTimer = false ; 		// if expires switch off and reset Timer status
			_flash_stat = F_OFF ;
			_curState = LOW;
		}
	}
	digitalWrite(_pin, _curState);	// update led with current status
	// Returns the updated pin state
	return _curState;
  }
