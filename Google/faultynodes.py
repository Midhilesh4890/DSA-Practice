"""Reachability and cheapest paths in a graph containing faulty nodes.

Question:
    Determine whether two nodes are connected without entering faulty nodes.
    Follow-ups ask for the shortest safe path and the cheapest path when faulty
    nodes may be repaired for either per-node or uniform costs.

BFS solves the unweighted variants; Dijkstra's algorithm handles repair costs.

Time complexity: O(V + E) for BFS and O((V + E) log V) for Dijkstra.
Space complexity: O(V + E).
"""

from collections import deque
import heapq


def can_reach(graph, faulty_nodes, start, destination):
    """Return whether a path exists without visiting a faulty node."""
    return min_teleportations(graph, faulty_nodes, start, destination) != -1


def min_teleportations(graph, faulty_nodes, start, destination):
    """Return the minimum edge count while avoiding faulty nodes, or -1."""
    if start in faulty_nodes or destination in faulty_nodes:
        return -1

    queue = deque([(start, 0)])
    visited = {start}
    while queue:
        node, distance = queue.popleft()
        if node == destination:
            return distance
        for neighbor in graph.get(node, ()):
            if neighbor not in visited and neighbor not in faulty_nodes:
                visited.add(neighbor)
                queue.append((neighbor, distance + 1))
    return -1


def _minimum_cost(graph, faulty_nodes, repair_cost, start, destination):
    distances = {start: 0}
    heap = [(0, start)]

    while heap:
        cost, node = heapq.heappop(heap)
        if cost != distances[node]:
            continue
        if node == destination:
            return cost

        for neighbor in graph.get(node, ()):
            candidate = cost + 1
            if neighbor in faulty_nodes:
                candidate += repair_cost(neighbor)
            if candidate < distances.get(neighbor, float("inf")):
                distances[neighbor] = candidate
                heapq.heappush(heap, (candidate, neighbor))
    return -1


def min_total_cost_varying(graph, faulty_nodes, repair_costs, start, destination):
    """Return path cost with a separate repair cost for each faulty node."""
    return _minimum_cost(
        graph,
        faulty_nodes,
        lambda node: repair_costs.get(node, float("inf")),
        start,
        destination,
    )


def min_total_cost_uniform(graph, faulty_nodes, cost, start, destination):
    """Return path cost when every faulty node has the same repair cost."""
    if cost < 0:
        raise ValueError("repair cost cannot be negative")
    return _minimum_cost(graph, faulty_nodes, lambda _node: cost, start, destination)


def _run_tests():
    graph = {
        "A": ["x"],
        "x": ["A", "y"],
        "y": ["x", "D"],
        "D": ["y"],
    }
    assert can_reach(graph, {"z"}, "A", "D")
    assert not can_reach(graph, {"x"}, "A", "D")
    assert min_teleportations(graph, set(), "A", "D") == 3
    assert min_total_cost_varying(graph, {"x"}, {"x": 4}, "A", "D") == 7
    assert min_total_cost_uniform(graph, {"x"}, 4, "A", "D") == 7


if __name__ == "__main__":
    _run_tests()
    print("All tests passed.")
