"""Maintain a restaurant waitlist and seat the earliest eligible group.

Question:
    Support adding a group, removing a group by ID, and finding the group that
    arrived earliest among those whose size is no larger than a table.

An insertion-ordered dictionary preserves the stable arrival order.

Complexity: O(1) add/remove, O(N) seating query, and O(N) space.
"""

from collections import OrderedDict


class RestaurantWaitlist:
    def __init__(self):
        self.waitlist = OrderedDict()
        self.next_group_id = 0

    def add_customer_group(self, size):
        """Add a positive-size group and return its permanent ID."""
        if size <= 0:
            raise ValueError("group size must be positive")
        group_id = self.next_group_id
        self.next_group_id += 1
        self.waitlist[group_id] = size
        return group_id

    def remove_customer_group(self, group_id):
        """Remove a waiting group; return whether the ID existed."""
        return self.waitlist.pop(group_id, None) is not None

    def find_group_for_table(self, table_size):
        """Return the earliest eligible group ID, or -1 when none fits."""
        for group_id, group_size in self.waitlist.items():
            if group_size <= table_size:
                return group_id
        return -1

    def display_waitlist(self):
        print(list(self.waitlist.values()))


def _run_tests():
    waitlist = RestaurantWaitlist()
    ids = [waitlist.add_customer_group(size) for size in [4, 2, 3, 6, 5]]
    assert waitlist.find_group_for_table(3) == ids[1]
    waitlist.remove_customer_group(ids[1])
    assert waitlist.find_group_for_table(3) == ids[2]
    assert waitlist.find_group_for_table(1) == -1


if __name__ == "__main__":
    _run_tests()
    print("All tests passed.")
