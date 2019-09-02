#pragma once

#include "cool-tree.h"
#include "symtab.h"

#include "typechecking.h"

#include <stack>

namespace mycode {

bool object_in_ancestry_attribs(Symbol sym, const Symbol c, SymbolTable<Symbol, symbol_table_data>*& sym_tab);

bool validate_exp_assign(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab);
bool validate_exp_static_dispatch(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab);
bool validate_exp_dispatch(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab);
bool validate_exp_cond(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab);
bool validate_exp_loop(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab);
bool validate_exp_typcase(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab);
bool validate_exp_block(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab);
bool validate_exp_let(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab);
bool validate_exp_plus(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab);
bool validate_exp_sub(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab);
bool validate_exp_mul(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab);
bool validate_exp_divide(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab);
bool validate_exp_neg(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab);
bool validate_exp_lt(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab);
bool validate_exp_eq(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab);
bool validate_exp_leq(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab);
bool validate_exp_comp(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab);
bool validate_exp_int_const(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab);
bool validate_exp_bool_const(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab);
bool validate_exp_string_const(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab);
bool validate_exp_new_(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab);
bool validate_exp_isvoid(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab);
bool validate_exp_no_expr(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab);
bool validate_exp_object(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab);
bool validate_case(Class_ in_class, Feature in_feature, Case e, SymbolTable<Symbol, symbol_table_data>* sym_tab);

bool validate_expression(Class_ in_class, Feature in_feature, Expression& e, SymbolTable<Symbol, symbol_table_data>*& sym_tab) {
  DEBUG_ACTION(std::cout << "Expression class(#) is: " << (int)e->get_expr_type() << std::endl);
  bool expression_is_valid = true;
  switch (e->get_expr_type()) {
    case expr_type::EXP_ASSIGN: {
      assign_class* assign_exp = (assign_class*) e;
      expression_is_valid = validate_exp_assign(in_class, in_feature, assign_exp, sym_tab);
      break;
    }
    case expr_type::EXP_STATIC_DISPATCH: {
      static_dispatch_class* static_dispatch_exp = (static_dispatch_class*) e;
      expression_is_valid = validate_exp_static_dispatch(in_class, in_feature, static_dispatch_exp, sym_tab);
      break;
    }
    case expr_type::EXP_DISPATCH: {
      dispatch_class* dispatch_exp = (dispatch_class*) e;
      expression_is_valid = validate_exp_dispatch(in_class, in_feature, dispatch_exp, sym_tab);
      break;
    }
    case expr_type::EXP_COND: {
      cond_class* cond_exp = (cond_class*) e;
      expression_is_valid = validate_exp_cond(in_class, in_feature, cond_exp, sym_tab);
      break;
    }
    case expr_type::EXP_LOOP: {
      loop_class* loop_exp = (loop_class*) e;
      expression_is_valid = validate_exp_loop(in_class, in_feature, loop_exp, sym_tab);
      break;
    }
    case expr_type::EXP_TYPCASE: {
      typcase_class* typcase_exp = (typcase_class*) e;
      expression_is_valid = validate_exp_typcase(in_class, in_feature, typcase_exp, sym_tab);
      break;
    }
    case expr_type::EXP_BLOCK: {
      block_class* block_exp = (block_class*) e;
      expression_is_valid = validate_exp_block(in_class, in_feature, block_exp, sym_tab);
      break;
    }
    case expr_type::EXP_LET: {
      let_class* let_exp = (let_class*) e;
      expression_is_valid = validate_exp_let(in_class, in_feature, let_exp, sym_tab);
      break;
    }
    case expr_type::EXP_PLUS: {
      plus_class* plus_exp = (plus_class*) e;
      expression_is_valid = validate_exp_plus(in_class, in_feature, plus_exp, sym_tab);
      break;
    }
    case expr_type::EXP_SUB: {
      sub_class* sub_exp = (sub_class*) e;
      expression_is_valid = validate_exp_sub(in_class, in_feature, sub_exp, sym_tab);
      break;
    }
    case expr_type::EXP_MUL: {
      mul_class* mul_exp = (mul_class*) e;
      expression_is_valid = validate_exp_mul(in_class, in_feature, mul_exp, sym_tab);
      break;
    }
    case expr_type::EXP_DIVIDE: {
      divide_class* divide_exp = (divide_class*) e;
      expression_is_valid = validate_exp_divide(in_class, in_feature, divide_exp, sym_tab);
      break;
    }
    case expr_type::EXP_NEG: {
      neg_class* neg_exp = (neg_class*) e;
      expression_is_valid = validate_exp_neg(in_class, in_feature, neg_exp, sym_tab);
      break;
    }
    case expr_type::EXP_LT: {
      lt_class* lt_exp = (lt_class*) e;
      expression_is_valid = validate_exp_lt(in_class, in_feature, lt_exp, sym_tab);
      break;
    }
    case expr_type::EXP_EQ: {
      eq_class* eq_exp = (eq_class*) e;
      expression_is_valid = validate_exp_eq(in_class, in_feature, eq_exp, sym_tab);
      break;
    }
    case expr_type::EXP_LEQ: {
      leq_class* leq_exp = (leq_class*) e;
      expression_is_valid = validate_exp_leq(in_class, in_feature, leq_exp, sym_tab);
      break;
    }
    case expr_type::EXP_COMP: {
      comp_class* comp_exp = (comp_class*) e;
      expression_is_valid = validate_exp_comp(in_class, in_feature, comp_exp, sym_tab);
      break;
    }
    case expr_type::EXP_INT_CONST: {
      DEBUG_ACTION(std::cout << "Expression type: INT_CONST" << std::endl );
      expression_is_valid = true;
      break;
    }
    case expr_type::EXP_BOOL_CONST: { 
      expression_is_valid = true;
      break;
    }
    case expr_type::EXP_STRING_CONST: { 
      expression_is_valid = true;
      break;
    }
    case expr_type::EXP_NEW_: {
      new__class* new__exp = (new__class*) e;
      expression_is_valid = validate_exp_new_(in_class, in_feature, new__exp, sym_tab);
      break;
    }
    case expr_type::EXP_ISVOID: {
      isvoid_class* isvoid_exp = (isvoid_class*) e;
      DEBUG_ACTION(std::cout << "Expression type: ISVOID" << std::endl );
      expression_is_valid = validate_exp_isvoid(in_class, in_feature, isvoid_exp, sym_tab);
      break;
    }
    case expr_type::EXP_NO_EXPR: { 
      expression_is_valid = true;
      break;
    }
    case expr_type::EXP_OBJECT: {
      object_class* object_exp = (object_class*) e->copy_Expression();
      expression_is_valid = validate_exp_object(in_class, in_feature, object_exp, sym_tab);
      break;
    }
    defualt: { 
      DEBUG_ACTION(std::cout << "Default VALIDATION!" <<std::endl);
      expression_is_valid = false;
    }
  }
  if (Symbol expr_type = get_expression_type(in_class, e, sym_tab)) {
    e->type = expr_type;
    //e->set_type(idtable.add_string(expr_type->get_string()));
    DEBUG_ACTION(std::cout << "Expression type set to " << expr_type << std::endl);
  } else {
    e->set_type(idtable.add_string(Object->get_string()));
    DEBUG_ACTION(std::cout << "couldn't find expression type so setting to: " << Object->get_string() << std::endl);
  }
  return expression_is_valid;
}

bool validate_exp_assign(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab) {
  assign_class* assign_exp = (assign_class*) e;
  Symbol type;
  bool still_valid = true;
  auto assignee_data = sym_tab->lookup(assign_exp->get_name());

  if (sym_tab->lookup(assign_exp->get_name()) || object_in_ancestry_attribs(assign_exp->get_name(), in_class->get_name(), sym_tab)) {
    still_valid =  validate_expression(in_class, in_feature, assign_exp->get_expr(), sym_tab);
    if (sym_tab->lookup(assign_exp->get_name())) {
      type = assignee_data->get_type();
      return  still_valid && type == get_expression_type(in_class, assign_exp->get_expr(), sym_tab);
    } else {
      type = find_type_of_attribute_in_ancestry(assign_exp->get_name(), in_class->get_name(), sym_tab);
      return still_valid && type == get_expression_type(in_class, assign_exp->get_expr(), sym_tab);
    }
  } else {
    return false;
  }
}
bool validate_exp_static_dispatch(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab) {
  static_dispatch_class* s_dispatch_exp = (static_dispatch_class*) e;
  Expression expr = s_dispatch_exp->get_expr();
  Symbol func_name = s_dispatch_exp->get_name();
  Symbol type_name = s_dispatch_exp->get_type_name();
  Expressions args = s_dispatch_exp->get_args();

  bool still_valid = validate_expression(in_class, in_feature, expr, sym_tab);
  Symbol expr_type = get_expression_type(in_class, expr, sym_tab);
  /**
   * Here we need to make sure that type_name is a super class of expr_type.
   */
  if (!is_super_type_of(type_name, expr_type, sym_tab)) {
    return false;
  }

  if (type_name == SELF_TYPE) {
    type_name = in_class->get_name();
  }

  if (!find_type_of_method_in_ancestry(func_name, type_name, sym_tab)) {
    still_valid = false;
  } else {

    /**
     * There is something to think about here, a little "issue" if one wishes to be pessimistic.
     * Say the static dispatch is of the form: e@T.func(args)
     * Here, I'm saying: get the method "func" defined in class T. But what if func
     * is a member of an ancestor of T and not T itself? Does the language specification mean 
     * that we should use that inherited method or should the compiler disallow this kind of expression.
     * 
     * As currently written, the compiler which crash (seg fault) if such an expresion is used:
     * pointer-variable `desired_feature` ends up not being set and is later used: SEG-FAULT! 
    */
    auto data = sym_tab->lookup(type_name);
    Features fs = data->features;
    method_class* desired_feature;
    for(int i = fs->first(); fs->more(i); i = fs->next(i)) {
      if (fs->nth(i)->get_name() == func_name) {
        if (fs->nth(i)->get_type() == 'a') { 
          return false;
        }
        else {
          desired_feature = (method_class*) fs->nth(i);
          break;
        }
      }
    }
    Formals desired_formals = desired_feature->get_formals(); //Ha! now it's formals vs arguments.
    if (desired_formals->len() != args->len()) {
      return false;
    }
    for (int i = args->first(); args->more(i); i = args->next(i)) {
      Expression nth_exp = args->nth(i);
      still_valid =  validate_expression(in_class, in_feature, nth_exp, sym_tab) \
                && desired_formals->nth(i)->get_type() == get_expression_type(in_class, args->nth(i), sym_tab) \
                && still_valid;
    }
  }
  DEBUG_ACTION(std::cout << "STATIC DISPATCH VALIDATION!" <<std::endl);
  return still_valid;
}
bool validate_exp_dispatch(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab) {
  dispatch_class* dispatch_exp = (dispatch_class*) e;
  Expression expr = dispatch_exp->get_expr();
  Symbol func_name = dispatch_exp->get_name();
  Expressions args = dispatch_exp->get_args();
  
  bool still_valid = validate_expression(in_class, in_feature, expr, sym_tab);
  Symbol expr_type = get_expression_type(in_class, expr, sym_tab);
  
  if (expr_type == SELF_TYPE) {
    expr_type = in_class->get_name();
  }
  
  if (!find_type_of_method_in_ancestry(func_name, expr_type, sym_tab)) {
    still_valid = false;
  } else {
    auto data = sym_tab->lookup(expr_type);
    Features fs = data->features;
    method_class* desired_method = NULL;
    for(int i = fs->first(); fs->more(i); i = fs->next(i)) {
      if (fs->nth(i)->get_name() == func_name) {
        if (fs->nth(i)->get_type() == 'a') { 
          return false;
        }
        else {
          desired_method = (method_class*) fs->nth(i);
          break;
        }
      }
    }
    if (desired_method == NULL) {
      desired_method = (method_class*) get_method_from_ancestry(func_name, expr_type, sym_tab);
    }
    if (desired_method == NULL) {
      return false;
    }
    Formals desired_formals = desired_method->get_formals(); //Ha! now it's formals vs arguments.
    if (desired_formals->len() != args->len()) {
      return false;
    }
    for (int i = args->first(); args->more(i); i = args->next(i)) {
      Expression nth_exp = args->nth(i);
      still_valid =  validate_expression(in_class, in_feature, nth_exp, sym_tab) \
                && desired_formals->nth(i)->get_type() == get_expression_type(in_class, args->nth(i), sym_tab) \
                && still_valid;
    }
  }
  return still_valid;
}
bool validate_exp_cond(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab) {
  cond_class* cond_exp = (cond_class*) e;
  Expression pred = cond_exp->get_pred();
  Expression then_exp = cond_exp->get_then_exp();
  Expression else_exp = cond_exp->get_else_exp();

  bool still_valid =  validate_expression(in_class, in_feature, pred, sym_tab) && \
         validate_expression(in_class, in_feature, then_exp, sym_tab) && \
         validate_expression(in_class, in_feature, else_exp, sym_tab);

  still_valid = still_valid && Bool == get_expression_type(in_class, pred, sym_tab);
  return still_valid;
}
bool validate_exp_loop(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab) {
  loop_class* loop_exp = (loop_class*) e;
  Expression pred = loop_exp->get_pred();
  Expression body = loop_exp->get_body();

  bool still_valid = validate_expression(in_class, in_feature, pred, sym_tab) && \
         validate_expression(in_class, in_feature, body, sym_tab);
         /* May need to possibly add pred variables to scope for body. Maybe. */
  still_valid = still_valid && Bool == get_expression_type(in_class, pred, sym_tab);
  return still_valid;
}
bool validate_exp_typcase(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab) {
  typcase_class* typcase_exp = (typcase_class*) e;
  Expression expr = typcase_exp->get_expr();
  Cases cases = typcase_exp->get_cases();
  bool still_valid = true;

  for (int i = cases->first(); cases->more(i); i  = cases->next(i)) {
    DEBUG_ACTION(std::cout << "Validating case" << std::endl);
    still_valid = validate_case(in_class, in_feature, cases->nth(i), sym_tab) && still_valid;
  }

  return still_valid;
  /* TODO: Typechecking! */
}
bool validate_case(Class_ in_class, Feature in_feature, Case c, SymbolTable<Symbol, symbol_table_data>* sym_tab) {
  branch_class* case_branch = (branch_class*) c;
  Symbol branch_id = case_branch->get_name();
  Symbol branch_type = case_branch->get_type_decl() == SELF_TYPE ? in_class->get_name() : case_branch->get_type_decl();
  Expression branch_expression = case_branch->get_expr();

  symbol_table_data* data = new symbol_table_data({NULL, NULL, branch_type, NULL});
  bool still_valid = true;
  
  sym_tab->enterscope();
  sym_tab->addid(branch_id, data);
  
  still_valid = validate_expression(in_class, in_feature, branch_expression, sym_tab);
  Symbol s = get_expression_type(in_class, branch_expression, sym_tab);
  still_valid = still_valid && branch_type == s;

  sym_tab->exitscope();
  return still_valid;
}
bool validate_exp_block(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab) {
  block_class* block_exp = (block_class*) e;
  Expressions expressions = block_exp->get_expressions();
  
  bool still_valid = true;
  
  for (int i = expressions->first(); expressions->more(i); i = expressions->next(i)) {
    Expression nth_exp = expressions->nth(i);
    still_valid = validate_expression(in_class, in_feature, nth_exp, sym_tab) && still_valid;
  }

  return still_valid;
}
bool validate_exp_let(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab) {
  let_class* let_exp = (let_class*) e;
  Symbol id = let_exp->get_identifier();
  Symbol type_decl = let_exp->get_type_decl();
  Expression init_expr = let_exp->get_init_expr();
  Expression body = let_exp->get_body();

  bool still_valid = sym_tab->lookup(type_decl) != NULL ? true: false;
  still_valid = still_valid && type_decl == get_expression_type(in_class, init_expr, sym_tab);

  symbol_table_data* data = new symbol_table_data({NULL, NULL, type_decl, NULL});
  sym_tab->enterscope();
  sym_tab->addid(id, data);
  
  still_valid = validate_expression(in_class, in_feature, body, sym_tab) && still_valid;
  
  sym_tab->exitscope();
  return still_valid;
  /* TODO: Typechecking! */
}
bool validate_exp_plus(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab) {
  plus_class* plus_exp = (plus_class*) e;
  bool still_valid =  validate_expression(in_class, in_feature, plus_exp->get_first_expression(), sym_tab) && \
         validate_expression(in_class, in_feature, plus_exp->get_second_expression(), sym_tab);

  still_valid = still_valid && \
                Int == get_expression_type(in_class, plus_exp->get_first_expression(), sym_tab) && \
                Int == get_expression_type(in_class, plus_exp->get_second_expression(), sym_tab);
  return still_valid;
}
bool validate_exp_sub(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab) {
  sub_class* sub_exp = (sub_class*) e;
  bool still_valid = validate_expression(in_class, in_feature, sub_exp->get_first_expression(), sym_tab) && \
         validate_expression(in_class, in_feature, sub_exp->get_second_expression(), sym_tab);
  
  still_valid = still_valid && \
                Int == get_expression_type(in_class, sub_exp->get_first_expression(), sym_tab) && \
                Int == get_expression_type(in_class, sub_exp->get_second_expression(), sym_tab);
  return still_valid;
}
bool validate_exp_mul(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab) {
  mul_class* mul_exp = (mul_class*) e;
  bool still_valid =  validate_expression(in_class, in_feature, mul_exp->get_first_expression(), sym_tab) && \
         validate_expression(in_class, in_feature, mul_exp->get_second_expression(), sym_tab);
  
  still_valid = still_valid && \
                Int == get_expression_type(in_class, mul_exp->get_first_expression(), sym_tab) && \
                Int == get_expression_type(in_class, mul_exp->get_second_expression(), sym_tab);
  return still_valid;
}
bool validate_exp_divide(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab) {
  divide_class* divide_exp = (divide_class*) e;
  bool still_valid = validate_expression(in_class, in_feature, divide_exp->get_first_expression(), sym_tab) && \
         validate_expression(in_class, in_feature, divide_exp->get_second_expression(), sym_tab);
  
  still_valid = still_valid && \
                Int == get_expression_type(in_class, divide_exp->get_first_expression(), sym_tab) && \
                Int == get_expression_type(in_class, divide_exp->get_second_expression(), sym_tab);
  return still_valid;
}
bool validate_exp_neg(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab) {
  neg_class* neg_exp = (neg_class*) e;
  bool still_valid =  validate_expression(in_class, in_feature, neg_exp->get_expr(), sym_tab);

  still_valid = still_valid && Bool == get_expression_type(in_class, neg_exp->get_expr(), sym_tab);
  
  return still_valid;
}
bool validate_exp_lt(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab) {
  lt_class* lt_exp = (lt_class*) e;
  bool still_valid =  validate_expression(in_class, in_feature, lt_exp->get_first_expression(), sym_tab) && \
         validate_expression(in_class, in_feature, lt_exp->get_second_expression(), sym_tab);

  still_valid = Int == get_expression_type(in_class, lt_exp->get_first_expression(), sym_tab) && \
                Int == get_expression_type(in_class, lt_exp->get_second_expression(), sym_tab);
  
  return still_valid;
}
bool validate_exp_eq(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab) {
  eq_class* eq_exp = (eq_class*) e;
  bool still_valid = validate_expression(in_class, in_feature, eq_exp->get_first_expression(), sym_tab) && \
         validate_expression(in_class, in_feature, eq_exp->get_second_expression(), sym_tab);

  Symbol type_1 = get_expression_type(in_class, eq_exp->get_first_expression(), sym_tab);
  Symbol type_2 = get_expression_type(in_class, eq_exp->get_second_expression(), sym_tab);

  if (type_1 != type_2) {
    still_valid = still_valid &&
                  type_1 != Bool && type_2 != Bool &&
                  type_1 != Int && type_2 != Int &&
                  type_1 != Str && type_2 != Str;
  }

  return still_valid;
}
bool validate_exp_leq(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab) {
  leq_class* leq_exp = (leq_class*) e;
  bool still_valid =  validate_expression(in_class, in_feature, leq_exp->get_first_expression(), sym_tab) && \
         validate_expression(in_class, in_feature, leq_exp->get_second_expression(), sym_tab);

  still_valid = Int == get_expression_type(in_class, leq_exp->get_first_expression(), sym_tab) && \
                Int == get_expression_type(in_class, leq_exp->get_second_expression(), sym_tab);
  
  return still_valid;
}
bool validate_exp_comp(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab) {
  comp_class* comp_exp = (comp_class*) e;
  bool still_valid =  validate_expression(in_class, in_feature, comp_exp->get_expression(), sym_tab);

  still_valid = still_valid && Int == get_expression_type(in_class, comp_exp->get_expression(), sym_tab);

  return still_valid;
}
bool validate_exp_int_const(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab) { 
  return true;
}
bool validate_exp_bool_const(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab) { 
  return true;
}
bool validate_exp_string_const(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab) { 
  return true;
}
bool validate_exp_new_(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab) {
  new__class* new__exp = (new__class*)e;
  if (sym_tab->lookup(new__exp->get_type_name())) {
    return true;
  }
  return false;
}
bool validate_exp_isvoid(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab) {
  isvoid_class* isvoid_exp = (isvoid_class*) e;
  return validate_expression(in_class, in_feature, isvoid_exp->get_expr(), sym_tab);
}
bool validate_exp_no_expr(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab) {
  return true;
}
bool validate_exp_object(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab) {
  bool okay;
  object_class* object_exp = (object_class*) e;
  if (sym_tab->lookup(object_exp->get_name())) {
    if (object_exp->get_name() == in_feature->get_name() && 
        !object_in_ancestry_attribs(object_exp->get_name(), in_class->get_name(), sym_tab)) {
      okay =  false;
    }
    okay =  true;
  } else if (object_in_ancestry_attribs(object_exp->get_name(), in_class->get_name(), sym_tab)) {
    okay = true;
  }

  return okay;
}

/**
  * This function checks whether a symbol is a feature of any class in the 
  * ancestry of that object. Of course, it needs the symbol table to do this.
  * 
  * @param sym The symbol being checked for (maybe an attribute or a method.)
  *        It must surely be an object identifier (attribute or method).
  * @param c The class whose ancestors are being checked. It must surely be a
  *        type (class) identifier
  * @param sym_tab The symbol table.
  */
  bool object_in_ancestry_attribs(Symbol sym, const Symbol c, SymbolTable<Symbol, symbol_table_data>*& sym_tab) {
    symbol_table_data* class_data = sym_tab->lookup(c);
    symbol_table_data* class_parent_data = sym_tab->lookup(class_data->parent);
    if (class_parent_data) {
      for (int i = class_parent_data->features->first(); class_parent_data->features->more(i); i = class_parent_data->features->next(i)) {
        if (sym == class_parent_data->features->nth(i)->get_name()) {
          return true;
        }
      }
    return object_in_ancestry_attribs(sym, class_data->parent, sym_tab);
    }
    return false;
  }

}
