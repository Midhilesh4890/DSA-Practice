"""Maintain a searchable union of half-open numeric intervals.

Question:
    Support insertion of ``[start, end)`` ranges, merging overlaps and adjacent
    ranges, and answer whether a point is covered.

The implementation stores sorted, disjoint intervals. Binary search locates the
first possible overlap and the interval immediately before a query point.

Insertion: O(N) worst case because list elements may shift; query: O(log N).
Space complexity: O(N), where N is the number of disjoint intervals.
"""

from bisect import bisect_right


class IntervalContainer:
    def __init__(self):
        self.intervals = []

    def insert_range(self, start, end):
        """Insert a non-empty half-open range and merge touching ranges."""
        if start >= end:
            return
        merged = []
        placed = False
        for current_start, current_end in self.intervals:
            if current_end < start:
                merged.append((current_start, current_end))
            elif end < current_start:
                if not placed:
                    merged.append((start, end))
                    placed = True
                merged.append((current_start, current_end))
            else:
                start = min(start, current_start)
                end = max(end, current_end)
        if not placed:
            merged.append((start, end))
        self.intervals = merged

    def query(self, point):
        """Return whether point belongs to any stored interval."""
        index = bisect_right(self.intervals, (point, float("inf"))) - 1
        return index >= 0 and self.intervals[index][0] <= point < self.intervals[index][1]

    # Compatibility with the names used by the original interview draft.
    InsertRange = insert_range
    Query = query


IntervalContainerSortedDict = IntervalContainer


def _run_tests():
    container = IntervalContainer()
    container.insert_range(2, 5)
    container.insert_range(9, 13)
    container.insert_range(3, 10)
    assert container.intervals == [(2, 13)]
    assert container.query(2)
    assert container.query(12)
    assert not container.query(13)
    assert not container.query(0)


if __name__ == "__main__":
    _run_tests()
    print("All tests passed.")
