"""Group records that share at least one property, including transitive links.

Question:
    Every record contains a unique ID followed by properties. Records belong to
    the same group when they share a property directly or through other records.

A disjoint-set union (DSU) joins a record with the first record seen for each
property, then collects IDs by their final representative.

Time complexity: O(P * alpha(N)); space complexity: O(N + P), where P is the
total number of property occurrences.
"""


class UnionFind:
    def __init__(self, size):
        self.parent = list(range(size))
        self.rank = [0] * size

    def find(self, node):
        if self.parent[node] != node:
            self.parent[node] = self.find(self.parent[node])
        return self.parent[node]

    def union(self, first, second):
        first_root, second_root = self.find(first), self.find(second)
        if first_root == second_root:
            return
        if self.rank[first_root] < self.rank[second_root]:
            first_root, second_root = second_root, first_root
        self.parent[second_root] = first_root
        if self.rank[first_root] == self.rank[second_root]:
            self.rank[first_root] += 1


def merge_properties(records):
    """Return a list of sets containing IDs in each connected group."""
    union_find = UnionFind(len(records))
    property_owner = {}

    for index, record in enumerate(records):
        if not record:
            raise ValueError("each record must contain an ID")
        for property_value in record[1:]:
            if property_value in property_owner:
                union_find.union(index, property_owner[property_value])
            else:
                property_owner[property_value] = index

    groups = {}
    for index, record in enumerate(records):
        groups.setdefault(union_find.find(index), set()).add(record[0])
    return list(groups.values())


def _run_tests():
    records = [["id1", "a", "b"], ["id2", "c", "a"], ["id3", "d"], ["id4", "c"]]
    assert {frozenset(group) for group in merge_properties(records)} == {
        frozenset({"id1", "id2", "id4"}),
        frozenset({"id3"}),
    }
    assert merge_properties([]) == []


if __name__ == "__main__":
    _run_tests()
    print("All tests passed.")
