"""Count freshwater lakes enclosed by a selected connected land component.

Question:
    In a binary grid, 1 is land and 0 is water. Given a land cell, count the
    four-directional water regions enclosed by that cell's land component.

First find the chosen land component. Within its padded bounding box, flood-fill
water connected to the outside; every remaining water component is a lake.

Time complexity: O(R * C). Space complexity: O(R * C).
"""

from collections import deque


DIRECTIONS = ((1, 0), (-1, 0), (0, 1), (0, -1))


def count_freshwater_lakes(grid, point):
    """Return the number of lakes enclosed by the point's land component."""
    if not grid or not grid[0]:
        raise ValueError("grid must not be empty")
    rows, columns = len(grid), len(grid[0])
    if any(len(row) != columns for row in grid):
        raise ValueError("grid must be rectangular")
    start_row, start_column = point
    if not (0 <= start_row < rows and 0 <= start_column < columns):
        raise ValueError("point is outside the grid")
    if grid[start_row][start_column] != 1:
        raise ValueError("point must identify a land cell")

    land = {(start_row, start_column)}
    queue = deque(land)
    while queue:
        row, column = queue.popleft()
        for row_delta, column_delta in DIRECTIONS:
            neighbor = row + row_delta, column + column_delta
            nr, nc = neighbor
            if 0 <= nr < rows and 0 <= nc < columns and grid[nr][nc] == 1 and neighbor not in land:
                land.add(neighbor)
                queue.append(neighbor)

    min_row = min(row for row, _ in land) - 1
    max_row = max(row for row, _ in land) + 1
    min_column = min(column for _, column in land) - 1
    max_column = max(column for _, column in land) + 1

    def neighbors(cell):
        row, column = cell
        for row_delta, column_delta in DIRECTIONS:
            candidate = row + row_delta, column + column_delta
            if min_row <= candidate[0] <= max_row and min_column <= candidate[1] <= max_column:
                yield candidate

    outside = (min_row, min_column)
    visited_water = {outside}
    queue = deque([outside])
    while queue:
        cell = queue.popleft()
        for neighbor in neighbors(cell):
            if neighbor not in land and neighbor not in visited_water:
                visited_water.add(neighbor)
                queue.append(neighbor)

    lakes = 0
    for row in range(min_row, max_row + 1):
        for column in range(min_column, max_column + 1):
            cell = row, column
            if cell in land or cell in visited_water:
                continue
            lakes += 1
            visited_water.add(cell)
            queue = deque([cell])
            while queue:
                for neighbor in neighbors(queue.popleft()):
                    if neighbor not in land and neighbor not in visited_water:
                        visited_water.add(neighbor)
                        queue.append(neighbor)
    return lakes


def _run_tests():
    ring = [[1, 1, 1], [1, 0, 1], [1, 1, 1]]
    assert count_freshwater_lakes(ring, (0, 0)) == 1
    assert count_freshwater_lakes([[1, 1], [1, 0]], (0, 0)) == 0
    two_lakes = [[1, 1, 1, 1, 1], [1, 0, 1, 0, 1], [1, 1, 1, 1, 1]]
    assert count_freshwater_lakes(two_lakes, (0, 0)) == 2


if __name__ == "__main__":
    _run_tests()
    print("All tests passed.")
