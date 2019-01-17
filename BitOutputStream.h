/* Filename: BitOutputStream.h
 * Date: Nov 22, 2016
 * Author: Larissa Johnson
 * Description: This is used to store encoded data from bits to bytes and 
 * write the bytes to output stream.
 * It is used in compress to write encoded data by bits 
 */
#ifndef BITOUTPUTSTREAM_H
#define BITOUTPUTSTREAM_H

#include <iostream>
class BitOutputStream{
  private:
    char buf; // one byte buffer of bits
    int nbits; // how many bits have been written to buf
    std::ostream & out; // reference to the output stream to use
  public:
  /** Initialize a BitOutputStream that will use 
   * the given ostream for output */
  BitOutputStream(std::ostream & os) : out(os), buf(0), nbits(0) {
    // clear buffer and bit counter 
  }
  
  /** Send the buffer to the output and clear it */
  void flush();
  /** Write the least significant bit of the argument to
   * the bit buffer, and increment the bit buffer index.
   * But flush the buffer first, if it is full */
  void writeBit(int i);
};
#endif
