"""Shuffle songs without replaying any of the previous K songs.

Question:
    Shuffle songs without replaying any of the previous K songs.

Approach:
    Track the recent queue and sample until selecting an eligible song.

Complexity:
    Expected O(1/(1-K/N)) per play and O(K) space.

Tests:
    Run this module for its examples and ``python Google/run_all_tests.py``
    from the repository root for the complete isolated test pass.
"""

import collections
import random
class Shuffler:
    def __init__(self, songs, k):
        self. n = len(songs)
        self.songs = songs
        self.q = collections.deque()
        self.songsInQ = set()
        self.k = k
        
    def playNext(self):
        # Keep randomly picking songs until one wasn't play k times ago
        randChoice = random.randrange(0, self.n)
        # O(P(N-K/N))
        while self.songs[randChoice] in self.songsInQ:
            randChoice = random.randrange(0, self.n)
            
        curSong = self.songs[randChoice]
        if len(self.q) == k:
            playableSong = self.q.popleft()
            self.songsInQ.remove(playableSong)
        
        self.q.append(curSong)
        self.songsInQ.add(curSong)
        return curSong
    

    
songs = ['A', 'B', 'C', 'D']
k = 2
shuf = Shuffler(songs, k)
for _ in range(50):
    print(shuf.playNext(), shuf.q, shuf.songsInQ)