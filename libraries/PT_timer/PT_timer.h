/*A Simple Timer
*fits for ProtoThreads
*By Malc 2012.3.18
*/
#ifndef PT_TIMER_H
#define PT_TIMER_H
typedef struct 
{  unsigned long start, overflow; 
}Timer;

class PT_timer
{
	public:
		PT_timer();
		void setTimer(unsigned long duration);
		unsigned Expired();
	private:
		Timer timer;
		};
#endif