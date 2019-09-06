#pragma once

#include "cool-tree.h"
#include "symtab.h"

#include "typechecking.h"

#include <stack>
#include <algorithm>

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
      expression_is_valid = validate_exp_comp(in_class, in_feature, neg_exp, sym_tab);
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
      expression_is_valid = validate_exp_neg(in_class, in_feature, comp_exp, sym_tab);
      break;
    }
    case expr_type::EXP_INT_CONST: {
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
      expression_is_valid = false;
    }
  }
  if (Symbol expr_type = get_expression_type(in_class, e, sym_tab)) {
    e->set_type(idtable.add_string(expr_type->get_string()));
  } else {
    e->set_type(idtable.add_string(Object->get_string()));
  }

  if (!expression_is_valid) {
      DEBUG_ACTION(std::cout << "Expression class(#) " << (int) e->get_expr_type() << " was faulty." << std::endl);
  }
  return expression_is_valid;
}

bool validate_exp_assign(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab) {
  assign_class* assign_exp = (assign_class*) e;
  Symbol type;
  Symbol assignee_name = assign_exp->get_name();
  Expression assign_rhs_expr = assign_exp->get_expr();

  symbol_table_data* assignee_data = sym_tab->lookup(assignee_name);
  bool still_valid = true;

  // The assignee must either be in scope  (case I) or an attribute inherited from one of in_class's ancestors (case II).
  if (assignee_data || object_in_ancestry_attribs(assignee_name, in_class->get_name(), sym_tab)) {
    
    // The expression being assigned to the assignee must be valid by itself within the current scope.
    still_valid =  validate_expression(in_class, in_feature, assign_rhs_expr, sym_tab);
    
    // Case I
    if (assignee_data) {
      type = assignee_data->get_type();

      // If the in-scope variable is declared as SELF_TYPE, substitute the class's name for it.
      if (type == SELF_TYPE) {
        type = in_class->get_name();
      }

      // The expression may be the type exactly, or a subtype of it.
      return still_valid && (type == get_expression_type(in_class, assign_rhs_expr, sym_tab) ||
                            is_super_type_of(type, get_expression_type(in_class, assign_rhs_expr, sym_tab), sym_tab));
    } 
    // Case II 
    else {
      type = find_type_of_attribute_in_class_or_ancestry(assignee_name, in_class->get_name(), sym_tab);

      // If it is declared as SELF_TYPE in the ancestor, substitute the class's name for it.
      if (type == SELF_TYPE) {
        type = in_class->get_name();
      }

      // The expression may be the type exactly, or a subtype of it.
      return still_valid && (type == get_expression_type(in_class, assign_rhs_expr, sym_tab) ||
                            is_super_type_of(type, get_expression_type(in_class, assign_rhs_expr, sym_tab), sym_tab));
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

  Symbol expr_type = get_expression_type(in_class, expr, sym_tab);
  bool still_valid = validate_expression(in_class, in_feature, expr, sym_tab);
  
  if (!is_super_type_of(type_name, expr_type, sym_tab)) {
    still_valid =  false;
  }

  if (!find_type_of_method_in_class_or_ancestry(func_name, type_name, sym_tab)) {
    still_valid = false;
  } else {

    // The method has to be defined in the exact class named by type_name.
    method_class* desired_method = (method_class*) get_method_from_class_or_ancestry(func_name, type_name , sym_tab);
    if (desired_method) {

      // Number of arguments should be the same as number of parameters in function declaration.
      Formals desired_formals = desired_method->get_formals(); 
      if (desired_formals->len() != args->len()) {
        still_valid =  false;
      }
      // Finally, the types of the arguments must match the declared parameter types.
      for (int i = args->first(); args->more(i); i = args->next(i)) {

        Expression nth_exp = args->nth(i);
        still_valid =  validate_expression(in_class, in_feature, nth_exp, sym_tab) \
                  && (desired_formals->nth(i)->get_type() == get_expression_type(in_class, args->nth(i), sym_tab) \
                      || is_super_type_of(desired_formals->nth(i)->get_type(), get_expression_type(in_class, args->nth(i), sym_tab), sym_tab)) \
                  && still_valid;
      }
    } else {
      still_valid = false;
    }
  }
  return still_valid;
}
bool validate_exp_dispatch(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab) {
  dispatch_class* dispatch_exp = (dispatch_class*) e;
  Expression expr = dispatch_exp->get_expr();
  Symbol func_name = dispatch_exp->get_name();
  Expressions args = dispatch_exp->get_args();
  
  Symbol expr_type = get_expression_type(in_class, expr, sym_tab);
  bool still_valid = validate_expression(in_class, in_feature, expr, sym_tab);
  
  if (expr_type == SELF_TYPE) {
    expr_type = in_class->get_name();
  }
  
  // If the method is not defined on the class or its ancestors, it's a bad expression. 
  if (method_class* desired_method = (method_class*) get_method_from_class_or_ancestry(func_name, expr_type, sym_tab)) {
    Formals desired_formals = desired_method->get_formals(); //Ha! now it's formals vs arguments.
    if (desired_formals->len() != args->len()) {
      return false;
    }
    for (int i = args->first(); args->more(i); i = args->next(i)) {
      Expression nth_exp = args->nth(i);
      Symbol nth_exp_type = get_expression_type(in_class, args->nth(i), sym_tab);
      if (nth_exp_type == SELF_TYPE) {nth_exp_type = in_class->get_name();}
      bool okay =  validate_expression(in_class, in_feature, nth_exp, sym_tab) \
                && (desired_formals->nth(i)->get_type() == nth_exp_type
                  || is_super_type_of(desired_formals->nth(i)->get_type(), nth_exp_type, sym_tab));
      still_valid = okay && still_valid;
    }
  } else {
    still_valid = false;
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

  std::vector<Symbol> types_seen_so_far;
  still_valid = validate_expression(in_class, in_feature, expr, sym_tab);

  for (int i = cases->first(); cases->more(i); i = cases->next(i)) {
    branch_class* nth_branch = (branch_class*)cases->nth(i);
    Symbol nth_branch_decl_type = nth_branch->get_type_decl();
   
    bool okay = validate_case(in_class, in_feature, nth_branch, sym_tab);
    if (std::find(types_seen_so_far.begin(), types_seen_so_far.end(), nth_branch_decl_type) == types_seen_so_far.end()) {
      types_seen_so_far.push_back(nth_branch_decl_type);
    } else {
      still_valid = false;
    }

    still_valid = okay && still_valid;    
  }

  return still_valid;
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
  still_valid = still_valid && is_super_type_of(branch_type, s, sym_tab);

  sym_tab->exitscope();
  return still_valid;
}
bool validate_exp_block(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab) {
  block_class* block_exp = (block_class*) e;
  Expressions expressions = block_exp->get_expressions();
  
  bool still_valid = true;
  
  for (int i = expressions->first(); expressions->more(i); i = expressions->next(i)) {
    Expression nth_exp = expressions->nth(i);
    bool okay = validate_expression(in_class, in_feature, nth_exp, sym_tab) && still_valid;
    still_valid = okay && still_valid;
  }

  // DEBUG_ACTION(std::cout << "Block just validated says: " << still_valid << std::endl);

  return still_valid;
}
bool validate_exp_let(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab) {
  let_class* let_exp = (let_class*) e;
  Symbol id = let_exp->get_identifier();
  Symbol type_decl = let_exp->get_type_decl();
  Expression init_expr = let_exp->get_init_expr();
  Expression body = let_exp->get_body();

  bool still_valid = sym_tab->lookup(type_decl) != NULL ? true : false;
  still_valid = id != self && still_valid;

  Symbol init_expr_type = get_expression_type(in_class, init_expr, sym_tab);
  still_valid = (init_expr_type == No_type || (type_decl == init_expr_type) || is_super_type_of(type_decl, init_expr_type, sym_tab)) && still_valid;

  symbol_table_data* data = new symbol_table_data({NULL, NULL, type_decl, NULL});
  sym_tab->enterscope();
  sym_tab->addid(id, data);
  
  still_valid = validate_expression(in_class, in_feature, init_expr, sym_tab) && still_valid;
  still_valid = validate_expression(in_class, in_feature, body, sym_tab) && still_valid;

  sym_tab->exitscope();
  return still_valid;
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
  bool still_valid = true;
  object_class* object_exp = (object_class*) e;
  if (sym_tab->lookup(object_exp->get_name())) {
    if (object_exp->get_name() == in_feature->get_name() && 
        !object_in_ancestry_attribs(object_exp->get_name(), in_class->get_name(), sym_tab)) {
      still_valid =  false;
      if (object_exp->get_name() == self) {
        still_valid = true;
      }
    }
    // still_valid =  true;
  } else if (object_in_ancestry_attribs(object_exp->get_name(), in_class->get_name(), sym_tab)) {
    still_valid = true;
  } else {
    still_valid = false;
  }
  return still_valid;
}

/**
  * This function checks whether a symbol is a feature of any class in the 
  * ancestry of that object. Of course, it needs the symbol table to do this.
  * 
  * @param sym The symbol being checked for (maybe an attribute or a method.)
  *        It must surely be an object identifier (attribute or method).
  * @param c The class whose ancestors are being checked. It must surely be a
  *        type (class) identifier
  * @param sym_tab The symbol table (pointer to it).
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
