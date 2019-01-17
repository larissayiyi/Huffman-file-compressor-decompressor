/* Filename: uncompress.cpp
 * Date: Nov 22, 2016
 * Author: Larissa Johnson
 * Description: This file uncompresses the encoded file created by compress.
 * It uses the "header" infomation provided by compress to recreate the 
 * huffmanTree and use it to decode the file
 */
#include "HCTree.h"
#include <vector>
#include <iostream>
#include <string.h>
#include <fstream>
#include <stdlib.h>

using namespace std;

int bitnum = 8; // 8 bits in a byte 
// main driver for uncompress
int main (int argc, char** argv) {
	// check the number of arguments
  if(argc != 3) {
    cerr << "Incorrect number of arguments\n";
    return -1;
  }
  // input and output files
  char * infile = argv[1];
  char * outfile = argv[2];
  
	// create file streams
  ifstream instream;
  ofstream outstream;
	// open input file
  instream.open(infile, ios::binary);
	if (!instream){
	  cerr << "Failed opening " << infile << endl;
    return -1;
	}
	// store frequency 
  vector <int> freq (256);
	// retrive ints of frequency
	int firstByte;
	int secondByte;
	int thirdByte;
  int frequency;
	int numbytes = 0;
	// should be 256 3 - bytes int long 
	for (int i = 0; i < 256; i++) {
    frequency = 0;
    firstByte = instream.get();
	  secondByte = instream.get();
	  thirdByte = instream.get();
	  frequency = (firstByte << (bitnum + bitnum)) | (secondByte << bitnum) | 
	    thirdByte;
	  freq[i] = frequency;
    numbytes = numbytes + frequency;
	}
	// check for the newline 
	int nextByte = instream.get();
	if (nextByte != '\n') {
	  cerr << "Something is not right" << endl;
	  return -1;
	}
  
	
	// build tree
  HCTree huffmanTree;
  huffmanTree.build(freq);
	
  byte symbol;
	// open outstream to write 
  outstream.open(outfile, ios::binary);
	if (!outstream) {
	  cerr << "error opening output file" << endl;
	}
	// read in bit by bit
	BitInputStream bitInStream (instream);
	// run it numbytes times
	for ( int i = 0; i < numbytes; i++) {
    // decode 
	  nextByte = huffmanTree.decode(bitInStream);
	  symbol = (byte) nextByte;
	  // store
	  outstream << symbol;
	  
	}
	// close both files
  instream.close();
  outstream.close();
  
  
}
