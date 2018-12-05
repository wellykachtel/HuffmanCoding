#####1. How you tested your programs to ensure correctness
We used the same methods of testing that 7coder used. Basically we checked that the 
string that was inputted into huff was equal to the string outputted from puff.

In the base case where a file could be empty, we throw a logic error. This was also tested.

With testing via the command line, we ran our code with all the files provided and did the 
diff command on the inputted and outputted files. These returned expected results.

#####2. Anything that surprised you while doing this assignment.
We encountered some bugs while trying to read the huff'ed file bit by bit. It was difficult to 
know if we were doing this correctly since the huff'ed file was gibberish. 