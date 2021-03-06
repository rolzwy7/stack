#include "pch.h"
#include <iostream>
#include <string>
#include <windows.h>
#include <TlHelp32.h>

using std::string;
using std::cout;
using std::endl;

DWORD getPidByName(LPCSTR process_name) {
	HANDLE snapshot;
	PROCESSENTRY32 pe;
	pe.dwSize = sizeof(PROCESSENTRY32);
	snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	string tmp = process_name + '\0';
	DWORD ret;
	short it;
	if (Process32First(snapshot, &pe)) {
		do {
			it = 0;
			while (pe.szExeFile[it]) {
				if (process_name[it] != pe.szExeFile[it])
					break;
				++it;
				if(pe.szExeFile[it] == 0) {
					ret = pe.th32ProcessID;  CloseHandle(snapshot);
					return ret;
				}
			}
		} while (Process32Next(snapshot, &pe));
	}
	CloseHandle(snapshot);
	return 0;
}


int main() {
	string a = "DummyExe.exe";
	cout << getPidByName(a.c_str());
	return 0;
}


/*
	// Read process memory
	HANDLE hProcess;
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, 9144);
	int address = 0x0028FE2C;
	int buffer;
	ReadProcessMemory(hProcess, (LPVOID)address, &buffer, sizeof(buffer), NULL);
	cout << buffer;

	// Write process memory
	int value = 9999;
	LPVOID lpFunction = (LPVOID)address;
	DWORD memloc = (DWORD)lpFunction;
	DWORD datasize = sizeof(value);
	if (WriteProcessMemory(hProcess, (LPVOID)address, &value, datasize, NULL)) {
		printf("\r[+] 0x%.8X -> %d    ", address, value);
	}
	else {
		cout << "failed";
	}
*/