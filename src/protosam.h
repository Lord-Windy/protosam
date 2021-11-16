#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <stdarg.h>

#include "sds.h"

#include "commonsam.h"

#define KEYLENGTH 16

// Steps for my prototype
// 1. Build a Hashmap
//  a. Start with an expanding array
//  b. Place a union
// 2. Object

typedef void* (*ObjectFunction)(void*, ...);
typedef u64 (*HashFunction)(char*, u64); //Key and Seed
struct Object;


/*
 * Old system being replaced with new
 */

//find way to force to 8 bytes
typedef enum {
  Fn,
  Obj,
  Ptr,
  Float,
  SInt,
  UInt,
  String,
} EntryType;

typedef union {
  ObjectFunction fn;
  struct Object* obj;
  void* ptr;
  f64 flo;
  i64 sint;
  u64 uint;
  sds str; //pointer to a string
} EntryData;

typedef struct {
  u64 hash;
  u8 key[KEYLENGTH];
  EntryType type;
  EntryData data;
} Entry;

typedef struct {
  u64 size;
  u64 seed;
  Entry* data;
} Table;

struct Object {
  i64 marked;
  i64 references;
  //table would go here
  struct Object** reference; //first pointer here, get to next one as we go
};

typedef struct Object Object;

typedef struct {
  u64 obj_num; //how many objects exist
  Object** object_list; //points to the entry position on the memory list
  u64 root_num;
  Object** roots; //points to entry position on the memory list
  u64 mem_size;
  u64 next_free_offset;//how far to jump to write new object in
  u8* mem; //pretend page file for now
} ObjectSystem;


//OBJECT Functions
ObjectSystem* obj_system_new(u64 init_mem_size);

//creates and returns blank object
Object* obj_register_new_obj(ObjectSystem* o);

//register a new reference
u64 obj_register_new_reference(Object* o, Object* ref);

//Root info
//Sets an object as a root -> necessary for mark and sweep to work
u64 obj_register_root(Object* o);


//TABLE Functions

Table* table_new(u64 size, u64 seed);

/*
 * Resizes the table and reallocates entries to reduce the linear probing
 * issues
 */ 
Table* table_resize(Table* t, u64 factor);

/*
 * Returns 0 if all good
 * Returns 1 if the table requires a resize (due to the need to probe
 *    deeper than some value, I want to say 3, about the same as an 8
 *    entry binary tree 
 */ 
u64 table_insert(Table* t, Entry* e);



Entry* entry_new(u8* key, HashFunction hasher, EntryType type, EntryData data);



//Hash functions
u64 practice_hash(char* key, u64 seed);






























