from Repo import Repository
from Domain import Driver


class DriverFileRepo(Repository):
    def __init__(self, fileName):
        super().__init__()
        self._file = fileName
        self._loadFile()

    def _loadFile(self):
        f = open(self._file, 'r')
        for line in f:
            if line == '' or line == '\n':
                break
            a = line
            a = a.strip()
            a = a.split(',')
            self.store(Driver(a[0], int(a[1]), int(a[2])))
        f.close()

    def _saveFile(self):
        f = open(self._file, 'w')
        for i in self._objects:
            f.write(str(i))
        f.close()

    def store(self, obj):
        Repository.store(self, obj)
        self._saveFile()
