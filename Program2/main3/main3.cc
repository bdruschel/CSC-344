/*
  file: main.cc
  This program uses a priority queue of "bottles"
  and simulates their arrival and removal from the queue.
  arrival - bottle of stated capacity is added to the queue,
            "sifting up" to its prioritized spot.
  service - that much beverage is removed from one or more
            bottles at the head of the queue.
            If the last bottle used to service the request is
            not fully drained it is put back into the queue,
            "sifting down" to its prioritized spot.
  notes: the terms sifting up/down refer to the classical implementation
         of a priority queue as a tree-based heap; this may not
         be the case in this actual implementation.
  Input: data formatted as
      event-1 int-1
      event-2 int-2
         :    :
      event-n int-n
  where event-i is arrive/serve
  and int-i is a positive integer

  Output: events as they happen w/ commentary on how they
          are handled and current state of the queue
*/
#include <iostream>
#include <string>
#include <queue>
#include <cassert>
using namespace std;

class Bottle {
   friend ostream& operator<<(ostream& o, const Bottle& b)
      { return o << "Bottle[" << b.cap << "]"; }
   friend bool operator<(const int i, const Bottle& b)
      { return i < b.cap; }
   friend bool operator==(const int i, const Bottle& b)
      { return i == b.cap; }
   friend int operator+(const int i, const Bottle& b)
      { return i + b.cap; }
   public:
      bool operator<(const Bottle& b) const { return cap < b.cap; }
      Bottle(int i) : cap(i) {}
   private:
      int cap;
};

priority_queue <Bottle> bottles;

void print (priority_queue<Bottle> pq) {
   while (!pq.empty()) {
      Bottle largest = pq.top();
      pq.pop();
      cout << largest << (!pq.empty() ? ", " : "");
   }
   cout << endl;
}

int main (int argc, char *argv[]) {
   string event;
   int amount;
   while (cin >> event >> amount) {
      cout << "Queue: "; print(bottles);
      cout << "Event: " << event << " w/ value " << amount << endl;
      if (event == "arrive") {
         cout << "Adding bottle to stockpile" << endl;
         bottles.push(Bottle(amount));
      } else if (event == "serve") {
         cout << "Using some resources from stockpile" << endl;

         int vol = 0;
         while ( vol < amount ) {
            if (!bottles.empty()) {
               Bottle top = bottles.top();
               bottles.pop();
               if (vol + top < amount) {
                  vol = vol + top;
               } else if (vol + top == amount) {
                  vol = vol + top;
                  break;
               } else {
                  int remains = (vol + top) - amount;
                  vol = amount;
                  bottles.push(Bottle(remains));
                  break;
               }
            } else {
               assert(bottles.empty());
               cout << "Bottle suppy exhausted, " <<
                       "can't meet remaining amount " <<
                       (amount - vol) << endl;
               break;
            }
         }

      } else {
         cout << "Ignoring event " << event <<  endl;
      }
   }

   while (!bottles.empty()) {
     Bottle largest = bottles.top();
     bottles.pop();
     cout << largest << endl;
   }
}

/*

   Data file:

arrive 10
arrive  5
arrive  7
serve   9
serve   8
arrive  4
arrive  3
serve  11
arrive  7
serve   9
arrive  2
serve   8
serve  10

*/
