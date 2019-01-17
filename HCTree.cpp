/* Filename: HCTree.cpp
 * Date: Nov 22, 2016
 * Author: Larissa Johnson
 * Description: Huffman tree is used for encoding and decoding data to achieve
 * file compression
 */
#include "HCTree.h"
#include <queue>
#include <vector>
#include <fstream>
#include <stack>
#include "HCNode.h"
#include "BitInputStream.h"
#include "BitOutputStream.h"

/*  Use the Huffman algorithm to build a Huffman coding trie.
 *  PRECONDITION: freqs is a vector of ints, such that freqs[i] is 
 *  the frequency of occurrence of byte i in the message.
 *  POSTCONDITION:  root points to the root of the trie,
 *  and leaves[i] points to the leaf node containing byte i.
 */
void HCTree::build(const vector<int>& freqs){
  // priority_queue so highest is always on the top
  priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> pq;
  for (int i = 0; i < freqs.size(); i++) {
    // for non-zero freqency put in the tree
    if (freqs[i] != 0) {
      leaves[i] = new HCNode(freqs[i], i);
      pq.push(leaves[i]);
    }
  }
	// as long as there is more than one tree in the forest 
  while ( pq.size() > 1 ) {
    HCNode * temp = new HCNode (0, 0);
    temp -> c0 = pq.top();
    temp -> c0 -> p = temp;
    pq.pop();
    temp -> c1 = pq.top();
    temp -> c1 -> p = temp;
    pq.pop();
    temp -> count = temp -> c0 -> count + temp -> c1 -> count;
	  // push the combined node back in the forest 
    pq.push(temp);
  }
	//root is the top of the priority_queue
  if (pq.size() != 0){
    root = pq.top();
  }
}
/*  Write to the given BitOutputStream
 *  the sequence of bits coding the given symbol.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
void HCTree::encode(byte symbol, BitOutputStream& out) const{
  stack <int> revcode;
  HCNode * temp = leaves[symbol];
  // symb is the only item in the tree
  if (temp == root) {
    out.writeBit(1);
    return;
  }
  // trace back to the root
  while (temp != root) {
    // c0 child
    if (temp -> p -> c0 == temp) {
      revcode.push(0);
    }
    // c1 child
    else {
      revcode.push(1);
    }
    // go up to the parent
    temp = temp -> p;
  }
  while (!revcode.empty()){
    out.writeBit(revcode.top());
    revcode.pop();
  }
}
/*  Write to the given ofstream
 *  the sequence of bits (as ASCII) coding the given symbol.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 *  THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT 
 *  BE USED IN THE FINAL SUBMISSION.
 */

void HCTree::encode(byte symbol, ofstream& out) const{
  stack <int> revcode;
  HCNode * temp = leaves[symbol];
  // symb is the only item in the tree
  if (temp == root) {
    out << '1';
    return;
  }
  // trace back to the root
  while (temp != root) {
    // c0 child
    if (temp -> p -> c0 == temp) {
      revcode.push(0);
    }
    // c1 child
    else {
      revcode.push(1);
    }
    // go up to the parent
    temp = temp -> p;
  }
  while (!revcode.empty()){
    if (revcode.top() == 0) {
	    out << (byte)'0';
  	}
	  else{
 	    out << (byte)'1';
	  }
    revcode.pop();
  }
}
/*  Return symbol coded in the next sequence of bits from the stream.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
int HCTree::decode(BitInputStream& in) const{
  int code;
  HCNode * temp = root;
	/*if (in.eof()){
	  return EOF;
	}*/
  while (temp -> c0 || temp -> c1){
    // read by single bits
	  code = in.readBit();
	  if(code < 0){
    	return EOF;
    }
    if (code == 0) {
      temp = temp -> c0;
    }
    else{
      temp = temp -> c1;
    }
    
  }
  return temp-> symbol;
	
}
/*  Return the symbol coded in the next sequence of bits (represented as 
 *  ASCII text) from the ifstream.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 *  THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT BE USED
 *  IN THE FINAL SUBMISSION.
 */
int HCTree::decode(ifstream& in) const{
  byte symb;
	// start from the root
  HCNode * temp = root;
	if (in.eof()){
	  return EOF;
	}
  while (temp -> c0 || temp -> c1){
    // get another byte
	  in >> symb;
	  if(in.eof()){
    	return EOF;
  }
    if (symb == '0') {
      temp = temp -> c0;
    }
    else{
      temp = temp -> c1;
    }
    
  }
  return temp-> symbol;
	
}

// helper method for the destructor to delete all node pointers recursively
void HCTree::deleteAll(HCNode * node) {
	if (node){
    if (node -> c0){
      deleteAll(node -> c0);
	  }
    if (node -> c1){
      deleteAll(node -> c1);
    }
    delete node;
	}
}

// destructor
HCTree::~HCTree(){
	if (root) {
    deleteAll(root);
	}
}

