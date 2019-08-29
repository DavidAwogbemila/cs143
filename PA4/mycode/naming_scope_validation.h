#include"cool-tree.h"
#include "symtab.h"

namespace mycode {

  bool validate_feature(Feature c, SymbolTable<Symbol, symbol_table_data>*& sym_tab);

  bool validate_class(Class_ c, SymbolTable<Symbol, symbol_table_data>*& sym_tab) {
    class__class* c_info = (class__class*) c->copy_Class_();
    Features c_features = c_info->get_features();
    bool still_valid = true;

    sym_tab->enterscope();
    init_feature_set_scope(c_features, sym_tab);

    for (int i = c_features->first(); c_features->more(i); i = c_features->next(i)) {
      still_valid = validate_feature(c_features->nth(i), sym_tab) && still_valid;
    }

    sym_tab->exitscope();
    return still_valid;
  }

  bool validate_feature(Feature c, SymbolTable<Symbol, symbol_table_data>*& sym_tab) {
    char type = c->get_type();
    bool still_valid = true;
    sym_tab->enterscope();

    if (type == 'a') {     // The feature is an attribute.
      attr_class* attrib = (attr_class*)c->copy_Feature();
      DEBUG_ACTION(std::cout << "validating attribute " << ((attr_class*)c->copy_Feature())->get_name() << std::endl);
      if (sym_tab->lookup(attrib->get_type_decl())) {
        // Then, if initialization expression is okay return true, else false.
        DEBUG_ACTION(std::cout << "Done validating attribute " << ((attr_class*)c->copy_Feature())->get_name() << std::endl);
        return true;
      } else {
        return false;
      }

    } else if (type == 'm') { // The feature is an method.
      DEBUG_ACTION(std::cout << "validating method " << ((attr_class*)c->copy_Feature())->get_name() << std::endl);
    }
    

    sym_tab->exitscope();
    return still_valid;
  }

}