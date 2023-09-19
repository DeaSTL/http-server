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

//Hsh Map : a dynamic array of key-value pairs

void dt_hashmap_create(dt_hashmap *hashmap,unsigned int element_size){
  hashmap->element_size = element_size;
  dt_vector_create(hashmap->values,10,hashmap->element_size);
  dt_vector_create(hashmap->keys  ,10,sizeof(int));
}


