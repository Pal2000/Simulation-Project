#include <stdio.h>
#include <stdlib.h>
#include<string.h>

int n;

//structure for all the processes
struct ProcessInfo{
	char pid[5];// process id
	int AT;  // arrival time
	int BT; // burst time
	int WT; // waiting time
	int CH; // only for check the traversed process for calculating waiting time
	int RT; // remaining time
	int priority; // priority

};


// METHODS-->>

// According to arrival time, sort the queue
void arrivalTimeSorting(struct ProcessInfo input[])
{
	int i,j;
	for(i=0;i<n-1;i++)
	{
		for(j=0;j<n-i-1;j++)
		{
		if(input[j].AT>input[j+1].AT)
		{
			struct ProcessInfo temp=input[j];
			input[j]=input[j+1];
			input[j+1]=temp;
		}
		else if(input[j].AT == input[j+1].AT && input[j].priority > input[j+1].priority)
		{
			struct ProcessInfo temp=input[j];
			input[j]=input[j+1];
			input[j+1]=temp;
		}
		else if((input[j].AT == input[j+1].AT)&& (input[j].priority == input[j+1].priority) && (input[j].pid > input[j+1].pid))
		{
			struct ProcessInfo temp=input[j];
			input[j]=input[j+1];
			input[j+1]=temp;
		}
		
		}
	}
}

//According to priority , sort the queue
void prioritySort(struct ProcessInfo input[],int size)
{
	int i,j;
	for(i=0;i<size-1;i++)
	{
		for(j=0;j<size-i-1;j++)
		{
		if(input[j].priority > input[j+1].priority)
		{
			struct ProcessInfo temp=input[j];
			input[j]=input[j+1];
			input[j+1]=temp;
		}
		}
	}
}

//According to pid , sort the queue
void pidSort(struct ProcessInfo input[])
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n-i-1;j++)
		{
		if(strcmp(input[j].pid,input[j+1].pid)>0)
		{
			struct ProcessInfo temp=input[j];
			input[j]=input[j+1];
			input[j+1]=temp;
		}
		
		}
	}
}


//display the queue
void displayPQ(struct ProcessInfo input[],int size)
{
	int i;
	printf("\n\n");
	for(i=0;i<size;i++)
	{
		printf("\n PID: %s   Arrival Time : %d   Burst Time : %d   Priority :  %d ",input[i].pid,input[i].AT,input[i].BT,input[i].priority);
	}
}


//display the queue
void display(struct ProcessInfo input[])
{
	int i;
	printf("\n");
	for(i=0;i<n;i++)
	{
		printf("\n PID: %s   Arrival Time : %d   Burst Time : %d   Priority :  %d ",input[i].pid,input[i].AT,input[i].BT,input[i].priority);
	}
}




//<< **************************************************************************************************************** >>//

