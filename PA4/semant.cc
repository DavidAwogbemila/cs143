

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "semant.h"
#include "symtab.h"
#include "utilities.h"

#include <vector>
#include <string>

#include "mycode/classes_graph.h"
#include "mycode/symbol_table_data.h"
#include "mycode/naming_scope_validation.h"

extern int semant_debug;
extern char *curr_filename;

//////////////////////////////////////////////////////////////////////
//
// Symbols
//
// For convenience, a large number of symbols are predefined here.
// These symbols include the primitive type and method names, as well
// as fixed names used by the runtime system.
//
//////////////////////////////////////////////////////////////////////
Symbol 
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
//
// Initializing the predefined symbols.
//
static void initialize_constants(void)
{
  arg         = idtable.add_string("arg");
  arg2        = idtable.add_string("arg2");
  Bool        = idtable.add_string("Bool");
  concat      = idtable.add_string("concat");
  cool_abort  = idtable.add_string("abort");
  copy        = idtable.add_string("copy");
  Int         = idtable.add_string("Int");
  in_int      = idtable.add_string("in_int");
  in_string   = idtable.add_string("in_string");
  IO          = idtable.add_string("IO");
  length      = idtable.add_string("length");
  Main        = idtable.add_string("Main");
  main_meth   = idtable.add_string("main");
  //   _no_class is a symbol that can't be the name of any 
  //   user-defined class.
  No_class    = idtable.add_string("_no_class");
  No_type     = idtable.add_string("_no_type");
  Object      = idtable.add_string("Object");
  out_int     = idtable.add_string("out_int");
  out_string  = idtable.add_string("out_string");
  prim_slot   = idtable.add_string("_prim_slot");
  self        = idtable.add_string("self");
  SELF_TYPE   = idtable.add_string("SELF_TYPE");
  Str         = idtable.add_string("String");
  str_field   = idtable.add_string("_str_field");
  substr      = idtable.add_string("substr");
  type_name   = idtable.add_string("type_name");
  val         = idtable.add_string("_val");
}

static std::vector<Class_> classes_list;

namespace mycode {

  // Store classes, their features and their parents in symboll table.
  void initialize_symbol_table_with_globals(std::vector<Class_>& classes_list,
                                            SymbolTable<Symbol, symbol_table_data>*& sym_tab) {
    sym_tab->enterscope();

    for (Class_ c: classes_list) {
      class__class* c_info = (class__class*)c->copy_Class_();
      symbol_table_data* data = new symbol_table_data;
      data->features = c_info->get_features();
      data->parent = c_info->get_parent_name();
      data->return_type = NULL;
      data->type = NULL;
      sym_tab->addid(c_info->get_name(), data);
    }
  }

}

ClassTable::ClassTable(Classes classes) : semant_errors(0) , error_stream(cerr) {

  /* Fill this in */
  install_basic_classes();
  Class_ faulty_class = NULL;
  std::vector<Class_> user_classes_list;

  for (int i = classes->first(); classes->more(i); i = classes->next(i)) {
    classes_list.push_back(classes->nth(i));
    user_classes_list.push_back(classes->nth(i));
  }

  mycode::inheritance_graph* i_graph = mycode::build_inheritance_graph(classes_list, faulty_class);

  if (!faulty_class) {
    DEBUG_ACTION(std::cout << "Built inheritance graph successfully." << std::endl);
  } else {
    DEBUG_ACTION(std::cout << "Unable to build inheritance graph. Program is semantically incorrect." << std::endl);
    semant_error(faulty_class);
    exit(1);
  }

  SymbolTable<Symbol, mycode::symbol_table_data>* symbol_table
    (new SymbolTable<Symbol, mycode::symbol_table_data>);

  mycode::initialize_symbol_table_with_globals(classes_list, symbol_table);
  
  for (Class_ c : user_classes_list) {
    DEBUG_ACTION(std::cout << "Validating class " << ((class__class*)c->copy_Class_())->get_name() << std::endl);
    if (mycode::validate_class(c, symbol_table) ) {
      DEBUG_ACTION(std::cout << "Class " 
                             << ((class__class*)c->copy_Class_())->get_name()
                             << " was okay!"
                             << std::endl);
      
    } else {
      DEBUG_ACTION(std::cout << "Error! while validating class " << ((class__class*)c->copy_Class_())->get_name() << std::endl);
      semant_error(c);
    }
  }
}

