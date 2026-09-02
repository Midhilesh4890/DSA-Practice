"""Support height updates and nearest-taller queries to the left.

Question:
    Maintain an array of heights under point updates. For an index, return the
    closest smaller index whose height is strictly greater than the current one.

A max segment tree skips ranges that contain no qualifying height and searches
right children first to find the nearest match.

Complexity: O(N) construction, O(log N) update/query, and O(N) space.
"""


class SegmentTree:
    def __init__(self, values):
        self.values = list(values)
        self.length = len(values)
        self.size = 1
        while self.size < self.length:
            self.size *= 2
        self.tree = [float("-inf")] * (2 * self.size)
        for index, value in enumerate(self.values):
            self.tree[self.size + index] = value
        for node in range(self.size - 1, 0, -1):
            self.tree[node] = max(self.tree[node * 2], self.tree[node * 2 + 1])

    def update_height(self, index, new_height):
        if not 0 <= index < self.length:
            raise IndexError("height index is out of range")
        self.values[index] = new_height
        node = self.size + index
        self.tree[node] = new_height
        node //= 2
        while node:
            self.tree[node] = max(self.tree[node * 2], self.tree[node * 2 + 1])
            node //= 2

    def find_nearest_taller_left(self, index):
        if not 0 <= index < self.length:
            raise IndexError("height index is out of range")
        if index == 0:
            return -1
        return self._rightmost_above(1, 0, self.size - 1, 0, index - 1, self.values[index])

    def _rightmost_above(self, node, left, right, query_left, query_right, threshold):
        if right < query_left or query_right < left or self.tree[node] <= threshold:
            return -1
        if left == right:
            return left
        middle = (left + right) // 2
        result = self._rightmost_above(node * 2 + 1, middle + 1, right, query_left, query_right, threshold)
        if result != -1:
            return result
        return self._rightmost_above(node * 2, left, middle, query_left, query_right, threshold)


def _run_tests():
    tree = SegmentTree([1, 10, 6, 7, 9, 8])
    assert tree.find_nearest_taller_left(5) == 4
    tree.update_height(4, 7)
    assert tree.find_nearest_taller_left(5) == 1
    assert SegmentTree([]).length == 0


if __name__ == "__main__":
    _run_tests()
    print("All tests passed.")
