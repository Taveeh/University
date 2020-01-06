class Student:
    """
    Class Student - has student id, name and group
    """

    def __init__(self, sid, sname, sgroup):
        self._id = sid
        self._name = sname
        self._group = sgroup

    @property
    def Id(self):
        return self._id

    @property
    def Name(self):
        return self._name

    @property
    def Group(self):
        return self._group

    @Name.setter
    def Name(self, name):
        if name is None or len(name) < 3:
            raise ValueError('Student name too short')
        self._name = name

    @Group.setter
    def Group(self, group):
        self._group = group

    def __str__(self):
        return self._name + ' has the ID ' + str(self._id) + ' and is in the group ' + str(self._group)

    def __repr__(self):
        return str(self)

    def __eq__(self, other):
        if not isinstance(other, Student):
            return False
        return self.Id == other.Id