//main
int main()
{
	
	struct ProcessInfo current;
	struct ProcessInfo process;
	struct ProcessInfo obj;
	int no,j,k,i;
	
	int cpuState = 0; //CPU busy =1 CPU idle=0
	int QT = 2 ; //Time Quantum for process
	strcpy(current.pid,"-1");
	current.priority = 1000000;
	int t=0;// time clock
	int pp=0;
	int rr=0;
	
	printf("\nEnter number of processes: ");
	scanf("%d",&no);
	n=no;
	struct ProcessInfo input[no]; // input for all process
	struct ProcessInfo pq[no];  // priority queue
	struct ProcessInfo rb[no]; // round robin queue
	int sizepq=-1,sizerb=-1;
	printf("\nEnter pid (in alphanumeric), arrival time, burst time, priority of %d  processes in this order only\n",no);
	for(i=0;i<no;i++)
	{
		scanf("%s",&input[i].pid);
		scanf("%d",&input[i].AT);
		scanf("%d",&input[i].BT);
		scanf("%d",&input[i].priority);
		input[i].CH=0;
		input[i].WT=0;
		input[i].RT=input[i].BT;
	}
	printf("\nYour entered Processes with proper details.\n");
	display(input);
	
	arrivalTimeSorting(input); //sort according to arrival time 
//	printf("\n Sorted input according to arrival time. ");
//	display(input);  //to see the sorted processes uncomment this
	
	int totalTime=0;  // calculate total time for creating gantt chart
	totalTime = totalTime + input[0].AT;
    for(i= 0 ;i< no; i++ )
    {
    	if( totalTime >= input[i].AT )
    	{
    		totalTime = totalTime +input[i].BT;
    	}
    	else
    	{
    		int diff = (input[i].AT - totalTime);
    		totalTime = totalTime + diff + input[i].BT;

    	}
    }

	char Ghantt[totalTime+1][5]; //Ghantt Chart
	for(i= 0; i< totalTime; i++ )
	{
		strcpy(Ghantt[i],"-1");
	}
	printf("\n\ntotal exection time : %d \n",totalTime);  // total time needed for all process
	
	for (t=0;t<=totalTime;t++)
	{
		for(i = 0; i<no ; i++ ) //Insert the process in Priority Queue whose arrival time matches with time clock
		{
			if(t == input[i].AT)
			{
				sizepq++;
				pq[sizepq].AT=input[i].AT;
        		pq[sizepq].BT = input[i].BT;
        		pq[sizepq].CH = input[i].CH;
        		pq[sizepq].priority = input[i].priority;
        		pq[sizepq].RT = input[i].RT;
        		pq[sizepq].WT = input[i].WT;
        		strcpy(pq[sizepq].pid,input[i].pid);
        		
        		prioritySort(pq,sizepq+1);// sort by priority
			}
		}
		
		if(cpuState == 0) //If CPU is idle
		{
			if(sizepq+1!=0)
			{
				current = pq[0];
				// poping out the first object in priority queue
				for(i=1;i<sizepq+1;i++)
				{
					pq[i-1]=pq[i];
				}
				sizepq--;
				cpuState = 1;
				pp = 1;
				//Q=2;
			}
			else if(sizerb+1!=0)
			{
				current = rb[0];
				// poping out the first object in round robin queue
				for(i=1;i<sizerb+1;i++)
				{
					rb[i-1]=rb[i];
				}
				sizerb--;
				cpuState = 1;
				rr = 1;
				QT= 2;
			}
		}
		else if(cpuState == 1) //If cpu has any procss
		{
			if(pp == 1 && (sizepq+1!=0))
			{
				if(pq[0].priority<current.priority ) //If new process has high priority means less priority no then current's priority no
				{
					sizerb++;
					rb[sizerb].AT=current.AT; //push current process in Rb
					rb[sizerb].BT=current.BT;
					rb[sizerb].WT=current.WT;
					rb[sizerb].priority=current.priority;
					rb[sizerb].RT=current.RT;
					rb[sizerb].CH=current.CH;
					strcpy(rb[sizerb].pid,current.pid);
					
					current = pq[0];
					// poping out the first object in priority queue
					for(i=1;i<sizepq+1;i++)
					{
						pq[i-1]=pq[i];
					}
					sizepq--;
					//QT = 2; 
				}
			}
			else if(rr == 1 && (sizepq+1!=0)) //If process is from RQ and new process come  in PQ
			{
				sizerb++;
				rb[sizerb].AT=current.AT; //push current process in Rb
				rb[sizerb].BT=current.BT;
				rb[sizerb].WT=current.WT;
				rb[sizerb].priority=current.priority;
				rb[sizerb].RT=current.RT;
				rb[sizerb].CH=current.CH;
				strcpy(rb[sizerb].pid,current.pid);
				
				current = pq[0];
				// poping out the first object in priority queue
				for(i=1;i<sizepq+1;i++)
				{
					pq[i-1]=pq[i];
				}
				sizepq--;

				rr = 0;
				pp = 1;
				QT = 2;
			}
		}


		if(current.pid != "-1") // Process is in Execution
		{
			current.RT--;
			QT--;
			strcpy(Ghantt[t],current.pid);
			if(current.RT == 0) //If process Finish
			{
				cpuState = 0 ;
				if(pp==0 && rr==1)
					QT = 2 ;
				strcpy(current.pid , "-1");
				current.priority =1000000 ;
				rr = 0;
				pp = 0;
			}
			// else if(QT==0)   //if you want to apply Quantum Time for Queue1 also uncomment this
			else if(QT== 0 && pp==0 && rr==1) //If time Qunatum of a current running process Finish
			{
				// push into rb queue becoz then it will excute acc to round robin 
				sizerb++;
				rb[sizerb].AT=current.AT; //push current process in Rb
				rb[sizerb].BT=current.BT;
				rb[sizerb].WT=current.WT;
				rb[sizerb].priority=current.priority;
				rb[sizerb].RT=current.RT;
				rb[sizerb].CH=current.CH;
				strcpy(rb[sizerb].pid,current.pid);

				strcpy(current.pid , "-1");
				current.priority = 1000000;
				rr = 0;
				pp = 0;
				cpuState=0;
			
			}
		}
	}
	
	
	// calculations for waiting time
	for(i=0;i<=totalTime;i++)
	{ 
		for(j=0;j<no;j++)
		{
			if(strcmp(Ghantt[i],input[j].pid)==0 && input[j].CH==0)
			{
				input[j].CH=1;
				int ft=i+1;
				int st=i;
				//printf("\n PID:  %s  %d  -  %d  ",input[j].pid,st,input[j].AT);
				int wt=st-input[j].AT;
				for(k=i+1;k<=totalTime;k++)
				{
					if(strcmp(Ghantt[k],input[j].pid)==0 )
					{
						//printf(" + ( %d - %d )",k,ft);
						wt+=(k-ft);
						ft=k+1;
					}
				}
				input[j].WT=wt;
				//printf(" = %d \n\n",input[j].WT);
			}
		}
	}
	
	// Ghantt Chart
	printf("\n NOTE :-- If value of Ghantt chart comes -1 that means CPU is IDLE, no process comes yet!!\n");
	printf("\n Ghantt Chart: \n");
	printf("***************\n\n");
	for(i=0;i<totalTime;i++)
	{
		printf(" %s   |   %d\n",Ghantt[i],i);
	}
	
//display of Waiting time of all the processes

	pidSort(input);  // sort to display according to pid of processes
	printf("\n");
	float sumWT=0, sumTA=0;
	for(i=0;i<no;i++)
	{
		printf("\n Pid : %s     Waiting Time: %d  ",input[i].pid,input[i].WT);
		sumWT+=input[i].WT;
		sumTA+=input[i].WT+input[i].BT;
	}
	
	printf("\n\n Average Waiting Time for all the processes is %0.2f",sumWT/no);
	printf("\n Average Turn Around Time for all processes is %0.2f",sumTA/no);

return 0;
}
