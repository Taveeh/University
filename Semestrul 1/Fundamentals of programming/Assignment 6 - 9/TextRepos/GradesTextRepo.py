from utils.repo import Repository
from domain.Grade import Grade
from domain.Student import Student
from domain.Assignment import Assignment


class GradesTextRepo(Repository):
    def __init__(self, fileName):
        super().__init__()
        self._file = fileName
        self._loadFile()

    def _loadFile(self):
        f = open(self._file, 'r')
        for x in f:
            a = x
            if a == '':
                break
            a = a.strip()
            a = a.split(',')
            self.store(Grade(Student(int(a[0]), '', ''), Assignment(int(a[1]), '', ''), int(a[2]), int(a[3])))
        f.close()

    def _saveFile(self):
        f = open(self._file, 'w')
        for i in self._objects:
            f.write(str(i.IdStud) + ',' + str(i.IdAssignment) + ',' + str(i.Id) + ',' + str(i.Grade) + '\n')
        f.close()

    def store(self, obj):
        Repository.store(self, obj)
        self._saveFile()

    def update(self, obj):
        Repository.update(self, obj)
        self._saveFile()

    def delete(self, objID):
        Repository.delete(self, objID)
        self._saveFile()

    def __del__(self):
        self._saveFile()
