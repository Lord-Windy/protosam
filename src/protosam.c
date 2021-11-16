#include "protosam.h"




//Object Functions
ObjectSystem* obj_system_new(u64 init_mem_size){
  ObjectSystem* o = malloc(sizeof(ObjectSystem));
  o->obj_num = 0;
  o->root_num = 0;
  o->roots = NULL;
  o->object_list = malloc(sizeof(Object*)*50); //make expandable later, for now set
  o->mem_size = init_mem_size;
  o->next_free_offset = 0;
  //in future this will be a large page file
  o->mem = malloc(sizeof(u8)*init_mem_size);

  return o;

}

Object* obj_register_new_obj(ObjectSystem* o){
  Object tmp;
  tmp.marked = 0;
  tmp.references = 0;
  tmp.reference = NULL;
  
  //copy in
  memcpy(o->mem + o->next_free_offset, &tmp, sizeof(Object));
  //set location
  Object* n = o->mem + o->next_free_offset;
  o->next_free_offset += sizeof(Object) + sizeof(Object*)*8;//give me 8 references to play with at start
  
  //register the object
  o->object_list[o->obj_num] = n;
  o->obj_num += 1;
  
  //return the blank object
  return n;
}

u64 obj_register_new_reference(Object* o, Object* ref){
  //Magic number ahoy!
  if (o->references > 7){
    return 1; //error to represent max references reached. Will change when I expand max references.
  }
  o->reference[o->references] = ref;
  return 0;
}

//Table Functions

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
  //e->hash = hasher(e->key.seed);
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
