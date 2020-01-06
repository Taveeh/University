######## IMPORTS ########
from domain import *
from functions import *
from tests import *
import re
#########################

def list_all(billList):
    '''
    list_all Function that lists all the expenses
    
    Arguments:
        billList {[list]} -- [list of all expenses]
    '''
    for i in billList:
        if i[2] != 'other':
            print('Apartment ' + str(i[0]) + ' has to pay ' + str(i[1]) + ' RON for ' + str(i[2]) + '.')
        else:
            print('Apartment ' + str(i[0]) + ' has to pay ' + str(i[1]) + ' RON for ' + str(i[2]) + ' expenses.')

def list_ap(billList, ap):
    '''
    Function to print all the expenses of an apartment
    Params:
        billList - list of all expenses
    '''
    for i in billList:
        if i[0] == ap:
            if i[2] != 'other':
                print('Apartment ' + str(i[0]) + ' has to pay ' + str(i[1]) + ' RON for ' + str(i[2]) + '.')
            else:
                print('Apartment ' + str(i[0]) + ' has to pay ' + str(i[1]) + ' RON for ' + str(i[2]) + ' expenses.')

def list_some_of_em(billList, params):
    '''
    list_some_of_em Function that lists expenses with a given property
    
    Arguments:
        billList {[list]} -- [list of all expenses]
        params {[list]} -- [list with property : >/=/<, value]
    '''
    params[1] = int(params[1])
    costDict = {}
    set_costs(billList, costDict)
    micmareegal = re.findall(r'^[<|>|=]$', params[0])
    if len(micmareegal) != 1:
        print('Bad command parameter')
        return
    micmareegal = micmareegal[0]
    if micmareegal == '<':
        for i in costDict:
            if costDict[i] < params[1]:
                print('Apartment ' + str(i) + ' has to pay ' + str(costDict[i]) + ' RON')
    elif micmareegal == '>':
        for i in costDict:
            if costDict[i] > params[1]:
                print('Apartment ' + str(i) + ' has to pay ' + str(costDict[i]) + ' RON')
    elif micmareegal == '=':
        for i in costDict:
            if costDict[i] == params[1]:
                print('Apartment ' + str(i) + ' has to pay ' + str(costDict[i]) + ' RON')


def show_bills(billList, params, history):
    '''
    Function that prints the expenses list
    Params:
        billList - list of expenses
    '''
    if len(params) == 0:
        list_all(billList)        
    elif len(params) == 1 and REisDigit(params[0]):
        list_ap(billList, int(params[0]))
    elif len(params) == 2 and REisDigit(params[1]):
        list_some_of_em(billList, params)
    else:
        print('Bad command parameters!!!')

def add_bill_ui(billList, params, history):
    if len(params) != 3:
        print('Bad expense parameters!')
        return
    if not REisDigit(params[0]) or not REisDigit(params[2]):
        print('Bad command parameters')
        return
    s = create_bill(params[0], params[2], params[1])
    if s == None:
        print('Invalid expense data')
        return
    history.append(billList[:])
    add_bill(billList, s)

def readCommand():
    cmd = input('Command: ')
    params = re.findall(r'([\S]+)', cmd)
    return (params[0], params[1:])

def help_command():
    '''
    Function to print the help menu
    '''
    print("Welcome to the help panel. This is what you can do:")
    print('add <apartment> <amount> <type>   --> adds an expense')
    print('remove <apartment>  --> removes all expenses of an apartment')
    print('remove <start apartment> to <end apartment>  --> removes all expenses of apartments from start to end')
    print('remove <type>  --> removes all expenses with a given type')
    print('replace <apartment> <type> with <amount> --> replace the amount of the expense with a type for an apartment with amount')
    print('list  --> prints all expenses')
    print('list [< | = | >] <value> --> list all apartments with expenses </>/= value')
    print('list <apartment>  --> list all expenses for an apartment')
    print('exit  --> exit program')
    print('sum <type>  --> write the total amount for the expenses having type')
    print('max <apartment>  --> write the maximum amount per each expense type for apartment')
    print('sort apartment  --> write the list of apartments sorted ascending by total amount of expenses')
    print('sort type  --> write the total amount of expenses for each type, sorted ascending by amount of money')
    print('filter <type>  --> keep only expenses for <type>')
    print('filter <value>  --> keep only expenses having amount smaller than <value>')
    print('undo  --> undo the last operation')

