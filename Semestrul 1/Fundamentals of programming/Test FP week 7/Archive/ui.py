from tests import *
from functions import *
from domain import *
def addFlight_ui(flightList):
    code = input('Code: ')
    duration = input('Duration: ')
    depCity = input('Departure city: ')
    destCity = input('Destination city: ')
    params = [code, duration, depCity, destCity]
    try:
        addFlight(flightList, params)
    except ValueError as uwu:
        print(uwu)

def changeTimeFlight_ui(flightList):
    code = input('Flight code: ')
    duration = input('New duration: ')
    try:
        modifyTime(flightList, code, duration)
    except ValueError as uwu:
        print(uwu)

def changeDestFlight_ui(flightList):
    initDest = input('Initial destination: ')
    finalDest = input('New destination: ')
    try:
        changeDest(flightList, initDest, finalDest)
    except ValueError as uwu:
        print(uwu)

def listFlight_ui(flightList):
    depCity = input('Departure city: ')
    l = showDep(flightList, depCity)
    if len(l) == 0:
        print('There are no flights starting from ' + depCity)
    else:
        for i in l:
            print('Flight with code ' + getCode(i) + ' with the duration of ' + getDuration(i) + ' minutes will depart from ' + getDep(i) + ' and will land in ' + getDest(i))

def printMenu():
    print('1. Add flight')
    print('2. Modify flight duration')
    print('3. Modify flight(s) destination')
    print('4. List flight for departure city')
    print('0. Exit')

def lsitAll(flightList):
    for i in flightList:
        print('Flight with code ' + getCode(i) + ' with the duration of ' + getDuration(i) + ' minutes will depart from ' + getDep(i) + ' and will land in ' + getDest(i))

def start():
    flightList = [createFlight('999', '25', 'London', 'Cluj'),
                createFlight('998', '67', 'Paris', 'London'),
                createFlight('997', '24', 'London', 'Paris'),
                createFlight('996', '45', 'London', 'Bucharest'),
                createFlight('987', '156', 'Frankfurt', 'Cluj'),
                createFlight('982', '65', 'Cluj', 'Iasi')]
    commands = {'1': addFlight_ui,
                '2': changeTimeFlight_ui,
                '3': changeDestFlight_ui,
                '4': listFlight_ui,
                '5': lsitAll}
    while True:
        printMenu()
        cmd = input('Command: ')
        if cmd == '0':
            return
        elif cmd in commands.keys():
            commands[cmd](flightList)
        else:
            print('Invalid command')

start()
test_uniquecode()
test_addFlight()