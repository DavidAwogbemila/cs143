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
        switch (attrib->get_init_expr()->get_expr_type() ) {
          case expr_type::EXP_ASSIGN: {}
          case expr_type::EXP_STATIC_DISPATCH: {}
          case expr_type::EXP_DISPATCH: {}
          case expr_type::EXP_COND: {}
          case expr_type::EXP_LOOP: {}
          case expr_type::EXP_TYPCASE: {}
          case expr_type::EXP_BLOCK: {}
          case expr_type::EXP_LET: {}
          case expr_type::EXP_PLUS: {}
          case expr_type::EXP_SUB: {}
          case expr_type::EXP_MUL: {}
          case expr_type::EXP_DIVIDE: {}
          case expr_type::EXP_NEG: {}
          case expr_type::EXP_LT: {}
          case expr_type::EXP_EQ: {}
          case expr_type::EXP_LEQ: {}
          case expr_type::EXP_COMP: {}
          case expr_type::EXP_INT_CONST: { return true; }
          case expr_type::EXP_BOOL_CONST: { return true; }
          case expr_type::EXP_STRING_CONST: { return true; }
          case expr_type::EXP_NEW_: {}
          case expr_type::EXP_ISVOID: {}
          case expr_type::EXP_NO_EXPR: { return true; }
          case expr_type::EXP_OBJECT: {
            /**
             * Algorithm:
             * if object is in immediate class scope:
             * --if object is same as attribute being initialized:
             * ----return false;
             * --return true (TODO: ADD TYPE-CHECK);
             * if object is an attribute of a parent class:
             * --return true (TODO: ADD TYPE-CHECK)
             */
            object_class* object_exp = (object_class*) attrib->get_init_expr()->copy_Expression();
            // if (sym_tab->probe(object_exp->get_name())) {
            //   if (object_exp->get_name() == attrib->get_name() && 
            //       !object_in_ancestry_attribs(object_exp, in_class->get_name(), sym_tab)) {
            //     return false;
            //   }
            //   return true;
            // } else if (object_in_ancestry_attribs(object_exp, in_class->get_name(), sym_tab)) {
            //   return true;
            // }
            // return false;
            return validate_exp_object(in_class, attrib, object_exp, sym_tab);
          }
          defualt: { return true; }
        }
        return true;
      } else {
        return false;
      }

    } else if (type == 'm') { // The feature is an method.
      method_class* method = (method_class*)c->copy_Feature();
      if (sym_tab->lookup(method->get_return_type())) {
        // Then, if initialization expression is okay return true, else false.
        return true;
      }
    }
    
    return still_valid;
  }

  /**
   * This function checks whether an object is a feature of any class in the 
   * ancestry of that object.
   */
  bool _object_in_ancestry_attribs(object_class* obj, const Symbol c, SymbolTable<Symbol, symbol_table_data>*& sym_tab) {
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