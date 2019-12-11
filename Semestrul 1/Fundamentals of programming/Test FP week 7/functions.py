from domain import *
def addFlight(flightList, params):
    '''
    addFlight Function that adds a flight to the list of flights
    
    Arguments:
        flightList {list} -- list of current flights
        params {list} -- list of parameters - code{string}, duration{string}, destCity{string}, depCity{string}
    
    Raises:
        ValueError: Code < 3 chars
        ValueError: Departure < 3 chars
        ValueError: Dest < 3 chars
        ValueError: Duration < 20 minutes
        ValueError: Code already exists
    '''
    if len(params[0]) < 3:
        raise ValueError('Code must have at least 3 characters')
    if len(params[2]) < 3:
        raise ValueError('Departure city must have at least 3 characters')
    if len(params[3]) < 3:
        raise ValueError('Destination city must have at least 3 characters')
    if int(params[1]) < 20:
        raise ValueError('Flight must have a duration of at least 20 minutes')
    if codeUniq(flightList, params[0]):
        raise ValueError('Code not unique')
    flightList.append(createFlight(params[0], params[1], params[2], params[3]))

def codeUniq(flightList, code):
    '''
    codeUniq Verifies if a flight code already exists
    
    Arguments:
        flightList {list} -- list of current flights
        code {string} -- code of flight
    
    Returns:
        True -- if code already exists 
        False -- otherwise
    '''
    for i in flightList:
        if getCode(i) == code:
            return True
    return False

def modifyTime(flightList, code, duration):
    '''
    modifyTime Function that modifies duration of flight
    
    Arguments:
        flightList {list} -- list of current flights
        code {string} -- code of fligh
        duration {string} -- duration in minutes
    
    Raises:
        ValueError: Flight does not exist
        ValueError: Duration must be more that 20 minutes
    '''
    fl = 0
    for i in flightList:
        if getCode(i) == code:
            fl = i
    if fl == 0:
        raise ValueError('Flight does not exist')
    if int(duration) < 20:
        raise ValueError('Duration must be > 20 minutes')
    setDuration(fl, duration)

def changeDest(flightList, d1, d2):
    '''
    changeDest Function that changes the destination of all flights that go to a city
    
    Arguments:
        flightList {list} -- list of all flights
        d1 {string} -- initial destination
        d2 {string} -- final destination
    
    Raises:
        ValueError: Destination must have at least 3 characters
    '''
    if len(d2) < 3:
        raise ValueError('Destination must have at least 3 characters')
    for i in flightList:
        if getDest(i) == d1:
            setDest(i, d2)

def interchange(flightList, i,  j):
    '''
    interchange Function that swaps the elements from positions i and j in array
    
    Arguments:
        flightList {list} -- list of flights
        i {int} -- index
        j {int} -- index
    '''
    a = flightList[i]
    flightList[i] = flightList[j]
    flightList[j] = a

def sortTime(flightList):
    '''
    sortTime Function that sorts list of flights ascending with regards to time
    
    Arguments:
        flightList {list} -- list of current flights
    '''
    for i in range(len(flightList)):
        for j in range(len(flightList)):
            if getDuration(flightList[j]) > getDuration(flightList[i]):
                interchange(flightList, i, j)

def showDep(flightList, depCity):
    '''
    showDep Function that creates a list with flight that depart from a given city
    
    Arguments:
        flightList {list} -- list of all flights
        depCity {string} -- departure city
    
    Returns:
        list -- list of flights starting from depCity
    '''
    l = []
    sortTime(flightList)
    for i in flightList:
        if getDep(i) == depCity:
            l.append(i)
    return l
