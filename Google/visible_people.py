"""Count how many people each person can see to their left.

Question:
    People stand in a row with distinct heights. Person ``i`` can see person
    ``j < i`` when everyone between them is shorter than both endpoints. Return
    the visible count for every person.

A decreasing monotonic stack removes and counts shorter visible people; the
remaining nearest taller person is also visible.

Time complexity: O(N). Space complexity: O(N).
"""


def visible_counts(heights):
    """Return left-facing visibility counts for distinct heights."""
    result = [0] * len(heights)
    stack = []
    for index, height in enumerate(heights):
        while stack and heights[stack[-1]] < height:
            stack.pop()
            result[index] += 1
        if stack:
            result[index] += 1
        stack.append(index)
    return result


def _run_tests():
    assert visible_counts([10, 6, 8, 5, 11, 9]) == [0, 1, 2, 1, 3, 1]
    assert visible_counts([1, 2, 3]) == [0, 1, 1]
    assert visible_counts([]) == []


if __name__ == "__main__":
    _run_tests()
    print("All tests passed.")
