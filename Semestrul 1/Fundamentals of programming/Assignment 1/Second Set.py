# [9] Consider a given natural number n. Determine the product p of all the proper factors of n.
'''
Function to calculate the product of the proper factors of a number
Input:
    n - integer
Output:
    p, product of the factors - integer
'''
def product(n):
    p = 1
    for i in range(2, int(n / 2) + 1):
        if n % i == 0:
            p *= i
    return p

n = int(input('Give n = '))
print(product(n))
