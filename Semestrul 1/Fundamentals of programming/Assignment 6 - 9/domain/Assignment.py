class Assignment:
    """
    Class assignment - has ID, description, deadline
    """

    def __init__(self, aid, desc, deadline):
        self._id = aid
        self._description = desc
        self._deadline = deadline

    @property
    def Id(self):
        return self._id

    @property
    def Description(self):
        return self._description

    @property
    def Deadline(self):
        return self._deadline

    @Description.setter
    def Description(self, v):
        self._description = v

    @Deadline.setter
    def Deadline(self, v):
        self._deadline = v

    def __str__(self):
        return 'Assignment #' + str(self._id) + ' urges you to ' + str(self._description) + ' until ' + str(
            self._deadline)

    def __repr__(self):
        return str(self)

    def __eq__(self, other):
        if not isinstance(other, Assignment):
            return False
        return self.Id == other.Id
