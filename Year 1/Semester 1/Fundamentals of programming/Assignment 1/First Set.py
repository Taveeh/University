# [2] Given natural number n, determine the prime numbers p1 and p2 such that n = p1 + p2 (check the Goldbach hypothesis).
'''
Function that verifies if a number is prime
Input: 
    x - integer
Output:
    True - if x is prime
    False - otherwise
'''
import math
def prime(x):
    if x <= 1:
        return False
    if x == 2:
        return True
    if x % 2 == 0:
        return False
    for i in range(3, int(math.sqrt(x)) + 1, 2):
        if x % i == 0:
            return False
    return True
assert False
'''
Function that verifies if the Goldbach Conjecture can be applied
Input: 
    x - integer
Output:
    True - if it can be applied
    False - otherwise
'''
def Goldbach(x):
    if x % 2 == 0:
        return True
    if x % 2 == 1:
        if not prime(x - 2):
            return False
        else:
            return True

'''
Function that finds the 2 prime numbers such as p1 + p2 = n
Input: n - integer
Output: p1, p2 - integer
'''
def GoldbachNumbers(n):
    for i in range(int(n / 2) + 1):
        if prime(i) and prime(n - i):
            return i, n - i
 
n = int(input('Give n = '))
if not Goldbach(n):
    print('There is no solution as the Goldbach Hypothesis cannot be applied in this case')
else:
    p1, p2 = GoldbachNumbers(n)
    print(p1, p2)
