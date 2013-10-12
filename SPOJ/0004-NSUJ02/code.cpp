#include <iostream>
#include <math.h>
using namespace std;

struct Pair {
	double a;
	double b;
};

Pair fibo(int  n){
	Pair ret;
	ret.a =0;
	ret.b =0;
	if (n <= 0) return ret;
	
	int  i = n - 1;
	
	double  a = 1, b = 0, c = 0, d = 1;
	double  tA,tB,tC,tD;
	while ( i > 0 ) {
		//printf(">>> %.0f %.0f %.0f %.0f \n", a,b,c,d);
		if (i%2 == 1) {
			tA = d*b + c*a;
			tB = d*(b+a)+c*b;
			a = tA; 
			b = tB;
		}
		tC = c*c + d*d;
		tD = d*(2*c+d);
		i = floor(i/2);
		c = tC; 
		d = tD;			
	}
	//printf(">>> %.0f %.0f %.0f %.0f \n", a,b,c,d);	
	
	ret.a = a;
	ret.b = b;
	return ret;
}


int main ()
{
	int numberOfTests, numA, numB, n;
	string st;
	
	cin >> numberOfTests;
	while (numberOfTests--) {
		cin >> st >> n;
		if (n > 0 ) {
			numA = numB = 0;
			for(int i =0; i < st.size(); i++) {
				if (st[i] == 'a') {
					numA++;
				} else {
					numB++;
				}
			}
			Pair pA = fibo(n+1);
			Pair pB = fibo(n+2);
			printf("%.0f\n",numA*(pA.a + pA.b) + numB*(pB.a +pB.b));
		} else {
			printf("%d\n",st.size());
		}
		
	}
    return 0;
};