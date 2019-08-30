#pragma once

#include <vector>

#include "stringtab.h"
#include "cool-tree.h"
#include "symtab.h"

namespace mycode {

  typedef struct data {
    Features features;        // Valid if the symbol table entry is a class.
    Symbol parent;            // Valid if the symbol table entry is a class.
    Symbol type;              // Valid if the symbol table entry is an attribute or case branch id.
    Symbol return_type;       // Valid if the symbol table entry is a method.
  } symbol_table_data;

  // Store classes, their features and their parents in symboll table.
  void initialize_symbol_table_with_globals(std::vector<Class_>& classes_list,
                                            SymbolTable<Symbol, symbol_table_data>*& sym_tab) {
    sym_tab->enterscope();

    for (Class_ c: classes_list) {
      class__class* c_info = (class__class*)c->copy_Class_();
      symbol_table_data* data = new symbol_table_data;
      data->features = c_info->get_features();
      data->parent = c_info->get_parent_name();
      data->return_type = NULL;
      data->type = NULL;
      sym_tab->addid(c_info->get_name(), data);
    }
  }

  // Store classes, their features and their parents in symboll table.
  void init_feature_set_scope(Features class_features,
                              SymbolTable<Symbol, symbol_table_data>*& sym_tab) {
    for(int i = class_features->first(); class_features->more(i); i = class_features->next(i)) {
      symbol_table_data* data = new symbol_table_data;
      char feature_type = class_features->nth(i)->get_type();
      data->features = NULL;
      data->parent = NULL;
      data->return_type = feature_type == 'm' ? class_features->nth(i)->get_return_type() : NULL ;
      data->type = feature_type == 'a' ? class_features->nth(i)->get_type_decl() : NULL ;;
      sym_tab->addid(class_features->nth(i)->get_name(), data);
    }
  }

}
