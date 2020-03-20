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

	int Ghant[totalTime]={0}; //Ghant Chart
	for(int i= 0; i< totalTime; i++ )
	{
		Ghant[i]=-1;
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
	
}
