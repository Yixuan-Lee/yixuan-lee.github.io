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
        print(l_highest)
        print(r_highest)
        # step 4: accumulate water
        for pos in range(0, len(height)):
            water += min(l_highest[pos], r_highest[pos]) - height[pos]
        return water
        # while l < r:
        #     if height[l] <= height[r]:
        #         if height[l] > l_highest:
        #             # water leaks to left, no accumulation
        #             # update left wall
        #             l_highest = height[l]
        #         else:
        #             # accumulate the water
        #             # warning: water may leak to right
        #             water += l_highest - height[l]
        #             # fix the warning
        #             water += 0 if l_highest <= r_highest else -abs(l_highest - r_highest)
        #         # update left pointer
        #         l += 1
        #     else:
        #         if height[r] > r_highest:
        #             # water leaks to right, no accumulation
        #             # update right wall
        #             r_highest = height[r]
        #         else:
        #             # accumulate the water
        #             # warning: water may leak to left
        #             water += r_highest - height[r]
        #             # fix the warning
        #             water += 0 if r_highest <= l_highest else -abs(r_highest - l_highest)
        #         r -= 1



if __name__ == '__main__':
    solu = Solution()
    print(solu.trap([0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1]))  # expect 6
    print(solu.trap([4, 2, 3]))     # expect 1