def remove_ui(billList, params, history):
    '''
    Function to remove the apartment(s) or the type selected
    Params:
        billList - list of expenses
        params - list of 1 or 3 elements
    Output:
        None - bad parameters
    '''
    l = len(params)
    if l != 1 and l != 3:
        print('Bad command parameters - length')
        return
    if l == 3 and not re.match(r'^to$', params[1]):
        print('Bad command parameters - wrong text')
        return
    if l == 1 and not (REisDigit(params[0]) or re.match(r'^water|heating|electricity|gas|other$', params[0])):
        print('Bad command parameters')
        return
    if l == 3 and not REisDigit(params[0]) and not REisDigit(params[2]):
        print('Bad command parameters')
        return
    history.append(billList[:])
    if re.match(r'^water|heating|electricity|gas|other$', params[0]):
        remove_type(params[0], billList)
    else:
        apstart = int(params[0])
        apend = apstart
        if l == 3:
            apend = int(params[2])
        if apstart > apend:
            print('Bad command parameters - start > end')
            return
        for i in range(apstart, apend + 1):
            remove_ap(i, billList)

def replace_ui(billList, params, history):
    if len(params) != 4:
        print('Bad command parameters')
        return
    if not REisDigit(params[0]) or not REisDigit(params[3]) or not re.match(r'^water|gas|other|electricity|heating$', params[1]) or not re.match(r'^with$', params[2]):
        print('Bad command parameter')
        return
    history.append(billList[:])
    if replace_bill(billList, params) == 0:
        print('Item with specified values does not exist')
        history.pop()
        return

def sum_ui(billList, params, history):
    if len(params) != 1:
        print('Bad command parameters')
        return
    params = params[0]
    if not re.match(r'^water|gas|other|electricity|heating$', params):
        print('Type does not exist')
        return
    print('Sum for type ' + params + ' is ' + str(sum_type(billList, params)))    

def max_ui(billList, params, history):
    if len(params) != 1:
        print('Bad command parameters')
        return
    if not REisDigit(params[0]):
        print('Bad command parameters')
        return
    params = int(params[0])
    bdict = max_ap(billList, params)
    for i in bdict:
        if bdict[i] != 0:
            print('Maximum amount of expense for type ' + i + ' is ' + str(bdict[i]))

def invalid_choice():
    print('Please choose a valid way of navigating the app')


def apartment_administrator_menu():
    billList = init_expenses()
    history = []
    commands = {
    '1': add_menu,
    '2': menu_remove,
    '3': menu_remove_some,
    '4': menu_remove_type,
    '5': menu_replace,
    '6': menu_list_all,
    '7': menu_list_ap,
    '8': menu_list_prop,
    '9': menu_sum,
    '10': menu_max,
    '11': menu_sort,
    '12': menu_filter_type,
    '13': menu_filter_val,
    '14': menu_undo
    }
    while True:
        print_menu()
        cmd = input('Command: ')
        if cmd == '0':
            return
        elif cmd in commands.keys():
            commands[cmd](billList, history)
        else:
            print('Invalid command')
######### MODIFY ############
def print_menu():
    print('This is the menu driven app')
    print('1. Add bill')
    print('2. Remove expenses for an apartment')
    print('3. Remove expenses from apartment x to y')
    print('4. Remove expenses for a given type')
    print('5. Replace value of expense for an apartment and type')
    print('6. List all expenses')
    print('7. List all expenses for a given apartment')
    print('8. List all apartments with expenses </=/> value')
    print('9. Write total amount of expenses for the given type')
    print('10. Write max amount for each expense type for given apartment')
    print('11. Sort by expense for apartment or type')
    print('12. Filter by type')
    print('13. Filter by value')
    print('14. Undo')
    print('0. Exit')

def menu_list_all(billList, history):
    list_all(billList)

def menu_max(billList, history):
    ap = input('Apartment: ')
    params = [ap]
    max_ui(billList, params, history)

def menu_sum(billList, history):
    ttype = input('Type: ')
    params = [ttype]
    sum_ui(billList, params, history)

def menu_remove(billList, history):
    ap = input('Apartment: ')
    params = [ap]
    remove_ui(billList, params, history)

