import unittest
from Board import Board


class MyTestCase(unittest.TestCase):
    def test_something(self):
        for i in range(50):
            try:
                b = Board()
            except Exception:
                assert False
            nr = 0
            for j in b.allData:
                if j == 1:
                    nr += 1
            self.assertEqual(nr, 10)


