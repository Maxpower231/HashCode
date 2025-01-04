#include "my_hashes.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char* argv[]) {
	char const* strs1[] = {
		"Hello world",
		"Hallo warld",
		"Goodbye world",
		"Jello world"
	};
	for (int i = 0; i < 4; ++i) {
		printf("hash_1 of %s: %d\n", strs1[i], (int)hash_1(strs1[i]));
	}
	char const *strs2[] = {
		"hel",
		"he",
		"h",
		""
	};

	for (int i = 0; i < 4; ++i) {
		int hashOut = hash_2(strs2[i]);
		printf("hash_2 of  %s: %d\n", strs2[i], hashOut);
		
		printf("\t %x", hashOut);
		for (int j = 0; j < strnlen_s(strs2[i], 1000); ++j) {
			printf("\t%x", strs2[j]);
		}
		printf("\n");
		
	}

	for (int i = 0; i < 4; ++i) {
		printf("hash_2 of %s: %d\n", strs1[i], (int)hash_2(strs1[i]));
	}
	return 0;
}