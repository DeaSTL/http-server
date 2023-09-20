typedef struct dt_vector_s{
  void* data;
  int size;
  unsigned int capacity;
  unsigned int element_size;
} dt_vector;



void dt_vector_create(dt_vector* vector, unsigned int initial_size, unsigned int element_size);

void dt_vector_destroy(dt_vector *vector);

void dt_vector_push_back(dt_vector *vector, void *element);

void* dt_vector_get(dt_vector *vector, unsigned int index);

void dt_vector_set(dt_vector *vector, unsigned int index, void *element);


typedef struct dt_hashmap_s{
  dt_vector* keys;
  dt_vector* values;
  unsigned int element_size;
} dt_hashmap;

int dt_hash(void* key, unsigned int element_size);

void dt_hashmap_create(dt_hashmap* hashmap, unsigned int element_size);

void dt_hashmap_destroy(dt_hashmap* hashmap);

void* dt_hashmap_find(dt_hashmap* hashmap, void* key);

void dt_hashmap_insert(dt_hashmap* hashmap, void* key, void* value);



