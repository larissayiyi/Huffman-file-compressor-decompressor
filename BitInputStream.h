/* Filename: BitInputStream.h
 * Date:Nov 22, 2016
 * Author: Larissa Johnson 
 * Description: This is used to take each byte from the inoput and read it bit
 * by bit. It is used in uncompress to read encoded data by bits
 */
#ifndef BITINPUTSTREAM_H
#define BITINPUTSTREAM_H
#include <iostream>
class BitInputStream{
  private:
    char buf; // one byte buffer of the bits
    int nbits; // how many bits have been written to buf
    std:: istream & in; // reference to the input stream to use
  public:
    /** Initialize a BitInputStream that will use 
     * the given ostream for output */
    BitInputStream (std:: istream & is) : in(is), buf(0), nbits(8){
      
    }
    /** Fill the buffer from the input */
    void fill();
  
    /** Read and return the next bit from the bit buffer.
    * Fill it first if necessary. */
    int readBit();
};
#endif
