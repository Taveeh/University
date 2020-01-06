class Driver:
    def __init__(self, name, x, y):
        self._name = name
        self._x = x
        self._y = y

    @property
    def Name(self):
        return self._name

    @Name.setter
    def Name(self, val):
        self._name = val

    @property
    def X(self):
        return self._x

    @property
    def Y(self):
        return self._y

    @X.setter
    def X(self, val):
        self._x = val

    @Y.setter
    def Y(self, val):
        self._y = val

    def __str__(self):
        return self._name + ',' + str(self._x) + ',' + str(self._y) + '\n'

    def __repr__(self):
        return self._name + ',' + str(self._x) + ',' + str(self._y)

    def __eq__(self, other):
        if type(other) != Driver:
            return False
        if self._name == other.Name and self._x == other.X and self._y == other.Y:
            return True
        return False


class Address:
    def __init__(self, id, name, x, y):
        self._id = id
        self._name = name
        self._x = x
        self._y = y

    @property
    def Id(self):
        return self._id

    @property
    def Name(self):
        return self._name

    @property
    def X(self):
        return self._x

    @property
    def Y(self):
        return self._y

    @Name.setter
    def Name(self, val):
        self._name = val

    @X.setter
    def X(self, val):
        self._x = val

    @Y.setter
    def Y(self, val):
        self._y = val

    def __str__(self):
        return str(self._id) + ',' + self._name + ',' + str(self._x) + ',' + str(self._y) + '\n'


