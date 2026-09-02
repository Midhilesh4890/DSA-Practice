"""Compute train occupancy at every station or time index.

Question:
    For a route with ``N`` indexed positions and passenger trips represented as
    half-open intervals ``[entry, exit)``, return the passenger count at each
    position.

A difference array records +1 at entry and -1 at exit. Its prefix sum is the
occupancy. Time complexity: O(N + T). Space complexity: O(N).
"""


def train_route_occupancy(length, tickets):
    """Return occupancy for every index of a route of the given length."""
    if length < 0:
        raise ValueError("length cannot be negative")
    difference = [0] * (length + 1)
    for entry, exit_ in tickets:
        if not 0 <= entry <= exit_ <= length:
            raise ValueError("ticket interval is outside the route")
        if entry == exit_:
            continue
        difference[entry] += 1
        difference[exit_] -= 1

    result = []
    occupancy = 0
    for index in range(length):
        occupancy += difference[index]
        result.append(occupancy)
    return result


# Backward-compatible name retained from the original scratchpad.
solve = train_route_occupancy


def _run_tests():
    assert train_route_occupancy(5, [(1, 4), (2, 5)]) == [0, 1, 2, 2, 1]
    assert train_route_occupancy(3, []) == [0, 0, 0]
    assert train_route_occupancy(0, []) == []


if __name__ == "__main__":
    _run_tests()
    print("All tests passed.")
