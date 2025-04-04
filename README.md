Wrote a program to identify optimized flight path from a given source airport to a destination airport, utilizing the A* algorithm.
A given flight data base consisting of 180,000+ flights was read from, and stored into a Binary Search Tree for cheap search, insertion, and iteration
Database of 1000+ airport geological positions was read from to compute the heurisitic in A*

Heuristic for this particular A* solution was the Haversine Distance from the source to destination summed to the current amount of travel time
Many constraints were applied including minimum and maximum layover times, maximum travel duration, preferred airlines, etc.
Variety of data structures such as hashtables, BSTs, priority queues, etc. were all utilized for efficiency

