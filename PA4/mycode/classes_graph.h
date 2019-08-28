#include <vector>
#include <set>
#include <queue>

#define DEBUGGING_

#ifdef DEBUGGING
#define DEBUG_PRINT(x) x
#else
#define DEBUG_PRINT(x)
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
    DEBUG_PRINT(std::cout << "Class " 
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
        DEBUG_PRINT(std::cout << "Adding class "
                               << class_to_add->get_name()
                               << " whose parent is "
                               << class_to_add->get_parent_name()
                               << "."
                               << std::endl);
        classes_in_i_graph.emplace(class_to_add->get_name());
      } else {
        graph_node* curr_child = root->first_child;
        while(curr_child->immediate_sibling != NULL) {
          curr_child = curr_child->immediate_sibling;
        }
        curr_child->immediate_sibling = new graph_node;
        curr_child = curr_child->immediate_sibling;
        curr_child->immediate_sibling = NULL;
        curr_child->first_child = NULL;
        curr_child->name = NULL;
      }
      return true;
  } else {
    graph_node* curr_child = root->first_child;
    while(!add_class_to_inheritance_graph(curr_child, c)) {
      curr_child = curr_child->immediate_sibling;
    }
    if (!curr_child) {
      return false;
    }
    return true;
  }
}

inheritance_graph* build_inheritance_graph(std::vector<Class_> classes_list, Symbol root_symbol, Class_& faulty_class) {
  inheritance_graph* inheritance = new graph;
  graph_node* root = new graph_node;
  root->first_child = NULL;
  root->immediate_sibling =  NULL;
  root->name = root_symbol;
  inheritance->root = root;
  
  classes_in_i_graph.emplace(root_symbol);
  
  DEBUG_PRINT(std::cout << "There are " << classes_list.size() << " classes with which to build" << std::endl);
  for (Class_ c : classes_list) {
      add_class_to_inheritance_graph(root, c);
  }

  while (!classes_not_ready.empty()) {
    Class_ curr_class = classes_not_ready.front();
    
    classes_not_ready.pop();
    
    if (!add_class_to_inheritance_graph(root, curr_class)) {
      if (classes_checked_second_time.find(curr_class) != classes_checked_second_time.cend()) {
        faulty_class = curr_class;
        DEBUG_PRINT(std::cout << "This was where I failed" << std::endl);
        break;
      }

      classes_not_ready.push(curr_class);
      classes_checked_second_time.emplace(curr_class);
    }
  }

  return inheritance;
}

}