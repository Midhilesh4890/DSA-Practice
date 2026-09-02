"""Remove K digits/elements to form the maximum remaining subsequence.

Question:
    Remove K digits/elements to form the maximum remaining subsequence.

Approach:
    A monotonic stack discards smaller earlier elements while removals remain.

Complexity:
    O(N) time and O(N) space.

Tests:
    Run this module for its examples and ``python Google/run_all_tests.py``
    from the repository root for the complete isolated test pass.
"""

# https://leetcode.com/problems/remove-k-digits/description/
# but google asked for n - k

def max_subsequence_integer(arr, k):
    stack = []
    n = len(arr)
    to_remove = n - k  # Elements that we can remove to maintain size K
    
    for num in arr:
        while stack and to_remove > 0 and stack[-1] < num:
            stack.pop()  # Remove smaller elements to maintain decreasing order
            to_remove -= 1
        stack.append(num)
    
    # Extract the first `k` elements from the stack
    result = list(stack)[:k]

    # Convert to an integer
    return int("".join(map(str, result)))

# Example usage:
arr = [4, 9, 0, 2]
k = 2
print(max_subsequence_integer(arr, k))  # Output: 92
