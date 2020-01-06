from tkinter import *
from Game import Game
from tkinter import messagebox
from tkinter.simpledialog import askstring
from tkinter.messagebox import showinfo
import sys
from copy import deepcopy
import time
from PIL import ImageTk, Image


class PopupWindowFinish:
    def __init__(self, master, kind):
        top = self.top = Toplevel(master)
        if kind:
            self.text = "GAME WON"
        else:
            self.text = "GAME LOST"
        self.lab = Label(top, text=self.text)
        self.lab.pack()
        self.btn = Button(top, text='Exit', command=lambda: top.quit())
        self.btn.pack()
#


class PopupWindowSize:
    def __init__(self, master):
        top = self.top = Toplevel(master)
        self.l1 = Label(top, text='width:')
        self.l2 = Label(top, text='height:')
        self.l1.pack()
        self.e1 = Entry(self.top)
        self.e1.pack()
        self.l2.pack()
        self.e2 = Entry(self.top)
        self.e2.pack()
        self.b = Button(top, text='OK', command=self.cleanup)
        self.b.pack()

    def cleanup(self):
        self.value1 = self.e1.get()
        self.value2 = self.e2.get()
        self.top.destroy()


class PopupWindowDif:
    def __init__(self, master):
        top = self.top = Toplevel(master)
        self.dif = 'Easy'
        self.l = Label(top, text='Choose difficulty')
        self.b1 = Button(top, text='Easy', command=self.retEz)
        self.b1.pack()
        self.b2 = Button(top, text='Medium', command=self.retMed)
        self.b2.pack()
        self.b3 = Button(top, text='Hard', command=self.retHard)
        self.b3.pack()

    def retEz(self):
        self.dif = 'Easy'
        self.top.destroy()

    def retMed(self):
        self.dif = 'Medium'
        self.top.destroy()

    def retHard(self):
        self.dif = 'Hard'
        self.top.destroy()


class GUI:
    def __init__(self, game):
        self._game = game
        self._game.setComputer('Hard')
        self.buttons = []
        self.playerMove = True

    def startUI(self):
        self.tk = Tk()
        self.tk.title('Obstruction')
        self.tk.geometry('600x700')
        frame1 = Frame(self.tk)
        frame1.pack()
        self.frame1 = frame1
        frame2 = Frame(self.tk)
        frame2.pack()
        self.frame2 = frame2
        self.btn = Button(frame1, text='Board size', command=self._initBoard)
        self.btn.pack()
        self.diff = Button(frame1, text='Difficulty', command=self._setDifficulty)
        self.diff.pack()
        # self.start = Button(frame1, text='Start game', command=self.startGame)
        # self.start.pack()
        self.tk.mainloop()

    def startGame(self):
        b = self._game.getBoard()
        while not b.isEnded():
            self.showBoard()
            if not self.playerMove:
                self._game.computerMove()
                self.playerMove = not self.playerMove
            if b.isEnded():
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

    def _setDifficulty(self):
        self.w2 = PopupWindowDif(self.frame1)
        self.diff['state'] = 'disabled'
        self.tk.wait_window(self.w2.top)
        self.diff['state'] = 'normal'
        self._game.setComputer(self.w2.dif)

    def _initBoard(self):
        self.w = PopupWindowSize(self.frame1)
        self.btn["state"] = "disabled"
        self.tk.wait_window(self.w.top)
        self.btn["state"] = "normal"
        x = self.w.value1
        y = self.w.value2
        self._game.setBoard(x, y)
        self.showBoard()

    def showBoard(self):
        self.d = {1: 'X', -1: '0', 0: ' ', 2: 'B'}
        self.buttonVariables = []
        for i in range(self._game.getBoard().sizeofX):
            tempArr = []
            for j in range(self._game.getBoard().sizeofY):
                textVar = StringVar(value="")
                tempArr.append(textVar)
                Button(self.frame2, font=('Times 20 bold'), bg='white', fg='black', height=2, width=4,
                       textvariable=textVar, command=lambda i=i, j=j: self.press(i, j)).grid(row=i, column=j)
            self.buttonVariables.append(tempArr)

    def updateBoard(self):
        for i in range(self._game.getBoard().sizeofX):
            for j in range(self._game.getBoard().sizeofY):
                newValue = self.d[self._game.getBoard().get(i, j)]
                self.buttonVariables[i][j].set(newValue)
        self.tk.update()

    def press(self, i, j):
        b = self._game.getBoard()
        try:
            self._game.playerMove(i, j)
        except Exception as err:
            print(err)
        self.updateBoard()
            # self.showBoard()
            # self.tk.update()
        if self._game.getBoard().isEnded():
            self.fin = PopupWindowFinish(self.frame1, True)
            # self.showBoard()
            return
        try:
            self._game.computerMove()
        except Exception as err:
            print(err)
        self.updateBoard()
        # self.tk.update()
        # self.showBoard()
        if self._game.getBoard().isEnded():
            # self.showBoard()
            self.fin = PopupWindowFinish(self.frame1, False)
            return
        # self.showBoard()


# game = Game()
# g = GUI(game)
# g.startUI()
