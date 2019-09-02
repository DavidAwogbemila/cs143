#pragma once

#include "cool-tree.h"


#define DEBUGGING

#ifdef DEBUGGING
#define DEBUG_ACTION(x) x << std::flush
#else
#define DEBUG_ACTION(x)
#endif

namespace mycode {

  typedef struct data {
    Features features;        // Valid if the symbol table entry is a class.
    Symbol parent;            // Valid if the symbol table entry is a class.
    Symbol type;              // Valid if the symbol table entry is an attribute or case branch id.
    Symbol return_type;       // Valid if the symbol table entry is a method.
    Formals formals;          // Valid if the symbol table entry is a method.
    Symbol get_type () {
      return copy_Symbol(type);
    }

  } symbol_table_data;


}