from Services.ServiceStudent import ServiceStudent
from utils.repo import Repository
from Services.ServiceAssignment import ServiceAssignment
from Services.ServiceGrade import ServiceGrade
from utils.generate import GenerateGrades, GenerateAssignments, GenerateStudents
from Services.undo import Undo
from ui.ui import UI
import sys
from PyQt5 import QtWidgets
from ui.gui import Home
from TextRepos.StudentTextRepo import StudentTextRepo
from TextRepos.AssignmentTextRepo import AssignmentTextRepo
from TextRepos.GradesTextRepo import GradesTextRepo
import configparser
from PickleRepos.GradePickleRepo import GradePickleRepo
from PickleRepos.AssignmentPickleRepo import AssignmentPickleRepo
from PickleRepos.StudentPickleRepo import StudentPickleRepo
from JsonRepos.StudentJsonRepo import StudentJsonRepo
from JsonRepos.AssignmentJsonRepo import AssignmentJsonRepo
from JsonRepos.GradesJsonRepo import GradesJsonRepo
from DatabaseRepos.StudentDatabaseRepo import StudentSqlRepo
from DatabaseRepos.AssignmentDatabaseRepo import AssignmentSqlRepo
from DatabaseRepos.GradeDatabaseRepo import GradeSqlRepo


class Settings:
    def __init__(self, propFile):
        self._propFile = propFile
        self._config = configparser.RawConfigParser()
        self._config.read(self._propFile)
        self._type = self._config.get('Settings', 'repository')
        self.files = []
        self._gui = False
        self._setFiles()
        self._setUI()

    def _setUI(self):
        a = self._config.get('Settings', 'ui').replace('"', '')
        if a == 'GUI' or a == 'gui':
            self._gui = True

    def _setFiles(self):
        if self._type == 'inmemory':
            return None
        elif self._type != 'database':
            self.files.append(self._config.get(
                'Settings', 'students').replace('"', ''))
            self.files.append(self._config.get(
                'Settings', 'assignments').replace('"', ''))
            self.files.append(self._config.get(
                'Settings', 'grades').replace('"', ''))
        else:
            self.files.append(self._config.get(
                'Settings', 'students').replace('"', ''))
            self.files.append(self._config.get(
                'Settings', 'assignments').replace('"', ''))
            self.files.append(self._config.get(
                'Settings', 'grades').replace('"', ''))

    def main(self):
        if self._type == 'inmemory':
            StudentRepo = Repository(GenerateStudents())
            AssignmentRepo = Repository(GenerateAssignments())
            GradesRepo = Repository(GenerateGrades(
                StudentRepo.getAll, AssignmentRepo.getAll))
        elif self._type == 'files':
            StudentRepo = StudentTextRepo(self.files[0])
            AssignmentRepo = AssignmentTextRepo(self.files[1])
            GradesRepo = GradesTextRepo(self.files[2])
        elif self._type == 'binaryfiles':
            StudentRepo = StudentPickleRepo(self.files[0])
            AssignmentRepo = AssignmentPickleRepo(self.files[1])
            GradesRepo = GradePickleRepo(self.files[2])
        elif self._type == 'json':
            StudentRepo = StudentJsonRepo(self.files[0])
            AssignmentRepo = AssignmentJsonRepo(self.files[1])
            GradesRepo = GradesJsonRepo(self.files[2])
        elif self._type == 'database':
            StudentRepo = StudentSqlRepo(self._config.get(
                'Settings', 'database').replace('"', ''), self.files[0])
            AssignmentRepo = AssignmentSqlRepo(self._config.get(
                'Settings', 'database').replace('"', ''), self.files[1])
            GradesRepo = GradeSqlRepo(self._config.get(
                'Settings', 'database').replace('"', ''), self.files[2])
        else:
            print('Invalid')
            return
        u = Undo()
        StudentService = ServiceStudent(StudentRepo, GradesRepo, u)
        AssignmentService = ServiceAssignment(AssignmentRepo, GradesRepo, u)
        GradesService = ServiceGrade(
            GradesRepo, StudentRepo, AssignmentRepo, u)
        if not self._gui:
            ui = UI(StudentService, AssignmentService, GradesService, u)
            ui.start()
        else:
            qApp = QtWidgets.QApplication(sys.argv)
            home = Home(StudentService, AssignmentService, GradesService, u)
            home.show()
            sys.exit(qApp.exec_())


try:
    s = Settings("settings.properties")
    s.main()
except Exception as err:
    print(err)
