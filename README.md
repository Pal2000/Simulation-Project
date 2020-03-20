 Simulation Based Assignment:
 <<--- Details of this Assignment -->>
 
 1. Fixed priority preemptive Scheduling (Queue 1)
 * Priority 0 is highest priority.
 * Quantum : 2 unit time
 * Preemptive:
If one process e.g. P1 is scheduled and running , now another process with higher priority comes e.g. P2. New process(high priority)
process P2 preempts currently running process P1 and process P1 will go to second level queue.

2. Round Robin Scheduling (Queue 2)
* Quantum : 2 unit time
* All the processes in second level queue will complete their execution according to round robin scheduling.
* Queue 2 will be processed after Queue 1 becomes empty.
* Priority of Queue 2 has lower priority than in Queue 1.


Suppose Queue 1 is empty and currently process from Queue 2 is being executed. Now, If at this time a new process arrives then new 
process will be part of Queue 1. So, new process should be scheduled as Queue 1 has higher priority than Queue 2. Again after Queue 1
becomes empty Queue 2 will resume execution.

<<-- Inputs -->>
pid -> process id
AT -> arrival time
BT -> burst time
QT -> quantum time
FT -> finish time
RT -> remaining time

<<=====================================================================================================================================>>
 
 
 ## Updation1   17-March-2020 ##
 Making a structure for the Queues and all the Process, created  priority Queue and Queue for Round Robin.
 
 ## Updation2   19-March-2020##
 Create a Gantt Chart which will show the flow in which all processes are executing.
 
