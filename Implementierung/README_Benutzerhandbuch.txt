==========================
USER MANUAL
==========================
Preface:
This program calculates ,how many people k must be in a room to find with probability 1/2 at least two people who share the same element of a basic set M with n elements with 3 methods:
V0 is the implementation with Heron method (main implementation).
V1 is the implementation with Look-Up-Table.
V2 is the implementation with pure row representation.

--------------------------

Usage:
Default mode :
-n <int> : describes the size of the base set M
-V <int> : describes the implementation to use.
-B <int> : describes the number of repetitions of the function call. The runtime of the given implementation is measured and printed.
Example: ./main -n 365 -V0 -B100 : The formula is calculated for 365 elements with the main implementation and repeated 100 times. The runtime is also measured and displayed.


Test mode : 
-T : By default, the tests are performed with the main implementation. You can also choose the implementation with -V and the number of repetitions with -B.
Example : -/main -T -V2 -B 100: The tests are executed with the pure row representation method and the runtime for 100 iterations is measured and displayed.
