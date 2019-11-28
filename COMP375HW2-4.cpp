// COMP375HW2-4.cpp : This file contains the 'main' function. Program execution begins and ends there.
// This program displays information about the kind of processor the user has
// Written by John Orekunrin

#include <iostream>
using namespace std;

char brand[49]; // name of the CPU
int save1, save2, save3; // place to save temporary values
int idCode = 0x80000001; // one less than input to cpuid instruction
int main(int argc, char* argv[]) {
	_asm {
		lea esi, brand // get the address of the beginning of array
		again : inc idCode // go to the next cpuid code
				mov eax, idCode // get cpuid code
				cmp eax, 0x80000005 // done all 4 values
				je done
				cpuid // get CPU information
				mov save1, ebx // save results
				mov save2, ecx
				mov save3, edx
				call savechar
				mov eax, save1 // get ebx word of result
				call savechar
				mov eax, save2 // get ecx word of result
				call savechar
				mov eax, save3 // get edx word of result
				call savechar
				jmp again
				savechar :		// Your method here
					mov [esi], al 	// saves the lower byte in the array
					shr eax, 8	// effectively shifts esi 8 bits (or 1 byte)
					inc esi	//  Points to the next byte
					mov [esi], al 	// saves the lower byte in the array
					shr eax, 8	// effectively shifts esi 8 bits (or 1 byte)
					inc esi	//  Points to the next byte
					mov [esi], al 	// saves the lower byte in the array
					shr eax, 8	// effectively shifts esi 8 bits (or 1 byte)
					inc esi	//  Points to the next byte
					mov [esi], al 	// saves the lower byte in the array
					inc esi	//  Points to the next byte
					ret
	done: mov[esi], 0 // terminate string with a null
	}
	cout << brand << endl; // display data from cpuid instruction
	return 0;
}