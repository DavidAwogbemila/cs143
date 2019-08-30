
#include "cool-tree.h"
#include "symtab.h"
#include "init_symbol_table.h"

namespace mycode {

bool object_in_ancestry_attribs(object_class* obj, const Symbol c, SymbolTable<Symbol, symbol_table_data>*& sym_tab);

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

bool validate_expression(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>*& sym_tab) {
  switch (e->get_expr_type()) {
    case expr_type::EXP_ASSIGN: {
      assign_class* assign_exp = (assign_class*) e;
      return validate_exp_assign(in_class, in_feature, assign_exp, sym_tab);
    }
    case expr_type::EXP_STATIC_DISPATCH: {
      static_dispatch_class* static_dispatch_exp = (static_dispatch_class*) e;
      return validate_exp_static_dispatch(in_class, in_feature, static_dispatch_exp, sym_tab);
    }
    case expr_type::EXP_DISPATCH: {
      dispatch_class* dispatch_exp = (dispatch_class*) e;
      return validate_exp_dispatch(in_class, in_feature, dispatch_exp, sym_tab);
    }
    case expr_type::EXP_COND: {
      cond_class* cond_exp = (cond_class*) e;
      return validate_exp_cond(in_class, in_feature, cond_exp, sym_tab);
    }
    case expr_type::EXP_LOOP: {
      loop_class* loop_exp = (loop_class*) e;
      return validate_exp_loop(in_class, in_feature, loop_exp, sym_tab);
    }
    case expr_type::EXP_TYPCASE: {
      typcase_class* typcase_exp = (typcase_class*) e;
      return validate_exp_typcase(in_class, in_feature, typcase_exp, sym_tab);
    }
    case expr_type::EXP_BLOCK: {
      block_class* block_exp = (block_class*) e;
      return validate_exp_block(in_class, in_feature, block_exp, sym_tab);
    }
    case expr_type::EXP_LET: {
      let_class* let_exp = (let_class*) e;
      return validate_exp_let(in_class, in_feature, let_exp, sym_tab);
    }
    case expr_type::EXP_PLUS: {
      plus_class* plus_exp = (plus_class*) e;
      return validate_exp_plus(in_class, in_feature, plus_exp, sym_tab);
    }
    case expr_type::EXP_SUB: {
      sub_class* sub_exp = (sub_class*) e;
      return validate_exp_sub(in_class, in_feature, sub_exp, sym_tab);
    }
    case expr_type::EXP_MUL: {
      mul_class* mul_exp = (mul_class*) e;
      return validate_exp_mul(in_class, in_feature, mul_exp, sym_tab);
    }
    case expr_type::EXP_DIVIDE: {
      divide_class* divide_exp = (divide_class*) e;
      return validate_exp_divide(in_class, in_feature, divide_exp, sym_tab);
    }
    case expr_type::EXP_NEG: {
      neg_class* neg_exp = (neg_class*) e;
      return validate_exp_neg(in_class, in_feature, neg_exp, sym_tab);
    }
    case expr_type::EXP_LT: {
      lt_class* lt_exp = (lt_class*) e;
      return validate_exp_lt(in_class, in_feature, lt_exp, sym_tab);
    }
    case expr_type::EXP_EQ: {
      eq_class* eq_exp = (eq_class*) e;
      return validate_exp_eq(in_class, in_feature, eq_exp, sym_tab);
    }
    case expr_type::EXP_LEQ: {
      leq_class* leq_exp = (leq_class*) e;
      return validate_exp_leq(in_class, in_feature, leq_exp, sym_tab);
    }
    case expr_type::EXP_COMP: {
      comp_class* comp_exp = (comp_class*) e;
      return validate_exp_comp(in_class, in_feature, comp_exp, sym_tab);
    }
    case expr_type::EXP_INT_CONST: { return true; }
    case expr_type::EXP_BOOL_CONST: { return true; }
    case expr_type::EXP_STRING_CONST: { return true; }
    case expr_type::EXP_NEW_: {
      new__class* new__exp = (new__class*) e;
      return validate_exp_new_(in_class, in_feature, new__exp, sym_tab);
    }
    case expr_type::EXP_ISVOID: {
      isvoid_class* isvoid_exp = (isvoid_class*) e;
      return validate_exp_isvoid(in_class, in_feature, isvoid_exp, sym_tab);
    }
    case expr_type::EXP_NO_EXPR: { return true; }
    case expr_type::EXP_OBJECT: {
      object_class* object_exp = (object_class*) e->copy_Expression();
      return validate_exp_object(in_class, in_feature, object_exp, sym_tab);
    }
    defualt: { 
      return false;
    }
  }
  return false;
}

bool validate_exp_assign(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab) {
  assign_class* assign_exp = (assign_class*) e;
  /* TODO: Do type-checking on type being assigned to. */
  return validate_expression(in_class, in_feature, assign_exp->get_expr(), sym_tab);
  }
bool validate_exp_static_dispatch(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab) {
  static_dispatch_class* s_dispatch_exp = (static_dispatch_class*) e;
  Expression expr = s_dispatch_exp->get_expr();
  Symbol func_name = s_dispatch_exp->get_name();
  Symbol type_name = s_dispatch_exp->get_type_name();
  Expressions args = s_dispatch_exp->get_args();

  bool still_valid = validate_expression(in_class, in_feature, expr, sym_tab);

  for (int i = args->first(); args->more(i); i = args->next(i)) {
    still_valid = validate_expression(in_class, in_feature, args->nth(i), sym_tab) && still_valid;
  }

  return still_valid;
  /* TODO: Typechecking! */
}
bool validate_exp_dispatch(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab) {
  dispatch_class* dispatch_exp = (dispatch_class*) e;
  Expression expr = dispatch_exp->get_expr();
  Symbol func_name = dispatch_exp->get_name();
  Expressions args = dispatch_exp->get_args();

  bool still_valid = validate_expression(in_class, in_feature, expr, sym_tab);

  for (int i = args->first(); args->more(i); i = args->next(i)) {
    still_valid = validate_expression(in_class, in_feature, args->nth(i), sym_tab) && still_valid;
  }

  return still_valid;
  /* TODO: Typechecking! */
}
bool validate_exp_cond(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab) {
  cond_class* cond_exp = (cond_class*) e;
  Expression pred = cond_exp->get_pred();
  Expression then_exp = cond_exp->get_pred();
  Expression else_exp = cond_exp->get_pred();
  /* TODO: Typecheck cond for Bool-ness */
  return validate_expression(in_class, in_feature, pred, sym_tab) && \
         validate_expression(in_class, in_feature, then_exp, sym_tab) && \
         validate_expression(in_class, in_feature, else_exp, sym_tab);


}
bool validate_exp_loop(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab) {
  loop_class* loop_exp = (loop_class*) e;
  Expression pred = loop_exp->get_pred();
  Expression body = loop_exp->get_body();

  return validate_expression(in_class, in_feature, pred, sym_tab) && \
         validate_expression(in_class, in_feature, body, sym_tab);
         /* May need to possibly add pred variables to scope for body. Maybe. */
}
bool validate_exp_typcase(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab) {
  typcase_class* typcase_exp = (typcase_class*) e;
  Expression expr = typcase_exp->get_expr();
  Cases cases = typcase_exp->get_cases();
  bool still_valid = true;
  for (int i = cases->first(); cases->more(i); i  = cases->next(i)) {
    still_valid = validate_case(in_class, in_feature, cases->nth(i), sym_tab) && still_valid;
  }
  return still_valid;
  /* TODO: Typechecking! */
}
bool validate_case(Class_ in_class, Feature in_feature, Case c, SymbolTable<Symbol, symbol_table_data>* sym_tab) {
  branch_class* case_branch = (branch_class*) c;
  Symbol branch_id = case_branch->get_name();
  Symbol branch_type = case_branch->get_type_decl();
  Expression branch_expression = case_branch->get_expr();

  symbol_table_data* data = new symbol_table_data({NULL, NULL, branch_type, NULL});
  sym_tab->enterscope();
  sym_tab->addid(branch_id, data);
  bool okay = validate_expression(in_class, in_feature, branch_expression, sym_tab);
  sym_tab->exitscope();
  return okay;
}
bool validate_exp_block(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab) {
  block_class* block_exp = (block_class*) e;
  Expressions expressions = block_exp->get_expressions();
  bool still_valid = true;
  for (int i = expressions->first(); expressions->more(i); i = expressions->next(i)) {
    still_valid = validate_expression(in_class, in_feature, expressions->nth(i), sym_tab) && still_valid;
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
  return validate_expression(in_class, in_feature, plus_exp->get_first_expression(), sym_tab) && \
         validate_expression(in_class, in_feature, plus_exp->get_second_expression(), sym_tab);
  /* TODO: Typechecking! */
}
bool validate_exp_sub(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab) {
  sub_class* sub_exp = (sub_class*) e;
  return validate_expression(in_class, in_feature, sub_exp->get_first_expression(), sym_tab) && \
         validate_expression(in_class, in_feature, sub_exp->get_second_expression(), sym_tab);
  /* TODO: Typechecking! */
}
bool validate_exp_mul(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab) {
  mul_class* mul_exp = (mul_class*) e;
  return validate_expression(in_class, in_feature, mul_exp->get_first_expression(), sym_tab) && \
         validate_expression(in_class, in_feature, mul_exp->get_second_expression(), sym_tab);
  /* TODO: Typechecking! */
}
bool validate_exp_divide(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab) {
  divide_class* divide_exp = (divide_class*) e;
  return validate_expression(in_class, in_feature, divide_exp->get_first_expression(), sym_tab) && \
         validate_expression(in_class, in_feature, divide_exp->get_second_expression(), sym_tab);
  /* TODO: Typechecking! */
}
bool validate_exp_neg(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab) {
  neg_class* neg_exp = (neg_class*) e;
  return validate_expression(in_class, in_feature, neg_exp->get_expr(), sym_tab);
  /* TODO: Typechecking */
}
bool validate_exp_lt(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab) {
  lt_class* lt_exp = (lt_class*) e;
  return validate_expression(in_class, in_feature, lt_exp->get_first_expression(), sym_tab) && \
         validate_expression(in_class, in_feature, lt_exp->get_second_expression(), sym_tab);
  /* TODO: Typechecking! */
}
bool validate_exp_eq(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab) {
  eq_class* eq_exp = (eq_class*) e;
  return validate_expression(in_class, in_feature, eq_exp->get_first_expression(), sym_tab) && \
         validate_expression(in_class, in_feature, eq_exp->get_second_expression(), sym_tab);
  /* TODO: Typechecking! */
}
bool validate_exp_leq(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab) {
  leq_class* leq_exp = (leq_class*) e;
  return validate_expression(in_class, in_feature, leq_exp->get_first_expression(), sym_tab) && \
         validate_expression(in_class, in_feature, leq_exp->get_second_expression(), sym_tab);
  /* TODO: Typechecking! */
}
bool validate_exp_comp(Class_ in_class, Feature in_feature, Expression e, SymbolTable<Symbol, symbol_table_data>* sym_tab) {
  comp_class* comp_exp = (comp_class*) e;
  return validate_expression(in_class, in_feature, comp_exp->get_expression(), sym_tab);
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
  object_class* object_exp = (object_class*) e;
  if (sym_tab->probe(object_exp->get_name())) {
    if (object_exp->get_name() == in_feature->get_name() && 
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
  * ancestry of that object. Of course, it needs the symbol table to do this.
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
