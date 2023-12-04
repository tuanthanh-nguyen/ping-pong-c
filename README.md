# ping pong c

## Description

Demonstrate intercomunication between 2 processes using pipe and file descriptors.
`pp2.c` basically forks 2 processes which talks to each other by 2 pipes which is a pair of read/write file descriptors, report it to `out1.txt` and `out2.txt`.
The parent process will wait for a duration and print result as bytes count exchanges between 2 processes.


## Run

```
gcc pp2.c -o pp2
./pp2
```

## TODO

+ `pp1.c` attempts to forks 2 proceses to read that execl a program. Takes `ping.c` and `pong.c` as 2 program to executes as 2 child processes.
+ reported results is mismatched since 2 processes bytes count must be different at most 1 bytes. (difference is 6 bytes currently)
