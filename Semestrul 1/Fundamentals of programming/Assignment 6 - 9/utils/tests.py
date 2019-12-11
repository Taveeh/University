import unittest
from utils.repo import Repository
from utils.exceptions import *
from Services.ServiceStudent import ServiceStudent
from Services.undo import Undo
from Services.ServiceAssignment import ServiceAssignment
from utils.generate import *
from Services.ServiceGrade import ServiceGrade


class MyTestCase(unittest.TestCase):
    def test_store(self):
        studs = Repository([])
        assigns = Repository([])
        grades = Repository([])
        studs.store(s1 := Student(1234, 'John Doe', 1))
        studs.store(s2 := Student(1235, 'Jane Doe', 2))
        assigns.store(a1 := Assignment(123, 'do', datetime.date.today()))
        assigns.store(a2 := Assignment(124, 'go', datetime.date(2019, 8, 29)))
        grades.store(g1 := Grade(s1, a1, 1))
        grades.store(g2 := Grade(s2, a2, 2, 8))
        with self.assertRaises(RepositoryException):
            studs.store(s1)
        self.assertEqual(len(studs), 2)
        self.assertEqual(a1.Description, 'do')
        self.assertEqual(a1.Deadline, datetime.date.today())
        a1.Description = 'did'
        a1.Deadline = datetime.date(2019, 11, 27)
        self.assertNotEqual(repr(a1), 0)
        self.assertEqual(a1 == s1, False)
        self.assertEqual(a1, Assignment(123, '', ''))
        self.assertEqual(g1.IdStud, s1.Id)
        self.assertEqual(g2.IdAssignment, a2.Id)
        self.assertEqual(g2.Grade, 8)
        g1.Grade = 5
        self.assertEqual(g1.Grade, 5)
        self.assertNotEqual(repr(g1), 0)
        g1.Grade = -1
        self.assertNotEqual(repr(g1), 0)

    def test_update(self):
        studs = Repository([])
        studs.store(s1 := Student(1234, 'John Doe', 1))
        studs.update(Student(1234, 'Jane Doe', 2))
        self.assertEqual(studs.getAll[0].Name, 'Jane Doe')
        self.assertEqual(studs.getAll[0].Group, 2)
        with self.assertRaises(RepositoryException):
            studs.update(Student(1235, 'Mark', 12))
        studs.getAll[0].Name = 'Jesus'
        self.assertEqual(studs.getAll[0].Name, 'Jesus')
        with self.assertRaises(ValueError):
            s1.Name = 'as'
        s1.Group = 5
        self.assertNotEqual(repr(s1), 0)
        self.assertEqual(s1 == 0, False)
        self.assertEqual(s1, Student(1234, 'Mike', 2))

    def test_remove(self):
        studs = Repository([])
        studs.store(s1 := Student(1234, 'John Doe', 1))
        self.assertNotEqual(str(studs), '\n')
        studs.delete(1234)
        self.assertEqual(len(studs), 0)
        with self.assertRaises(RepositoryException):
            studs.delete(s1.Id)

    def test_studServ(self):
        studs = Repository([])
        grades = Repository([])
        assigns = Repository([])
        u = Undo()
        students = ServiceStudent(studs, grades, u)
        with self.assertRaises(StudentException):
            students.store('a123', 'John Doe', '1')
        students.store('12349', 'Jane Doe', '12')
        with self.assertRaises(StudentException):
            students.store('12349', 'John Doe', '2')
        with self.assertRaises(StudentException):
            students.store('123', 'John Doe', 'a2')
        with self.assertRaises(StudentException):
            students.delete('a12')
        studs.store(s1 := Student(1234, 'John Doe', 1))
        studs.store(s2 := Student(1235, 'Jane Doe', 2))
        assigns.store(a1 := Assignment(123, 'do', datetime.date.today()))
        assigns.store(a2 := Assignment(124, 'go', datetime.date(2019, 8, 29)))
        grades.store(g1 := Grade(s1, a1, 1))
        grades.store(g2 := Grade(s2, a2, 2, 8))
        students.delete('1234')
        with self.assertRaises(StudentException):
            students.update('123d', 'Mark', '2')
        with self.assertRaises(StudentException):
            students.update('1237', 'Mark', '2')
        students.update('1235', 'John Doe', '0')
        students.update('1235', '0', '3')
        students.update('1235', 'Jesus', '3')
        self.assertNotEqual(str(students), 0)
        self.assertNotEqual(students.find('1234'), 0)

    def test_assignServ(self):
        studs = Repository([])
        grades = Repository([])
        assigns = Repository([])
        u = Undo()
        assignments = ServiceAssignment(assigns, grades, u)
        studs.store(s1 := Student(1234, 'John Doe', 1))
        studs.store(s2 := Student(1235, 'Jane Doe', 2))
        assigns.store(a1 := Assignment(123, 'do', datetime.date.today()))
        assigns.store(a2 := Assignment(124, 'go', datetime.date(2019, 8, 29)))
        grades.store(g1 := Grade(s1, a1, 1))
        grades.store(g2 := Grade(s2, a2, 2, 8))
        with self.assertRaises(AssignmentException):
            assignments.store('123d', '', '', '', '')
        with self.assertRaises(AssignmentException):
            assignments.store('123', '', '', '', '')
        assignments.store('125', 'do', '12', '12', '2020')
        with self.assertRaises(AssignmentException):
            assignments.delete('123d')
        assignments.delete('123')
        with self.assertRaises(AssignmentException):
            assignments.update('23d', '', '')
        with self.assertRaises(AssignmentException):
            assignments.update('123', '', '')
        assignments.update('124', '0', datetime.date.today())
        assignments.update('124', 'wow', '0')
        assignments.update('124', 'woow', datetime.date.today())
        with self.assertRaises(AssignmentException):
            assignments.sortAssign('12d')
        with self.assertRaises(AssignmentException):
            assignments.sortAssign('123')
        with self.assertRaises(GradeException):
            assignments.sortAssign('125')
        self.assertEqual(type(assignments.sortAssign('124')), str)
        with self.assertRaises(GradeException):
            assignments.sortDeadline()
        grades.store(g1 := Grade(s1, assigns.getAll[0], 5, -1))
        with self.assertRaises(GradeException):
            assignments.sortDeadline()
        assignments.update('124', 'do', datetime.date(2019, 8, 8))
        self.assertEqual(type(assignments.sortDeadline()), str)
        self.assertNotEqual(str(assignments), 0)

    def test_generate(self):
        for i in range(20):
            l1 = GenerateStudents()
            l2 = GenerateAssignments()
            l3 = GenerateGrades(l1, l2)
            self.assertEqual(len(l1), 20)
            self.assertEqual(len(l2), 20)
            self.assertEqual(len(l3), 35)

    def test_servGrade(self):
        studs = Repository([])
        grades = Repository([])
        assigns = Repository([])
        u = Undo()
        studs.store(s1 := Student(1234, 'John Doe', 1))
        studs.store(s2 := Student(1235, 'Jane Doe', 2))
        assigns.store(a1 := Assignment(123, 'do', datetime.date.today()))
        assigns.store(a2 := Assignment(124, 'go', datetime.date(2019, 8, 29)))
        assigns.store(Assignment(125, 'wow', datetime.date.today()))
        servgr = ServiceGrade(grades, studs, assigns, u)
        with self.assertRaises(StudentException):
            servgr.addAssignmentToStud('123d', '123')
        with self.assertRaises(AssignmentException):
            servgr.addAssignmentToStud('1234', '123d')
        with self.assertRaises(StudentException):
            servgr.addAssignmentToStud('2136', '123')
        with self.assertRaises(AssignmentException):
            servgr.addAssignmentToStud('1234', '213')
        servgr.addAssignmentToStud('1234', '123')
        with self.assertRaises(GradeException):
            servgr.addAssignmentToStud('1234', '123')
        with self.assertRaises(StudentException):
            servgr.addAssignmentToGroup('d', '123')
        with self.assertRaises(StudentException):
            servgr.addAssignmentToGroup('3', '123')
        with self.assertRaises(AssignmentException):
            servgr.addAssignmentToGroup('1', 'd2')
        with self.assertRaises(AssignmentException):
            servgr.addAssignmentToGroup('1', '126')
        servgr.addAssignmentToGroup('2', '125')
        servgr.addAssignmentToGroup('1', '123')
        servgr.gradeStud('1234', '123', '10')
        with self.assertRaises(StudentException):
            servgr.gradeStud('12d', '123', '10')
        with self.assertRaises(AssignmentException):
            servgr.gradeStud('1234', '12d', '10')
        with self.assertRaises(GradeException):
            servgr.gradeStud('1234', '123', 'd')
        with self.assertRaises(GradeException):
            servgr.gradeStud('1234', '123', '11')
        with self.assertRaises(StudentException):
            servgr.gradeStud('1237', '123', '10')
        with self.assertRaises(AssignmentException):
            servgr.gradeStud('1234', '1237', '10')
        with self.assertRaises(GradeException):
            servgr.gradeStud('1234', '123', '8')
        with self.assertRaises(GradeException):
            servgr.gradeStud('1235', '123', '10')
        self.assertNotEqual(servgr.getAssigned, 0)

        servgr.sortStuds()
        self.assertEqual(type(servgr.getGraded()), str)
        self.assertEqual(type(servgr.getUnGraded()), str)

    def test_undo(self):
        studs = Repository([])
        grades = Repository([])
        assigns = Repository([])
        assigns.store(Assignment(123, 'do', datetime.date.today()))
        u = Undo()
        studServ = ServiceStudent(studs, grades, u)
        gradeServ = ServiceGrade(grades, studs, assigns, u)
        studServ.store('1234', 'John Doe', '1')
        studServ.store('1235', 'Jane Doe', '2')
        gradeServ.addAssignmentToGroup('1', '123')
        u.undo()
        u.redo()
        u.undo()
        u.undo()
        u.undo()
        u.redo()
        u.redo()
        u.undo()
        u.redo()
        u.undo()
        u.undo()
        with self.assertRaises(ValueError):
            u.undo()
        studServ.store('1236', 'Mike Doe', '1')
        with self.assertRaises(ValueError):
            u.redo()



