"""Find positions whose following digits match the prefix of pi.

Question:
    Find positions whose following digits match the prefix of pi.

Approach:
    Compare each candidate position with the supplied pi digit string.

Complexity:
    O(N*P) time and O(1) auxiliary space.

Tests:
    Run this module for its examples and ``python Google/run_all_tests.py``
    from the repository root for the complete isolated test pass.
"""

def findMatchingIndices(pi: str) -> list[int]:
    """
    Find indices i where pi[i-len(str(i)):i] equals str(i).
    For example, for i=456, check if pi[453:456] equals "456".
    
    Args:
        pi (str): String representation of pi digits
        
    Returns:
        list[int]: List of 1-based indices that match the criteria
    """
    result = []
    n = len(pi)
    
    for i in range(1, n + 1):
        index_str = str(i)
        index_len = len(index_str)
        
        # Check if we have enough digits to the left in pi
        if i < index_len:
            continue
            
        # For multi-digit indices, check if all digits match
        # Example: For index 456, check if pi[453:456] == "456"
        match = True
        for j in range(index_len):
            pi_pos = i - index_len + j
            if pi[pi_pos] != index_str[j]:
                match = False
                break
                
        if match:
            result.append(i)
            
    return result

# Example Test
pi = "314159265359"
print(findMatchingIndices('456'))