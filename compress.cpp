/* Filename: compress.cpp
 * Date: Nov 22, 2016
 * Author: Larissa Johnson
 * Description: This function takes 2 file as inputs then reads through the 
 * first file to compute the freqency of each unique symbols. Then it 
 * creates a huffmanTree to use for encoding the data into the second file
 */
#include "HCTree.h"
#include "BitInputStream.h"
#include "BitOutputStream.h"
#include <vector>
#include <iostream>
#include <string.h>
#include <fstream>
#include <stdlib.h>

int maxbyte = 255; // max value of a byte
int bitnum = 8; // 8 bits in a byte 
using namespace std;

// helper method to write the header part of the compressed file
void writefreq(vector<int>& freq, ofstream& out){
  for (int i = 0; i< 256; i++){
    int temp = freq[i];
    // write first byte
    byte tempbyte;
    tempbyte = (temp >> (bitnum + bitnum)) & maxbyte;
    out.put(tempbyte);
    // second byte
    tempbyte = (temp >> bitnum) & maxbyte;
    out.put(tempbyte);
    // third byte
    tempbyte = temp & maxbyte;
    out.put(tempbyte);
  }
  out.put('\n');
}

// main driver for the compression function
int main (int argc, char** argv) {
  // check numbers of arguments
  if (argc != 3) {
    cerr << "Incorrect number of arguments.\n";
    return -1;
  }
  // get the file names
  char * infile = argv[1];
  char * outfile = argv[2];
  
  // set the in and out stream
  ifstream instream;
  ofstream outstream;
  // open input file
  instream.open(infile, ios::binary);
  if(!instream) {
    cerr << "Failed opening " << infile << endl;
    return -1;
  }
  // to store freqency
  vector <int> freq (256);
  // taken from the lecture slide 
  int nextByte;
  int unique = 0;
  int totalBytes = 0;
  // store frequency and totalBytes in the file
  while ((nextByte = instream.get()) != EOF) {
    
      if ( freq[nextByte] == 0 ){
        unique++;
      } 
      freq[nextByte]++;
      totalBytes++;
  }
  instream.close();
  
  // build the tree
  HCTree huffmanTree;
  huffmanTree.build(freq);
  
  // open again for compression
  instream.open(infile, ios::binary);
  outstream.open(outfile, ios::binary);
  // bit output stream
  BitOutputStream bstream (outstream);
  // check for end of file
  if (!instream || !outstream){
    cerr << "Failed opening files " << endl;
    return -1;
  }
  // write the tree
  writefreq(freq, outstream);
  
  byte symbol;
  // encode the same file
  for (int i = 0; i < totalBytes; i++) {
    if ((nextByte = instream.get()) != EOF){
      symbol = (byte) nextByte;
      huffmanTree.encode(symbol, bstream);
    }
    else{
      break;
    }
  }
  // flush out remaining data and close the files
  bstream.flush();
  instream.close();
  outstream.close();
  return 0;
}
