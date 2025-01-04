#pragma once

//Returns a hash that uses every second byte
// XORed together
char hash_1(char const* str);

//Returns the hash as an int.
//Uses a sliding window of size sizeof(int)
// that moves sizeof(int) spots to the right
// on each iteration.
//Uses XOR as hash function of each window.
int hash_2(char const* str);