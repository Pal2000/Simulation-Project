#include<bits/stdc++.h>
using namespace std;

//structure for all the processes
struct ProcessInfo{
	string pid;
	int AT;
	int BT;
	int WT;
	int CH;
	int RT;
	int priority;
};

//objects for structures
struct ProcessInfo current;
typedef struct ProcessInfo process;
struct ProcessInfo obj;


///Methods:-->

//display the input
void display(vector<process> input)
{
	cout<<"\n\n";
	for(int i=0;i<input.size();i++)
	{
		cout<<" PID : "<<input[i].pid<<"  Arrival Time : "<<input[i].AT<<"  Burst Time : "<<input[i].BT<<"  Priority : "<<input[i].priority<<"\n";
	}
}
// According to arrival time, sort the input
bool arrivalTimeSorting( const process& p1 ,const process& p2)
{
	if(p1.AT < p2.AT)
		return true;
	else if(p1.AT > p2.AT)
		return false;
	if(p1.priority < p2.priority)
		return true;
	else if(p1.priority > p2.priority)
		return false;
	if(p1.pid < p2.pid)
		return true;

	return false;
}

// According to priority, sort the queue
struct prioritySort
{
	bool operator()(const process& x ,const process& y)
	{
		if( x.priority > y.priority )
			return true;
		else if( x.priority < y.priority )
			return false;
		if( x.pid > y.pid )
			return true;

		return false;
		
	}
};

//According to pid, sort the processes
bool pidSort(const process& x , const process& y)
{
	return x.pid < y.pid;
}


//to display the created priority queue
void showpq(priority_queue < process ,vector<process> ,prioritySort> pq)
{
	while(!pq.empty())
	{
		obj=pq.top();
		cout<<" PID : "<<obj.pid<<"  Arrival Time : "<<obj.AT<<"  Burst Time : "<<obj.BT<<"  Priority : "<<obj.priority<<"\n";
		pq.pop();
	}
}


