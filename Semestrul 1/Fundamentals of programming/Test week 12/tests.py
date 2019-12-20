from Repo import Repository
from service import *
import unittest
from Domain import *


class MyTests(unittest.TestCase):
    def testDistance(self):
        self.assertEqual(distance(1, 2, 3, 4), 4)
        self.assertEqual(distance(9, 9, 9, 9), 0)

    def testClosest(self):
        d = Repository()
        a = Repository()
        ds = DriverService(d)
        ads = AddressService(a)
        d.store(dr1 := Driver('mark', 12, 23))
        d.store(dr2 := Driver('jesus', 14, 15))
        a.store(ad1 := Address(1, 'independentei', 16, 16))
        self.assertEqual(ads.find('1'), ad1)
        self.assertEqual(ds.distanceToAddress(ad1.X, ad1.Y)[0][0], dr2)