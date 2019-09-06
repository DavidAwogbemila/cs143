#include <cool-tree.h>
#include "symtab.h"
#include "expression_classes.h"
#include "expression_validation.h"
#include "typechecking.h"

namespace mycode {

  // Store classes, their features and their parents in symbol table.
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
      Expression init_expr = attrib->get_init_expr();
      Symbol attribute_decl_type = attrib->get_type_decl();
      Symbol init_expr_type = get_expression_type(in_class, init_expr, sym_tab);
      // If a parent class has an attribute with a similar name, it must be of the same type.
      if (attr_class* corresponding_parent_attribute = (attr_class*) get_attribute_from_class_or_ancestry(attrib->get_name(), in_class->get_parent_name(), sym_tab)) {
        if (corresponding_parent_attribute->get_type_decl() != attrib->get_type_decl()) {
          still_valid = false;
        } 
      }

      // If the attribute is uninitialized, set its type in the AST to No_type.
      if (init_expr_type == No_type) {
        still_valid = sym_tab->lookup(attribute_decl_type) && still_valid;
        attrib->get_init_expr()->set_type(No_type);
      } 
      // Else, the declared type and the type of the initializing expression must both be valid.
      else if (sym_tab->lookup(attribute_decl_type) && sym_tab->lookup(init_expr_type)) {
        if (attribute_decl_type != init_expr_type) {
          // init_expr_type can't be SELF_TYPE (get_expression_type(...) ensures this).
          // So, the attribute's declared type must either be:
          //   (i) SELF_TYPE - and therefore the type of the init_expr must be 
          //       the same as in_class->get_name() or a subclass of it.
          if (attribute_decl_type == SELF_TYPE) {
            if (!is_super_type_of(in_class->get_name(), init_expr_type , sym_tab) &&
                in_class->get_name() != init_expr_type) {
                  still_valid = false;
            }
          } 
          else if (init_expr_type == SELF_TYPE) {
            still_valid = (attribute_decl_type == in_class->get_name() ||
                          is_super_type_of(attribute_decl_type, in_class->get_name(), sym_tab)) &&
                          still_valid;
          }
          //  (ii) Any subclass of the attribute's declared type.
          else if (!is_super_type_of(attribute_decl_type, init_expr_type, sym_tab)) {
            still_valid = false;
          }
        }

        // The attribute cannot be named self.
        if (attrib->get_name() == self) {
          still_valid = false;
        }

        // The expression must be independently valid within the current scope.
        still_valid = validate_expression(in_class, c, attrib->get_init_expr(), sym_tab) && still_valid;

      } else { // Either the type declared of the expression type is faulty.
        still_valid = false;
      }

    } else if (feature_type == 'm') { // The feature is an method.
      method_class* method = (method_class*) c;
      Symbol method_decl_return_type = method->get_return_type(), method_expr_return_type;
      Formals method_formals = method->get_formals();

      if (sym_tab->lookup(method_decl_return_type)) {
        // If a method with the same name exists in any of the ancestors of the class,
        // The signature and return type declared in this class must match.
        if (method_class* corresponding_parent_method = 
           (method_class*) get_method_from_class_or_ancestry(method->get_name(), in_class->get_parent_name() ,sym_tab)) { 
          DEBUG_ACTION(std::cout << "There is an inherited method named: " << method->get_name() << std::endl);
          Formals parent_formals = corresponding_parent_method->get_formals();
          // For signatures to match, they must have equal number of parameters.
          // And return types must be the same.
          if ((parent_formals->len() != method_formals->len()) ||
              corresponding_parent_method->get_return_type() != method_decl_return_type) {
            still_valid = false;
          }
          else {
            for (int i = parent_formals->first(); parent_formals->more(i); i = parent_formals->next(i)) {
              if (parent_formals->nth(i)->get_type() != method_formals->nth(i)->get_type()) {
                still_valid = false;
              } else {
              }
            }
          }
        }

        sym_tab->enterscope();
        std::vector<Symbol> params;
        for (int i = method_formals->first(); method_formals->more(i); i = method_formals->next(i)) {
          // Each parameter must:
          //    (i) Be of a recognized type.
          //   (ii) Not be named "self"
          if (!sym_tab->lookup(method_formals->nth(i)->get_type()) ||
              method_formals->nth(i)->get_name() == self ||
              method_formals->nth(i)->get_type() == SELF_TYPE) {
            still_valid = false;
          }
          if (std::find(params.begin() , params.end(), method_formals->nth(i)->get_name()) != params.end()) {
            still_valid = false;
          }
          params.push_back(method_formals->nth(i)->get_name());
          symbol_table_data* data = new symbol_table_data({NULL, NULL, method_formals->nth(i)->get_type(), NULL});
          sym_tab->addid(method_formals->nth(i)->get_name(), data);
        }

        // Finally, the expression in the feature must be valid within the current scope.
        // And its return type must match (or be a subclass of) the method's declared type.
        still_valid = validate_expression(in_class, c, method->get_expr(), sym_tab) && still_valid;
        method_expr_return_type = get_expression_type(in_class, method->get_expr(), sym_tab);

        if (method_decl_return_type != method_expr_return_type) {
          if (method_decl_return_type == SELF_TYPE) {
            Symbol m = method_expr_return_type;
            still_valid = false;
          } else {
            Symbol m = method_expr_return_type;
            if (m == SELF_TYPE) {
              still_valid = (is_super_type_of(method_decl_return_type, in_class->get_name(), sym_tab) ||
                            method_decl_return_type == in_class->get_name()) &&
                            still_valid;
            } else {
              still_valid = is_super_type_of(method_decl_return_type, m, sym_tab) &&
                            still_valid;
            }

          }

        }

        sym_tab->exitscope();
  
      } else { // Faulty return type declared.
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
      bool valid = validate_feature(c, c_features->nth(i), sym_tab);
      if(valid) {
      } else {
        still_valid = false;
      }
    }

    sym_tab->exitscope();
    return still_valid;
  }

}