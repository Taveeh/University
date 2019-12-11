from functions import *

##################
#                #
# TEST FUNCTIONS #
#                #
##################

def test_init_expenses():
    blist = init_expenses()
    assert len(blist) == 11

def test_remove_bill():
    blist = [create_bill(10, 567, 'gas'), create_bill(10, 235, 'electricity'), create_bill(5, 12, 'other')]
    ap_test1 = 10
    ap_test2 = 5
    assert remove_ap(ap_test1, blist) == 1
    assert len(blist) == 1
    assert remove_ap(ap_test2, blist) == 1
    assert len(blist) == 0

def test_remove_type():
    blist = [create_bill(10, 567, 'gas'), create_bill(10, 235, 'gas'), create_bill(5, 12, 'other')]
    ty_test1 = 'gas'
    ty_test2 = 'other'
    assert remove_type(ty_test1, blist)
    assert len(blist) == 1
    assert remove_type(ty_test2, blist) == 1
    assert len(blist) == 0

def test_replace_bill():
    blist = [create_bill(10, 128, 'other')]
    p1 = [10, 'other', 'with', 500]
    p2 = [10, 'gas', 'with',  500]
    assert replace_bill(blist, p1) == 1
    assert blist[0][1] == 500
    assert replace_bill(blist, p2) == 0

def test_add_bill():
    '''
    Function to test add_bill function
    '''
    blist = []
    b1 = create_bill(13, 100, 'gas')
    assert add_bill(blist, b1) == 0
    assert len(blist) == 1
    assert get_apartment(blist[0]) == 13
    assert get_amount(blist[0]) == 100
    assert get_type(blist[0]) == 'gas'

def test_set_costs():
    blist = [create_bill(1, 98, 'other'), create_bill(1, 102, 'water')]
    bdict = {}
    set_costs(blist, bdict)
    assert len(bdict) == 1
    assert bdict[1] == 200

def test_max_ap():
    blist = [create_bill(1, 100, 'gas'), create_bill(1, 199, 'gas') ]
    bap = 1
    d = max_ap(blist, bap)
    assert len(d) == 5
    assert d['gas'] == 199
    assert d['electricity'] == 0
    assert d['other'] == 0
    assert d['water'] == 0
    assert d['heating'] == 0

def test_sum_type():
    blist = [create_bill(1, 100, 'gas'), create_bill(1, 199, 'gas') ]
    btype = 'gas'
    d = sum_type(blist, btype)
    assert d == 299

def test_filter_type():
    blist = [create_bill(1, 100, 'gas'),
    create_bill(2, 200, 'water'),
    create_bill(3, 200, 'gas')]
    t = 'gas'
    filter_type(blist, t)
    assert len(blist) == 2
    try:
        filter_type(blist, 'hdjsfa')
        assert False
    except ValueError:
        assert True

def test_create_bill():
    assert len(create_bill(12, 198, 'water')) == 3

def test_digit():
    assert REisDigit('1234567890')
    assert not REisDigit('1234asbc')

def test_sort_ap():
    blist = [create_bill(1, 100, 'water'), create_bill(2, 50, 'water'), create_bill(3, 25, 'gas')]
    blist = sort_ap(blist)
    assert get_type(blist[0]) == 'gas'
    assert get_apartment(blist[2]) == 1

def test_sort_type():
    blist = [create_bill(1, 100, 'water'), create_bill(2, 50, 'water'), create_bill(3, 25, 'gas')]
    blist = sort_type(blist)
    assert blist['water'] == 150

