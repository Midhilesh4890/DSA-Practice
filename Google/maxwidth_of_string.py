"""Find the longest substring whose first character is smaller than its last.

Question: For a string, maximize ``j - i + 1`` subject to ``i < j`` and
``text[i] < text[j]``. A decreasing stack of candidate left endpoints and a
right-to-left scan solves the problem.

Complexity: O(N) time and O(N) space.
"""

# Find maximum length of a substring of a string with first charachter 
# lexicographically smaller than its last charachter.


# assume string length 10^5 char long, assume 26 small case english letters in string


# solve it in linear time.


# input : "dbabcb"
# output : 4


class Solution:
    def maxWidthRamp(self, nums) -> int:
        n = len(nums)
        stack = []

        for i in range(n):
            if not stack or nums[stack[-1]] > nums[i]:
                stack.append(i)

        res = 0

        for j in range(n - 1, -1, -1):
            while stack and nums[stack[-1]] < nums[j]:
                width = j - stack[-1] + 1
                res = max(res, width)
                stack.pop()

        return res


def _run_tests():
    solution = Solution()
    assert solution.maxWidthRamp("dbabcb") == 4
    assert solution.maxWidthRamp("aaaa") == 0
    assert solution.maxWidthRamp("") == 0


if __name__ == "__main__":
    _run_tests()
    print("All tests passed.")



        
