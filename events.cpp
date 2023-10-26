#include <systemc>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <deque>
 
 using namespace std;
 using namespace sc_core;
 
 SC_MODULE(Fibonacci)
{

public:
sc_event ev;
sc_event ev1;
	SC_HAS_PROCESS(Fibonacci);

	Fibonacci(sc_module_name name, int limitDole=10, int limitGore=100);

	void generateArray();
	void monitor();
protected:
	deque<int> ints;
	int limitDole,limitGore;
};

int sc_main(int argc, char* argv[])
{
	Fibonacci uut("UUT");

	sc_start(10, SC_US);

	cout << "Simulation finished at " << sc_time_stamp() << endl;
	return 0;
}
Fibonacci::Fibonacci(sc_module_name name,
				   int limitDole, int limitGore) :
	limitDole(limitGore), limitGore(limitGore)
{
	SC_THREAD(generateArray);
 	SC_THREAD(monitor);
	srand(time(NULL));
}
void Fibonacci::generateArray()
{
   int t; int num1=0, num2=1;
   int next=1, n=64;
	while(true)
	{
	   int i=0;
	    while(i < n){
	      t=(rand() % (limitGore+1)) + limitDole;
		wait(t, SC_NS);
		ev.notify(5,SC_NS);
		cout<<"vreme: "<<sc_time_stamp()<<endl<<endl;
		num1=num2;
		num2=next;
		next=num1+num2;
		ints.push_back(next);
		
		i++;
	   }
	   //sc_stop();
		//ints.push_back();
	}
}

void Fibonacci::monitor()
{
	while(true)
	{
		wait(ev);
		if(ints.size() != 0)
		{
			long unsigned int num = ints.front();
			ints.pop_front();
			cout << "generisan: " << num <<
				" at time " << sc_time_stamp() <<
				".\n";
		}
	}
}
