from utils.repo import Repository
import json
from domain.Student import Student
from utils.generate import GenerateStudents


class StudentJsonRepo(Repository):
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
            self.store(Student(int(data[i][0]), data[i][1], int(data[i][2])))
        f.close()

    def _saveFile(self):
        students = {}
        for i in range(len(self._objects)):
            students[i] = str(self._objects[i].Id) + ',' + \
                self._objects[i].Name + ',' + str(self._objects[i].Group)
        with open(self._file, 'w') as f:
            json.dump(students, f)
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
