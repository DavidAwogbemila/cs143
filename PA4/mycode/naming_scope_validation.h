#include <cool-tree.h>
#include "symtab.h"
#include "expression_classes.h"
#include "expression_validation.h"

namespace mycode {

  bool validate_feature(const Class_ in_class, Feature c, SymbolTable<Symbol, symbol_table_data>*& sym_tab);

  bool validate_class(Class_ c, SymbolTable<Symbol, symbol_table_data>*& sym_tab) {
    class__class* c_info = (class__class*) c->copy_Class_();
    Features c_features = c_info->get_features();
    bool still_valid = true;

    sym_tab->enterscope();
    init_feature_set_scope(c_features, sym_tab);

    for (int i = c_features->first(); c_features->more(i); i = c_features->next(i)) {
      still_valid = validate_feature(c, c_features->nth(i), sym_tab) && still_valid;
    }

    sym_tab->exitscope();
    return still_valid;
  }

  bool validate_feature(const Class_ in_class, Feature c, SymbolTable<Symbol, symbol_table_data>*& sym_tab) {
    char type = c->get_type();
    bool still_valid = true;

    if (type == 'a') {     // The feature is an attribute.
      attr_class* attrib = (attr_class*)c->copy_Feature();
      if (sym_tab->lookup(attrib->get_type_decl())) {
        // Then, if initialization expression is okay return true, else false.
        return validate_expression(in_class, c, attrib->get_init_expr(), sym_tab);
      } else {
        return false;
      }

    } else if (type == 'm') { // The feature is an method.
      method_class* method = (method_class*)c->copy_Feature();
      sym_tab->enterscope();
      if (sym_tab->lookup(method->get_return_type())) {
        // Then, if initialization expression is okay return true, else false.
        Formals method_formals = method->get_formals();
        for (int i = method_formals->first(); method_formals->more(i); i = method_formals->next(i)) {
          if (!sym_tab->lookup(method_formals->nth(i)->get_type())) {
            /* If any parameter type is bad, return false. */
            still_valid = false;
          }
          symbol_table_data* data = new symbol_table_data({NULL, NULL, method_formals->nth(i)->get_type(), NULL});
          sym_tab->addid(method_formals->nth(i)->get_name(), data);
        }
        still_valid = validate_expression(in_class, c, method->get_expr(), sym_tab);
      } else {
        still_valid = false;
      }
      sym_tab->exitscope();
    }
    
    return still_valid;
  }
}