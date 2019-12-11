from domain import createFlight
from functions import addFlight
from functions import codeUniq

def test_uniquecode():
    fl = [createFlight('999', '45', 'dasfsd', 'dasfasdf')]
    assert codeUniq(fl, '999') == True
    assert codeUniq(fl, '99g;') == False

def test_addFlight():
    fl = []
    params = ['999', '82', 'Cluj', 'London']
    addFlight(fl, params)
    assert len(fl) == 1
    params = ['987', '18', 'Cluj', 'London']
    try:
        addFlight(fl, params)
        assert False
    except ValueError:
        assert True
    params = ['98z', '82', 'AB', 'London']
    try:
        addFlight(fl, params)
        assert False
    except ValueError:
        assert True
    params = ['987', '82', 'Cluj', 'AB']
    try:
        addFlight(fl, params)
        assert False
    except ValueError:
        assert True