#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

struct Pizza {
	int price;
	string name;
};

int main ()
{
	int numberOfTests, numberOfPizzas, numberOfToppingsGirl;
	int cheapestPizza = 0;
	int numToppings;
	string currTopping;
	vector<string> toppingsListGirl;
	
	vector<Pizza> pizzasList;
	
    cin >> numberOfTests;
	while (numberOfTests--)
    {
		cheapestPizza = 0;
		cin >> numberOfPizzas >> numberOfToppingsGirl;
		
		//toppings girl
		toppingsListGirl.resize(numberOfToppingsGirl);
		for(int i = 0; i < numberOfToppingsGirl; i++){
			cin >> toppingsListGirl[i];
		}
		
		//sort toppings girl
		sort (toppingsListGirl.begin(), toppingsListGirl.end());
		
		pizzasList.resize(numberOfPizzas);
		for(int i = 0; i < numberOfPizzas; i++){
			//read pizza
			cin >> numToppings >> pizzasList[i].price >> pizzasList[i].name;
			
			// read toppings
			int foundToppings = 0;
			for(int j = 0; j < numToppings; j++){
				cin >> currTopping;
				if (binary_search (toppingsListGirl.begin(), toppingsListGirl.end(), currTopping)) {
					//found
					foundToppings++;
				}
			}
			
			pizzasList[i].price += 350*(numberOfToppingsGirl - foundToppings);
			
			// cheapest pizza?
			if (pizzasList[i].price < pizzasList[cheapestPizza].price) {
				cheapestPizza = i;
			}
			
		}
		
		cout << pizzasList[cheapestPizza].name << " " << pizzasList[cheapestPizza].price << endl;
    }
    return 0;
}