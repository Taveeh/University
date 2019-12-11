'''
Airport
Flight: <code> <duration> <departure city> <destination city>
'''

def createFlight(cod, duration, departureCity, destinationCity):
    '''
    createFlight Function that creates a flight as a list
    
    Arguments:
        cod {string} -- code of fligh
        duration {string} -- duration in minutes
        departureCity {string} -- departure city
        destinationCity {string} -- destination city
    
    Returns:
        list -- a flight
    '''
    return [cod, duration, departureCity, destinationCity]

'''
Getters

Returns:
    string -- code/duration/destination city/departure city of a flight
'''
def getCode(flight):
    return flight[0]

def getDuration(flight):
    return flight[1]

def getDep(flight):
    return flight[2]

def getDest(flight):
    return flight[3]

'''
Setters
Set duration/ destination city of a flight
'''

def setDuration(flight, value):
    flight[1] = value

def setDest(flight, value):
    flight[3] = value
