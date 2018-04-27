Contents:
    1. Compiling
    2. Running
    3. Algorithm Explanation
    4. References


1. Compiling the Program
    The program comes with a makefile that will compiled the program
    with the necessary flags.  To compile the program, just run the "make"
    command from within the same directory as the makefile.

    The program makes uses of a handful of C++11 features so must be compiled
    with the necessary flags.  This can be done by adding the -std=c++11 flag 
    when running g++.


2. Running the Program
    Once the program has been compiled, it can be run by running the
    command "./editdis" from within the same directory as the executable. 
    Input can be given directly to the program from the terminal, or it can
    take in a piped file using the < operator.

    Example:
    ./editdis < test.txt


3. Algorithm Explanation
    The primary algorithm used is based on the "Wagner-Fischer" algorithm.  The
    recurrence relation for the algorithm is as follows:

    s(1..i)     -- Contains the first word
    t(1..j)     -- Contains the second word
    
    M(i, j) = M(i-1, j-1) + copyCost;    if s(i) = t(j)
    M(i, j) = min(  
                    M(i-1, j  ) + deletionCost,
                    M(i  , j-1) + insertionCost,
                    M(i-1, j-1) + substitutionCost
                 );

    Base Case:  M(i, 0) = i * insertionCost;
                M(0, j) = j * deletionCost;

    
    The Algorithm is modified to allow for variables costs in all areas.  This
    algorithm assumes that only a single operation can be performed and that
    substitution is only allowed if s(i) and t(j) are different.  If they are
    the same, then only a copy is allowed.


4. References
    I used the wikipedia article: https://en.wikipedia.org/wiki/Edit_distance
    to better understand the problem and the algorithm.  My recurrence relation
    is heavily based on the information in that article.
