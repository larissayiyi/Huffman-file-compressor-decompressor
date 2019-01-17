/* Filename: HCNode.cpp
 * Date: Nov 22, 2016
 * Author: Larissa Johnson
 * Description: Nodes of the huffman tree used for encoding data for 
 * compression
 */
#include "HCNode.h"

#include <iostream>

typedef unsigned char byte;

using namespace std;
bool HCNode::operator<(const HCNode& other){
  if ( count != other.count ) {
    return count > other.count;
  }
  return symbol > other.symbol;
}
