"""
General solution 1

1. Idea:

We allocate two array which length is same as height recording the left
highest and right highest heights at each position.
The water accumulated at each position is equal to the formula:
    accumulation at i = min(left_highest[i], right_highest[i]) - height[i]

2. Performance

Time complexity : O(3*n)
Space complexity: 2*n

"""

from typing import List


class Solution:
    def trap(self, height: List[int]) -> int:
        # edge checking
        if len(height) == 0:
            return 0

        # step 1: set up two pointers
        l = 0
        r = len(height) - 1
        # step 2: set up recorders
        water = 0
        l_highest = [0] * len(height)
        r_highest = [0] * len(height)
        l_highest[l] = height[l]
        r_highest[r] = height[r]
        l += 1
        r -= 1
        # step 3: calculate the left highest and right highest at each position
        # left highest
        for pos in range(l, len(height)):
            l_highest[pos] = max(l_highest[pos - 1], height[pos])
        # right highest
        for pos in range(r, -1, -1):
            r_highest[pos] = max(r_highest[pos + 1], height[pos])
        # print(l_highest)
        # print(r_highest)
        # step 4: accumulate water
        for pos in range(0, len(height)):
            water += min(l_highest[pos], r_highest[pos]) - height[pos]
        return water


if __name__ == '__main__':
    solu = Solution()
    print(solu.trap([0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1]))  # expect 6
    print(solu.trap([4, 2, 3]))     # expect 1
