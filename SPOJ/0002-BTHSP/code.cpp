#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <list>
#include <utility> 


 

using namespace std;


int main ()
{
	int velocity, time;
	while (true) {
		cin >> velocity >>  time;
		printf("%dn", velocity*time);
	}
    return 0;
};