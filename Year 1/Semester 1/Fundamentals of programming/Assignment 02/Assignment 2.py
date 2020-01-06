import math
'''
Function that creates a complex number
Input:
    a, b - integers
Output:
    list - complex number
'''
def create_number(a = 0, b = 0):
    return [a, b]

'''
Functions to get real/imaginary part of a number
Input:
    number - list of 2 elements
Output:
    number[0] - real part
    or
    number[1] - imaginary part
'''

def get_real_part(number):
    return number[0]

def get_imaginary_part(number):
    return number[1]

'''
Functions to set the real/imaginary part of a number
Input:
    n - integer
    number - list of 2 elements
'''
def set_real_part(n, number):
    number[0] = n

def set_imaginary_part(n, number):
    number[1] = n

'''
Function that reads a complex number
Parameters:
    -
Output:
    s - list of 2 elements (complex number)
'''
def read_number():
    realPart = float(input("Real part: "))
    imaginaryPart = float(input("Imaginary part: "))
    if realPart == int(realPart):
        realPart = int(realPart)
    if imaginaryPart == int(imaginaryPart):
        imaginaryPart = int(imaginaryPart)
    s = create_number(realPart, imaginaryPart)
    return s

'''
Function that reads the list of complex numbers from the console
Parameters:
    complexList - list of complex numbers
'''
def read_complex_numbers(complexList):
    print("How many complex numbers would you like to add to the list?")
    n = int(input("A: "))
    for i in range(n):
        complexList.append(read_number())

'''
Function to display the current list of numbers
Params:
    complexList - list of complex numbers
'''
def show_list(complexList):
    print('The list has ' + str(len(complexList)) + ' elements')
    for i in complexList:
        r = get_real_part(i)
        im = get_imaginary_part(i)
        if r == 0:
            if im == 1:
                print('i')
            elif im == -1:
                print('-i')
            elif im == 0:
                print('0')
            else:
                print(str(im) + 'i')
        else:
            if im == 1:
                print(str(r) + '+i')
            elif im == -1:
                print(str(r) + '-i')
            elif im < 0:
                print(str(r) + str(im) + 'i')
            elif im == 0:
                print(str(r))
            else:
                print(str(r) + '+' + str(im) + 'i')


'''
Function to calculate the modulus of a complex number
Input:
    number - list
Output:
    m - modulus of the number (float)
'''
def no_modulus(number):
    r = get_real_part(number)
    im = get_imaginary_part(number)
    return math.sqrt(r * r + im * im)

'''
Function that finds the longest sequence with modulus < 10
Input:
    complexList - list of all complex numbers
Output:
    res - sequence
'''
def first_property(complexList):
    s = []
    res = []
    l = 0
    lmax = 0
    for i in complexList:
        if no_modulus(i) <= 10:
            l += 1
            s.append(i)
            if l > lmax:
                lmax = l
                res = s
        else:
            l = 0
            s = []
    return res
'''
Function to calculate the sum of 2 complex numbers
Input:
   n1, n2 - complex numbers
Output:
    sum - complex number
'''
def sum_complex(n1, n2):
    return create_number(get_real_part(n1) + get_real_part(n2), get_imaginary_part(n1) + get_imaginary_part(n2))

'''
Function to find the longest sequence with 2 consecutive numbers having equal sum
Input:
    complexList - list of complex numbers
Output:
    l - length of the sequence
    res - sequence
'''

def second_property(complexList):
    s = [complexList[0], complexList[1]]
    res = s
    l = 2
    lmax = 2
    sumc = sum_complex(complexList[0], complexList[1])
    for i in range(1, len(complexList) - 1):
        if sum_complex(complexList[i], complexList[i + 1]) == sumc:
            l += 1
            s.append(complexList[i + 1])
            if l > lmax:
                res = s
                lmax = l
        else:
            l = 2
            sumc = sum_complex(complexList[i], complexList[i + 1])
            s = [complexList[i], complexList[i + 1]]
    return res
        

'''
Main function with the user interface
'''
def start():
    numbers = [create_number(1, -2), create_number(0, 1), create_number(1, -2), create_number(3, 7), create_number(-9, 3), create_number(12, 0), create_number(9, 6), create_number(4, 20),create_number(28, 10) , create_number(-5, 3), create_number(68, 419)]
    while True:
        print("1. Read a list of complex numbers")
        print("2. Display the list")
        print("3. Display the longest sequence with modulus in the [0, 10] range")
        print("4. Display the longest sequence with consecutive terms having equal sum")
        print("5. Exit application")
        choice = int(input("Your wish is my command: "))
        if choice == 1:
            read_complex_numbers(numbers)
        elif choice == 2:
            show_list(numbers)
        elif choice == 3:
            show_list(first_property(numbers))
        elif choice == 4:
            show_list(second_property(numbers))
        elif choice == 5:
            return
        else:
            print("Please introduce a valid number")
    
start()