Bicol University  
College of Science  
Computer Science Department  

**CS 114 – Operating Systems**  

*Machine Exercise No.2*  
A. Read the manual (man) about the **fork()** , **getpid()** , **getppid()** **UNIX/Linux API**
functions. Then write a program which creates one child process, and then both parent and
child are running in blind loops displaying their PIDs and PPIDs. This way you will have the
models of typical I/O-oriented processes. Perform some observations, how the CPU time is
shared between these two processes and how they are reacting for Ctrl+C (**SIGINT**) or
default **SIGTERM signal** (sent from command line by kill shell command when running in
background – can be some fun). The output screen may look like this:    
**[PARENT]: PID 2374, PPID 2360  
[PARENT]: PID 2374, PPID 2360  
[CHILD]: PID 2375, PPID 2374  
[PARENT]: PID 2374, PPID 2360  
[CHILD]: PID 2375, PPID 2374  
[CHILD]: PID 2375, PPID 2374  
[PARENT]: PID 2374, PPID 2360…**    
B. Read the manual about the **wait()** and **exec()** families of functions. Then write a program
which creates one child process, loads new binary code (compiled from other source) for the
child, and then parent waits (without using CPU nor I/O) until child finishes his task (counting
from 1 to 10 and displaying counter status for example). The output screen may
look like this:    
**[PARENT]: PID 2421, waits for child with PID 2422  
[CHILD]: PID 2421, starts counting:  
[CHILD]: i = 1  
[CHILD]: i = 2  
...  
[CHILD]: i = 10  
[PARENT]: Child with PID 2422 finished and unloaded.**