//main
int main()
{
	string pid;
	int AT;  // arrival time
	int BT; // burst time
	int WT; // waiting time
	int CH; // only for check the traversed process for calculating waiting time
	int RT; // remaining time
	int priority; // priority
	int no;
	
	int cpuState = 0; //CPU busy =1 CPU idle=0
	int QT = 2 ; //Time Quantum for process
	current.pid = "-1";
	current.priority = 1000000;
	int t=0;// time clock
	int pp=0;
	int rr=0;
	
	cout<<"\n Enter number of processes: ";
	cin>>no;
	vector<process> input;
	cout<<"\nEnter pid (in alphanumeric), arrival time, burst time, priority of "<<no<<" processes in this order only\n";
	for(int i=0;i<no;i++)
	{
		cin>>pid>>AT>>BT>>priority;
		obj.pid=pid;
		obj.AT=AT;
		obj.BT=BT;
		obj.RT=BT;
		obj.CH=0;
		obj.priority=priority;
		input.push_back(obj);
	}
	
	cout<<"\n\nYour entered Processes with proper details.\n";
	display(input);
	
	sort(input.begin(),input.end(),arrivalTimeSorting); //sort according to arrival time 
	//cout<<"\n Sorted input according to arrival time. ";
	//display(input);  //to see the sorted processes uncomment this
	
	int totalTime=0;  // calculate total time for creating gantt chart
	totalTime = totalTime + input[0].AT;
    for(int i= 0 ;i< no; i++ )
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

	string Ghantt[totalTime+1]={""}; //Ghantt Chart
	for(int i= 0; i< totalTime; i++ )
	{
		Ghantt[i]="-1";
	}
	cout<<"\ntotal exection time : "<<totalTime<<endl<<endl;  // total time needed for all process
	

	priority_queue < process ,vector<process> ,prioritySort> pq;  //priority queue
	
	/*for( int j = 0; j< no ; j++ )  // to check the queue uncomment this
	{
		pq.push(input[j]);
	}
	showpq(pq);*/
	
	queue<process> rb;  //round robin queue
	
	
	
	for (t=0;t<=totalTime;t++)
	{
		for( int i = 0; i<no ; i++ ) //Insert the process in Priority Queue whose arrival time matches with time clock
		{
			if(t == input[i].AT)
			{
				pq.push(input[i]);
			}
		}
		

		if(cpuState == 0) //If CPU is idle
		{
			if(!pq.empty())
			{
				current = pq.top();
				pq.pop();
				cpuState = 1;
				pp = 1;
				//QT = 2; 
			}
			else if(!rb.empty())
			{
				current = rb.front();
				rb.pop();
				cpuState = 1;
				rr = 1;
				QT= 2;
			}
		}
		else if(cpuState == 1) //If cpu has any procss
		{
			if(pp == 1 && (!pq.empty()))
			{
				if(pq.top().priority<current.priority ) //If new process has high priority means less priority no then current's priority no
				{
					rb.push(current); //push current process in Rb
					current = pq.top();
					pq.pop();
					//QT = QT*2; 
				}
			}
			else if(rr == 1 && (!pq.empty())) //If process is from RQ and new process come  in PQ
			{
				rb.push(current); // push into the rb queue for later turn
				current = pq.top();
				pq.pop();
				rr = 0;
				pp = 1;
				QT = 2;
			}
		}


		if(current.pid != "-1") // Process is in Execution
		{
			current.RT--;
			QT--;
			Ghantt[t] = current.pid;
			if(current.RT == 0) //If process Finish
			{
				cpuState = 0 ;
				if(pp==0 && rr==1)
					QT = 2 ;
				current.pid = "-1";
				current.priority =1000000 ;
				rr = 0;
				pp = 0;
			}
			else if(QT== 0 && pp==0 && rr==1) //If time Qunatum of a current running process Finish
			{
				rb.push(current);// push into rb queue becoz then it will excute acc to round robin 
				current.pid = "-1";
				current.priority = 1000000;
				rr = 0;
				pp = 0;
				cpuState=0;
			}
		}
	}
/*
for(int i=0;i<=totalTime;i++)
{
	cout<<Ghantt[i]<<"  ";
}
*/
	
	
	// calculations for waiting time
	for(int i=0;i<=totalTime;i++)
	{ 
		for(int j=0;j<no;j++)
		{
			if(Ghantt[i]==input[j].pid && input[j].CH==0)
			{
				input[j].CH=1;
				int ft=i+1;
				int st=i;
				//cout<<"\n PID: "<<input[j].pid<<"  "<<st<<" - "<<input[j].AT;
				int wt=st-input[j].AT;
				for(int k=i+1;k<=totalTime;k++)
				{
					if(Ghantt[k]==input[j].pid)
					{
						//cout<<" + ("<<k<<" - "<<ft<<")  ";
						wt+=(k-ft);
						ft=k+1;
					}
				}
				input[j].WT=wt;
				//cout<<" = "<<input[j].WT<<endl<<endl;
			}
		}
	}
	
	// Ghantt Chart
	cout<<"\n NOTE :-- If value of Ghantt chart comes -1 that means CPU is IDLE, no process comes yet!!";
	cout<<"\n Ghantt Chart: \n";
	cout<<"***************\n\n";
	for(int i=0;i<totalTime;i++)
	{
		cout<<Ghantt[i]<<"  |   "<<i<<"\n";
	}
	
//display of Waiting time of all the processes

	sort( input.begin(), input.end(), pidSort );  // sort to display according to pid of processes
	cout<<"\n\n";
	float sumWT=0, sumTA=0;
	for(int i=0;i<no;i++)
	{
		cout<<"\n Pid : "<<input[i].pid<<"  WT : "<<input[i].WT;
		sumWT+=input[i].WT;
		sumTA+=input[i].WT+input[i].BT;
	}
	
	cout<<"\n\n Average Waiting Time for all the processes is "<<sumWT/no;
	cout<<"\n\n Average Turn Around Time for all processes is "<<sumTA/no;
}
