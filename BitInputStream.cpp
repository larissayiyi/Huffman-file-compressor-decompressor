/* Filename: BitInputStream.cpp
 * Date: Nov 22, 2016
 * Author: Larissa Johnson
 * Description: This is used to take each byte from the input and read it bit
 * by bit. It is used in uncompress to read encoded data by bits
 */
#include "BitInputStream.h"
#include <iostream>

using namespace std;

/** Fill the buffer from the input */
void BitInputStream::fill() {
   buf = in.get();
   nbits = 0;
  }

/** Read and return the next bit from the bit buffer.
 * Fill it first if necessary. 
 * Return 1 if the bit read is 1
 * Return 0 if the bit read is 0
 */
int BitInputStream::readBit(){
  int numbits = 8; 
  // if all bits in the buffer are read fill the buffer first
  if (nbits == numbits){
    fill();
  }
  // increment number read
  nbits++;
  int bit = (buf >> ( numbits - nbits)) & 1;
  return bit;
}
