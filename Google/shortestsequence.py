"""Find the shortest string over a fixed alphabet that is not a substring.

Question:
    Given an input string and an alphabet, return a shortest sequence that does
    not occur contiguously in the input. Ties are resolved lexicographically.

The breadth-first search enumerates candidates by increasing length.

Time complexity: O(A^L * (N + L)) in the worst case, where A is the alphabet
size, N is the input length, and L is the answer length.
Space complexity: O(A^L * L) for the BFS queue.
"""

from collections import deque


def find_shortest_seq_not_present(s: str, alphabet: str = "abcdef") -> str:
    """Return the shortest lexicographically first missing substring."""
    if not alphabet:
        raise ValueError("alphabet must not be empty")

    queue = deque(alphabet)
    while queue:
        candidate = queue.popleft()
        if candidate not in s:
            return candidate
        for character in alphabet:
            queue.append(candidate + character)

    raise RuntimeError("unreachable for a finite input string")


def _run_tests() -> None:
    assert find_shortest_seq_not_present("aabcdf") == "e"
    assert find_shortest_seq_not_present("abcdefacbeddefd") == "aa"
    # "ab" is present across the "aa"/"bb" boundary; "ad" is first missing.
    assert find_shortest_seq_not_present("abcdefacbeddefdaabbccddeeff") == "ad"
    assert find_shortest_seq_not_present("", "01") == "0"


if __name__ == "__main__":
    _run_tests()
    print("All tests passed.")
