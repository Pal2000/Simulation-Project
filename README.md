 Simulation Based Assignment:
 
 
This system will show you the entire details about the order in which processes have executed by CPU scheduling in the form of Ghantt Chart. It will also show you the total time needed for executing all processes. Moreover, It will also display the waiting time and turn around time.
 
 NOTE: -->> os1 file is .C file and os2 file is .C++ file. Although the content is same, just language difference is there. In c++ file I have used C++ STL for priority Queue and Queue for Round Robin and in C language I have used structures.

 
 <<--- Details of this Assignment -->> 
 
 1. Fixed priority preemptive Scheduling (Queue 1)
 * Priority 0 is highest priority.
 * Preemptive:
If one process e.g. P1 is scheduled and running , now another process with higher priority comes e.g. P2. New process(high priority)
process P2 preempts currently running process P1 and process P1 will go to second level queue.

2. Round Robin Scheduling (Queue 2)
* Quantum : Multiples of 2 unit time
* All the processes in second level queue will complete their execution according to round robin scheduling.
* Queue 2 will be processed after Queue 1 becomes empty.
* Priority of Queue 2 has lower priority than in Queue 1.


Let suppose Queue 1 is empty and currently process from Queue 2 is being executed. Now, If at this time a new process arrives then new 
process will be part of Queue 1. So, new process should be scheduled as Queue 1 has higher priority than Queue 2. Again after Queue 1
becomes empty Queue 2 will resume execution.

<<-- Inputs -->>
pid -> process id
AT -> arrival time
BT -> burst time
QT -> quantum time
RT -> remaining time
WT -> waiting time

<<=====================================================================>>
 
