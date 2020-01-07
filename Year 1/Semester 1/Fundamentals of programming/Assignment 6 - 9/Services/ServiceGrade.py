from domain.Grade import Grade
from utils.exceptions import StudentException, AssignmentException, GradeException
import random
from Services.undo import FunctionCall, Operation, CascadeOperation
from utils import IterableObject


class ServiceGrade:
    def __init__(self, repo, students, assignments, serviceUndo):
        self._repo = repo
        self._studs = students
        self._assigns = assignments
        self._undo = serviceUndo

    def genId(self):
        '''
        genId Function to generate a random ID for grade

        Returns:
            int -- ID
        '''
        g = random.randint(1000, 1999)
        while any(i.Id == g for i in self._repo.getAll):
            g = random.randint(1000, 1999)
        return g

    def addAssignmentToStud(self, stud, assignment):
        '''
        addAssignmentToStud Function to give an assignment to a student

        Arguments:
            stud {string} -- ID of student
            assignment {strin} -- id of assignment

        Raises:
            StudentException: Invalid ID
            AssignmentException: Invalid ID
            StudentException: Student does not exist
            AssignmentException: Assignment does not exist
            GradeException: Student already has that assignment
        '''
        if not stud.isdigit():
            raise StudentException('Invalid ID')
        if not assignment.isdigit():
            raise AssignmentException('Invalid ID')
        stud = int(stud)
        assignment = int(assignment)
        stud = self._studs.find(stud)
        assignment = self._assigns.find(assignment)
        if stud is None:
            raise StudentException('Student does not exist')
        if assignment is None:
            raise AssignmentException('Assignment does not exist')
        for i in self._repo.getAll:
            if i.IdStud == stud.Id and i.IdAssignment == assignment.Id:
                raise GradeException('Student already has that assignment')
        gid = self.genId()
        undo = FunctionCall(self._repo.delete, gid)
        redo = FunctionCall(self._repo.store, Grade(stud, assignment, gid))
        op = Operation(undo, redo)
        self._undo.recordOperation(op)
        self._repo.store(Grade(stud, assignment, gid))

    def addAssignmentToGroup(self, group, assignment):
        '''
        addAssignmentToGroup Function to add assignment to a group of students

        Arguments:
            group {string} -- group of students
            assignment {string} -- assignment id

        Raises:
            StudentException: Group must be a number
            StudentException: There are no students in that group
            AssignmentException: Invalid assignment ID
            AssignmentException: Assignment does not exist
        '''
        studs = []
        if not group.isdigit():
            raise StudentException('Group must be a number')
        group = int(group)
        for i in self._studs.getAll:
            if i.Group == group:
                studs.append(i)
        if not len(studs):
            raise StudentException('There are no students in that group')
        if not assignment.isdigit():
            raise AssignmentException('Invalid assignment ID')
        assignment = int(assignment)
        assignment = self._assigns.find(assignment)
        if assignment is None:
            raise AssignmentException('Assignment does not exist')
        csc = CascadeOperation()
        for i in studs:
            ok = 0
            for j in self._repo.getAll:
                if j.IdStud == i.Id and j.IdAssignment == assignment.Id:
                    ok = 1
            if not ok:
                gid = self.genId()
                undo = FunctionCall(self._repo.delete, gid)
                redo = FunctionCall(
                    self._repo.store, Grade(i, assignment, gid))
                op = Operation(undo, redo)
                csc.append(op)
                self._repo.store(Grade(i, assignment, gid))
        self._undo.recordOperation(csc)

    def gradeStud(self, stud, assignment, grade):
        '''
        gradeStud Function to grade a student

        Arguments:
            stud {string} -- student id
            assignment {string} -- assignment id
            grade {string} -- grade

        Raises:
            StudentException: Invalid ID
            AssignmentException: Invalid ID
            GradeException: Invalid Grade
            GradeException: Invalid Grade
            StudentException: Student does not exist
            AssignmentException: Assignment does not exist
            GradeException: Student already has a grade for given assignment
            GradeException: Student does not have that assignment
        '''
        if not stud.isdigit():
            raise StudentException('Invalid ID')
        if not assignment.isdigit():
            raise AssignmentException('Invalid ID')
        if not grade.isdigit():
            raise GradeException('Invalid grade')
        grade = int(grade)
        if grade < 1 or grade > 10:
            raise GradeException('Invalid grade')
        stud = int(stud)
        assignment = int(assignment)
        stud = self._studs.find(stud)
        assignment = self._assigns.find(assignment)
        if stud is None:
            raise StudentException('Student does not exist')
        if assignment is None:
            raise AssignmentException('Assignment does not exist')
        for i in self._repo.getAll:
            if i.IdStud == stud.Id and i.IdAssignment == assignment.Id and i.Grade != -1:
                raise GradeException(
                    'Student already has a grade for that assignment')
        g = 0
        for i in self._repo.getAll:
            if i.IdStud == stud.Id and i.IdAssignment == assignment.Id:
                g = i
        if isinstance(g, int):
            raise GradeException('Student does not have that assignment')
        undo = FunctionCall(self._repo.update, g)
        redo = FunctionCall(self._repo.update, Grade(
            stud, assignment, g.Id, grade))
        op = Operation(undo, redo)
        self._undo.recordOperation(op)
        self._repo.update(Grade(stud, assignment, g.Id, grade))

    @property
    def getAssigned(self):
        return self._repo

    def sortStuds(self):
        '''
        sortStuds Function to sort all students by grade

        Returns:
            list -- list of students that have grades sorted from high to low
        '''

        d1 = {}
        d2 = {}
        si = []
        for i in self._studs.getAll:
            si.append(i.Id)
        d1 = {x: 0 for x in si}
        d2 = {x: 0 for x in si}
        for i in self._repo.getAll:
            if i.Grade != -1:
                d1[i.IdStud] += i.Grade
                d2[i.IdStud] += 1


        for i in d1:
            if d2[i] != 0:
                d1[i] /= d2[i]

        l = IterableObject.sortFunction(self._studs.getAll,
                                        key=lambda x, y: d1[x.Id] > d1[y.Id])

        r = ''
        for i in range(len(l)):
            if d1[l[i].Id] > 0:
                r += ('Student ' + str(l[i]) + ' has the average grade ' +
                      str(format(d1[l[i].Id], '.2f')))
                r += '\n'
        return r

    # def removeGrade(self, stud, assign, grade):
    #     '''
    #     removeGrade Function to remove a grade
    #
    #     Arguments:
    #         stud {} -- student id
    #         assign {} -- assignment id
    #         grade {} -- grade
    #     '''
    #     pass
    def getGraded(self):
        r = ''
        for i in self._repo.getAll:
            if i.Grade != -1:
                r += str(i)
                r += '\n'
        return r

    def getUnGraded(self):
        r = ''
        for i in self._repo.getAll:
            if i.Grade == -1:
                r += str(i)
                r += '\n'
        return r
