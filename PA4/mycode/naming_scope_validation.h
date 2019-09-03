#include <cool-tree.h>
#include "symtab.h"
#include "expression_classes.h"
#include "expression_validation.h"
#include "typechecking.h"

namespace mycode {

  // Store classes, their features and their parents in symboll table.
  void init_feature_set_scope(Class_ in_class, Features class_features,
                              SymbolTable<Symbol, symbol_table_data>*& sym_tab) {
    for(int i = class_features->first(); class_features->more(i); i = class_features->next(i)) {
      symbol_table_data* data = new symbol_table_data;
      char feature_type = class_features->nth(i)->get_type();
      data->features = NULL;
      data->parent = NULL;
      data->return_type = feature_type == 'm' ? class_features->nth(i)->get_return_type() : NULL ;
      data->type = feature_type == 'a' ? class_features->nth(i)->get_type_decl() : NULL ;
      sym_tab->addid(class_features->nth(i)->get_name(), data);
    }

    sym_tab->addid(SELF_TYPE, new symbol_table_data({NULL, NULL, in_class->get_name(), NULL}));
    sym_tab->addid(self, new symbol_table_data({NULL, NULL, SELF_TYPE, NULL, NULL}));

  }

  bool validate_feature(const Class_ in_class, Feature c, SymbolTable<Symbol, symbol_table_data>*& sym_tab) {
    char feature_type = c->get_type(); // whether method (m) or attribute (a);
    bool still_valid = true;

    if (feature_type == 'a') {   // The feature is an attribute.
      attr_class* attrib = (attr_class*) c;
      Symbol feature_decl_type = attrib->get_type_decl();
      Symbol init_expr_type = get_expression_type(in_class, attrib->get_init_expr(), sym_tab);
      auto exp = attrib->get_init_expr();
      attr_class* corresponding_parent_attribute = (attr_class*)get_attribute_from_ancestry(attrib->get_name(), in_class->get_parent_name(), sym_tab);
      if (corresponding_parent_attribute) {
        if (corresponding_parent_attribute->get_type_decl() != attrib->get_type_decl()) {
          still_valid = false;
        } 
      }
      if (init_expr_type == No_type) {
        still_valid = sym_tab->lookup(feature_decl_type) && still_valid;
        attrib->get_init_expr()->set_type(No_type);
      } else if (sym_tab->lookup(feature_decl_type) && sym_tab->lookup(init_expr_type)) {
        if (feature_decl_type != init_expr_type) {
          // We know that init_expr_type will have been converted to the class name
          // by get_expression_type(..).
          if (feature_decl_type != SELF_TYPE && !is_super_type_of(feature_decl_type, init_expr_type, sym_tab)) {
            still_valid = false;
            DEBUG_ACTION(std::cout << "Cannot have an attribute named self." << std::endl);
          }
        }
        if (attrib->get_name() == self) {
          still_valid = false;
        }
        still_valid = still_valid && validate_expression(in_class, c, attrib->get_init_expr(), sym_tab);
      } else {
        still_valid = false;
      }

    } else if (feature_type == 'm') { // The feature is an method.
      method_class* method = (method_class*)c;
      Symbol method_decl_return_type = method->get_return_type(), method_expr_return_type;
      if (sym_tab->lookup(method_decl_return_type)) {
        // Then, if initialization expression is okay return true, else false.
        Formals method_formals = method->get_formals();
        method_class* corresponding_parent_method = (method_class*)get_method_from_ancestry(method->get_name(), in_class->get_parent_name() ,sym_tab);
        if (corresponding_parent_method) { //Signatures must match.
          Formals parent_formals = corresponding_parent_method->get_formals();
          if (parent_formals->len() != method_formals->len()) {
            still_valid = false;
          } else {
            for (int i = parent_formals->first(); parent_formals->more(i); i = parent_formals->next(i)) {
              if (parent_formals->nth(i)->get_type() != method_formals->nth(i)->get_type()) {
                still_valid == false;
              }
            }
          }
        }
        sym_tab->enterscope();
        for (int i = method_formals->first(); method_formals->more(i); i = method_formals->next(i)) {
          if (!sym_tab->lookup(method_formals->nth(i)->get_type()) ||
               method_formals->nth(i)->get_name() == self) {
            /* If any parameter type is bad, return false. */
            still_valid = false;
          }
          symbol_table_data* data = new symbol_table_data({NULL, NULL, method_formals->nth(i)->get_type(), NULL});
          sym_tab->addid(method_formals->nth(i)->get_name(), data);
        }
        still_valid = validate_expression(in_class, c, method->get_expr(), sym_tab) && still_valid;
        method_expr_return_type = get_expression_type(in_class, method->get_expr(), sym_tab);
        if (method_expr_return_type != method_decl_return_type) {
          if (method_decl_return_type != SELF_TYPE) {
            DEBUG_ACTION(std::cout << "method validation says types don't match" << std::endl);
            if (!is_super_type_of(method_decl_return_type, method_expr_return_type, sym_tab)) {
              still_valid = false;
            }
          }
        }
        sym_tab->exitscope();
      } else {
        still_valid = false;
      }
    }
    
    return still_valid;
  }

  bool validate_class(Class_& c, SymbolTable<Symbol, symbol_table_data>*& sym_tab) {
    class__class* c_info = (class__class*) c;
    Features c_features = c_info->get_features();
    bool still_valid = true;

    sym_tab->enterscope();
    init_feature_set_scope(c, c_features, sym_tab);

    for (int i = c_features->first(); c_features->more(i); i = c_features->next(i)) {
      DEBUG_ACTION(std::cout << "Validating feature " << c_features->nth(i)->get_name() << std::endl);
      bool valid = validate_feature(c, c_features->nth(i), sym_tab);
      if(valid) {
        DEBUG_ACTION(std::cout << "Feature " << c_features->nth(i)->get_name() << " is okay " << std::endl);
      } else {
        DEBUG_ACTION(std::cout << "Feature " << c_features->nth(i)->get_name() << " is not okay " << std::endl);
        still_valid = false;
      }
    }

    sym_tab->exitscope();
    return still_valid;
  }

}