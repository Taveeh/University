from Board import Board
from Game import Game
from Game import GameException


class UI:
    def __init__(self, game):
        self._game = game

    def readCommand(self):
        msg = input('Command: ')
        a = msg.find(' ')
        if a == 0:
            return 'Error'
        msg = msg.strip()
        msg = msg.split()
        return msg

    def warp(self, cmd):
        cmd = cmd[1]
        x = cmd[0]
        y = cmd[1]
        self._game.warp(x, y)

    def fire(self, cmd):
        cmd = cmd[1]
        x = cmd[0]
        y = cmd[1]
        self._game.fire(x, y)

    def cheat(self, cmd):
        self._game.cheat()
        print(self._game)
        self._game.cheat()

    def start(self):
        print(self._game)
        while True:
            cmd = self.readCommand()
            d = {'warp': self.warp, 'fire': self.fire, 'cheat': self.cheat}
            if cmd[0] in d.keys():
                try:
                    d[cmd[0]](cmd)
                    print(self._game)
                except ValueError as err:
                    print(err)
                except TypeError as err:
                    print(err)
                    return
                except GameException as err:
                    print(err)
                    return
                except Exception as err:
                    print(err)

            else:
                print('Invalid command')


b = Board()
g = Game(b)
u = UI(g)
u.start()