/*
	Brandon Druschel
	Assignment #2: Seafood
	Due Date: 11/2/16
	
	Description:
		Seafood.cc generates a priority queue of four different "boxes" of Seafood
		(shrimp, lobster, crab, and swordfish). Each type of fish has a certain
		quantity that is allowed to fit within its own box, and the box has its
		own expiration date. Each queue is ordered by the expiration date, and
		any box that is "open" will take priority over any other box. 
		
		The queue is outputted to the user each time a box of seafood has been added.
		
		The user can choose whether to "stock" the seafood supply with some fresh
		product, or "buy" a certain amount of seafood from the supplies that are
		present. If a request to buy something can't be met, the request is put
		into its own queue until a new stock arrives that will fulfill the request.
		
	Implementation:
		'canonicalize' is a function that takes in a date string and rearranges it in
		such a way that makes comparing between two different dates much easier. 
		This particular function was borrowed from here:
		http://cs.oswego.edu/~odendahl/coursework/csc344/201609/assignments/02/regex-test.cc
		
		'pShrimp'/'pLobster'/'pCrab'/'pSwordfish' takes in a priority queue of the
		respective seafood type and prints the contents of the priority queue, including
		all of the essential variables that represent each seafood as well as whether
		the box is "open" or not.
		
	Input: [event] [date] [seafood type] [amount]
	Output: See description.
*/

#include <iostream>
#include <string>
#include <queue>
#include <cassert>
#include <regex>
using namespace std;

string canonicalize(string date_in) {
   regex exp("(..)/(..)/(....)");
   smatch sm;
   if (regex_match (date_in, sm, exp) && sm.size() == 4) {
      string date_out = sm[3].str() + "/" + sm[1].str() + "/" + sm[2].str();
      return date_out;
   } else {
      return date_in;
   }
}

class Seafood {
	protected:
		string ExpirationDate;
		mutable bool isOpen = false;
	public:
		bool operator<(const Seafood& s) const { 
			if(this->getOpen() && s.getOpen()){ //is the seafood in-queue open?
				return true;
			}
			else if(this->getOpen() && !s.getOpen()){ 
				return false;
			}
			else if(this->getOpen() == s.getOpen()){ //if both boxes are open or closed, sort by date
				return canonicalize(ExpirationDate) > canonicalize(s.ExpirationDate);
			}
		}
		Seafood(string);
		string check() const { //used when outputting a queue (i.e. pShrimp)
			if(!isOpen) {
				return "c";
			}
			else {
				return "o";
			}
		}
		void openBox() const{
			if(!isOpen){
				isOpen = true;
			}
		}
		bool getOpen() const {
			return isOpen;
		}
		string getDate() const {
			return ExpirationDate;
		}
};
Seafood::Seafood (string d) {
	ExpirationDate = d;
}

class Shrimp: public Seafood {
	private:
		mutable int quantity = 50;
	public:
		Shrimp(string d) : Seafood(d) {}
        int getQ() const {
			return quantity;
		}
		void setQ(int i) const {
			quantity = quantity + i;
		}
		void getInfo(){
			cout << "Seafood[" << "50" << "(" << quantity << ")" << ExpirationDate << "]" << this->check();
		}
};

class Lobster: public Seafood {
	private:
		mutable int quantity = 4;
	public:
		Lobster(string d) : Seafood(d) {}
		int getQ() const {
			return quantity;
		}
		void setQ(int i) const {
		quantity = quantity + i;
		}
		void getInfo(){
			cout << "Seafood[" << "4" << "(" << quantity << ")" << ExpirationDate << "]" << this->check();
		}
};

class Crab: public Seafood {
	private:
		mutable int quantity = 6;
	public:
		Crab(string d) : Seafood(d) {}
		int getQ() const {
			return quantity;
		}
		void setQ(int i) const {
		quantity = quantity + i;
		}
		void getInfo(){
			cout << "Seafood[" << "6" << "(" << quantity << ")" << ExpirationDate << "]" << this->check();
		}
};

class Swordfish: public Seafood {
	private:
		mutable int quantity = 8;
	public:
		Swordfish(string d) : Seafood(d) {}
		int getQ() const {
			return quantity;
		}
		void setQ(int i) const {
		quantity = quantity + i;
		}
		void getInfo(){
			cout << "Seafood[" << "8" << "(" << quantity << ")" << ExpirationDate << "]" << this->check();
		}
};

class Request {
	private:
		string type;
		int quantity;
		string ExpirationDate;
	public:
		Request(string,int,string);
		bool operator<(const Request& r) const { 
			return true; //no actual ordering for customer queues
		}
		string getType() const{
			return type;
		}
		int getQ() const{
			return quantity;
		}
};
Request::Request (string t, int q, string d) {
	type = t;
	quantity = q;
	ExpirationDate = d;
}

