#pragma once

#include "cool-tree.h"

namespace mycode {
  typedef struct data {
    Features features;        // Valid if the symbol table entry is a class.
    Symbol parent;            // Valid if the symbol table entry is a class.
    Symbol type;              // Valid if the symbol table entry is an attribute or case branch id.
    Symbol return_type;       // Valid if the symbol table entry is a method.
  } symbol_table_data;

}