class Solution(object):
    def twoSum(self, nums, target):
        a=[]
        for i in range(len(nums)):
            if nums[i]<target:
                a.append(nums[i])
        for j in range(len(nums)):
            for k in range(j+1,len(nums)):
                if target==nums[j]+nums[k]:
                    return [j,k]
