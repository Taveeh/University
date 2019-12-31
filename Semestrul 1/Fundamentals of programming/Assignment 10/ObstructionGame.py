from UI import UI
from GUI import GUI
from Game import Game


def start():
    g = Game()
    print('!!!Chooose user interface!!!')
    print('1. Console')
    print('2. Graphic')
    cmd = input('> ')
    if cmd == '1':
        ui = UI(g)
        ui.start()
    elif cmd == '2':
        ui = GUI(g)
        ui.startUI()
    else:
        print('Invalid command')


start()
