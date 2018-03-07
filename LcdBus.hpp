/*
 * LcdBus.hpp
 *
 *  Created on: 31.08.2017
 *      Author: Marcin.Andrys
 */

#ifndef LCDBUS_HPP_
#define LCDBUS_HPP_

#include <stdint.h>
#include "Arduino.h"

class LcdBus
{
public:

  static void init(void);

	static void pinConfig(int d0, int d1, int d2, int d3, int rst,
			int rd, int rs, int wr, int cs, int busy);

	static void writeCmd(uint8_t reg, uint8_t value);

	static void readCmd(uint8_t reg, uint8_t &value);

	static void writeData(uint8_t data);

	static void readData(uint8_t &data);

private:

	/* Pins */
	static int d0, d1, d2, d3, rst, rd, rs, wr, cs, busy;

	/* Nibble select low or high 4 bits */
	enum nibble
	{
		eLow, eHigh
	};

	/* Data bus setup */
	static void busWrite(uint8_t data, nibble HL);
	static void busRead(uint8_t &data, nibble HL);

	/* Chip select line */
	static void setCS()
	{
		//digitalWrite(cs, LOW);
	}
	static void clrCS()
	{
    //digitalWrite(cs, LOW);  
	}

	/* Reset line */
	static void setRST()
	{
    /* not needed if reset connected externally */
		digitalWrite(rst, HIGH);
	}
	static void clrRST()
	{
   /* not needed if reset connected externally */
		digitalWrite(rst, LOW);
	}

	/* Read line */
	static void setRD()
	{
		digitalWrite(rd, HIGH);
	}
	static void clrRD()
	{
		digitalWrite(rd, LOW);
	}

	/* Write line */
	static void setWR()
	{
		digitalWrite(wr, HIGH);
	}
	static void clrWR()
	{
		digitalWrite(wr, LOW);
	}

	/* Register select line */
	static void setRS()
	{
		digitalWrite(rs, HIGH);
	}
	static void clrRS()
	{
		digitalWrite(rs, LOW);
	}

	/* Waiting when driver is busy */
	static void waitBusy()
	{
//		while (HIGH == digitalRead(busy))
//		{
//			delay(1);
//		}
	}

};

#endif /* LCDBUS_HPP_ */
