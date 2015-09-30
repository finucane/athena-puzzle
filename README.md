#athena-puzzle

This is my solution to an candidate screening  puzzle I did for a company called Athena Health in San Francisco, who were looking to hire an iOS programmer. They liked my solution and had me travel to the office and spend a half a day implementing a couple of little programs under the pressure of a job interview situation.

#Puzzle

The puzzle was stated as follows:

Consider a "word" as any sequence of capital letters A-Z (not limited to just "dictionary words"). For any word with at least two different letters, there are other words composed of the same letters but in a different order (for instance, STATIONARILY/ANTIROYALIST, which happen to both be dictionary words; for our purposes "AAIILNORSTTY" is also a "word" composed of the same letters as these two).

We can then assign a number to every word, based on where it falls in an alphabetically sorted list of all words made up of the same set of letters. One way to do this would be to generate the entire list of words and find the desired one, but this would be slow if the word is long.

Write a program which takes a word as a command line argument and prints to standard output its number. Do not use the method above of generating the entire list. Your program should be able to accept any word 20 letters or less in length (possibly with some letters repeated), and should use no more than 1 GB of memory and take no more than 500 milliseconds to run. Any answer we check will fit in a 64-bit integer.

Sample words, with their rank:  

ABAB = 2  
AAAB = 1  
BAAA = 4  
QUESTION = 24572  
BOOKKEEPER = 10743  
NONINTUITIVENESS = 8222334634  

Your program will be judged on how fast it runs and how clearly the code is written. We will be running your program as well as reading the source code, so anything you can do to make this process easier would be appreciated.

#Solution

My solution is in a single .cpp file with header.

bash-3.2$ g++ PermutationNumber.cpp  
bash-3.2$ ./a.out QUESTION  
24572  
bash-3.2$  

See Number.cpp for comments on how the solution works, and work.jpeg for my doodles.


