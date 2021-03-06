#ifndef COOKIEBOYDIVIDER_H
#define COOKIEBOYDIVIDER_H

#include "CookieboyDefs.h"

namespace Cookieboy
{

/*
Very simple timer. Clocked at 16384 Hz. Doesn't generate any interrupts. Loops from 0 to 255.
*/
class DividerTimer
{
public:
	DividerTimer(const bool &_CGB, const bool &_CGBDoubleSpeed) : CGB(_CGB), CGBDoubleSpeed(_CGBDoubleSpeed)
	{
		Reset();
	}
	
	void Step(DWORD clockDelta)
	{
		//In double speed mode DIV operates twice as fast
		if (CGB && CGBDoubleSpeed)
		{
			clockDelta *= 2;
		}

		ClockCounter += clockDelta;

		//Divider increments every 256 ticks
		if (ClockCounter >= 256)
		{
			int passedPeriods = ClockCounter / 256;
			ClockCounter %= 256;

			DIV += passedPeriods;
		}
	}

	void Reset()
	{
		ClockCounter = 0;
		DIV = 0;
	}

	void EmulateBIOS()
	{
		Reset();
	}

	void DIVChanged(BYTE value)
	{
		DIV = 0; 
	}

	BYTE GetDIV() 
	{
		return DIV;
	}
	
private:
	const bool &CGB;
	const bool &CGBDoubleSpeed;

	DWORD ClockCounter;
	
	BYTE DIV;	//Divider Register (R/W)
				//This register is incremented 16384 (~16779 on SGB) times a second. Writing any value sets it to $00
};

}

#endif