def menu_remove_some(billList, history):
    apstart = input('Start ap: ')
    apend = input('End ap: ')
    params = [apstart, 'to', apend]
    remove_ui(billList, params, history)

def menu_remove_type(billList, history):
    ttype = input('Type: ')
    params = [ttype]
    remove_ui(billList, params, history)

def menu_replace(billList, history):
    ap = input('Please enter apartment number: ')
    ttype = input('Please enter expense type: ')
    val = input('Value to change: ')
    history.append(billList[:])
    pos = ['water', 'electricity', 'gas', 'heating', 'other']
    if ap.isdigit() == False:
        print('Invalid number')
        return
    if ttype not in pos:
        print('Invalid type')
        return
    params = [ap, ttype, 'with', val]
    replace_bill(billList, params)

def add_menu(billList, history):
    ap = input('Apartment number: ')
    value = input('Amount: ')
    ttype = input('Type: ')
    params = [ap, value, ttype]
    add_bill_ui(billList, params, history)

def menu_list_ap(billList, history):
    ap = int(input('Show apartment: '))
    list_ap(billList, ap)

def menu_list_prop(billList, history):
    sign = input('>/=/<: ')
    nr = input('Than: ')
    params = [sign, nr]
    list_some_of_em(billList, params)

def apartment_administrator_ui():
    billList = init_expenses()
    history = []
    commands = {'add': add_bill_ui, 
    'list':show_bills,
    'remove':remove_ui, 
    'replace': replace_ui, 
    'sum': sum_ui, 
    'max': max_ui, 
    'sort': sort_ui, 
    'filter': filter_ui,
    'undo': undo_ui}
    while True:
        cmdset = readCommand()
        cmd = cmdset[0]
        params = cmdset[1]
        if re.match(r'^exit$', cmd):
            return
        if re.match(r'^help$', cmd):
            help_command()
            continue
        flag = False
        for item in commands.items():
            if re.match(f'^{item[0]}$', cmd):
                item[1](billList, params, history)
                flag = True
        if not flag:
            print('Bad command!!')

def menu_sort(billList, history):
    wut = input('Sort by(type/apartment): ')
    params = [wut]
    sort_ui(billList, params, history)

def menu_filter_type(billList, history):
    huh = input('Type: ')
    params = [huh]
    filter_ui(billList, params, history)

def menu_filter_val(billList, history):
    huh = input('Value: ')
    params = [huh]
    filter_ui(billList, params, history)

def filter_ui(billList, params, history):
    history.append(billList[:])
    if len(params) != 1:
        print('Wrong parameters')
        return
    if not REisDigit(params[0]):
        try:
            filter_type(billList, params[0])
            print('Filtered successfully')
        except ValueError as uwu:
            print(uwu)
            history.pop()
    else:
        params[0] = int(params[0])
        try:
            filter_value(billList, params[0], history)
            print('Filtered successfully')
        except ValueError as uwu:
            print(uwu)
            history.pop()

def sort_ui(billList, params, history):
    if len(params) != 1:
        print('Invalid command')
        return
    if re.match(r'^apartment$', params[0]):
        b = sort_ap(billList)
        params = ['>', '-1']
        list_some_of_em(b, params)
    elif re.match(r'^type$', params[0]):
        d = sort_type(billList)
        for i in d:
            print('Type ' + i + ' has a total of ' + str(d[i]) + ' RON')
    else:
        print('Invalid command')
        return

def undo_ui(billList, params, history):
    try:
        undo(billList, params, history)
    except ValueError as uwu:
        print(uwu)

def menu_undo(billList, history):
    try:
        undo(billList, [], history)
    except ValueError as uwu:
        print(uwu)

def start():
    while True:
        print('Welcome to the Apartment Administrator oficial app. Please choose your method to access the program')
        print('For Menu-Driven App type 1 or menu')
        print('For Console UI App type 2 or console')
        print('In order to exit the program type 0 or exit')
        cmd = input('State your choice: ')
        if re.match(r'^1$', cmd) or re.match(r'^menu$', cmd):
            apartment_administrator_menu()
        elif re.match(r'^2$', cmd) or re.match(r'^console$', cmd):
            apartment_administrator_ui()
        elif re.match(r'^0$', cmd) or re.match(r'^exit$', cmd):
            return
        else:
            invalid_choice()
