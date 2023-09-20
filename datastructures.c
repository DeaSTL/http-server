#include "datastructures.h"
#include <stdlib.h>
#include <string.h>



// Vector: a dynamic array
void dt_vector_create(dt_vector *vector,unsigned int initial_size,unsigned int element_size){
  vector->size = initial_size;
  vector->element_size = element_size;
  vector->data = calloc(initial_size,element_size);
}

void* dt_vector_get(dt_vector *vector,unsigned int index){
  return vector->data + (index * vector->element_size);
}

void dt_vector_set(dt_vector *vector,unsigned int index,void* value){
  memcpy(
      vector->data + (index * vector->element_size),
      value,vector->element_size
      );
}

void dt_vector_resize(dt_vector *vector,unsigned int new_size){
  vector->size = new_size;
  vector->data = realloc(vector->data,new_size * vector->element_size);
}

void dt_vector_destroy(dt_vector *vector){
  free(vector->data);
  free(vector);
}

//Hash Map : a dynamic array of key-value pairs
int dt_hash(void *key, unsigned int key_size){
  int hash = 0;
  #define HASH_CON_1 0x9e3779b9
  #define HASH_CON_2 0xdeadbeef
  #define HASH_CON_3 0xbeefdead
  #define HASH_CON_4 0x69696969
  for(int i = 0; i < key_size; i++){
    hash += ((char*)key)[i] + HASH_CON_1 + (hash << 9) + (hash >> 21) ^ HASH_CON_2;
  }
  return hash;
}
void dt_hashmap_create(dt_hashmap *hashmap,unsigned int element_size){
  hashmap->element_size = element_size;
  dt_vector_create(hashmap->values,10,hashmap->element_size);
  dt_vector_create(hashmap->keys  ,10,sizeof(int));
}

