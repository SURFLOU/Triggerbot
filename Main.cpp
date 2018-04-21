#include "Triggerbot.h"

Triggerbot Trigger;

int main()
{
	Trigger.AttachProcess();
	Trigger.Trigger();

	return 0;
} 
