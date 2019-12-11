from domain import Book
from service import Service
def test_book():
    book1 = Book('0x33ccff', 'Karl Marx', 'The Communist Manifesto')
    assert book1.Isbn == '0x33ccff' and book1.Author == 'Karl Marx' and book1.Title == 'The Communist Manifesto'

def test_addBook():
    book1 = Book('0xffffff', 'The Cat', 'Meow')
    s = Service()
    try:
        s.addBook(book1)
        assert False
    except ValueError:
        assert True
    book2 = Book('1', 'The Dog', 'Meow')
    s.addBook(book2)
    assert len(s.Library) == 12

def test_filterBook():
    s = Service()
    assert len(s.Library) == 11
    s.removeBooks('Harry')
    assert len(s.Library) == 7

