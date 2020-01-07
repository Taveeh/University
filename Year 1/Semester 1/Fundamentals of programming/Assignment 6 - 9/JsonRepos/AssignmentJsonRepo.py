from utils.repo import Repository
import json
from domain.Assignment import Assignment
import datetime
from utils.generate import GenerateAssignments


class AssignmentJsonRepo(Repository):
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
            self.store(Assignment(int(data[i][0]), data[i][2], datetime.date(
                int(data[i][4]), int(data[i][3]), int(data[i][2]))))
        f.close()

    def _saveFile(self):
        assignments = {}
        for i in range(len(self._objects)):
            assignments[i] = str(self._objects[i].Id) + ',' + self._objects[i].Description + ',' + str(
                self._objects[i].Deadline.day) + ',' + str(self._objects[i].Deadline.month) + ',' + str(self._objects[i].Deadline.year)
        with open(self._file, 'w') as f:
            json.dump(assignments, f)
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
