# Gridworld
A C++ approach to implementing the Gridworld. (From the book Reinforcement Learning)
It has been proved that the result of 4*4 grid is identical to the result in the book.

The result.png shows the running result of a 6*6 grid, with the terminal on (0,0) and (5,5)

For simplicity, the whole program does not take the efficiency in to consideration, though Dynamic Programming is already an inefficient process. As you can see, the code has many for loops. In each loop, the program checks the terminal and the block, by traversing ALL elements in the vector.
