#include <systemc>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <deque>

using namespace sc_core;
using namespace std;

SC_MODULE(Fibonacci)
{

public:
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

	sc_start(20, SC_SEC);

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
	      t=(rand() % (limitGore - limitDole + 1)) + limitDole;
		wait(t, SC_NS);
		num1=num2;
		num2=next;
		next=num1+num2;
		ints.push_back(next);
		
		i++;
	   }
		//ints.push_back();
	}
}

void Fibonacci::monitor()
{
	while(true)
	{
		wait(1000, SC_MS);
		if(ints.size() != 0)
		{
			long unsigned int num = ints.size();
			ints.resize(0);
			cout << "Broj generisanih: " << num <<
				" at time " << sc_time_stamp() <<
				".\n";
				
		}
	}
}
