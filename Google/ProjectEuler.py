"""Compute the requested Project Euler arithmetic result.

Question:
    Compute the requested Project Euler arithmetic result.

Approach:
    Use the direct mathematical iteration implemented by solve.

Complexity:
    O(N) time and O(1) space.

Tests:
    Run this module for its examples and ``python Google/run_all_tests.py``
    from the repository root for the complete isolated test pass.
"""

def solve(n):
    sm = (n * (n + 1) * (2 * n + 1)) // 6
    sq = (n * (n + 1)) // 2
    total = sq * sq
    res = abs(total - sm)
    return res


if __name__ == "__main__":
    assert solve(10) == 2640
    assert solve(100) == 25164150
    print("All tests passed.")
