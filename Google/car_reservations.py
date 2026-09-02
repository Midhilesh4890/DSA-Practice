"""Assign the minimum number of cars to non-overlapping reservations.

Question:
    Each reservation is a half-open interval ``[start, end)``. Assign a car to
    every reservation so that overlapping reservations use different cars and
    return both the per-car schedule and the assignment in input order.

The algorithm processes reservations by start time. One heap tracks busy cars
by end time and another tracks reusable car identifiers.

Time complexity: O(N log N). Space complexity: O(N).
"""

import heapq


def assign_cars(reservations):
    """Return ``(schedules, assignments)`` using the fewest possible cars."""
    ordered = sorted(enumerate(reservations), key=lambda item: item[1])
    busy = []  # (end_time, car_id)
    available = []  # reusable car IDs
    assignments = [0] * len(reservations)
    schedules = {}

    for original_index, (start, end) in ordered:
        if end < start:
            raise ValueError("a reservation cannot end before it starts")

        while busy and busy[0][0] <= start:
            _, car_id = heapq.heappop(busy)
            heapq.heappush(available, car_id)

        if available:
            car_id = heapq.heappop(available)
        else:
            car_id = len(schedules)
            schedules[car_id] = []

        assignments[original_index] = car_id
        schedules[car_id].append((start, end))
        heapq.heappush(busy, (end, car_id))

    return schedules, assignments


def _run_tests() -> None:
    schedules, assignments = assign_cars([(1, 4), (10, 12), (2, 5), (5, 8)])
    assert len(schedules) == 2
    assert assignments[0] != assignments[2]
    assert assignments[1] in schedules
    assert assign_cars([]) == ({}, [])
    assert len(assign_cars([(1, 2), (2, 3), (3, 4)])[0]) == 1


if __name__ == "__main__":
    _run_tests()
    print("All tests passed.")
