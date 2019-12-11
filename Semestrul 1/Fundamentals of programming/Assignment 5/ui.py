from service import Service
from domain import Book
from tests import *
class UI:
    def __init__(self, service):
        self._service = service
        self._history = []
    
    def addBook(self):
        isbn = input('ISBN: ')
        author = input('Author: ')
        title = input('Title: ')
        self._history.append(self._service.Library[:])
        newBook = Book(isbn, author, title)
        self._service.addBook(newBook)

    def printMenu(self):
        print('Welcome to the best book database')
        print('1. Add book')
        print('2. Show books')
        print('3. Remove all books starting with a given word')
        print('4. Undo')
        print('0. Exit')
    
    def showBooks(self):
        for s in self._service.Library:
            print(s)
    
    def filterBooks(self):
        w = input('Word: ')
        self._history.append(self._service.Library[:])
        self._service.removeBooks(w)
    
    def undo(self):
        self._service.undo(self._history)
    
    def start(self):
        d = {'1':self.addBook,
            '2': self.showBooks,
            '3': self.filterBooks,
            '4': self.undo}
        while True:
            self.printMenu()
            cmd = input('Command: ')
            if cmd == '0':
                return
            else:
                try:
                    d[cmd]()
                except ValueError as uwu:
                    print(uwu)

s = Service()
ui = UI(s)
ui.start()


test_addBook()
test_book()
test_filterBook()