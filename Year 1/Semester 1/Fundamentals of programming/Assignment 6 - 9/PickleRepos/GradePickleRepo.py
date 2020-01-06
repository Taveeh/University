from utils.repo import Repository
import pickle
from domain.Grade import Grade
from domain.Student import Student
from domain.Assignment import Assignment


class GradePickleRepo(Repository):
    def __init__(self, fileName):
        super().__init__()
        self._file = fileName
        self._loadFile()

    def _loadFile(self):
        result = []
        try:
            f = open(self._file, 'rb')
            result = pickle.load(f)
        except EOFError:
            result = []
        except IOError as err:
            raise err
        if len(result) == 0:
            return []
        for i in range(len(result)):
            result[i] = result[i].strip()
            result[i] = result[i].split(',')
            self.store(Grade(Student(int(result[i][0]), '', ''), Assignment(int(result[i][1]), '', ''), int(result[i][2]), int(result[i][3])))
        f.close()

    def _saveFile(self):
        f = open(self._file, 'wb')
        text = []
        for i in self._objects:
            text.append(str(i.IdStud) + ',' + str(i.IdAssignment) + ',' + str(i.Id) + ',' + str(i.Grade) + '\n')
        pickle.dump(text, f)
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


