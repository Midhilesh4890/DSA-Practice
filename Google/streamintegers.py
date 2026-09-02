"""Emit and remove any streamed triple whose range is at most D.

Question:
    Emit and remove any streamed triple whose range is at most D.

Approach:
    Maintain values in sorted order and scan a sliding window after insertion.

Complexity:
    O(N) per item with list storage and O(N) space.

Tests:
    Run this module for its examples and ``python Google/run_all_tests.py``
    from the repository root for the complete isolated test pass.
"""

from bisect import insort

class Solution:
    def __init__(self, d):
        # D is the maximum allowed difference between any two numbers in a triple.
        self.D = d
        # Use SortedList to maintain the incoming numbers in sorted order.
        self.sl = []

    def process(self, item):
        """
        Process a new item from the stream.
        If a valid triple is found (three numbers whose max difference <= D),
        print the triple and remove them from the sorted list.
        """
        # Insert the new item into the sorted list.
        insort(self.sl, item)
        
        # Use two pointers (i and j) to find a contiguous segment in the sorted list.
        i = 0
        # Iterate over the sorted list with pointer j.
        for j in range(len(self.sl)):
            # Ensure the window from i to j satisfies: difference <= D.
            # If not, move the left pointer i until it does.
            while self.sl[j] - self.sl[i] > self.D:
                i += 1
            # Check if the current window size is at least 3.
            if j - i + 1 >= 3:
                # We found a valid triple. Choose the first three elements in this window.
                triple = list(self.sl[i:i+3])
                print("Found triple:", triple)
                # Remove these three numbers from the sorted list.
                for num in triple:
                    self.sl.remove(num)
                # Once a triple is found and removed, return it.
                return triple
        # If no valid triple is found yet, return None.
        return None

# Example usage:
if __name__ == "__main__":
    # Initialize the solution with D = 5.
    sol = Solution(5)
    # Define a stream of numbers.
    stream = [1, 10, 7, -2, 8]
    # Process each number in the stream.
    for item in stream:
        result = sol.process(item)
        if result:
            # If a triple was found, it has already been printed.
            print("Triple returned:", result)
