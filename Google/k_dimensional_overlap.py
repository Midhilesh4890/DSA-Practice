"""Count coverage of inclusive axis-aligned boxes in a K-dimensional grid.

Question:
    Given each grid dimension and inclusive boxes ``(low, high)``, return a
    nested list whose cells contain the number of boxes covering that point.

Each box updates its 2^K difference-array corners. Prefix sums along every axis
then recover coverage.

Time complexity: O(B * 2^K + K * product(dims)).
Space complexity: O(product(size + 1 for size in dims)).
"""

from itertools import product


def k_dim_overlap_inclusive(dimensions, boxes):
    if not dimensions or any(size <= 0 for size in dimensions):
        raise ValueError("all dimensions must be positive")

    axes = len(dimensions)
    extended = [size + 1 for size in dimensions]
    strides = [1] * axes
    for axis in range(axes - 2, -1, -1):
        strides[axis] = strides[axis + 1] * extended[axis + 1]
    difference = [0] * _product(extended)

    def flat_index(point):
        return sum(coordinate * stride for coordinate, stride in zip(point, strides))

    for low, high in boxes:
        if len(low) != axes or len(high) != axes:
            raise ValueError("box dimensionality does not match the grid")
        if any(not 0 <= low[axis] <= high[axis] < dimensions[axis] for axis in range(axes)):
            raise ValueError("box is outside the grid")
        for choices in product((0, 1), repeat=axes):
            corner = [high[axis] + 1 if choices[axis] else low[axis] for axis in range(axes)]
            difference[flat_index(corner)] += -1 if sum(choices) % 2 else 1

    for axis in range(axes):
        for point in product(*(range(size) for size in extended)):
            if point[axis] == 0:
                continue
            previous = list(point)
            previous[axis] -= 1
            difference[flat_index(point)] += difference[flat_index(previous)]

    def build(axis, prefix):
        if axis == axes:
            return difference[flat_index(prefix)]
        return [build(axis + 1, prefix + [coordinate]) for coordinate in range(dimensions[axis])]

    return build(0, [])


def _product(values):
    result = 1
    for value in values:
        result *= value
    return result


def _run_tests():
    assert k_dim_overlap_inclusive([2, 3], [([0, 0], [0, 1]), ([0, 1], [1, 2])]) == [
        [1, 2, 1],
        [0, 1, 1],
    ]
    assert k_dim_overlap_inclusive([3], [([1], [2])]) == [0, 1, 1]


if __name__ == "__main__":
    _run_tests()
    print("All tests passed.")
