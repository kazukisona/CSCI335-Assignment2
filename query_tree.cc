// Kazuki Sona
// Main file for Part2(a) of Homework 2.

#include "AvlTree.h"
#include "BinarySearchTree.h"
#include "SequenceMap.h"

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

namespace {

// helper functions
// @&db_line: a string reference to a line from db
// @return: enzyme acronyms part of the input line
string GetEnzymeAcronym(string &db_line) {

  string an_enz_acro;
  int i = 0;

  while (db_line[i] != '/') {
    an_enz_acro += db_line[i];
    ++i;
  }

  // update db_line by deleting enzyme acronym part
  db_line = db_line.substr(i+1);

  return an_enz_acro;
} 

// @&db_line: a string reference to a line from db
// @&a_reco_seq: a string reference to a recognize sequence found in db_line
// @return: true if there is a recognize sequence, if not return false
bool GetNextRegocnitionSequence(string &db_line, string &a_reco_seq) {

  if (db_line.size() <= 1)
    return false;

  // initialize a_reco_seq
  a_reco_seq = "";
  int i = 0;

  while (db_line[i] != '/') {
    a_reco_seq += db_line[i];
    ++i;
  }

  // update db_line
  db_line = db_line.substr(a_reco_seq.size()+1);

  return true;
}

// @a_tree: tree 
// @num_queries: number of queries in a input file
// make a query and query a_tree for num_queries times
template <typename TreeType>
void Query(TreeType &a_tree, int num_queries) {
    string query_reco_seq;
    SequenceMap query;

    for (int i = 0; i < num_queries; ++i) {
      cin >> query_reco_seq;
      query = SequenceMap(query_reco_seq, "");
      a_tree.findElement(query);
    }
}

// QueryTree function
// @db_filename: an input filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
template <typename TreeType>
void QueryTree(const string &db_filename, TreeType &a_tree) {
  // Code for running Part2(a)
  // You can use public functions of TreeType. For example:

  //============= Tree construction part ================
  // open file
  ifstream file(db_filename);

  string db_line;

  // pre-processing header
  // pass the first 10 lines 
  for (int i = 0; i < 10; ++i) {
    getline(file, db_line);
  }

  // construct a tree
  while (getline(file, db_line)) {

    if (db_line == "")
      break;

    string an_enz_acro = GetEnzymeAcronym(db_line);

    string a_reco_seq;

    while (GetNextRegocnitionSequence(db_line, a_reco_seq)) {
      SequenceMap new_sequence_map(a_reco_seq, an_enz_acro);
      if (!a_tree.contains(new_sequence_map))
        a_tree.insert(new_sequence_map);
    }
  }

  // print the constructed tree
  a_tree.printTree();

  cout << endl;

  //============= Querying tree part ================
  // get queries and print result three times
  Query(a_tree, 3);
}

}  // namespace

int main(int argc, char **argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <databasefilename> <tree-type>" << endl;
    return 0;
  }
  const string db_filename(argv[1]);
  const string param_tree(argv[2]);
  cout << "Input filename is " << db_filename << endl;
  cout << "Type of tree is " << param_tree << endl;
  if (param_tree == "BST") {
    // Note that you will replace BinarySearchTree<int> with BinarySearchTree<SequenceMap>
    BinarySearchTree<SequenceMap> a_tree;
    QueryTree(db_filename, a_tree);
  } else if (param_tree == "AVL") {
    // Note that you will replace AvlTree<int> with AvlTree<SequenceMap>
    AvlTree<SequenceMap> a_tree;
    QueryTree(db_filename, a_tree);
  } else {
    cout << "Uknown tree type " << param_tree << " (User should provide BST, or AVL)" << endl;
  }
  return 0;
}
