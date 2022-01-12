# Operating-System

## Parent and Child Processes
## Expected output
parent (PID 333275) created child_1 (PID 333276)</br>
parent (PID 333275) is waiting for child_1 (PID 333276) to complete before creating child_2 child_1 (PID 333276) is calling an external program external_program.out and leaving parent From the external program: The PID was 333276 for child_1
parent (PID 333275) created child_2 (PID 333277)</br>
child_2 (PID 333277) created child_2.1 (PID 333278)</br>
child_2.1 (PID 333278) is calling an external program external_program.out and leaving child_2 From the external program: The PID was 333278 for child_2.1</br>
child_1 and child_2 are completed and parent process is terminating...</br>

## Inter-Processes Communications
## Expected output
1. parent (PID 2209) created a child (PID 2213)</br>
2. parent (PID 2209) receives X = "CS" from the user</br>
3. parent (PID 2209) writes X = "CS" to the pipe</br>
4. child (PID 2213) receives Y = "3305" and Z = "is fun!" from the user</br>
5. child (PID 2213) concatenates Y and Z to generate Y' = " 3305 is fun!"</br>
6. child (PID 2213) reads X from pipe = "CS"</br>
7. child (PID 2213) concatenates X and Y' to generate Z' = "CS 3305 is fun!"</br>
8. child (PID 2213) writes Z' into the pipe</br>
9. parent (PID 2209) reads concatenated result from the pipe (Z' = "CS 3305 is fun!")</br>

## Inter-Thread Communications
## Expected Output
1. parent (PID 2209) receives X = 7 and Y = 6 from the user</br>
2. parent (PID 2209) writes X = 7 and Y = 6 to the pipe</br>
3. thread(TID100) readsX=7andY=6fromthepipe</br>
4. thread (TID 100) writes X+Y = 13 to the pipe</br>
5. thread (TID 101) reads X+Y = 13 from the pipe</br>
6. thread (TID 101) identifies X+Y= 13 as an odd number</br>
7. thread (TID 101) writes X+Y = 13 to the pipe</br>
8. thread (TID 102) reads X+Y = 13 from the pipe</br>
9. thread (TID 102) identifies X+Y=13 as a 2 digit number</br>

## Performance Evaluation of CPU Scheduling Algorithms
## Expected Output
Process: P1 Arrival Time: 0 Burst time: 24 Waiting Time: 6 Turnaround Time: 30 </br>
Process: P2 Arrival Time: 1 Burst time: 3 Waiting Time: 3 Turnaround Time: 6 </br>
Process: P3 Arrival Time: 2 Burst time: 3 Waiting Time: 5 Turnaround Time: 8 </br>
Total Turnaround Time: 44 Average waiting time = 4.67s Average turnaround time = 14.67</br>

Process: P1 Arrival Time: 0 Burst time: 10 Waiting Time: 21 Turnaround Time: 31 </br>
Process: P2 Arrival Time: 1 Burst time: 5 Waiting Time: 13 Turnaround Time: 18 </br>
Process: P3 Arrival Time: 2 Burst time: 8 Waiting Time: 17 Turnaround Time: 25 </br>
Process: P4 Arrival Time: 3 Burst time: 9 Waiting Time: 20 Turnaround Time: 29 </br>
Total Turnaround Time: 103 <br>
Average waiting time = 17.75 <.br>
Average turnaround time = 25.75</br>
