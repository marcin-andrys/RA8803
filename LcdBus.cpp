/*
 * LcdBus.cpp
 *
 *  Created on: 31.08.2017
 *      Author: Marcin.Andrys
 */
#include <stdint.h>
#include "Arduino.h"
#include "LcdBus.hpp"

int LcdBus::d0 = 12;
int LcdBus::d1 = 5;
int LcdBus::d2 = 4;
int LcdBus::d3 = 2;

int LcdBus::rst = 0;
int LcdBus::rd = 13;
int LcdBus::rs = 16;
int LcdBus::wr = 14;
int LcdBus::cs = 0;
int LcdBus::busy = 0;

void LcdBus::pinConfig(int d0, int d1, int d2, int d3, int rst, int rd, int rs,
		int wr, int cs, int busy)
{

	LcdBus::d0 = d0;
	LcdBus::d1 = d1;
	LcdBus::d2 = d2;
	LcdBus::d3 = d3;

	LcdBus::rst = rst;
	LcdBus::rd = rd;
	LcdBus::rs = rs;
	LcdBus::wr = wr;
	LcdBus::cs = cs;
	LcdBus::busy = busy;
}

void LcdBus::init()
{
	pinMode(d0, OUTPUT);
	pinMode(d1, OUTPUT);
	pinMode(d2, OUTPUT);
	pinMode(d3, OUTPUT);

	//pinMode(rst, OUTPUT);
	pinMode(rd, OUTPUT);
	pinMode(rs, OUTPUT);
	pinMode(wr, OUTPUT);
	//pinMode(cs, OUTPUT);
	//pinMode(busy, INPUT);

	busWrite(0x00, eHigh);
	setCS();
	setRD();
	setWR();
	setRS();
  delay(100);

	setRST();
	clrCS();
	delay(100);
	clrRST();
	delay(100);
	setRST();
	delay(100);
}

void LcdBus::busWrite(uint8_t data, nibble HL)
{

	pinMode(d0, OUTPUT);
	pinMode(d1, OUTPUT);
	pinMode(d2, OUTPUT);
	pinMode(d3, OUTPUT);

	if (eLow == HL)
	{
		digitalWrite(d0, (data & 0x01) != 0 ? HIGH : LOW);
		digitalWrite(d1, (data & 0x02) != 0 ? HIGH : LOW);
		digitalWrite(d2, (data & 0x04) != 0 ? HIGH : LOW);
		digitalWrite(d3, (data & 0x08) != 0 ? HIGH : LOW);
	}
	else
	{
		digitalWrite(d0, (data & 0x10) != 0 ? HIGH : LOW);
		digitalWrite(d1, (data & 0x20) != 0 ? HIGH : LOW);
		digitalWrite(d2, (data & 0x40) != 0 ? HIGH : LOW);
		digitalWrite(d3, (data & 0x80) != 0 ? HIGH : LOW);
	}
}

void LcdBus::busRead(uint8_t &data, nibble HL)
{

	pinMode(d0, INPUT);
	pinMode(d1, INPUT);
	pinMode(d2, INPUT);
	pinMode(d3, INPUT);

	if (eLow == HL)
	{
		data &= 0xF0;
		data |= digitalRead(d0) << 0x00;
		data |= digitalRead(d1) << 0x01;
		data |= digitalRead(d2) << 0x02;
		data |= digitalRead(d3) << 0x03;
	}
	else
	{
		data &= 0x0F;
		data |= digitalRead(d0) << 0x04;
		data |= digitalRead(d1) << 0x05;
		data |= digitalRead(d2) << 0x06;
		data |= digitalRead(d3) << 0x07;
	}
}

void LcdBus::writeCmd(uint8_t reg, uint8_t value)
{

	clrCS();
	setRD();
	clrRS();
	busWrite(reg, eHigh);
	clrWR();
	setWR();
	busWrite(reg, eLow);
	clrWR();
	setWR();
	setRS();
	setCS();

	clrCS();
	setRD();
	clrRS();
	busWrite(value, eHigh);
	clrWR();
	setWR();
	busWrite(value, eLow);
	clrWR();
	setWR();
	setCS();
}

void LcdBus::readCmd(uint8_t reg, uint8_t &value)
{

	clrCS();
	setRD();
	clrRS();
	busWrite(reg, eHigh);
	clrWR();
	setWR();
	busWrite(reg, eLow);
	clrWR();
	setWR();
	setRS();
	setCS();

	clrCS();
	setWR();
	clrRS();
	clrRD();
	busRead(value, eHigh);
	setRD();
	clrRD();
	busRead(value, eLow);
	setRD();
	setRS();
	setCS();

}

void LcdBus::writeData(uint8_t data)
{

	waitBusy();

	clrCS();
	setRD();
	setRS();
	busWrite(data, eHigh);
	clrWR();
	setWR();
	busWrite(data, eLow);
	clrWR();
	setWR();
	setRS();
	setCS();

}

void LcdBus::readData(uint8_t &data)
{
	clrCS();
	setWR();
	setRS();
	clrRD();
	busRead(data, eHigh);
	setRD();
	clrRD();
	busRead(data, eLow);
	setRD();
	setRS();
	setCS();
}
