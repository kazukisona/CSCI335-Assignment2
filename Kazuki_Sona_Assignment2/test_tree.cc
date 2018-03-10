// Kazuki Sona
// Date: March 8th, 2018
// Main file for Part2(b) of Homework 2.

#include "AvlTree.h"
#include "BinarySearchTree.h"
#include "SequenceMap.h"

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
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

//@db_filename: open file named db_filename
//@&a_tree: reference to a tree
// Construct a tree of TreeType with data in db_filename
template <typename TreeType>
void ConstructTree(const string db_filename, TreeType &a_tree) {
  ifstream file(db_filename);
  string db_line; // file line 
  
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
  file.close();
}

// @db_filename: an input database filename.
// @seq_filename: an input sequences filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
template <typename TreeType>
void TestTree(const string &db_filename, const string &seq_filename, TreeType &a_tree) {
  // Code for running Part2(b)  
  //============= Tree construction part ================
  ConstructTree(db_filename, a_tree);
  
  a_tree.printTree();
  cout << endl;

  // == answers the questions ==
  // question #2
  cout << "2: " << a_tree.numOfNodes() << endl;

  // question #3
  double avg_depth = (double) a_tree.totalPathLength() / (double) a_tree.numOfNodes();
  cout << "3a: " << avg_depth << endl;
  cout << "3b: " << (avg_depth / log(a_tree.numOfNodes())) << endl;

  int numCalls = 0; // number of recursive calls
  int num_success = 0; // number of success of find() or remove()
  int num_fail = 0; // number of failure of find() or remove()
  string a_sequence;
  SequenceMap query;

  // open sequence.txt file
  ifstream seqFile(seq_filename);

  // find each sequence in a tree
  while (getline(seqFile, a_sequence)) {
    query = SequenceMap(a_sequence, "");

    if (a_tree.find(query, numCalls))
      num_success++;
    else
      num_fail++;
  }

  // question #4
  cout << "4a: " << num_success << endl;
  cout << "4b: " << ((double) numCalls / (double) (num_success+num_fail)) << endl;

  seqFile.close();

  // initialize statistics
  numCalls = 0;
  num_success = 0;
  num_fail = 0;

  // open sequence.txt file for removing
  ifstream rmFile(seq_filename);

  while (getline(rmFile, a_sequence)) {
    query = SequenceMap(a_sequence, "");

    if (a_tree.remove(query, numCalls))
      num_success++;
    else
      num_fail++;
  }

  // question #5
  cout << "5a: " << num_success << endl;
  cout << "5b: " << ((double) numCalls / (double) (num_success+num_fail)) << endl;

  // question #6
  cout << "6a: " << a_tree.numOfNodes() << endl;
  avg_depth = (double) a_tree.totalPathLength() / (double) a_tree.numOfNodes();
  cout << "6b: " << avg_depth << endl;
  cout << "6c: " << (avg_depth / log(a_tree.numOfNodes())) << endl;
 }
}  // namespace

int
main(int argc, char **argv) {
  if (argc != 4) {
    cout << "Usage: " << argv[0] << " <databasefilename> <queryfilename> <tree-type>" << endl;
    return 0;
  }
  const string db_filename(argv[1]);
  const string seq_filename(argv[2]);
  const string param_tree(argv[3]);
  cout << "Input file is " << db_filename << ", and sequences file is " << seq_filename << endl;
  cout << "Type of tree is " << param_tree << endl;
  if (param_tree == "BST") {
    // Note that you will replace BinarySearchTree<int> with BinarySearchTree<SequenceMap>
    BinarySearchTree<SequenceMap> a_tree;
    TestTree(db_filename, seq_filename, a_tree);
  } else if (param_tree == "AVL") {
    // Note that you will replace AvlTree<int> with AvlTree<SequenceMap>
    AvlTree<SequenceMap> a_tree;
    TestTree(db_filename, seq_filename, a_tree);
  } else {
    cout << "Uknown tree type " << param_tree << " (User should provide BST, or AVL)" << endl;
  }
  return 0;
}
