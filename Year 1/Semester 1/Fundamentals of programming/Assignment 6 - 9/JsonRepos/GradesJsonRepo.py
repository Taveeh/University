from utils.repo import Repository
from domain.Grade import Grade
from domain.Assignment import Assignment
from domain.Student import Student
import json


class GradesJsonRepo(Repository):
    def __init__(self, fileName):
        super().__init__()
        self._file = fileName
        self._loadFile()

    def _loadFile(self):
        with open(self._file) as f:
            try:
                data = json.load(f)
            except Exception:
                f.close()
                return
        for i in data.keys():
            data[i] = data[i].split(',')
            self.store(Grade(Student(int(data[i][0]), '', ''), Assignment(
                int(data[i][1]), '', ''), int(data[i][2]), int(data[i][3])))
        f.close()

    def _saveFile(self):
        grades = {}
        for i in range(len(self._objects)):
            grades[i] = str(self._objects[i].IdStud) + ',' + str(self._objects[i].IdAssignment) + \
                ',' + str(self._objects[i].Id) + ',' + \
                str(self._objects[i].Grade)
        with open(self._file, 'w') as f:
            json.dump(grades, f)
        f.close()

    def store(self, obj):
        Repository.store(self, obj)
        self._saveFile()

    def update(self, obj):
        Repository.update(self, obj)
        self._saveFile()

    def delete(self, objID):
        r = Repository.delete(self, objID)
        self._saveFile()
        return r
