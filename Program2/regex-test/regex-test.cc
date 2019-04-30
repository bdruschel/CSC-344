/**
 *  Compile with -std=c++11 option with gnu compiler
 *     g++ -std=c++11 -o test regex-test.cc
 *
 */
#include <iostream>
#include <string>
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

int main (int argc, char *argv[]) {
   string s1, s2;
   cout << "Enter string 1 > ";
   cin >> s1;
   cout << "Enter string 2 > ";
   cin >> s2;
   cout << "DEBUG: String 1 = " << canonicalize(s1) << endl;
   cout << "DEBUG: String 2 = " << canonicalize(s2) << endl;
   if (canonicalize(s1) < canonicalize(s2)) {
      cout << s1 << " is less than " << s2 << endl;
   } else {
      cout << s2 << " is less than " << s1 << endl;
   }
}

