#include<bits/stdc++.h>
using namespace std;

//structure for all the processes
struct ProcessInfo{
	string pid;
	int AT;
	int BT;
	int WT;
	int FT;
	int RT;
	int ST;
	int priority;
};

//objects for structures
struct ProcessInfo current;
typedef struct ProcessInfo process;
struct ProcessInfo obj;


///Methods:-->

//display the queues
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
	int AT;
	int BT;
	int WT;
	int FT;
	int RT;
	int ST;
	int priority;
	int no;
	
	int cpuState = 0; //CPU busy =1 CPU idle=0
	int QT = 2 ; //Time Quantum for process
	current.pid = "-1";
	current.priority = 1000000;
	int t=0;// time clock
	int pp=0;
	int rr=0;
	
	cout<<"\n Enter no of process: ";
	cin>>no;
	vector<process> input;
	cout<<"\n Enter pid( in alphanumeric), arrival time, burst time, priority of "<<no<<" processes \n";
	for(int i=0;i<no;i++)
	{
		cin>>pid>>AT>>BT>>priority;
		obj.pid=pid;
		obj.AT=AT;
		obj.BT=BT;
		obj.RT=BT;
		obj.priority=priority;
		input.push_back(obj);
	}
	display(input);
	//sort according to arrival time 
	sort(input.begin(),input.end(),arrivalTimeSorting);
	cout<<"\n sorted input according to arrival time. ";
	display(input);
	
	// calculate total time for creating gantt chart
	int totalTime=0;
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
    		totalTime = totalTime + diff + BT;

    	}
    }

	string Ghantt[totalTime]={""}; //Ghantt Chart
	for(int i= 0; i< totalTime; i++ )
	{
		Ghantt[i]=-1;
	}
	cout<<"\ntotal exection time : "<<totalTime<<endl;
	
	//priority queue
	priority_queue < process ,vector<process> ,prioritySort> pq;
	/*for( int j = 0; j< no ; j++ )
	{
		pq.push(input[j]);
	}
	//display queue
	showpq(pq);*/
	
	//round robin
	queue<process> rb;
	
	
	
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
				QT = 2; 
			}
			else if(!rb.empty())
			{
				current = rb.front();
				rb.pop();
				cpuState = 1;
				rr = 1;
				QT = 2;
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
					QT = 2; 
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
			cout<<"Ghatt process: "<<Ghantt[t]<<"\t";
			if(current.RT == 0) //If process Finish
			{
				cpuState = 0 ;
				QT = 2 ;
				current.pid = -1;
				current.priority =1000000 ;
				rr = 0;
				pp = 0;
			}
			else if(QT== 0 ) //If time Qunatum of a current running process Finish
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


	//sort( input.begin(), input.end(), idsort );
/*	
	for(int i=0;i<n;i++)
	{
		for(int k=total_exection_time;k>=0;k--)
		{
			if(Ghant[k]==i+1)
			{
				input[i].F_time=k+1;
				break;

			}
		}
	}
	
*/	
	
	
}
