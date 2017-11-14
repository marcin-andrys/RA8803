/*
 * RA8803.cpp
 *
 *  Created on: 30.08.2017
 *      Author: Marcin.Andrys
 */
#include "RA8803.hpp"

template<typename Bus>
RA8803<Bus>::RA8803(uint32_t dimX, uint32_t dimY): Adafruit_GFX(320, 48)
{
  xDimension = dimX;
  yDimension = dimY;
}

template<typename Bus>
void RA8803<Bus>::init()
{
  Bus::init();

	Bus::writeCmd(LCD_WLCR, LCD_WLCR_VALUE);
	Bus::writeCmd(LCD_BTMR, LCD_BTMR_VALUE);
	Bus::writeCmd(LCD_MISC, LCD_MISC_VALUE);

	Bus::writeCmd(LCD_ASPR, LCD_APSR_VALUE);
	Bus::writeCmd(LCD_ADSR, LCD_ADSR_VALUE);
	Bus::writeCmd(LCD_WCCR, LCD_WCCR_VALUE);
	Bus::writeCmd(LCD_MAMR, LCD_MAMR_VALUE);

	Bus::writeCmd(LCD_DOWL, LCD_DOWL_VALUE);
	Bus::writeCmd(LCD_AWTR, LCD_AWTR_VALUE);
	Bus::writeCmd(LCD_AWBR, LCD_AWBR_VALUE);
	Bus::writeCmd(LCD_AWLR, LCD_AWLR_VALUE);
	Bus::writeCmd(LCD_AWRR, LCD_AWRR_VALUE);
	Bus::writeCmd(LCD_DWTR, LCD_DWTR_VALUE);
	Bus::writeCmd(LCD_DWBR, LCD_DWBR_VALUE);
	Bus::writeCmd(LCD_DWLR, LCD_DWLR_VALUE);
	Bus::writeCmd(LCD_DWRR, LCD_DWRR_VALUE);

	Bus::writeCmd(LCD_CPXR, LCD_CPXR_VALUE);
	Bus::writeCmd(LCD_BGSG, LCD_BGSG_VALUE);
	Bus::writeCmd(LCD_CPYR, LCD_CPYR_VALUE);
	Bus::writeCmd(LCD_BGCM, LCD_BGCM_VALUE);
	Bus::writeCmd(LCD_EDCM, LCD_EDCM_VALUE);
	Bus::writeCmd(LCD_SCCR, LCD_SCCR_VALUE);

	Bus::writeCmd(LCD_TPCR, LCD_TPCR_VALUE);
	Bus::writeCmd(LCD_TPSR, LCD_TPSR_VALUE);
	Bus::writeCmd(LCD_TPXR, LCD_TPXR_VALUE);
	Bus::writeCmd(LCD_TPYR, LCD_TPYR_VALUE);
	Bus::writeCmd(LCD_TPZR, LCD_TPZR_VALUE);

	Bus::writeCmd(LCD_LCCR, LCD_LCCR_VALUE);
	Bus::writeCmd(LCD_PNTR, LCD_PNTR_VALUE);

	Bus::writeCmd(LCD_FNCR, LCD_FNCR_VALUE);
	Bus::writeCmd(LCD_FVHT, LCD_FVHT_VALUE);
	clear();
	delay(10);

}

template<typename Bus>
void RA8803<Bus>::clear()
{
	uint8_t reg;
//	Bus::writeCmd(0xe0, 0x00);
//	Bus::readCmd(0xf0,reg);
//	reg &= 0xf7;
//	reg |= 0x08;
//	Bus::writeCmd(0xf0, reg);

  memset(framebuffer, 0, 1920);
 
	delay(1);
}

template<typename Bus>
void RA8803<Bus>::fill()
{
	unsigned char reg;
//	Bus::writeCmd(0xe0, 0xff);
//	Bus::readCmd(0xf0,reg);
//	reg &= 0xf7;
//	reg |= 0x08;
//	Bus::writeCmd(0xf0, reg);

  memset(framebuffer, 0xff, 1920);
 
	delay(1);
}

template<typename Bus>
void RA8803<Bus>::setXY(int x, int y)
{
	Bus::writeCmd(LCD_CPXR, x);
	Bus::writeCmd(LCD_CPYR, y);
}

template<typename Bus>
void RA8803<Bus>::drawPixel(int16_t x, int16_t y, uint16_t color) 
{
	  uint32_t buffer_pos = (x>>3)+y*(xDimension>>3);

	  if(buffer_pos < (xDimension * yDimension/8)){
    if(color != 0)
	    framebuffer[buffer_pos] |=1<<(7 - x%8);
     else
      framebuffer[buffer_pos] &=~(1<<(7 - x%8));
	  }
}

template<typename Bus>
void RA8803<Bus>::display(){
  uint32_t size = xDimension * yDimension/8;
  uint8_t * buffer = framebuffer;
  static uint8_t buffer_id = 0;
  
	Bus::writeCmd(0x60,0x00);
	Bus::writeCmd(0x70,0x00);

	  while(size--){
		  Bus::writeData(*buffer++);
	  }
   
  if(0 == buffer_id)
  {
    buffer_id = 1;
    Bus::writeCmd(LCD_MAMR, LCD_MAMR_B1);
  }else{
    buffer_id = 0;
    Bus::writeCmd(LCD_MAMR, LCD_MAMR_B2);
  }
}
