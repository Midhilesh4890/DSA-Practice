"""Insert inclusive ranges and query whether a point is covered.

Question:
    Maintain a union of inclusive integer ranges under insertion and point
    membership queries.

Ranges remain sorted and disjoint.

Complexity: O(N) insertion, O(log N) query, and O(N) space.
"""

from bisect import bisect_right


class Intervals:
    def __init__(self):
        self.intervals = []

    def insert(self, start, end):
        if start > end:
            raise ValueError("range start cannot exceed range end")

        merged = []
        placed = False
        for current_start, current_end in self.intervals:
            if current_end + 1 < start:
                merged.append((current_start, current_end))
            elif end + 1 < current_start:
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
        index = bisect_right(self.intervals, (point, float("inf"))) - 1
        return index >= 0 and self.intervals[index][0] <= point <= self.intervals[index][1]


def _run_tests():
    ranges = Intervals()
    ranges.insert(1, 5)
    ranges.insert(10, 15)
    assert ranges.query(1) and ranges.query(5)
    assert not ranges.query(6)
    ranges.insert(6, 9)
    assert ranges.intervals == [(1, 15)]


if __name__ == "__main__":
    _run_tests()
    print("All tests passed.")
