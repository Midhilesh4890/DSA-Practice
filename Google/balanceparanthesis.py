"""Decide whether digit-directed deletions can leave balanced parentheses.

Question:
    A string contains parentheses and digits. At each digit d, delete exactly d
    parentheses occurring to its left; digits do not appear in the result.
    Return whether some sequence of choices leaves a balanced string.

The set of distinct surviving prefixes is carried forward. At a digit, every
choice of d deleted positions is generated and deduplicated.

Time complexity: exponential in the number of parentheses in the worst case.
Space complexity: exponential for the set of possible prefixes.
"""

from itertools import combinations


def can_balance_parentheses(text):
    """Return whether at least one legal deletion sequence is balanced."""
    possibilities = {""}

    for character in text:
        if character in "()":
            possibilities = {prefix + character for prefix in possibilities}
        elif character.isdigit():
            delete_count = int(character)
            next_possibilities = set()
            for prefix in possibilities:
                if delete_count > len(prefix):
                    continue
                for deleted in combinations(range(len(prefix)), delete_count):
                    deleted = set(deleted)
                    next_possibilities.add(
                        "".join(value for index, value in enumerate(prefix) if index not in deleted)
                    )
            possibilities = next_possibilities
            if not possibilities:
                return False
        else:
            raise ValueError("input may contain only parentheses and digits")

    return any(_is_balanced(candidate) for candidate in possibilities)


def _is_balanced(text):
    balance = 0
    for character in text:
        balance += 1 if character == "(" else -1
        if balance < 0:
            return False
    return balance == 0


def _run_tests():
    assert not can_balance_parentheses("((2))")
    assert can_balance_parentheses("((((2))")
    assert can_balance_parentheses("(()1(1))")
    assert can_balance_parentheses("")
    assert not can_balance_parentheses("1")


if __name__ == "__main__":
    _run_tests()
    print("All tests passed.")
