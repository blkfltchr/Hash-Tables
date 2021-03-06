#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/****
  Basic hash table key/value pair
 ****/
typedef struct Pair {
  char *key;
  char *value;
} Pair;

/****
  Basic hash table
 ****/
typedef struct BasicHashTable {
  int capacity;
  Pair **storage;
} BasicHashTable;

/****
  Create a key/value pair to be stored in the hash table.
 ****/
Pair *create_pair(char *key, char *value)
{
  Pair *pair = malloc(sizeof(Pair));
  pair->key = key;
  pair->value = value;

  return pair;
}

/****
  Use this function to safely destroy a hashtable pair.
 ****/
void destroy_pair(Pair *pair)
{
  if (pair != NULL) free(pair);
}

/****
  djb2 hash function

  Do not modify this!
 ****/
unsigned int hash(char *str, int max)
{
  unsigned long hash = 5381;
  int c;
  unsigned char * u_str = (unsigned char *)str;

  while ((c = *u_str++)) {
    hash = ((hash << 5) + hash) + c;
  }

  return hash % max;
}


/****
  Fill this in.

  All values in storage should be initialized to NULL
  (hint: look up `calloc`)
 ****/
BasicHashTable *create_hash_table(int capacity)
{ 
  BasicHashTable *ht = malloc(sizeof(BasicHashTable)); // initialize ht pointer using Basic hashtable struct
  ht->capacity = capacity; // set capacity
  ht->storage = calloc(capacity, sizeof(Pair)); // set storage with calloc (length, sizeof(element))

  return ht; // return ht
}

/****
  Fill this in.

  If you are overwriting a value with a different key, print a warning.

  Don't forget to free any malloc'ed memory!
 ****/
void hash_table_insert(BasicHashTable *ht, char *key, char *value)
{
  unsigned int i = hash(key, ht->capacity); // create index using djb2 hash function
  if (ht->storage[i]) // check if value exists at key
    {
      printf("Warning... overwriting existing value...");
      free(ht->storage[i]); // destroy existing key-value pair
    }
  ht->storage[i] = create_pair(key, value); // create new pair
}

/****
  Fill this in.

  Don't forget to free any malloc'ed memory!
 ****/
void hash_table_remove(BasicHashTable *ht, char *key)
{
  unsigned int i = hash(key, ht->capacity); // create index using djb2 hash function
  if (ht->storage[i]) // check if value exists at key
  {
    free(ht->storage[i]); // destroy existing key-value pair
    ht->storage[i] = NULL; // replace with NULL
  }
}

/****
  Fill this in.

  Don't forget to free any malloc'ed memory!
 ****/
void destroy_hash_table(BasicHashTable *ht)
{
  if (ht) {
    for(int i = 0; i < ht->capacity; i++)
    {
      if(ht->storage[i])
      {
        free(ht->storage[i]); // deleting indexes 
      }
    }
    free(ht->storage);
    free(ht);
  }
}

/****
  Fill this in.

  Should return NULL if the key is not found.
 ****/
char *hash_table_retrieve(BasicHashTable *ht, char *key)
{
  unsigned int i = hash(key, ht->capacity); // create index using djb2 hash function
  if (ht) // check if value exists at key
    {
      for(int i = 0; i < ht->capacity; i++) // loop for as long as index exists
        {
          return ht->storage[i];
          return ht->storage;
          return ht;// return indices, storage and hashtable 
        }  
    }
  return NULL; // return NULL if ht doesn't exist
}




#ifndef TESTING
int main(void)
{
  struct BasicHashTable *ht = create_hash_table(16);

  hash_table_insert(ht, "line", "Here today...\n");

  printf("%s", hash_table_retrieve(ht, "line"));

  hash_table_remove(ht, "line");

  if (hash_table_retrieve(ht, "line") == NULL) {
    printf("...gone tomorrow. (success)\n");
  } else {
    fprintf(stderr, "ERROR: STILL HERE\n");
  }

  destroy_hash_table(ht);

  return 0;
}
#endif
