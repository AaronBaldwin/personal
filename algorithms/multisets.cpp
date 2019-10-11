#include <cstdlib>
#include <vector>
#include <iostream>
#include <set>

using namespace std;

int main(int argc, char** argv) {

  std::multiset<int> s1;
  std::multiset<int, greater<int>> s2; // Sort in descending order

  s1.insert(5);
  s1.insert(2);
  s1.insert(4);
  s1.insert(4);

  s2.insert(15);
  s2.insert(14);
  s2.insert(17);
  s2.insert(10);
  s2.insert(15);

  // lower_bound finds the lowest index that contains that value
  // upper_bound, coincidentally finds the highest index with that value
  for(auto i = s2.lower_bound(15); i != s2.end(); i++) {
      cout << *i <<  ", " << endl;
  }

  // lower_bound finds the next index above 3 in the case where 3 is not present
  // it finds 4 in this case.
  int val = *s1.lower_bound(3);
  cout << " the found lower val is " << val << endl;

  val = *s1.upper_bound(3);
  cout << " the found upper val is " << val << endl;

  return 0;
}

