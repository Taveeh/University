"""
Generate all sequences of n parentheses that close correctly.
"""
from Recursive import RecursiveSolution
from Iterative import IterativeSolution


def start():
    n = input('n = ')
    try:
        n = int(n)
    except Exception as ex:
        print(ex)
        return
    print('1. Iterative solution')
    print('2. Recursive solution')
    sol = input('> ')
    if sol == '1':
        array = IterativeSolution(n)
    elif sol == '2':
        array = RecursiveSolution(n)
    else:
        print('Invalid command')
        return
    print(array)


start()



