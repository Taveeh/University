from utils.exceptions import RepositoryException
from utils.IterableObject import SirIndian


class Repository(SirIndian):
    def __init__(self, objlist=None):
        super().__init__()
        if objlist is None:
            self._objects = SirIndian()
        else:
            self._objects = SirIndian(objlist)

    def store(self, obj):
        '''
        store Function that stores an item to the list

        Arguments:
            obj  -- object to be added

        Raises:
            RepositoryException: Element already exists
        '''
        if self.find(obj.Id) is not None:
            raise RepositoryException(
                'Element having id = ' + str(obj.Id) + ' already exists')
        self._objects.append(obj)

    def find(self, objID):
        '''
        find Function to find an element by id

        Arguments:
            objID {int} -- id of element

        Returns:
            element -- element if found | None otherwise
        '''
        for e in self._objects:
            if objID == e.Id:
                return e
        return None

    def update(self, obj):
        '''
        update Function to update an element from the list

        Arguments:
            obj {object} -- object to be updated

        Raises:
            RepositoryException: Item does not exist
        '''
        elem = self.find(obj.Id)
        if elem is None:
            raise RepositoryException('Item does not exist')
        idx = self._objects.index(elem)
        self._objects.remove(elem)
        self._objects.insert(idx, obj)

    def delete(self, objID):
        '''
        delete Function to delete an element from the list

        Arguments:
            objID {int} -- id of object to be deleted

        Raises:
            RepositoryException: Item does not exist

        Returns:
            object -- object deleted
        '''
        obj = self.find(objID)
        if obj is None:
            raise RepositoryException('Item does not exist')
        self._objects.remove(obj)
        print(obj)
        return obj

    @property
    def getAll(self):
        return self._objects

    def __len__(self):
        return len(self._objects)

    def __str__(self):
        r = '\n'
        for e in self._objects:
            r += str(e)
            r += '\n'
        return r
