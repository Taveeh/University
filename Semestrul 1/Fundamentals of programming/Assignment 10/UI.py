from texttable import Texttable
import random
from Board import Board
from Game import Game
from Computer import *


class UI:
    def __init__(self, game):
        self._game = game

    def initBoard(self):
        sizex = input('Number of rows: ')
        sizey = input('Number of columns: ')
        self._game.setBoard(sizex, sizey)

    def initDifficulty(self):
        print('Levels:')
        print('1. Easy')
        print('2. Medium')
        print('3. Hard')
        lvl = input('Difficulty: ')
        d = {'1': 'Easy',
             '2': 'Medium',
             '3': 'Hard'}
        self._game.setComputer(d[lvl])

    @staticmethod
    def _readPlayerMove():
        try:
            cmd = input('Place: ').split(' ')
            return (int(cmd[0]), int(cmd[1]))
        except Exception as err:
            print(err)
            print('Invalid coordinates')

    def start(self):
        self.initBoard()
        self.initDifficulty()
        b = self._game.getBoard()
        playerMove = True
        while not b.isEnded():
            print(b)
            print()
            if playerMove:
                try:
                    move = self._readPlayerMove()
                    self._game.playerMove(*move)
                except Exception as ex:
                    print(ex)
                    continue
            else:
                self._game.computerMove()
            playerMove = not playerMove
            if b.isEnded():
                if playerMove:
                    print(''' ______   _______ _______ _______ _______ ___ _______                                         
                     |   _  \ |   _   |       |   _   |   _   |   |       |                                        
                     |.  |   \|.  1___|.|   | |.  l   |.  |   |.  |.|   | |                                        
                     |.  |    |.  __)_`-|.  |-|.  _   |.  |   |.  `-|.  |-'                                        
                     |:  1    |:  1   | |:  | |:  |   |:  1   |:  | |:  |                                          
                     |::.. . /|::.. . | |::.| |::.|:. |::.. . |::.| |::.|                                          
                     `------' `-------' `---' `--- ---`-------`---' `---'                                          
                      _______  _______ _______ _______ ___ ___ _______     ___ ___ ___ ___ ___ ___ _______ ______  
                     |   _   \|   _   |   _   |   _   |   Y   |   _   |   |   Y   |   Y   |   Y   |   _   |   _  \ 
                     |.  1   /|.  1___|.  1___|.  |   |.      |.  1___|   |.  1   |.  |   |.      |.  1   |.  |   |
                     |.  _   \|.  __)_|.  |___|.  |   |. \_/  |.  __)_    |.  _   |.  |   |. \_/  |.  _   |.  |   |
                     |:  1    |:  1   |:  1   |:  1   |:  |   |:  1   |   |:  |   |:  1   |:  |   |:  |   |:  |   |
                     |::.. .  |::.. . |::.. . |::.. . |::.|:. |::.. . |   |::.|:. |::.. . |::.|:. |::.|:. |::.|   |
                     `-------'`-------`-------`-------`--- ---`-------'   `--- ---`-------`--- ---`--- ---`--- ---'
                                                                                                                   ''')
                else:
                    print('GAME WON')
        print(b)


# g = Game()
# u = UI(g)
# u.start()