// Priority Queue for each type of Seafood
priority_queue <Shrimp> shrimps;
priority_queue <Lobster> lobsters;
priority_queue <Crab> crabs;
priority_queue <Swordfish> swordfishes;

// Priority Queue for customer requests
priority_queue <Request> requests;

// Print contents of each queue of seafood
void pShrimp(priority_queue<Shrimp> pq) {
   while (!pq.empty()) {
      Shrimp t = pq.top();
      pq.pop();
      t.getInfo(); cout << (!pq.empty() ? ", " : "");
   }
   cout << endl;
}
void pLobster(priority_queue<Lobster> pq) {
   while (!pq.empty()) {
      Lobster t = pq.top();
      pq.pop();
      t.getInfo(); cout << (!pq.empty() ? ", " : "");
   }
   cout << endl;
}
void pCrab(priority_queue<Crab> pq) {
   while (!pq.empty()) {
      Crab t = pq.top();
      pq.pop();
      t.getInfo(); cout << (!pq.empty() ? ", " : "");
   }
   cout << endl;
}
void pSwordfish(priority_queue<Swordfish> pq) {
   while (!pq.empty()) {
      Swordfish t = pq.top();
      pq.pop();
      t.getInfo(); cout << (!pq.empty() ? ", " : "");
   }
   cout << endl;
}