void ClassTable::install_basic_classes() {

  // The tree package uses these globals to annotate the classes built below.
  // curr_lineno  = 0;
  Symbol filename = stringtable.add_string("<basic class>");
  
  // The following demonstrates how to create dummy parse trees to
  // refer to basic Cool classes.  There's no need for method
  // bodies -- these are already built into the runtime system.
  
  // IMPORTANT: The results of the following expressions are
  // stored in local variables.  You will want to do something
  // with those variables at the end of this method to make this
  // code meaningful.
  // 
  // The Object class has no parent class. Its methods are
  //        abort() : Object    aborts the program
  //        type_name() : Str   returns a string representation of class name
  //        copy() : SELF_TYPE  returns a copy of the object
  //
  // There is no need for method bodies in the basic classes---these
  // are already built in to the runtime system.
  Class_ Object_class =
	class_(Object, 
	       No_class,
	       append_Features(
			       append_Features(
					       single_Features(method(cool_abort, nil_Formals(), Object, no_expr())),
					       single_Features(method(type_name, nil_Formals(), Str, no_expr()))),
			       single_Features(method(copy, nil_Formals(), SELF_TYPE, no_expr()))),
	       filename);

  // 
  // The IO class inherits from Object. Its methods are
  //        out_string(Str) : SELF_TYPE       writes a string to the output
  //        out_int(Int) : SELF_TYPE            "    an int    "  "     "
  //        in_string() : Str                 reads a string from the input
  //        in_int() : Int                      "   an int     "  "     "
  //
  Class_ IO_class = 
	class_(IO, 
	      Object,
	      append_Features(
		      append_Features(
			       append_Features(
					       single_Features(method(out_string, single_Formals(formal(arg, Str)),
								      SELF_TYPE, no_expr())),
					       single_Features(method(out_int, single_Formals(formal(arg, Int)),
								      SELF_TYPE, no_expr()))),
			       single_Features(method(in_string, nil_Formals(), Str, no_expr()))),
		      single_Features(method(in_int, nil_Formals(), Int, no_expr()))),
	     filename);  
  //
  // The Int class has no methods and only a single attribute, the
  // "val" for the integer. 
  //
  Class_ Int_class =
	class_(Int, 
	       Object,
	       single_Features(attr(val, prim_slot, no_expr())),
	       filename);

  //
  // Bool also has only the "val" slot.
  //
  Class_ Bool_class =
	class_(Bool, Object, single_Features(attr(val, prim_slot, no_expr())),filename);

  //
  // The class Str has a number of slots and operations:
  //       val                                  the length of the string
  //       str_field                            the string itself
  //       length() : Int                       returns length of the string
  //       concat(arg: Str) : Str               performs string concatenation
  //       substr(arg: Int, arg2: Int): Str     substring selection
  //       
  Class_ Str_class =
  class_(Str, 
	      Object,
	      append_Features(
	       append_Features(
			       append_Features(
					       append_Features(
							       single_Features(attr(val, Int, no_expr())),
							       single_Features(attr(str_field, prim_slot, no_expr()))),
					       single_Features(method(length, nil_Formals(), Int, no_expr()))),
			       single_Features(method(concat, 
						      single_Formals(formal(arg, Str)),
						      Str, 
						      no_expr()))),
	       single_Features(method(substr, 
				      append_Formals(single_Formals(formal(arg, Int)), 
						     single_Formals(formal(arg2, Int))),
				      Str, 
				      no_expr()))),
	     filename);






  
  classes_list.push_back(Object_class);
  classes_list.push_back(IO_class);
  classes_list.push_back(Int_class);
  classes_list.push_back(Bool_class);
  classes_list.push_back(Str_class);
}

////////////////////////////////////////////////////////////////////
//
// semant_error is an overloaded function for reporting errors
// during semantic analysis.  There are three versions:
//
//    ostream& ClassTable::semant_error()                
//
//    ostream& ClassTable::semant_error(Class_ c)
//       print line number and filename for `c'
//
//    ostream& ClassTable::semant_error(Symbol filename, tree_node *t)  
//       print a line number and filename
//
///////////////////////////////////////////////////////////////////

ostream& ClassTable::semant_error(Class_ c)
{                                                             
  return semant_error(c->get_filename(),c);
}    

ostream& ClassTable::semant_error(Symbol filename, tree_node *t)
{
  error_stream << filename << ":" << t->get_line_number() << ": ";
  return semant_error();
}

ostream& ClassTable::semant_error()                  
{                                                 
  semant_errors++;                            
  return error_stream;
} 



/*   This is the entry point to the semantic checker.

     Your checker should do the following two things:

     1) Check that the program is semantically correct
     2) Decorate the abstract syntax tree with type information
        by setting the `type' field in each Expression node.
        (see `tree.h')

     You are free to first do 1), make sure you catch all semantic
     errors. Part 2) can be done in a second stage, when you want
     to build mycoolc.
 */
void program_class::semant()
{
  initialize_constants();

  /* ClassTable constructor may do some semantic analysis */
  ClassTable *classtable = new ClassTable(classes);

  /* some semantic analysis code may go here */

  if (classtable->errors()) {
  	cerr << "Compilation halted due to static semantic errors." << endl;
	  exit(1);
  }
}
