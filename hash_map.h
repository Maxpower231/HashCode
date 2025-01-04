#pragma once

typedef struct hash_map_s HashMap;
//typedef int (*hashStringToIntfp)(char const *);

HashMap* createNewHashMap(unsigned arraySize, int (*intHash_pfnc)(const *input));

int insertIntoHashMap(HashMap* map, char const* key, char const* value);
char const* readFromHashMap(HashMap* map, char const* key);
int isKeyInHashMap(HashMap* map, char const* key);