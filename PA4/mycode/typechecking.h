#pragma once
#include <stack>

#include "cool-tree.h"
#include "symtab.h"

#include "expression_classes.h"
#include "symbol_table_data.h"

extern Symbol 
  arg,
  arg2,
  Bool,
  concat,
  cool_abort,
  copy,
  Int,
  in_int,
  in_string,
  IO,
  length,
  Main,
  main_meth,
  No_class,
  No_type,
  Object,
  out_int,
  out_string,
  prim_slot,
  self,
  SELF_TYPE,
  Str,
  str_field,
  substr,
  type_name,
  val;



namespace mycode {

  Symbol evaluate_lub_of_types(Symbol s1, Symbol s2, SymbolTable<Symbol, symbol_table_data>*& sym_tab);
  Symbol get_cases_lub(Cases cs, SymbolTable<Symbol, symbol_table_data>*& sym_tab);

Feature get_method_from_ancestry(Symbol feature_name, Symbol class_name, SymbolTable<Symbol, symbol_table_data>*& sym_tab) {
  auto data = sym_tab->lookup(class_name);
  if (data) {
    Features fs = data->features;
    if (fs == NULL) {
      return NULL;
    }
    for (int i = fs->first(); fs->more(i); i = fs->next(i)) {
      Feature f = fs->nth(i);
      if (f->get_type() == 'm' && f->get_name() == feature_name) {
        return f;
      }
    }
    return get_method_from_ancestry(feature_name, data->parent, sym_tab);
  }
  return NULL;
}

Feature get_attribute_from_ancestry(Symbol feature_name, Symbol class_name, SymbolTable<Symbol, symbol_table_data>*& sym_tab) {
  auto data = sym_tab->lookup(class_name);
  if (data) {
    Features fs = data->features;
    if (fs == NULL) {
      return NULL;
    }
    for (int i = fs->first(); fs->more(i); i = fs->next(i)) {
      Feature f = fs->nth(i);
      if (f->get_type() == 'a' && f->get_name() == feature_name) {
        return f;
      }
    }
    return get_attribute_from_ancestry(feature_name, data->parent, sym_tab);
  }
  return NULL;
}

Symbol find_type_of_attribute_in_ancestry(Symbol feature_name, Symbol class_name, SymbolTable<Symbol, symbol_table_data>*&sym_tab) {
  // DEBUG_ACTION(std::cout << "looking for " << feature_name << " in class " << class_name << std::endl);
  auto data = sym_tab->lookup(class_name);
  if (data) {
    // DEBUG_ACTION(std::cout << "we have data on class " << class_name << std::endl);
    Features fs = data->features;
    // DEBUG_ACTION(std::cout << "and we can get the features " << std::endl);
    for (int i = fs->first(); fs->more(i); i = fs->next(i)) {
      Feature f = fs->nth(i);
      // DEBUG_ACTION(std::cout << "checking feature " << f->get_name() << std::endl);
      if (f->get_type() == 'a' && f->get_name() == feature_name) {
        // DEBUG_ACTION(std::cout << "found the attribute! " << f->get_name() << std::endl);
        return f->get_type_decl();
      }
    }
    return find_type_of_attribute_in_ancestry(feature_name, data->parent, sym_tab);
  }
  return NULL;
}

Symbol find_type_of_method_in_ancestry(Symbol feature_name, Symbol class_name, SymbolTable<Symbol, symbol_table_data>*&sym_tab) {
  auto data = sym_tab->lookup(class_name);
  if (data) {
    Features fs = data->features;
    if (fs == NULL) {
    }
    for (int i = fs->first(); fs->more(i); i = fs->next(i)) {
      Feature f = fs->nth(i);
      if (f->get_type() == 'm' && f->get_name() == feature_name) {
        return f->get_return_type();
      }
    }
    return find_type_of_method_in_ancestry(feature_name, data->parent, sym_tab);
  }
  return NULL;
}

bool is_super_type_of(Symbol parent, Symbol child, SymbolTable<Symbol, symbol_table_data>*& sym_tab) {
  if (parent == child) return true;
  auto data = sym_tab->lookup(child);
  while (data) {
    if (data->parent == parent) {
      return true;
    } else {
      data = sym_tab->lookup(data->parent);
    }
  }
  return false;
}


