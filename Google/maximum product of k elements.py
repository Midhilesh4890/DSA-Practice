"""Find the maximum product obtainable from exactly K array elements.

Question:
    Choose exactly K values, preserving no positional requirement, so their
    product is as large as possible. Values may be positive, zero, or negative.

Dynamic programming tracks both the smallest and largest product for every
selection size because multiplying by a negative swaps their roles.

Time complexity: O(N*K). Space complexity: O(K).
"""


def maxProductTwoPointerInPlace(array, count):
    """Return the maximum product of exactly ``count`` elements."""
    if count < 0 or count > len(array):
        raise ValueError("count must be between zero and the array length")
    if count == 0:
        return 1

    maximum = [None] * (count + 1)
    minimum = [None] * (count + 1)
    maximum[0] = minimum[0] = 1

    for value in array:
        for selected in range(count, 0, -1):
            if maximum[selected - 1] is None:
                continue
            candidates = (
                value * maximum[selected - 1],
                value * minimum[selected - 1],
            )
            candidate_maximum = max(candidates)
            candidate_minimum = min(candidates)
            if maximum[selected] is None:
                maximum[selected] = candidate_maximum
                minimum[selected] = candidate_minimum
            else:
                maximum[selected] = max(maximum[selected], candidate_maximum)
                minimum[selected] = min(minimum[selected], candidate_minimum)

    return maximum[count]


def _run_tests():
    assert maxProductTwoPointerInPlace([1, 2, 3, 4, 5], 3) == 60
    assert maxProductTwoPointerInPlace([-10, -20, 5, 2], 2) == 200
    assert maxProductTwoPointerInPlace([-10, -20, -5, -2, 3], 3) == 600
    assert maxProductTwoPointerInPlace([1, -2, 3, -4, 5], 3) == 40
    assert maxProductTwoPointerInPlace([0, -1, -2], 2) == 2


if __name__ == "__main__":
    _run_tests()
    print("All tests passed.")
