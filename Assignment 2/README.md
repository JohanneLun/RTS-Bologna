Lab assignment 2 - Expanded Dining Philosophers Problem

I have chosen to leave the code as one file, as I did not feel it was necessary to divide it into a .c and .h files. There are comments in the code, but only a minimum as htey can make it harder to actually see the code. 

The numbering of the philosphers are from 0 to 4, when there are 5 philosophers. The chopstick pair to a philosophers right has the same number as the philosopher, and the pair to their left is the id of the philosopher modulo the number of philosophers (id%num_phil). Each of the chopsticks in the pair to the right is id and id+1. The ones to the left are either id-1 and id-2, or for the philosopher with id=0: (id*2 - 2)%N_CHOPSTICKS and (id*2 - 1)%N_CHOPSTICKS. Meaning num_chopsicks-1 and -2. 

I have defined another enum type to make the reading a bit easier. It tells us what side hte philosopher has picked up 2 and 1 chopsticks. 

In the monitor struct there is a mutex, an array of condvars (one for each of the philosophers), an array for the pairs of chopsticks that tells how many chopsticks are on the table, and an array for knowing which of the chopsticks are used. The last array is only needed to be able to print the number/id of the chopsticks used. 
