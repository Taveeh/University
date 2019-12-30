import unittest
from Board import Board


class MyTestCase(unittest.TestCase):
    def test_board(self):
        with self.assertRaises(ValueError):
            b = Board('asdas', '3')
        b = Board('2', '2')
        b.move(1, 1, '0')
        self.assertEqual(b.isEnded(), True)
        self.assertEqual(b.get(0, 0), 2)
        with self.assertRaises(ValueError):
            b.move(2, 2, 'X')
        with self.assertRaises(ValueError):
            b.move(1, 1, 'p')
        with self.assertRaises(ValueError):
            b.move(1, 1, 'X')




