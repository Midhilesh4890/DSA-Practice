"""Determine the winner of a game played on independent candy baskets.

Question:
    Basket ``(candies, limit)`` permits removing between 1 and
    ``floor(candies / limit)`` candies. Alice and Bob alternate moves across
    all baskets; a player with no move loses. Determine the winner under
    optimal play.

Approach:
    Each basket is an impartial subgame. Compute its Sprague-Grundy number from
    every legal successor, then XOR the basket values (the Sprague-Grundy
    theorem). Memoization prevents repeated subproblems.

Complexity:
    For a basket with C candies and limit L, O(C^2/L) worst-case time and O(C)
    memo/recursion space. Across baskets, add those bounds.
"""

from functools import lru_cache


def calculate_grundy(candies, limit):
    """Return the exact Grundy number for one basket."""
    if candies < 0:
        raise ValueError("candies cannot be negative")
    if limit <= 0:
        raise ValueError("limit must be positive")

    @lru_cache(maxsize=None)
    def grundy(remaining):
        maximum_take = remaining // limit
        if maximum_take == 0:
            return 0

        reachable = {
            grundy(remaining - taken)
            for taken in range(1, maximum_take + 1)
        }
        value = 0
        while value in reachable:
            value += 1
        return value

    return grundy(candies)


def determine_winner(baskets):
    """Return ``'Alice'`` for a non-zero Nim sum, otherwise ``'Bob'``."""
    nim_sum = 0
    for candies, limit in baskets:
        nim_sum ^= calculate_grundy(candies, limit)
    return "Alice" if nim_sum else "Bob"


def _run_tests():
    cases = [
        ([(8, 3), (6, 2), (5, 4)], "Alice"),
        ([(10, 4), (7, 2), (9, 3), (2, 1)], "Alice"),
        ([(20, 5), (3, 7), (17, 2), (3, 4)], "Bob"),
        ([], "Bob"),
    ]
    for baskets, expected in cases:
        assert determine_winner(baskets) == expected


if __name__ == "__main__":
    _run_tests()
    print("All tests passed.")
