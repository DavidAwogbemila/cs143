#include <vector>

#include "stringtab.h"
#include "cool-tree.h"
#include "symtab.h"

namespace mycode {

  typedef struct data {
    Features features;
    Symbol parent;
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
      sym_tab->addid(c_info->get_name(), data);
    }
  }

  // Store classes, their features and their parents in symboll table.
  void init_feature_set_scope(Features class_features,
                              SymbolTable<Symbol, symbol_table_data>*& sym_tab) {
  }

}
