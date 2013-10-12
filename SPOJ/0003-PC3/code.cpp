#include <iostream>

using namespace std;


int rec(int n1, int n2){
	int min = (n1 < n2 ? n1 : n2);
	if(n1%min == 0 && n2%min == 0 )
		return min;
	else{
		if (n1 < n2) {
			return rec(n1,n2 - n1);
		} else {
			return rec(n1-n2,n2);
		}
	}
}
int main ()
{
	int numberOfTests, n1, n2, min;
	
	cin >> numberOfTests;
	while (numberOfTests--) {
		cin >> n1 >> n2;
		printf("%d\n",rec(n1,n2));
	}
    return 0;
};