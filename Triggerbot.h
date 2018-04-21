#pragma once

#include "ProcMem.h";

class Triggerbot
{
public:
	Triggerbot();
	~Triggerbot();

protected:
	ProcMem Mem;

protected:
	const DWORD teamOffset = 0xF0;
	const DWORD healthOffset = 0xFC;
	const DWORD EntLoopDist = 0x10;
	const DWORD playerBase = 0xAA6614;
	const DWORD entityBase = 0x4A838FC;
	const DWORD crosshairOffset = 0xB2A4;

protected:
	DWORD dwClientDLL;
	
public:
	void AttachProcess();
	void Trigger();
};
