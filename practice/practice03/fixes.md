# Practice03 MathUtils Bug Fixes:
## sumRange(int start, int end);
* Off-by-one error in for-loop. This causes the loop to iterate one more than the provided end value. The fix was to replace the < with <= in the exit condition on the loop.

## containsNegative(const std::vector<int> &numbers):
* Off-by-one error in for-loop. The causes the for-loop to go out of bounds. The solution was to replace the loop with a range-based for-loop.
* Incorrect conditional operator when testing for number. Caused: This caused the test to return true if the number is positive, which is pretty counterproductive in this scenario. The fix was to switch > with <.

## findMax(const std::vector<int> &numbers)
* Off-by-one error in for-loop. This causes the loop to go out of bounds. The fix was to change the conditional operator from <= to <.

The rest of the tests passed fine.