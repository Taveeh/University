
from domain import *
import operator
import re

def init_expenses():
    '''
    init_expenses Function to initialise the expenses for the program
    
    Returns:
        [list] -- [list of expenses]
    '''
    billList = [create_bill(1, 100, 'other'),
    create_bill(1, 201, 'gas'),
    create_bill(2, 200, 'water'),
    create_bill(3, 300, 'gas'),
    create_bill(4, 400, 'electricity'),
    create_bill(5, 500, 'heating'),
    create_bill(6, 600, 'other'),
    create_bill(7, 700, 'water'),
    create_bill(8, 800, 'gas'),
    create_bill(9, 900, 'electricity'),
    create_bill(10, 1000, 'heating')]
    return billList

def add_bill(billList, bill):
    '''
    Function to add a bill
    Params
        billList - list of bills
        bill 
    Output:
        0 - succes
    '''
    billList.append(bill)
    return 0

def sum_type(billList, ttype):
    '''
    sum_type [Calculates the sum of all expenses with a given type]
    
    Arguments:
        billList {[list]} -- [ist of all expenses]
        ttype {[string]} -- [type of expense]
    
    Returns:
        [integer] -- [sum of all expenses]
    '''
    s = 0
    for i in billList:
        if get_type(i) == ttype:
            s = s + get_amount(i)
    return s

def create_bill(tapartment, tamount, ttype):
    '''
    Function that creates and expense
    Params:
        apartment
        amount
        type
    Output:
        succes - returns the bill
        error - return None
    '''
    tapartment = int(tapartment)
    tamount = int(tamount)
    ttype = str(ttype)
    if tapartment < 0:
        return None
    if tamount < 0:
        return None
    if not re.match(r'^water|heating|electricity|gas|other$', ttype):
        return None
    return[tapartment, tamount, ttype]

def REisDigit(parame):
    return re.match(r'^[\d]+$', parame)

def max_ap(billList, ap):
    '''
    max_ap [Calculates the maximum for amount for each expense type for the given apartment]
    
    Arguments:
        billList {[list]} -- [list of expenses]
        ap {[integer]} -- [number of apartment]
    Returns:
        [dictionary] -- [returns all expenses for given type]
    '''
    d = {'gas': 0, 'other': 0, 'electricity': 0, 'heating': 0, 'water': 0}
    for i in billList:
        if get_apartment(i) == ap:
            d[get_type(i)] = max(get_amount(i), d[get_type(i)])
    return d

def remove_ap(apartment, billList):
    '''
    Function to remove the expenses for an apartment
    Params:
        apartment - integer
        billList - list of expenses
    Ouput:
        1 - expenses are removed
    '''
    i = 0
    l = len(billList)
    while (i < l):
        if billList[i][0] == apartment:
            del billList[i]
            l = l - 1
            continue
        i = i + 1
    return 1

def remove_type(ttype, billList):
    '''
    Function to remove the expenses for a type
    Params:
        ttype - string
        billList - list of expenses
    Ouput:
        1 - expenses are removed
    '''
    i = 0
    l = len(billList)
    while (i < l):
        if billList[i][2] == ttype:
            del billList[i]
            l = l - 1
            continue
        i = i + 1
    return 1

def replace_bill(billList, params):
    '''
    Function to replace the bill for ap and type with amount
    Params:
        billList - list of expenses
        params - list
    Output:
        1 - replaced 
        0 - item does not exist
    '''
    params[0] = int(params[0])
    params[3] = int(params[3])
    for i in billList:
        if i[0] == params[0] and i[2] == params[1]:
            set_amount(i, params[3])
            return 1
    return 0

def set_costs(billList, costDict):
    '''
    set_costs Function to set the total costs of an apartment
    
    Arguments:
        billList {[list]} -- [list of all expenses]
        costDict {[dict]} -- [dictioary for every apartment]
    '''
    for i in billList:
        costDict[i[0]] = 0
    for i in billList:
        costDict[i[0]] = costDict[i[0]] + int(i[1])

def sort_ap(billList):
    '''
    sort_ap [Function to sort all apartments by total amount of expenses]
    
    Arguments:
        billList {[list]} -- [list of expenses]
    
    Returns:
        [list] -- [list of sorted expenses]
    '''
    d = {}
    set_costs(billList, d)
    b = sorted(billList, key= lambda x: d[x[0]])
    return b

def sort_type(billList):
    '''
    sort_type [Function to sort the types by price]
    
    Arguments:
        billList {[list]} -- [list of expenses]
    
    Returns:
        [dict] -- [dictionary with every type's total price(sorted)]
    '''
    d = {'water': 0, 'heating': 0, 'electricity': 0, 'other': 0, 'gas': 0}
    for i in billList:
        d[get_type(i)] += get_amount(i)
    sorted_d = sorted(d.items(), key= operator.itemgetter(1))
    d = {}
    for i in sorted_d:
        d[i[0]] = i[1]
    return d

def filter_type(billList, ttype):
    '''
    filter_type Function to filter expenses with type ttype
    
    Arguments:
        billList {[list]} -- [list of expenses]
        ttype {[string]} -- [type of expense]
    
    Raises:
        ValueError: [Type does not exist]
    '''
    pos = ['water', 'gas', 'electricity', 'other', 'heating']
    if ttype not in pos:
        raise ValueError('Invalid type')
    for i in pos:
        if i != ttype:
            remove_type(i, billList)

def filter_value(billList, value, history):
    '''
    filter_value Function to filter values < than a value
    
    Arguments:
        billList {[list]} -- [list of expenses]
        value {[int]} -- [value]
    
    Raises:
        ValueError: [Value smaller than 0]
    '''
    if value <= 0:
        raise ValueError('Expenses have a positive value')
    history.append(billList[:])
    i = 0
    l = len(billList)
    while i < l:
        if get_amount(billList[i]) >= value:
            billList.pop(i)
            l -= 1
            continue
        i += 1

def undo(billList, params, history):
    if len(history) == 0:
        raise ValueError('No more undos')
    billList.clear()
    billList.extend(history.pop())
