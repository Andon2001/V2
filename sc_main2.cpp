#include <systemc>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <deque>

using namespace sc_core;
using namespace std;

SC_MODULE(loto)
{
public:
	SC_HAS_PROCESS(loto);

	loto(sc_module_name name);

	void lotoNumber();
	void firstPlayer();
	void secondPlayer();
	void thirdPlayer();
	void compare();
protected:
	deque<int> ints;
};

int sc_main(int argc, char* argv[])
{
	loto uut("loto");

	sc_start(5, SC_SEC);

	cout << "Simulation finished at " << sc_time_stamp() << endl;
	return 0;
}
loto::loto(sc_module_name name)
	//limitDole(limitGore), limitGore(limitGore)
{
	SC_THREAD(lotoNumber);
 	/*SC_THREAD(firstPlayer);
 	SC_THREAD(secondPlayer);
 	SC_THREAD(thirdPlayer);*/
 	SC_THREAD(compare);
	srand(time(NULL));
}
void loto::lotoNumber()
{
   int num, n=7;
	while(true)
	{
	   wait(142857,SC_US);
	   
	   num = (rand() % 33) + 7;
	   ints.push_front(num);
	}
}

void loto::compare()
{
     while(true)
     {
       wait(1000, SC_MS);
       
       for(int i=0;i<8;i++){
       int num=ints.back();
       cout<<"kombinacija: "<< num;
       }
       cout<<endl;
	ints.resize(0);
		
     }
}
