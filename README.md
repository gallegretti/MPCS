# MPCS

Usage: MPCS.exe <file> [options]  

For a <file> that has two related strings, one per line  

options:  
 
--glpk         Outputs the GLPK data for the problem in the stdout 
-s <seed>      Seed to be used in the GRASP's RNG                 (Does not apply to --glpk)  
-t <seconds>   Time in seconds that the program is allowed to run (Does not apply to --glpk)  
--verbose      Prints verbose log in the stdout                   (Does not apply to --glpk)  


for example:

MPCS.exe group1\1 -s 42 -t 10

Will run the problem group1\1 with the seed 42 for 10 seconds.


MPCS.exe group1\1 --glpk >> data.txt

Will generate the data for the integer programming for the group1\1 problem


To run the integer programming run like so:

glpsol.exe --math mpcsmodel.txt -d data.txt

