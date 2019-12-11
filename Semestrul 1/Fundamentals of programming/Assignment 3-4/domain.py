
'''
Functions to get the apartment, amount, type of expenses
Params:
    bill - list
'''
def get_apartment(bill):
    return bill[0]
def get_amount(bill):
    return bill[1]
def get_type(bill):
    return bill[2]

'''
Function that sets the apartment, amount or type of expenses
Params:
    bill - list
    ap, am, ty
'''
def set_apartment(bill, ap):
    bill[0] = ap
def set_amount(bill, am):
    bill[1] = am
def set_type(bill, ty):
    bill[2] = ty

def set_params(params):
    for i in range(len(params)):
        params[i] = params[i][0]



