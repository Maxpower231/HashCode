#include "my_hashes.h"

#include <string.h>

//Returns a hash that uses every second byte
// XORed together
char hash_1(char const* str) {
	char hashOut = 0;
	for (int i = 0; i < strnlen_s(str, 1000); i += 2) {
		hashOut ^= str[i];
	}
	return hashOut;
}

//Returns the hash as an int.
//Uses a sliding window of size sizeof(int)
// that moves sizeof(int) spots to the right
// on each iteration.

int hash_2(char const* str) {
	int length = strnlen_s(str, 1000);
	int hashOut = 0;
	//If length is less than 4, we just grab the first
	// couple of bytes and produce an int from that.
	if (length < 4) {
		for (int i = 0; i < 4; ++i) {
			if (i < length) {
				hashOut += str[i];
			}
			if (i < 3) {
				hashOut <<= 8;
			}
		}
		return hashOut;
	}
	//Otherwise we walk the string and move the sliding window
	int intsize = sizeof(int);
	for (int i = 0; i + intsize - 1 < length; i += 2) {
		char const* strptr = str + i;
		int const* intptr = (int const*)strptr;
		hashOut ^= *intptr;
	}
	return hashOut;
}