from utils.repo import Repository
from domain.Student import Student


class StudentTextRepo(Repository):
    def __init__(self, fileName):
        super().__init__()
        self._file = fileName
        self._loadFile()

    def _loadFile(self):
        l = []
        f = open(self._file, 'r')
        for x in f:
            if x == '':
                break
            a = x
            a = a.strip()
            a = a.split(',')
            self.store(Student(int(a[0]), a[1], int(a[2])))
        f.close()

    def store(self, obj):
        Repository.store(self, obj)
        self._saveFile()

    def _saveFile(self):
        f = open(self._file, 'w')
        for i in self._objects:
            f.write(str(i.Id) + ',' + i.Name + ',' + str(i.Group) + '\n')
        f.close()

    def __del__(self):
        self._saveFile()

    def update(self, obj):
        Repository.update(self, obj)
        self._saveFile()

    def delete(self, objID):
        Repository.delete(self, objID)
        self._saveFile()


