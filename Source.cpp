#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<queue>
using namespace std;
int time_slice, p;
struct process {
	int processNum;
	int arrival_time;
	int waiting_time;
	int numExecution;
	int remaining_time;
	int total_time;
	int process_length;
	process(int a, int b, int c){
		arrival_time = a;
		waiting_time = 0;
		numExecution = 0;
		remaining_time = b;
		processNum = c;
		total_time = 0;
		process_length = b;
	}
	void computeW(int t){
		int total = t - arrival_time;
		total -= (time_slice * numExecution);
		waiting_time += total;
	}
	void print()
	{
		printf("Process %d analysis:\n", processNum);
		printf("the process arrived at %d time\n", arrival_time);
		printf("The process total time in the system was %d\n", total_time);
		printf("The process waiting time in the system was %d\n", waiting_time);
		printf("The process was executed %d times\n", numExecution);
		printf("The process turnaround time is %d\n\n", total_time / process_length);
		
	}
};
queue<process> processes;
vector<process> input;
int main(){
	printf("Enter the requested time slice:\n");
	scanf("%d", &time_slice);
	printf("Enter the requested number of processes:\n");
	scanf("%d", &p);
	for (int i = 0; i < p; ++i){
		int ptime;
		printf("enter the total time for the process to run until completion:\n");
		scanf("%d", &ptime);
		process pr(i, ptime, i + 1);
		processes.push(pr);
		input.push_back(pr);
	}
	int time = 0;
	while (!processes.empty()){
		process proc = processes.front();
		processes.pop();
		proc.computeW(time);
		proc.numExecution++;
		if (proc.remaining_time > time_slice){
			time += time_slice;
			proc.remaining_time -= time_slice;
			processes.push(proc);
		}
		else if (proc.remaining_time == time_slice){
			time += time_slice;
			proc.remaining_time -= time_slice;
			proc.total_time = time;
		}
		else {
			time += proc.remaining_time;
			proc.remaining_time = 0;
			proc.total_time = time;
		}
		input[proc.processNum-1] = proc;
	}
	for (int i = 0; i < input.size(); ++i)
	{
		input[i].print();
	}
	return 0;
}