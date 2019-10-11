#include <cstdlib>
#include <iostream>
#include <vector>

/*
  Given a set of coin denominations and an amount of change
  that must be given to someone, calculate how many of each
  coin should be given such that the number of coins returned
  in total is the minimum.  For example, in USA currency and
  a total to return of 47 cents, one quarter, 2 dimes, and 2
  pennies should be returned (5 total coins)
*/

// A more interesting problem set arises with coin denominations of
// 1, 3, 4 and a target result of 6 cent.  The correct result is
// 2 3-cent pieces rather than 2-1s and 1-4.  The difference is three coins
// in the result rather than two coins.  This sort of case precludes a strictly
// greedy solution from being employable.

// My first idea is, for instance, if we wish to find the result for 47cents
// Start with 1 cent and calculate what coins are optimal for returning only one cent
// Then iterate up to 47, keeping track of the optimal solution for each target amount

// This is also essentially an algebraic equation in x + 3y + 4z = 6
// We can bound each coin's range by (target / valueOfCoin) rounded down.  So in thie
// case of a [1,3,4] coinset, and trying to make 6 cents in change,
// there must be between 0-6 pennies, 0-2 3-cent-pieces, and 0-1 4-cent-pieces.
// To calculate all solutions, we could begin at the highest demonination
// and loop over its possible values.  This would be roughly O(t^n) with
// n being the number of coin denominations and t being the target value of coins.

// More interestingly still are cases where there may not be
// valid solutions.  If there is no one-cent piece, then there
// could never be a solution for simply returning one.
// In the [2, 5, 6, 7] set, for instance, we can see that
// 1, 3, 9 have no answers although everything greater will.
// In this problem, 6 and 7 are "redundant" in that they can
// be composed of smaller coin denominations.  Any problem set
// with the penny in it means that all other coin denominations
// are "redundant" except obviously we'd rather receive the
// most minimal result

// If we are given a coin-set and a target value, we can start
// by giving one coin back, thus reducing the problem to a smaller
// set.  For instance, if we need to return 6 cents and we have [1,3,4]
// demoninations then the possible solutions would start with:
// 1 penny and 5 to return, 1 3-cent piece and 3 to return, and 1 4-cent
// piece and 2 to return.  We may already have calculated 2,3, and 5
// solutions so in theory, whichever of those is the best would be the same
// best solution for this one but adding one more coin onto it.

// Sample solution iteration for 1-cent, 3-cent, 4-cent coins
// The best solution for each value is designated with a star
// and the total number of coins (or cost) of the solution
// 1: [1, 0, 0]
// 2: [2, 0, 0]
// 3: [3, 0, 0], [0, 1, 0]*1
// 4: [4, 0, 0], [1, 1, 0], [0, 0, 1]*1
// 5: [5, 0, 0], [2, 1, 0], [1, 0, 1]*2
// 6: [6, 0, 0], [3, 1, 0], [2, 0, 1], [0, 2, 0]*2

// When looking for the best solution for a target number,
// we first look to see if a coin exists for that denomination.
// If that coin exists, then the best solution is simply one of
// that coin.  This is a basecase.  Otherwise, the algorithm
// proceeds as described, considering returning one coin
// and reducing the problem to a smaller denomination

// For instance, if we wished to find the best solution for 7 in the [1,3,4]
// problem set, then we first check to see if there is a 7-piece.  There is not.
// Then we check against 6, 4, and 3 and we note that 3 and 4 both have
// a solution with only one coin.  6 has a solution with two coins.
// This means that the solution (3) + 4-piece and (4) + 3-piece are both
// equally good solutions which return two coins.  In fact, the solutions are
// precisely the same since we don't care about order.  The solution for 7 is
// to return a 3-piece and a 4-piece. 


// Note- ended up using solution that iterates from 1 to the target value
// and calculates all possible values.  This might run slower than the recursive
// solution but should be same approximate order of complexity.

