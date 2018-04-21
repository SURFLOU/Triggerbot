#include "ProcMem.h"

using namespace std;

#pragma region Misc Functions

ProcMem::ProcMem() {

}

ProcMem::~ProcMem() {
	CloseHandle(hProcess);
}


int ProcMem::chSizeOfArray(char *chArray) {


	for (int iLength = 1; iLength < MAX_PATH; iLength++)
		if (chArray[iLength] == '*')
			return iLength;

	cout << "\nLENGTH: Failed To Read Length Of Array\n";
	return 0;
}


int ProcMem::iSizeOfArray(int *iArray) {


	for (int iLength = 1; iLength < MAX_PATH; iLength++)
		if (iArray[iLength] == '*')
			return iLength;

	cout << "\nLENGTH: Failed To Read Length Of Array\n";
	return 0;
}


bool ProcMem::iFind(int *iAry, int iVal) {

	for (int i = 0; i < 64; i++)
		if (iVal == iAry[i] && iVal != 0)
			return true;

	return false;
}

#pragma endregion



#pragma region Memory Functions


void ProcMem::Process(char* ProcessName) {


	HANDLE hPID = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	PROCESSENTRY32 ProcEntry;
	ProcEntry.dwSize = sizeof(ProcEntry);


	do
		if (!strcmp(ProcEntry.szExeFile, ProcessName))
		{


			dwPID = ProcEntry.th32ProcessID;
			CloseHandle(hPID);


			hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPID);
			return;
		}
	while (Process32Next(hPID, &ProcEntry));

	cout << "\nPROCESS: Process Not Found\n";
	system("pause");
	exit(0);
}


void ProcMem::Patch(DWORD dwAddress, char *Patch_Bts, char *Default_Bts) {


	int iSize = chSizeOfArray(Default_Bts);


	if (!bPOn)
		for (int i = 0; i < iSize; i++)
			Read<BYTE>(dwAddress + i, Patch_Bts[i]);
	else
		for (int i = 0; i < iSize; i++)
			Read<BYTE>(dwAddress + i, Default_Bts[i]);

	bPOn = !bPOn;
}

DWORD ProcMem::AOB_Scan(DWORD dwAddress, DWORD dwEnd, char *Bytes) {


	int iBytesToRead = 0, iTmp = 0;
	int length = chSizeOfArray(Bytes);
	bool bTmp = false;


	if (Bytes[0] == '?')
	{
		for (; iBytesToRead < MAX_PATH; iBytesToRead++)
			if (Bytes[iBytesToRead] != '?')
			{
				iTmp = (iBytesToRead + 1);
				break;
			}
	}


	for (; dwAddress < dwEnd; dwAddress++)
	{
		if (iBytesToRead == length)
			return dwAddress - iBytesToRead;

		if (Read<BYTE>(dwAddress) == Bytes[iBytesToRead] || (bTmp && Bytes[iBytesToRead] == '?'))
		{
			iBytesToRead++;
			bTmp = true;
		}
		else
		{
			iBytesToRead = iTmp;
			bTmp = false;
		}
	}

	cout << "\nAOB_SCAN: Failed To Find Byte Pattern\n";
	return 0;
}


DWORD ProcMem::Module(LPSTR ModuleName) {


	HANDLE hModule = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPID);
	MODULEENTRY32 mEntry;
	mEntry.dwSize = sizeof(mEntry);


	do
		if (!strcmp(mEntry.szModule, ModuleName))
		{
			CloseHandle(hModule);
			return (DWORD)mEntry.modBaseAddr;
		}
	while (Module32Next(hModule, &mEntry));

	cout << "\nMODULE: Process Platform Invalid\n";
	return 0;
}

#pragma endregion
