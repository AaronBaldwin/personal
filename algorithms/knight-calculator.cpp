#include <cstdlib>
#include <vector>
#include <iostream>

using namespace std;

int calc(int m, int n) {
  if(m < n) {
      int temp = n;
      n = m;
      m = temp;
  }

  if(m == 0 && n == 0) {
      return 0;
  }
  else if(m == 1 && n == 0) {
      return 3;
  }
  else if(m == 1 && n == 1) {
      return 2;
  }
  else if(m == 2 && n == 0) {
      return 2;
  }
  else if(m == 3 && n == 1) {
      return 2;
  }
  else if(n == 0) {
      return calc(m - 2, n + 1) + 1;
  }

  return calc(m-2, n-1) + 1;
}

int main(int argc, char** argv) {
  int m = atoi(argv[1]);
  int n = atoi(argv[2]);


  

  int result = calc(m, n);
  cout << "found result " << result << endl;

  return 0;
}

