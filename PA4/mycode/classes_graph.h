#include <vector>
#include <set>
#include <queue>
#include<unistd.h>

#define DEBUGGING

#ifdef DEBUGGING
#define DEBUG_ACTION(x) x << std::flush
#else
#define DEBUG_ACTION(x)
#endif

#include "stringtab.h"
#include "cool-tree.h"

namespace mycode {

static std::set<Symbol> classes_in_i_graph;
static std::set<Class_> classes_checked_second_time;
static std::queue<Class_> classes_not_ready;

typedef struct node {
    struct node* immediate_sibling;
    struct node* first_child;
    Symbol name;
} graph_node;

typedef struct graph {
    graph_node* root;
} inheritance_graph;

bool add_class_to_inheritance_graph(graph_node*& root, const Class_ c) {

  if (!root) return false;
  
  class__class* class_to_add = (class__class*) c->copy_Class_();
  
  if (classes_in_i_graph.find(class_to_add->get_parent_name()) == classes_in_i_graph.cend()) {
    classes_not_ready.push(c);
    DEBUG_ACTION(std::cout << "Class " 
                          << class_to_add->get_name()
                          << " was not ready because "
                          << class_to_add->get_parent_name()
                          << " was not in the tree."
                          << std::endl);
    return false;
  }

  if (root->name == class_to_add->get_parent_name()) {
    if (root->first_child == NULL) {
      root->first_child = new graph_node;
      root->first_child->immediate_sibling = NULL;
      root->first_child->first_child = NULL;
      root->first_child->name = class_to_add->get_name();
      DEBUG_ACTION(std::cout << "Adding class "
                             << class_to_add->get_name()
                             << " whose parent is "
                             << class_to_add->get_parent_name()
                             << " as first child."
                             << std::endl);
      classes_in_i_graph.emplace(class_to_add->get_name());
    } else {
      graph_node* curr_child = root->first_child;
      while(curr_child->immediate_sibling != NULL) {
        curr_child = curr_child->immediate_sibling;
      }

      // DEBUG_ACTION(std::cout << "Adding class ["
      //                        << class_to_add->get_name()
      //                        << "] whose parent is "
      //                        << class_to_add->get_parent_name()
      //                        << "."
      //                        << "aha"
      //                        << std::endl);
      DEBUG_ACTION(std::cout << "found a place for class:" << class_to_add->get_name() << " ");
      curr_child->immediate_sibling = new graph_node;
      curr_child = curr_child->immediate_sibling;
      curr_child->immediate_sibling = NULL;
      curr_child->first_child = NULL;
      curr_child->name = class_to_add->get_name();
      classes_in_i_graph.emplace(class_to_add->get_name());
    }
    return true;
  } else {
    if (!(root->first_child && add_class_to_inheritance_graph(root->first_child, c))) {
      graph_node* curr_sibling = root->immediate_sibling;
      while(curr_sibling && !add_class_to_inheritance_graph(curr_sibling, c)) {
        DEBUG_ACTION(std::cout << "oo");
        // if (curr_sibling == NULL) DEBUG_ACTION(std::cout << "a big mystery");
        curr_sibling = curr_sibling->immediate_sibling;
      }
      if (!curr_sibling) {
        return false;
      }
      return true;
    }
  }
  DEBUG_ACTION(std::cout << "returning true");
  return true;
}

inheritance_graph* build_inheritance_graph(std::vector<Class_> classes_list, Class_& faulty_class) {
  Symbol root_symbol = ((class__class*)classes_list[0]->copy_Class_())->get_name();
  classes_list.erase(classes_list.begin());

  inheritance_graph* inheritance = new graph;
  graph_node* root = new graph_node;
  root->first_child = NULL;
  root->immediate_sibling =  NULL;
  root->name = root_symbol;
  inheritance->root = root;
  
  classes_in_i_graph.emplace(root_symbol);
  /*Class_ c : classes_list*/
  for (Class_ c : classes_list) {
    DEBUG_ACTION(std::cout << "Trying to add class " << ((class__class*)c->copy_Class_())->get_name()  << std::endl);
    if (add_class_to_inheritance_graph(root, c))
      DEBUG_ACTION(std::cout << "Added class " << ((class__class*)c->copy_Class_())->get_name()  << std::endl);
  }
  int num_outstanding = classes_not_ready.size();

  DEBUG_ACTION(std::cout << classes_not_ready.size() << " classes have not been added" << std::endl);
  while (num_outstanding) {
    DEBUG_ACTION(std::cout << "a");
    Class_ curr_class = classes_not_ready.front();
    
    DEBUG_ACTION(std::cout << "b");
    classes_not_ready.pop();
    num_outstanding--;
    DEBUG_ACTION(std::cout << "c");
    
    if (!add_class_to_inheritance_graph(root, curr_class)) {
      DEBUG_ACTION(std::cout << "D");
      if (classes_checked_second_time.find(curr_class) != classes_checked_second_time.cend()) {
        DEBUG_ACTION(std::cout << "E");
        faulty_class = curr_class;
        DEBUG_ACTION(std::cout << "This was where I failed" << std::endl);
        break;
      }

      classes_not_ready.push(curr_class);
      classes_checked_second_time.emplace(curr_class);
      num_outstanding++;
    }
  }

  return inheritance;
}

}