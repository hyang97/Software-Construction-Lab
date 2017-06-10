Week 8 Homework: Writing a multithreaded version of Brian Allen's ray tracer
code

Issues I ran into:

- since the thread function was declared outside of the main function, all of
the variables in the scope of the main function had to be made available to the
thread function somehow. this was accomplished by creating an argument struct
that held all of the variables that the thread function needed (the thread
function is a slightly altered version of the double for loop iterating through
each pixel of the image).

- in order to avoid issues with reassigning constant variables, all variables in
argument struct were pointers to the variables needed (except for the thread
number variable)

- the first "working" version of the parallelized code created almost the
identical image as baseline.ppm, except there were black bars that appeared when
the number of threads were > 1. my code was skipping rows because all of the
threads had the same thread number, since I passed in a pointer to the argument
struct and all threads had a pointer pointing to the same struct (the last
one). in order to fix this, I created an array of argument structs, each with
their own thread numbers. this fixed the issue.

Performance increase with multithreading:

for reference, copied from make-log.txt:

1 thread:
real    0m49.302s
user    0m49.299s
sys     0m0.002s

2 threads:
real    0m24.782s
user    0m49.203s
sys     0m0.003s

4 threads:
real    0m12.570s
user    0m49.417s
sys     0m0.003s

8 threads:
real    0m6.836s
user    0m52.154s
sys     0m0.003s

Multithreading brought very effective speedups to the program - almost exactly
proportional, in fact. Each time the thread count doubled, the runtime
halved. This is indicative of the parallel nature of computer graphics.
