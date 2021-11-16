#include "protosam.h"

Table* table_new(u64 size, u64 seed){
  Table* t = malloc(sizeof(Table));
  t->size = size;
  t->seed = seed;
  t->data = calloc(size, sizeof(Entry)); //make sure its set to 0

  return t;

}

Entry* entry_new(u8* key, HashFunction hasher, EntryType type, EntryData data){

  Entry* e = calloc(1, sizeof(Entry));
  memcpy(e->key, key, KEYLENGTH);
  e->hash = hasher(e->key,seed);
  e->type = type;
  e->data = data;
  return e;

}

u64 table_insert(Table* t, Entry* e){
  if (t == NULL || e == NULL){
    return 20;
  } else if (e->key[0] == '\0'){
    return 21;
  }


}
