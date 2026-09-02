"""Determine whether interval operations can reduce an array to zero.

Question:
    Each query ``[left, right]`` may subtract one from any chosen subsequence
    (subset of indices) inside that interval. Can all non-negative array values
    be reduced to zero after using every query at most once?

An index can be selected independently in every covering query. Therefore the
answer is true exactly when each index is covered at least ``array[index]``
times. A difference array computes all coverage counts in one pass.

Time complexity: O(N + Q). Space complexity: O(N).
"""


def can_reduce_to_zero(array, queries):
    """Return whether the available range operations cover every requirement."""
    if any(value < 0 for value in array):
        raise ValueError("array values must be non-negative")

    difference = [0] * (len(array) + 1)
    for left, right in queries:
        if not 0 <= left <= right < len(array):
            raise ValueError("query is outside the array")
        difference[left] += 1
        difference[right + 1] -= 1

    coverage = 0
    for index, required in enumerate(array):
        coverage += difference[index]
        if coverage < required:
            return False
    return True


def _run_tests():
    assert can_reduce_to_zero([1, 2, 3], [(0, 1), (1, 2), (0, 2), (1, 2)])
    assert not can_reduce_to_zero([2, 0], [(0, 1)])
    assert can_reduce_to_zero([], [])
    assert can_reduce_to_zero([0, 0], [])


if __name__ == "__main__":
    _run_tests()
    print("All tests passed.")
