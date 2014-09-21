closest-point
=============

Here was the assignment

CS 5050 Assignment Five 40 points

1)      Implement a problem generator for the closest pair problem. On a domain of 100 by 100, generate n points with different distributions: a) random, b) uniform (hexagonal so that all nearby distances are the same), c) mixed, 95% points are laid out in the hexagonal pattern, the rest are randomly placed).

2)      Implement the simple n times n algorithm for closest pair

3)      Implement divide and conquer Slow algorithm: sort by x first, then in the solution construction compute the best distance as min or left and right, then extract points in the slice that lie within +/- best distance, then use the naive algorithm over the points in the slice to determine the distance to be returned. Note that we expect this algorithm to be slow.

4)      Implement divide and conquer Fast algorithm: as above but use the technique discussed in class: sort the strip by y then linear scan looking back 6 points

5)      Do a randomized study on the three algorithms vs. three types of problems. Use a semi-log plot to display the results and a doubling scheme to increase problem sizes. Assume the problem size is a power of two. Make sure you run your algorithms for as larger problem size as possible. Each point on the graph should be the result of at least 10 distinct runs (when the problems are randomized). Fit lines to the results and provide a table of the slopes.

6)      Does the problem type affect the performance of the algorithms? Carefully explain why if there is a difference. If not, then explain why not.

7)      The 40 points will be awarded as follows: 20 points fully working program that correctly implements the algorithms and the problem generator; 10 points for the empirical studies and line fitting; 10 points for the correct graphs and correct technical explanation of the behavior.

8)      Submit your graphs and report, data files containing your raw data and your commented code along with instructions to run the code.
