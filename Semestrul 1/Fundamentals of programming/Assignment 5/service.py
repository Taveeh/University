from domain import Book
class Service:
    def __init__(self):
        self._books = [Book('0xffffff', 'Karl Marx', 'The Communist Manifesto'),
                    Book('0xfffffe', 'J. K. Rowling', 'Harry Potter 1'),
                    Book('0xfffffd', 'J. K. Rowling', 'Harry Potter 2'),
                    Book('0xfffffc', 'J. K. Rowling', 'Harry Potter 3'),
                    Book('0xfffffb', 'J. K. Rowling', 'Harry Potter 4'),
                    Book('0xfffffa', 'George R. R. Martin', 'A Song of Ice and Fire'),
                    Book('0xfffff9', 'Fyodor Dostoyevsky', 'The Brothers Karamazov'),
                    Book('0xfffff8', 'Marcel Proust', 'In Search of Lost Time'),
                    Book('0xfffff7', 'Franz Kafka', 'Metamorphosis'),
                    Book('0xfffff6', 'Harper Lee', 'To Kill a Mockingbird'),
                    Book('0xfffff5', 'Margaret Mitchell', 'Gone With the Wind')]
    
    def addBook(self, book):
        '''
        addBook Function that adds a book to the list
        
        Arguments:
            book {Book} -- a book
        
        Raises:
            ValueError: ISBN not unique
        '''
        for s in self._books:
            if s.Isbn == book.Isbn:
                raise ValueError('ISBN already exists')
        self._books.append(book)
    
    @property
    def Library(self):
        return self._books
    
    def undo(self, history):
        '''
        undo Undo the last operations
        
        Arguments:
            history {list} -- list of operations
        
        Raises:
            ValueError: No more undos
        '''
        if len(history) == 0:
            raise ValueError('No more undos')
        self.Library.clear()
        self.Library.extend(history.pop())
    
    def removeBooks(self, givWord):
        '''
        removeBooks Function that removes all the books starting with a given name
        
        Arguments:
            givWord {string} -- given word
        '''
        i = 0
        l = len(self._books)
        while (i < l):
            if self._books[i].firstWord == givWord:
                self._books.pop(i)
                l = l - 1
                continue
            i = i + 1
