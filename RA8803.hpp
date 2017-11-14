/*
 * RA8803.hpp
 *
 *  Created on: 30.08.2017
 *      Author: Marcin.Andrys
 */

#ifndef RA8803_HPP_
#define RA8803_HPP_

#include <stdint.h>
#include <Adafruit_GFX.h>

#include "LcdBus.hpp"

/* LCD registers */
#define LCD_WLCR  0x00  //Whole chip LCD Controller Register
#define LCD_MISC  0x01  //Mosc. Register
#define LCD_ASPR  0x02
#define LCD_ADSR  0x03
#define LCD_WCCR  0x10
#define LCD_DOWL  0x11
#define LCD_MAMR  0x12

#define LCD_AWRR  0x20
#define LCD_AWBR  0x30
#define LCD_AWLR  0x40
#define LCD_AWTR  0x50
#define LCD_DWRR  0x21
#define LCD_DWBR  0x31
#define LCD_DWLR  0x41
#define LCD_DWTR  0x51

#define LCD_CPXR  0x60
#define LCD_BGSG  0x61
#define LCD_CPYR  0x70
#define LCD_BGCM  0x71
#define LCD_EDCM  0x72
#define LCD_BTMR  0x80
#define LCD_SCCR  0x90

#define LCD_LCCR  0xd0  //LCD Contrast Control Register
#define LCD_TPCR  0xc0  //Touch Panel Control Register
#define LCD_TPSR  0xc1  //Touch Panel Status Register
#define LCD_TPXR  0xc8  //Touch Panel Segment High Byte Data Register
#define LCD_TPYR  0xc9  //Touch Panel Common High Byte Data Register
#define LCD_TPZR  0xca  //Touch Panel Segment&Common Low Byte Data Register
#define LCD_PNTR  0xe0
#define LCD_FNCR  0xf0
#define LCD_FVHT  0xf1

/* LCD config */
#define LCD_MAMR_B1  (0x80 | 0x21)
#define LCD_MAMR_B2  (0x80 | 0x12)
#define LCD_MAMR_VALUE  (0x80 | 0x11)
#define LCD_WLCR_VALUE  0xc4
#define LCD_MISC_VALUE  0x43
#define LCD_DOWL_VALUE  0x00
#define LCD_DWTR_VALUE  0
#define LCD_DWBR_VALUE  0x2f
#define LCD_DWLR_VALUE  0
#define LCD_DWRR_VALUE  0x27
#define LCD_AWTR_VALUE  0
#define LCD_AWBR_VALUE  0x2f
#define LCD_AWLR_VALUE  0
#define LCD_AWRR_VALUE  0x27
#define LCD_PNTR_VALUE  0x00
#define LCD_CPXR_VALUE  0x00
#define LCD_BGSG_VALUE  0x00
#define LCD_CPYR_VALUE  0x00
#define LCD_BGCM_VALUE  0x00
#define LCD_EDCM_VALUE  0xef
#define LCD_SCCR_VALUE  50
#define LCD_FNCR_VALUE  0x84
#define LCD_FVHT_VALUE  0x0f
#define LCD_TPCR_VALUE  0xc8
#define LCD_TPSR_VALUE  0x3a
#define LCD_TPXR_VALUE  0x80
#define LCD_TPYR_VALUE  0x80
#define LCD_TPZR_VALUE  0x00
#define LCD_LCCR_VALUE  0x00
#define LCD_APSR_VALUE  0x10
#define LCD_ADSR_VALUE  0x80
#define LCD_WCCR_VALUE  0xA8
#define LCD_BTMR_VALUE  0xff

template<typename Bus>
class RA8803 : public Adafruit_GFX
{
	public:

    RA8803(uint32_t dimX, uint32_t dimY);
    
		void init();
		void clear();
		void fill();
		void setXY(int x, int y);
		void drawPixel(int16_t x, int16_t y, uint16_t color) ;
		void drawBuffer(uint8_t * buffer, uint32_t size);
    void display();

	private:
		uint32_t xDimension, yDimension;
    //TODO Better buffer allocation
		uint8_t framebuffer[1920];
};


#endif /* RA8803_HPP_ */
