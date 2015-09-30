//
//  Number.cpp
//  athena
//
//  Created by Finucane on 1/6/15.
//


#include <iostream>
#include "PermutationNumber.h"


/*stub for an assertion macro*/

#if 0
#define insist(e) if(!(e)){printf ("assertion failed %s:%d (%s)", __FILE__, __LINE__, #e); exit(0);}
#else
#define insist(e)((void)(e))
#endif



/*
 Number is a class that encapsulates the solution to this programming puzzle thing (compute
 the index of a word if that word were in a sorted list of permutations of that word.)
 
 in the sub-computations a sorted string is used to represent the original word or substrings
 of the original word. this simplifies some of the code, for instance
 counting duplicate sequences of characters for the permuation math, or counting
 the number of letters lexigraphically less than a given letter.
 
 in the main "number" computation, which recursively computes the number
 of sorted permutations before a given start letter, the sorted word is recursed on
 in parallel to the original word.
 
 without optimizing any of the factorial computations or some of string computations
 this thing runs 2 orders of magnitude faster than 500 msecs on my old mac, but for fun
 i at least did a table for the factorials.
*/

PermutationNumber::PermutationNumber ()
{
  /*set up factorial table*/
  memset (factorials, 0, sizeof (factorials));
  factorials [0] = 1;
  for (uint64_t i = 1; i < MAX_WORD; i++)
    factorials [i] = factorials [i-1] * i;
}

/*
 return n! for n <= MAX_WORD
*/
uint64_t PermutationNumber::factorial (unsigned n)
{
  insist (n <= MAX_WORD);
  return factorials [n];
}

/*
 return number of occurences of char "character" in string "string"
*/

unsigned PermutationNumber::numOccurences (char character, std::string&string)
{
  unsigned count = 0;
  
  for (int i = 0; i < string.length (); i++)
  {
    if (string [i] == character)
      count++;
  }
  return count;
}


/*
 return the number of unique permuations of a sorted string that may have
 duplicate letters. the formula for this is n! / (n1! n2! n3! ...)
 where n1, n2, etc are the counts of each duplicate letter.
 
 more than 20! doesn't fit into 64 bits, so "s" cannot be longer
 than 20 chars. (MAX_WORD)
 
 that the string is sorted makes computing the denominator easier.
*/

uint64_t PermutationNumber::numPermutations (std::string&sorted)
{
  insist (sorted.length () <= MAX_WORD);
  
  uint64_t denominator = 1;
  char last = 0;
  
  for (int i = 0; i < sorted.length (); i++)
  {
    /*if we have reached a new character in the sequence, get its occurence
     count and include its factorial into the denominator*/
    
    if (last != sorted [i])
    {
      last = sorted [i];
      denominator *= factorial (numOccurences (last, sorted));
    }
  }
  
  insist (denominator);

  return factorial ((unsigned) sorted.length ()) / denominator;
}



/*
 return the number of letters in "sorted" that are less than "character", this
 includes duplicates.
*/
unsigned PermutationNumber::numLessThan (char character, std::string&sorted)
{
  unsigned i = 0;
  for (i = 0; i < sorted.length () && sorted [i] < character; i++);
  return i;
}

/*
 recursive method to return the "number" of string "word" where "sorted" is "word"
 with its characters sorted
*/
uint64_t PermutationNumber::number (std::string&word, std::string&sorted)
{
  insist (word.length () == sorted.length ());
  insist (word.length () <= MAX_WORD);
  
  /*if the word one or fewer letters there's just 1 permuation and its "number" is 1*/
  if (word.length () < 2)
    return 1;
  
  /*
   otherwise its number is how many permutations there are of words starting
   with letters less than the word's first letter, plus whatever the "number" is of
   the rest of the word.
 
   in the sorted list of permuations, the number of permutations up to
   the first letter of word is the number of permutations for all the words
   starting with letters less than word [0]. this is the number of permutations
   starting at any fixed letter, in other words permuations-per-letter, multiplied by how
   many letters there are before word [0] lexigraphically. this letter count
   includes duplicates.
   */
  
  uint64_t lessThan = numLessThan (word [0], sorted);
  uint64_t beforePermutations = 0;
  
  if (lessThan != 0)
  {
    /*permuations starting at any given letter...*/
    uint64_t perLetter = numPermutations (sorted) / sorted.length ();
    beforePermutations = lessThan * perLetter;
  }
  
  /*
    for the recursion, word loses its first character, and sorted, which
    is always word that has been sorted, loses one occurence of word [0].
  */
  insist (sorted.find (word [0]) != std::string::npos);
  sorted.erase (sorted.find (word [0]), 1);
  word.erase (0, 1);
  
  return beforePermutations + number (word, sorted);
}

/*
 return the 1-based index of "cstring" in a sorted list of its unique permutations
*/
uint64_t PermutationNumber::number (const char*cstring)
{
  insist (cstring);

  /*get the word and a sorted copy of it*/
  std::string word (cstring);
  std::string sorted (word);
  sort (sorted.begin (), sorted.end ());
  return number (word, sorted);
}


/*
 for ease of building this puzzle code throw in main here...
*/
int main(int argc, const char*argv[])
{
  if (argc!= 2 || strlen (argv [1]) > 20)
  {
    std::cout << "usage: " << argv [0] << " <string-which-is-less-than-21-chars>\n";
    return 0;
  }
  
  PermutationNumber pn;
  
  std::cout << pn.number (argv [1]) << "\n";
}


