/*A Simple Timer
*fits for ProtoThreads
*By Malc 2012.3.18
*/
#include "PT_timer.h"
#include "wiring.c"
PT_timer::PT_timer()
{
	
}
void PT_timer::setTimer(unsigned long duration)
{
	timer.start=millis();
	timer.overflow=duration;
	}
unsigned PT_timer::Expired()
{
	return millis()-timer.start>=timer.overflow;
	}