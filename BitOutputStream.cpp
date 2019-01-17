/* Filename:BitOutputStream.cpp
 * Date: Nov 22, 2016
 * Author: Larissa Johnson
 * Description: This is used to store encoded data from bits to bytes and 
 * write the bytes to output stream.
 * It is used in compress to write encoded data by bits 
 */
#include "BitOutputStream.h"
#include <iostream>

using namespace std;

/** Send the buffer to the output and clear it */
void BitOutputStream::flush() {
   out.put(buf);
   out.flush();
   buf = nbits = 0;
}
 /** Write the least significant bit of the argument to
  * the bit buffer, and increment the bit buffer index.
  * But flush the buffer first, if it is full */
 void BitOutputStream::writeBit(int i){
   int numbits = 8;
   if ( nbits == numbits){
     flush();
   }
   // just incase if i is not zero or one
   i = i << (numbits - 1) >> (numbits - 1);
   // increment number of bits
   nbits++;
   // store bits from left to right
   buf = buf | (i<< (numbits-nbits));
 }
