"""For each value, find the leftmost earlier smaller value/index.

Question:
    For each value, find the leftmost earlier smaller value/index.

Approach:
    Maintain an ordered view of previously seen values for predecessor queries.

Complexity:
    O(N log N) time and O(N) space.

Tests:
    Run this module for its examples and ``python Google/run_all_tests.py``
    from the repository root for the complete isolated test pass.
"""

from bisect import bisect_left, insort

def find_leftmost_smaller_sortedlist(arr):
    seen = []
    result = []
    
    for num in arr:
        idx = bisect_left(seen, num)  # Locate the greatest prior value < num.
        if idx == 0:
            result.append(-1)
        else:
            result.append(seen[idx - 1])
        
        insort(seen, num)
    
    return result
arr = [2, 1, 3, 2, 1, 3]
m = max(arr)

print(find_leftmost_smaller_sortedlist(arr))  # Output: [-1, -1, 2, 1, -1, 2]
