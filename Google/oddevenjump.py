"""Count starting positions that reach the end using odd/even jump rules.

Question: Count indices from which alternating next-higher and next-lower jumps
can reach the final array index.

Sorted-value monotonic-stack passes find the next higher and lower indices;
backward dynamic programming marks reachable states.

Complexity: O(N log N) time and O(N) space.
"""

# Array Jumping


# You are given an integer array A of size N. You can jump from index J to index K, such that K > J, in the following way:


# during odd-numbered jumps (i.e. jumps 1, 3, 5 and so on), you jump to the smallest index K such that A[J] < A[K] and A[K] − A[J] is minimal among all possible K's.
# during even-numbered jumps (i.e. jumps 2, 4, 6 and so on), you jump to the smallest index K such that A[J] > A[K] and A[J] − A[K] is minimal among all possible K's.


# It may be that, for some index J, there is no legal jump. In this case the jumping stops.


# Write a function that, given an integer array A of length N, returns an integer denoting the number of starting points from which you can reach (maybe by jumping more than once) the end of the array A (index N − 1).


# A = [10, 13, 12, 14, 15]
# Answer: [14,15]

class Solution:
    def oddEvenJumps(self, A) -> int:
        n = len(A)
        if n == 0:
            return 0
        next_higher, next_lower = [0] * n, [0] * n

        stack = []
        for a, i in sorted([a, i] for i, a in enumerate(A)):
            while stack and stack[-1] < i:
                next_higher[stack.pop()] = i
            stack.append(i)

        stack = []
        for a, i in sorted([-a, i] for i, a in enumerate(A)):
            while stack and stack[-1] < i:
                next_lower[stack.pop()] = i
            stack.append(i)

        higher, lower = [0] * n, [0] * n
        higher[-1] = lower[-1] = 1
        for i in range(n - 1)[::-1]:
            higher[i] = lower[next_higher[i]]
            lower[i] = higher[next_lower[i]]
        return sum(higher)


def _run_tests():
    solution = Solution()
    assert solution.oddEvenJumps([10, 13, 12, 14, 15]) == 2
    assert solution.oddEvenJumps([2, 3, 1, 1, 4]) == 3
    assert solution.oddEvenJumps([]) == 0


if __name__ == "__main__":
    _run_tests()
    print("All tests passed.")