class Solution {
  public:
    Solution(int* amounts, int length) {
      coinAmounts = amounts;
      coinsTotal = 0;
      for(int i = 0; i < length; i++) {
        coinsTotal += amounts[i];
      }
    }
    Solution(Solution* previous, int coinIndexToIncrement, int length) {
      coinAmounts = new int[length];
      memcpy(coinAmounts, previous->coinAmounts, sizeof(int) * length);
      coinAmounts[coinIndexToIncrement]++;
      coinsTotal = previous->coinsTotal + 1;
    }
    int* coinAmounts;
    int coinsTotal;
};

using namespace std;
int main(int argc, char** argv) {

  if(argc < 3) { 
    cout << "Must provide at least two arguments: target and denomination..." << endl;
    return 1;
  }

  int distinctCoinTypes = argc - 2;
  int coinDenominations[distinctCoinTypes];
  int target = atoi(argv[1]);
  vector<Solution*> solutions;
  solutions.resize(target + 1);

  // Create an array with all the coin denominations in it
  for(int i = 2; i < argc; i++) {
    int converted = atoi(argv[i]);
    coinDenominations[i - 2] = converted;
  }
  sort(coinDenominations, coinDenominations + distinctCoinTypes);

  // Calculate every optimal solution starting with (1)
  for(int targetCoinValue = 1; targetCoinValue <= target; targetCoinValue++) {
    // Is there a precise coin for this value?
    int* exactCoin = find(coinDenominations, coinDenominations + distinctCoinTypes, targetCoinValue);
    bool foundExactCoin = (bool)(exactCoin != coinDenominations + distinctCoinTypes);

    // If there is a precise coin for this target sum,
    // then the correct solution is exactly one of that coin
    if(foundExactCoin == true) {
      int index = exactCoin - coinDenominations;

      // Initialize the solution to an array of [0]s
      int* coinAmounts = new int[distinctCoinTypes];
      for(int i = 0; i < distinctCoinTypes; i++) { coinAmounts[i] = 0; }
      coinAmounts[index] = 1;
      Solution* oneCoinSolution = new Solution(coinAmounts, distinctCoinTypes);

      solutions[targetCoinValue] = oneCoinSolution;
      continue;
    }

    // Otherwise need to base this solution on a previous one
    Solution* bestPreviousSolution = NULL;
    int coinIndexToIncrement = -1;

    for(int coinToAddToSolution = 0; coinToAddToSolution < distinctCoinTypes; coinToAddToSolution++) {
      int newTarget = targetCoinValue - coinDenominations[coinToAddToSolution];
      if(newTarget < 0) { break; }
      Solution* oldSolution = solutions[newTarget];
      if(oldSolution == NULL) { continue; }

      if(bestPreviousSolution == NULL ||
        oldSolution->coinsTotal < bestPreviousSolution->coinsTotal) {
        bestPreviousSolution = oldSolution;
        coinIndexToIncrement = coinToAddToSolution;
      }
    }

    // If there is no direct match for this target value and
    // there is no smaller solution which can be added to
    // which would make this solution, then it is impossible
    if(bestPreviousSolution == NULL) {
      solutions[targetCoinValue] = NULL;
      continue;
    }

    // This new solution is the same coin distribution as a previously
    // calculated solution but with one coin count incremented
    Solution* newSolution = new Solution(bestPreviousSolution, coinIndexToIncrement, distinctCoinTypes);
    solutions[targetCoinValue] = newSolution;
  }

  Solution* calculatedSolution = solutions[target];
  // If there is no possible solution log that and return 1
  if(calculatedSolution == NULL) {
    cout << "There is no solution for adding up to " << target << endl;
    return 1;
  }

  // Otherwise print an array of values of each coin to distribute,
  // sorted from smallest to largest coin
  cout << "Found optimal solution for " << target << " [";
  int* coinAmounts = calculatedSolution->coinAmounts;
  for(int i = 0; i < distinctCoinTypes; i++) {
    cout << coinAmounts[i];
    if(i + 1 < distinctCoinTypes) {
      cout << ", ";
    }
  }
  cout << "]" << endl;
  cout << "This solution returns " << calculatedSolution->coinsTotal << " coins" << endl;
  return 0;
}
