from utils.repo import Repository
from domain.Assignment import Assignment
import datetime


class AssignmentTextRepo(Repository):
    def __init__(self, fileName):
        super().__init__()
        self._file = fileName
        self._loadFile()

    def _loadFile(self):
        f = open(self._file, 'r')
        for x in f:
            if x == '':
                break
            a = x
            a = a.strip()
            a = a.split(',')
            self.store(y := Assignment(int(a[0]), a[1], datetime.date(int(a[4]), int(a[3]), int(a[2]))))
            # print(y)
        f.close()

    def _saveFile(self):
        f = open(self._file, 'w')
        for i in self._objects:
            f.write(str(i.Id) + ',' + i.Description + ',' + str(i.Deadline.day) + ',' + str(i.Deadline.month) + ',' + str(i.Deadline.year) + '\n')
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
