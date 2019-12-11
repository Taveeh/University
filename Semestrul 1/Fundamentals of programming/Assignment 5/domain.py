# BOOKS
'''
    All books must have an isbn (unique, string), author and title(string)
'''
import re
class Book:
    def __init__(self, isbn, author, title):
        self._isbn = isbn
        self._author = author
        self._title = title
    @property
    def Isbn(self):
        return self._isbn
    
    @property
    def Author(self):
        return self._author
    
    @property
    def Title(self):
        return self._title
    
    @property
    def firstWord(self):
        return re.findall(r'^\w+', self.Title)[0]
    
    @Isbn.setter
    def Isbn(self, value):
        self._isbn = value
    
    @Author.setter
    def Author(self, value):
        self._author = value
    
    @Title.setter
    def Title(self, value):
        self._title = value
    
    def __str__(self):
        return 'Book ' + self.Title + ', written by ' + self.Author + ' has the isbn ' + self.Isbn
