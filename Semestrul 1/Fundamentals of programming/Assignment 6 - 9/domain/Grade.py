class Grade:
    def __init__(self, stud, assig, gid, grade=-1):
        self._id = gid
        self._sid = stud
        self._aid = assig
        self._grade = grade

    @property
    def Id(self):
        return self._id

    @property
    def IdStud(self):
        return self._sid.Id

    @property
    def IdAssignment(self):
        return self._aid.Id

    @property
    def Grade(self):
        return self._grade

    @Grade.setter
    def Grade(self, value):
        self._grade = value

    def __str__(self):
        if self._grade != -1:
            return 'Student ' + str(self._sid.Id) + ' has the grade ' + str(self._grade) + ' at assignment #' + str(
                self._aid.Id)
        else:
            return 'Student ' + str(self._sid.Id) + ' has to do assignment #' + str(self._aid.Id)

    def __repr__(self):
        return str(self)
