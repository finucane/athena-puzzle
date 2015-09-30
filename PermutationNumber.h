//
//  PermutationNumber.h
//
//  Created by Finucane on 1/6/15.
//

#ifndef Number_h
#define Number_h

#include <string>

class PermutationNumber
{
  private:
  enum
  {
    MAX_WORD = 20
  };
  uint64_t factorials [MAX_WORD];
  uint64_t factorial (unsigned n);
  unsigned numOccurences (char character, std::string&sorted);
  uint64_t numPermutations (std::string&sorted);
  unsigned numLessThan (char character, std::string&sorted);
  uint64_t number (std::string&word, std::string&sorted);
  
  public:
  PermutationNumber ();
  uint64_t number (const char*s);
};

#endif