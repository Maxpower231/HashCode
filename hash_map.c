#include "hash_map.h"

#include <stdlib.h>
#include <string.h>

#define MAX_KEY_LENGTH 100
#define MAX_VALUE_LENGTH 1000

typedef struct ll_node_s {
	char *key;
	char* value;
	struct ll_node_s *next;
}MapNode;

typedef struct hash_map_s {
	MapNode **nodeArray;  
	unsigned arraySize;
	int (*intHash_pfnc)(char const* input);
}HashMap;

HashMap* createNewHashMap(unsigned arraySize, int (*intHash_pfnc)(char const* input)) {
	if (!intHash_pfnc) {
		return NULL;
	}
	HashMap* map = malloc(sizeof(*map));
	if (!map) {
		return NULL;
	}
	if (arraySize == 0) {
		arraySize = 10;
	}
	MapNode** nodes = malloc(sizeof(*nodes) * arraySize);
	if (!nodes) {
		free(map);
		return NULL;
	}
	for (unsigned i = 0; i < arraySize; ++i) {
		nodes[i] = NULL;
	}
	map->arraySize = arraySize;
	map->nodeArray = nodes;
	map->intHash_pfnc = intHash_pfnc;

	return map;
}


MapNode* createNewNode(char const* key, char const* value, MapNode* pnext) {
	MapNode* pnode = malloc(sizeof(*pnode));
	if (!pnode) {
		return NULL;
	}
	unsigned keyLen = strnlen_s(key, MAX_KEY_LENGTH) + 1;
	unsigned valueLen = strnlen_s(value, MAX_KEY_LENGTH) + 1;
	char* keyStr = malloc(keyLen);
	char* valueStr = malloc(valueLen);
	if (!keyStr || !valueStr) {
		free(keyStr);
		free(valueStr);
		free(pnode);
		return NULL;
	}
	strcpy_s(keyStr, keyLen, key); 
	strcpy_s(valueStr, valueLen, key);

	pnode->key = keyStr;
	pnode->value = valueStr;
	pnode->next = pnext;

	return pnode;
}

int insertIntoHashMap(HashMap* map, char const* key, char const* value) {
	//Check if the map is NULL or not
	if (!map) {
		return 0;
	}
	//Calculate the index into the table
	int hash = map->intHash_pfnc(key);
	int index = hash % map->arraySize;
	MapNode* node = map->nodeArray[index];
	//Is there anything in this list?
	if (!node) {
		//Nope, first time this element of the array has been accessed.
		//Need to make a new list.
		MapNode* newNode = createNewNode(key, value, NULL);
		if (!newNode) {
			//Whoops, can't create new node for whatever reason
			return 0;
		}
		map->nodeArray[index] = newNode;
	}
	else {
		//There is at least one node already at this index.
		MapNode* currentNode = node;
		while (currentNode != NULL) {
			//Is this key a match?
			if (strcmp(currentNode->key, key) == 0) {
				//This key is a match, so all we need to do is
				// update the value node.
				//We can just check if the value has actually changed or not
				if (strcmp(currentNode->value, value) != 0) {
					//Allocate memory for the new value string
					char* newValue = malloc(strlen(value) + 1);
					if (!newValue) {
						return 0;
					}
					//Copy the text into the string
					strcpy_s(newValue, strlen(value) + 1, value);
					//Free the old value
					free(currentNode->value);
					//Assign the new value
					currentNode->value = newValue;
				}
				break;
			}
			currentNode = currentNode->next;
		}
		//If when we get here the currentNode is equal to NULL, it 
		// means we went through the entire list without finding
		// a node that has this key. So we make a new one.
		if (currentNode == NULL) {
			MapNode* newNode = createNewNode(key, value, map->nodeArray[index]);
			if (!newNode) {
				return 0;
			}
			map->nodeArray[index] = newNode;
		}
	}
	return 1;

	/*
	int hash = map->intHash_pfnc(key);
	unsigned index = hash % map->arraySize;
	MapNode *head = map->nodeArray[index];
	//Two cases here: if head is NULL, this is the first time this
	// hash has appeared, so we just insert this key-value pair as the head node.
	if (head == NULL) {
		//Create new head for empty list
		MapNode *newNode = createNewNode(key, value, NULL);
		if (!newNode) {
			return 0;
		}
		map->nodeArray[index] = newNode;
		return 1;
	}
	else {
		//Check if node already exists or not
		MapNode *current = head;
		while (current != NULL) {
			if (strcmp(current->key, key)) {
				//This is a match, replace the old value with the new value
				char *newValue = malloc(strnlen_s(value, MAX_VALUE_LENGTH) + 1);
				if (!newValue) {
					//Not enough memory for the new value.
					return 0;
				}
				strcpy_s(newValue, strnlen_s(value, MAX_VALUE_LENGTH) + 1, value);
				free(current->value);
				current->value = newValue;
				return 1;
			}
			current = current->next;
		}
		//If we get here, we reached the end of the list without finding our key
		// So we need to add a new node.
		MapNode *newNode = createNewNode(key, value, head);
		if (!newNode) {
			return 0;
		}
		map->nodeArray[index] = newNode;
		return 1;
	}
	*/
}

int isKeyInHashMap(HashMap *map, char const *key) {
	if (!map) {
		return 0;
	}
	int hash = map->intHash_pfnc(key);
	int index = hash % map->arraySize;
	MapNode* node = map->nodeArray[index];
	if (!node) {
		return 0;
	}
	MapNode* current = node;
	while (current) {
		if (strcmp(key, current->key) == 0) {
			return 1;
		}
		current = current->next;
	}
}

char const *readFromHashMap(HashMap *map, char const *key){
	if (!map) {
		return NULL;
	}
	int hash = map->intHash_pfnc(key);
	int index = hash % map->arraySize;
	MapNode* node = map->nodeArray[index];
	if (!node) {
		return NULL;
	}
	MapNode* current = node;
	while (current) {
		if (strcmp(key, current->key) == 0) {
			return current->value;
		}
		current = current->next;
	}
	return NULL;
}





