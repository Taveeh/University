from service import *
from Repo import Repository
from DriverFileRepo import DriverFileRepo
from AddressFileRepo import AddressFileRepo
from Domain import *


class UI:
    def __init__(self, serviceAddress, serviceDriver):
        self._address = serviceAddress
        self._driver = serviceDriver

    @staticmethod
    def printMenu():
        print()
        print('1. List addresses')
        print('2. List drivers')
        print('3. Sort drivers by distance to an address')
        print('4. Print the pair of drivers who are closest to each other')
        print('0. Exit')
        print()

    def listAddress(self):
        print(str(self._address))

    def listDrivers(self):
        print(str(self._driver))

    def sortByDistance(self):
        address = input('Address ID: ')
        a = self._address.find(address)
        if not a:
            print('Does not exist')
            return
        for i in self._driver.distanceToAddress(a.X, a.Y)[0]:
            print(str(i) + 'Distance: ' + str(self._driver.distanceToAddress(a.X, a.Y)[1][i.Name]) + '\n')

    def closestDrivers(self):
        a = self._driver.closestDrivers()
        print('Driver1: ' + str(a[0]))
        print('Driver2: ' + str(a[1]))
        print('Distance: ' + str(a[2]))

    def main(self):
        d = {'1': self.listAddress,
             '2': self.listDrivers,
             '3': self.sortByDistance,
             '4': self.closestDrivers}
        while True:
            self.printMenu()
            cmd = input('Command: ')
            print()
            if cmd == '0':
                return
            elif cmd in d.keys():
                try:
                    d[cmd]()
                except Exception as err:
                    print(err)
            else:
                print('Bad command')


drivers = DriverFileRepo('drivers.txt')
addresses = AddressFileRepo('addresses.txt')
dServ = DriverService(drivers)
aServ = AddressService(addresses)
u = UI(aServ, dServ)
u.main()