  /**
 * This function gets te type of an expression.
 * ******************************************** 
 * CAUTION: This function returns NULL!
 * ********************************************
 * A return value of NULL should be replaced with Object for recovery purposes
 * so the compiler can continue.
 */
Symbol get_expression_type(Class_ c, Expression e, SymbolTable<Symbol, symbol_table_data>*& sym_tab) {
  switch (e->get_expr_type()) {
    case expr_type::EXP_ASSIGN: {
      assign_class* assign_exp = (assign_class*) e;
      if (symbol_table_data* assign_type = sym_tab->lookup(assign_exp->get_name())) {
        return assign_type->get_type();
      } else if (Symbol attr_type = find_type_of_attribute_in_ancestry(assign_exp->get_name(), c->get_name(), sym_tab)) {
        return attr_type == SELF_TYPE ? c->get_name() : attr_type;
      }
      return NULL;
    }
    case expr_type::EXP_STATIC_DISPATCH: {
      static_dispatch_class* static_dispatch_exp = (static_dispatch_class*) e;
      Symbol required_type = static_dispatch_exp->get_type_name();
      if (required_type == SELF_TYPE) {
        required_type = c->get_name();
      }
      if (sym_tab->lookup(required_type)) {
        symbol_table_data* data = sym_tab->lookup(required_type);
        Features type_features = data->features;
        for (int i = type_features->first(); type_features->more(i); i = type_features->next(i)) {
          Feature f = type_features->nth(i);
          if (f->get_name() == static_dispatch_exp->get_name()) {
            if (f->get_type() == 'a') { return NULL; } // not a method, can't be used for dispatch.
            return f->get_return_type() == SELF_TYPE ? c->get_name() : f->get_return_type();
          }
        }
        return NULL;
      }
      return NULL;
    }
    case expr_type::EXP_DISPATCH: {
      dispatch_class* dispatch_exp = (dispatch_class*) e;
      Symbol expr_type = get_expression_type(c, dispatch_exp->get_expr(), sym_tab);
      if (expr_type == NULL) {
        return NULL;
      } else if (expr_type == SELF_TYPE) {
        expr_type = c->get_name();
      }
      if (symbol_table_data* data = sym_tab->lookup(expr_type)) {
        Features type_features = data->features;
        for (int i = type_features->first(); type_features->more(i); i = type_features->next(i)) {
          Feature f = type_features->nth(i);
          if (f->get_name() == dispatch_exp->get_name()) {
            if (f->get_type() == 'a') { // not a method, can't be used for dispatch.
              return NULL; 
            }
            return f->get_return_type() == SELF_TYPE ? expr_type : f->get_return_type();
          }
        }
        if (Feature f = get_method_from_ancestry(dispatch_exp->get_name(), c->get_name(), sym_tab)) {
            return f->get_return_type() == SELF_TYPE ? expr_type : f->get_return_type();
        }
        return NULL;
      }
      return NULL;
    }
    case expr_type::EXP_COND: {
      cond_class* cond_exp = (cond_class*) e;
      Symbol then_type = get_expression_type(c, cond_exp->get_then_exp(), sym_tab);
      Symbol else_type = get_expression_type(c, cond_exp->get_else_exp(), sym_tab);
      if (!(then_type && else_type)) { return NULL; }

      Symbol lub = evaluate_lub_of_types(then_type, else_type, sym_tab);
      return lub == SELF_TYPE ? c->get_name() : lub;
    }
    case expr_type::EXP_LOOP: {
      return Object;
    }
    case expr_type::EXP_TYPCASE: {
      typcase_class* typcase_exp = (typcase_class*) e;
      Symbol lub = get_cases_lub(typcase_exp->get_cases(), sym_tab);
      return lub == SELF_TYPE ? c->get_name() : lub;
    }
    case expr_type::EXP_BLOCK: {
      block_class* block_exp = (block_class*) e;
      Expressions exprs = block_exp->get_expressions();
      Expression e;
      // There is probably a more efficient way to do this but oh well.
      for (int i = exprs->first(); exprs->more(i); i = exprs->next(i)) {
        e = exprs->nth(i);
      }
      return get_expression_type(c, e, sym_tab);
    }
    case expr_type::EXP_LET: {
      let_class* let_exp = (let_class*) e;
      return get_expression_type(c, let_exp->get_body(), sym_tab);
    }
    case expr_type::EXP_PLUS: {
      return Int;
    }
    case expr_type::EXP_SUB: {
      return Int;
    }
    case expr_type::EXP_MUL: {
      return Int;
    }
    case expr_type::EXP_DIVIDE: {
      return Int;
    }
    case expr_type::EXP_NEG: {
      return Bool;
    }
    case expr_type::EXP_LT: {
      return Bool;
    }
    case expr_type::EXP_EQ: {
      return Bool;
    }
    case expr_type::EXP_LEQ: {
      return Bool;
    }
    case expr_type::EXP_COMP: {
      return Int;
    }
    case expr_type::EXP_INT_CONST: { 
      return Int;
    }
    case expr_type::EXP_BOOL_CONST: { 
      return Bool;
    }
    case expr_type::EXP_STRING_CONST: { 
      return Str;
    }
    case expr_type::EXP_NEW_: {
      new__class* new__exp = (new__class*) e;
      Symbol new_type_name = new__exp->get_type_name();
      return new_type_name == SELF_TYPE ? c->get_name() : new_type_name;
    }
    case expr_type::EXP_ISVOID: {
      return Bool;
    }
    case expr_type::EXP_NO_EXPR: { 
      return No_type;
    }
    case expr_type::EXP_OBJECT: {
      object_class* object_exp = (object_class*) e->copy_Expression();
      if (sym_tab->lookup(object_exp->get_name())) {
        Symbol object_type =  sym_tab->lookup(object_exp->get_name())->get_type();
        return object_type == SELF_TYPE ? c->get_name() : object_type;
      } else if (Symbol type_from_ancestor = find_type_of_attribute_in_ancestry(object_exp->get_name(), c->get_name(), sym_tab)) {
        return type_from_ancestor == SELF_TYPE ? c->get_name() : type_from_ancestor;
      }
      return NULL;
    }
    default: { 
      return Object;
    }
    david: {
      /* Both VSCODE's linter and g++ lets you do this. Crazy. */
      return NULL;
    }
  }
  return Object;
}

Symbol evaluate_lub_of_types(Symbol s1, Symbol s2, SymbolTable<Symbol, symbol_table_data>*& sym_tab) {
  Symbol s1_temp = s1, s2_temp = s2, curr_lub = Object;
  std::stack<Symbol> stack1({s1_temp}), stack2({s2_temp});

  while (s1_temp && s1_temp != Object) {
    auto data = sym_tab->lookup(s1_temp);
    s1_temp = data->parent;
    stack1.push(s1_temp);
  }
  
  while (s2_temp && s2_temp != Object) {
    auto data = sym_tab->lookup(s2_temp);
    s2_temp = data->parent;
    stack2.push(s2_temp);
  }

  while (stack1.top() == stack2.top()) {
    curr_lub = stack1.top();
    stack1.pop(); stack2.pop();
  }
  
  return curr_lub;
}

Symbol get_cases_lub(Cases the_cases, SymbolTable<Symbol, symbol_table_data>*& sym_tab) {
  return Object;
}


}