
#include "cool-tree.h"
#include "symtab.h"
#include "init_symbol_table.h"

namespace mycode {

bool object_in_ancestry_attribs(object_class* obj, const Symbol c, SymbolTable<Symbol, symbol_table_data>*& sym_tab);


bool validate_exp_assign(Expression e, SymbolTable<Symbol, symbol_table_data> sym_tab) {
}
bool validate_exp_static_dispatch(Expression e, SymbolTable<Symbol, symbol_table_data> sym_tab) {}
bool validate_exp_dispatch(Expression e, SymbolTable<Symbol, symbol_table_data> sym_tab) {}
bool validate_exp_cond(Expression e, SymbolTable<Symbol, symbol_table_data> sym_tab) {}
bool validate_exp_loop(Expression e, SymbolTable<Symbol, symbol_table_data> sym_tab) {}
bool validate_exp_typcase(Expression e, SymbolTable<Symbol, symbol_table_data> sym_tab) {}
bool validate_exp_block(Expression e, SymbolTable<Symbol, symbol_table_data> sym_tab) {}
bool validate_exp_let(Expression e, SymbolTable<Symbol, symbol_table_data> sym_tab) {}
bool validate_exp_plus(Expression e, SymbolTable<Symbol, symbol_table_data> sym_tab) {}
bool validate_exp_sub(Expression e, SymbolTable<Symbol, symbol_table_data> sym_tab) {}
bool validate_exp_mul(Expression e, SymbolTable<Symbol, symbol_table_data> sym_tab) {}
bool validate_exp_divide(Expression e, SymbolTable<Symbol, symbol_table_data> sym_tab) {}
bool validate_exp_neg(Expression e, SymbolTable<Symbol, symbol_table_data> sym_tab) {}
bool validate_exp_lt(Expression e, SymbolTable<Symbol, symbol_table_data> sym_tab) {}
bool validate_exp_eq(Expression e, SymbolTable<Symbol, symbol_table_data> sym_tab) {}
bool validate_exp_leq(Expression e, SymbolTable<Symbol, symbol_table_data> sym_tab) {}
bool validate_exp_comp(Expression e, SymbolTable<Symbol, symbol_table_data> sym_tab) {}
bool validate_exp_int_const(Expression e, SymbolTable<Symbol, symbol_table_data> sym_tab) {}
bool validate_exp_bool_const(Expression e, SymbolTable<Symbol, symbol_table_data> sym_tab) {}
bool validate_exp_string_const(Expression e, SymbolTable<Symbol, symbol_table_data> sym_tab) {}
bool validate_exp_new_(Expression e, SymbolTable<Symbol, symbol_table_data> sym_tab) {}
bool validate_exp_isvoid(Expression e, SymbolTable<Symbol, symbol_table_data> sym_tab) {}
bool validate_exp_no_expr(Expression e, SymbolTable<Symbol, symbol_table_data> sym_tab) {}
bool validate_exp_object(Class_ in_class, Feature attrib, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab) {
  /**
   * Algorithm:
   * if object is in immediate class scope:
   * --if object is same as attribute being initialized:
   * ----return false;
   * --return true (TODO: ADD TYPE-CHECK);
   * if object is an attribute of a parent class:
   * --return true (TODO: ADD TYPE-CHECK)
   */ 
  // object_class* object_exp = (object_class*) attrib->get_init_expr()->copy_Expression();
  object_class* object_exp = (object_class*) e;
  if (sym_tab->probe(object_exp->get_name())) {
    if (object_exp->get_name() == attrib->get_name() && 
        !object_in_ancestry_attribs(object_exp, in_class->get_name(), sym_tab)) {
      return false;
    }
    return true;
  } else if (object_in_ancestry_attribs(object_exp, in_class->get_name(), sym_tab)) {
    return true;
  }
  return false;
}

/**
  * This function checks whether an object is a feature of any class in the 
  * ancestry of that object.
  */
  bool object_in_ancestry_attribs(object_class* obj, const Symbol c, SymbolTable<Symbol, symbol_table_data>*& sym_tab) {
    symbol_table_data* class_data = sym_tab->lookup(c);
    symbol_table_data* class_parent_data = sym_tab->lookup(class_data->parent);
    if (class_parent_data) {
      for (int i = class_parent_data->features->first(); class_parent_data->features->more(i); i = class_parent_data->features->next(i)) {
        if (obj->get_name() == class_parent_data->features->nth(i)->get_name()) {
          return true;
        }
      }
    return object_in_ancestry_attribs(obj, class_data->parent, sym_tab);
    }
    return false;
  }

}
