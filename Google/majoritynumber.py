"""Find the most frequent character and its occurrence boundaries.

Question:
    Find the most frequent character and its occurrence boundaries.

Approach:
    Count frequencies and binary-search boundary positions in the ordered string.

Complexity:
    O(N) time and O(1) alphabet space.

Tests:
    Run this module for its examples and ``python Google/run_all_tests.py``
    from the repository root for the complete isolated test pass.
"""

def find_most_frequent_letter(s):
    def find_boundary(s, ch, left=True):
        lo, hi = 0, len(s) - 1
        boundary = -1
        while lo <= hi:
            mid = (lo + hi) // 2
            if s[mid] == ch:
                boundary = mid
                if left:
                    hi = mid - 1  # Search left boundary
                else:
                    lo = mid + 1  # Search right boundary
            elif s[mid] < ch:
                lo = mid + 1
            else:
                hi = mid - 1
        return boundary

    n = len(s)
    max_freq = 0
    most_frequent = s[0]

    i = 0
    while i < n:
        ch = s[i]
        left = find_boundary(s, ch, left=True)
        right = find_boundary(s, ch, left=False)
        freq = right - left + 1

        if freq > max_freq:
            max_freq = freq
            most_frequent = ch
        
        i = right + 1  # Move to the next distinct letter

    return most_frequent

# Example usage:
s = "AAAABCC"
print(find_most_frequent_letter(s))  # Output: "A"
