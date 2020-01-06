import unittest
from Board import Board
from Game import Game


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

    def test_game(self):
        g = Game()
        g.setComputer('Easy')
        g.setBoard('2', '2')
        g.computerMove()
        self.assertEqual(g.getBoard().isEnded(), True)

    def test_computer(self):
        g = Game()
        g.setComputer('Hard')
        g.setBoard('3', '3')
        g.computerMove()
        self.assertEqual(g.getBoard().isEnded(), True)