int main (int argc, char *argv[]) {
	int temp; //temporary int set for amount of fish between stocks
	
	string event; //'stock' or 'buy'
	string date; //expiration date
	string type; //shrimp, lobster, crab or swordfish
	int amount; //amount of boxes to stock OR fish to buy
	
	while (cin >> event >> date >> type >> amount) {
		cout << "Event: " << event << " || Date: " << date << " || Type: " << type << " || Amount: " << amount << endl;
		if (event == "stock") {
			cout << "Adding seafood to stockpile" << endl;
			if (type == "shrimp") {
				for(int i = 0; i < amount; i++){
					shrimps.push(Shrimp(date));
				}
				if(!requests.empty() && requests.top().getType() == "shrimp"){
					shrimps.top().setQ(requests.top().getQ()*-1);
					cout << "Selling " << requests.top().getQ() << " units to waiting customer" << endl;
					requests.pop();
				}
				cout << "Shrimp: "; pShrimp(shrimps);
			}
			else if (type == "lobster") {
				for(int i = 0; i < amount; i++){
					lobsters.push(Lobster(date));
				}
				if(!requests.empty() && requests.top().getType() == "lobster"){
					lobsters.top().setQ(requests.top().getQ()*-1);
					cout << "Selling " << requests.top().getQ() << " units to waiting customer" << endl;
					requests.pop();
				}				
				cout << "Lobster: "; pLobster(lobsters);
			}
			else if (type == "crab") {
				for(int i = 0; i < amount; i++){
					crabs.push(Crab(date));
				}
				if(!requests.empty() && requests.top().getType() == "crab"){
					crabs.top().setQ(requests.top().getQ()*-1);
					cout << "Selling " << requests.top().getQ() << " units to waiting customer" << endl;
					requests.pop();
				}	
				cout << "Crab: "; pCrab(crabs);
			}
			else if (type == "swordfish") {
				for(int i = 0; i < amount; i++){
					swordfishes.push(Swordfish(date));
				}
				if(!requests.empty() && requests.top().getType() == "swordfish"){
					swordfishes.top().setQ(requests.top().getQ()*-1);
					cout << "Selling " << requests.top().getQ() << " units to waiting customer" << endl;
					requests.pop();
				}					
				cout << "Swordfish: "; pSwordfish(swordfishes);
			}
			else{
				cout << "Invalid fish: " << type << endl;
			}
		 } 
		 else if (event == "buy") {
			cout << "Selling some product from stockpile" << endl;
			if (type == "shrimp") {
				if(!shrimps.empty()){
					shrimps.top().setQ(amount*(-1));
					cout << "Using some resources from stockpile" << endl;
					if(shrimps.top().getQ() == 0){
						shrimps.pop();
						cout << "DEBUG: matched needed amount exactly." << endl;
					}
					else if(shrimps.top().getQ() < 0){
							temp = shrimps.top().getQ();
							shrimps.pop();
							cout << "DEBUG: Box has been emptied. Removing from queue."<< endl;
						if(!shrimps.empty()) {
							shrimps.top().setQ(temp);
						}
						else {
							cout << "DEBUG: Out of boxes. still need " << temp*(-1) << " more units." << endl;
							requests.push(Request(type, temp*(-1), date));
							cout << "Putting customer on queue for " << temp*(-1) << " units" << endl;
						}
					}
					else {
						cout << "DEBUG: have " << shrimps.top().getQ() << " units left" << endl;
					}
					if(shrimps.top().getQ() < 50){
						shrimps.top().openBox();
					}
					cout << "Shrimp: "; pShrimp(shrimps);
				}
				else {
					cout << "DEBUG: No boxes! Customer needs " << amount << " units." << endl;
					requests.push(Request(type, amount, date));
					cout << "Putting customer on queue for " << amount << " units" << endl;
				}
			}
			else if (type == "lobster") {
				if(!lobsters.empty()){
					lobsters.top().setQ(amount*(-1));
					cout << "Using some resources from stockpile" << endl;
					if(lobsters.top().getQ() == 0){
						lobsters.pop();
						cout << "DEBUG: matched needed amount exactly." << endl;
					}
					else if(lobsters.top().getQ() < 0){
							temp = lobsters.top().getQ();
							lobsters.pop();
							cout << "DEBUG: Box has been emptied. Removing from queue."<< endl;
						if(!lobsters.empty()) {
							lobsters.top().setQ(temp);
						}
						else {
							cout << "DEBUG: Out of boxes. still need " << temp*(-1) << " more units." << endl;
							requests.push(Request(type, temp*(-1), date));
							cout << "Putting customer on queue for " << temp*(-1) << " units" << endl;
						}
					}
					else {
						cout << "DEBUG: have " << lobsters.top().getQ() << " units left" << endl;
					}
					if(lobsters.top().getQ() < 4){
						lobsters.top().openBox();
					}
					cout << "Lobster: "; pLobster(lobsters);
				}
				else {
					cout << "DEBUG: No boxes! Customer needs " << amount << " units." << endl;
					requests.push(Request(type, amount, date));
					cout << "Putting customer on queue for " << amount << " units" << endl;
				}
			}
			else if (type == "crab") {
				if(!crabs.empty()){
					crabs.top().setQ(amount*(-1));
					cout << "Using some resources from stockpile" << endl;
					if(crabs.top().getQ() == 0){
						crabs.pop();
						cout << "DEBUG: matched needed amount exactly." << endl;
					}
					else if(crabs.top().getQ() < 0){
							temp = crabs.top().getQ();
							crabs.pop();
							cout << "DEBUG: Box has been emptied. Removing from queue."<< endl;
						if(!crabs.empty()) {
							crabs.top().setQ(temp);
						}
						else {
							cout << "DEBUG: Out of boxes. still need " << temp*(-1) << " more units." << endl;
							requests.push(Request(type, temp*(-1), date));
							cout << "Putting customer on queue for " << temp*(-1) << " units" << endl;
						}
					}
					else {
						cout << "DEBUG: have " << crabs.top().getQ() << " units left" << endl;
					}
					if(crabs.top().getQ() < 6){
						crabs.top().openBox();
					}
					cout << "Crab: "; pCrab(crabs);
				}
				else {
					cout << "DEBUG: No boxes! Customer needs " << amount << " units." << endl;
					requests.push(Request(type, amount, date));
					cout << "Putting customer on queue for " << amount << " units" << endl;
				}
			}
			else if (type == "swordfish") {
				if(!swordfishes.empty()){
					swordfishes.top().setQ(amount*(-1));
					cout << "Using some resources from stockpile" << endl;
					if(swordfishes.top().getQ() == 0){
						swordfishes.pop();
						cout << "DEBUG: matched needed amount exactly." << endl;
					}
					else if(swordfishes.top().getQ() < 0){
							temp = swordfishes.top().getQ();
							swordfishes.pop();
							cout << "DEBUG: Box has been emptied. Removing from queue."<< endl;
						if(!swordfishes.empty()) {
							swordfishes.top().setQ(temp);
						}
						else {
							cout << "DEBUG: Out of boxes. still need " << temp*(-1) << " more units." << endl;
							requests.push(Request(type, temp*(-1), date));
							cout << "Putting customer on queue for " << temp*(-1) << " units" << endl;
						}
					}
					else {
						cout << "DEBUG: have " << swordfishes.top().getQ() << " units left" << endl;
					}
					if(swordfishes.top().getQ() < 8){
						swordfishes.top().openBox();
					}
					cout << "Swordfish: "; pSwordfish(swordfishes);
				}
				else {
					cout << "DEBUG: No boxes! Customer needs " << amount << " units." << endl;
					requests.push(Request(type, amount, date));
					cout << "Putting customer on queue for " << amount << " units" << endl;
				}
			}
			else{
				cout << "Invalid fish: " << type << endl;
			}
		}
		else {
			cout << "Invalid event: " << event << endl;
		}
	}
}
