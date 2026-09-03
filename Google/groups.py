"""Sort and deduplicate the item numbers inside every section.

Question:
    Given a list of integer sections, return the same number of sections with
    each section sorted in ascending order and duplicate values removed.
    Values must lie in ``[0, max_value]``.

Approach:
    A reusable counting array marks values present in each section, after which
    a linear scan emits them in order.

Complexity:
    O(I + S*M) time and O(M) auxiliary space, where I is the number of input
    items, S is the number of sections, and M is ``max_value + 1``.
"""


def counting_sort_deduplicate(sections, max_value):
    """Return independently sorted, duplicate-free sections."""
    if max_value < 0:
        raise ValueError("max_value cannot be negative")

    result = []
    for section in sections:
        present = [False] * (max_value + 1)
        for value in section:
            if not 0 <= value <= max_value:
                raise ValueError("section value is outside the declared range")
            present[value] = True
        result.append([value for value, exists in enumerate(present) if exists])
    return result


def _run_tests():
    sections = [[2, 2, 6], [1, 3, 4], [2, 3, 4]]
    assert counting_sort_deduplicate(sections, 6) == [
        [2, 6],
        [1, 3, 4],
        [2, 3, 4],
    ]
    assert counting_sort_deduplicate([], 0) == []
    assert counting_sort_deduplicate([[]], 0) == [[]]


if __name__ == "__main__":
    _run_tests()
    print("All tests passed.")
