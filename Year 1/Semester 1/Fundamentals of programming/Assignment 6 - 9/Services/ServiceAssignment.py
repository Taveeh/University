from utils.exceptions import AssignmentException, GradeException
import datetime
from domain.Assignment import Assignment
from Services.undo import FunctionCall, Operation, CascadeOperation
from copy import deepcopy
from utils import IterableObject

class ServiceAssignment:
    def __init__(self, repo, gradesRepo, serviceUndo):
        self._repo = repo
        self._grades = gradesRepo
        self._undo = serviceUndo

    def store(self, aid, description, day, month, year):
        '''
        store Function to add an assignment
        
        Arguments:
            aid {string} -- assignment id
            description {string} -- description
            day {string} -- deadline day
            month {strign} -- deadline month
            year {string} -- deadline year
        
        Raises:
            AssignmentException: Invalid ID
            AssignmentException: ID already exists
        '''
        if not aid.isdigit():
            raise AssignmentException('Invalid ID')
        aid = int(aid)
        assignment = self._repo.find(aid)
        if assignment is not None:
            raise AssignmentException('ID already exists')
        day = int(day)
        month = int(month)
        year = int(year)
        deadline = datetime.date(year, month, day)
        undo = FunctionCall(self._repo.delete, aid)
        redo = FunctionCall(self._repo.store, Assignment(aid, description, deadline))
        op = Operation(undo, redo)
        self._undo.recordOperation(op)
        self._repo.store(Assignment(aid, description, deadline))

    def delete(self, aid):
        '''
        delete Function to delete an assignment 
        
        Arguments:
            aid {string} -- assignment id
        
        Raises:
            AssignmentException: Invalid ID
        '''
        if not aid.isdigit():
            raise AssignmentException('Invalid ID')
        aid = int(aid)
        assignment = self._repo.delete(aid)
        casc = CascadeOperation()
        undo = FunctionCall(self._repo.store, assignment)
        redo = FunctionCall(self._repo.delete, aid)
        op = Operation(undo, redo)
        casc.append(op)
        le = len(self._grades.getAll)
        i = 0
        while i < le:
            if self._grades.getAll[i].IdAssignment == assignment.Id:
                redo1 = FunctionCall(self._grades.delete, self._grades.getAll[i].Id)
                undo1 = FunctionCall(self._grades.store, self._grades.getAll[i])
                casc.append(Operation(undo1, redo1))
                self._grades.delete(self._grades.getAll[i].Id)
                le -= 1
                continue
            i += 1
        self._undo.recordOperation(casc)

    def update(self, aid, desc, deadline):
        '''
        update Function to update an assignment
        
        Arguments:
            aid {string} -- assignment id
            desc {string} -- description
            deadline {datetime} -- deadline
        
        Raises:
            AssignmentException: Invalid ID
            AssignmentException: Assignment does not exist
        '''
        if not aid.isdigit():
            raise AssignmentException('Invalid ID')
        aid = int(aid)
        assignment = self._repo.find(aid)
        if assignment is None:
            raise AssignmentException('Assignment does not exist')
        undo = FunctionCall(self._repo.update, deepcopy(assignment))
        if desc == '0':
            assignment.Deadline = deadline
            redo = FunctionCall(self._repo.update, assignment)
        elif deadline == '0':
            assignment.Description = desc
            redo = FunctionCall(self._repo.update, assignment)
        else:
            assignment.Description = desc
            assignment.Deadline = deadline
            redo = FunctionCall(self._repo.update, assignment)
        op = Operation(undo, redo)
        self._undo.recordOperation(op)
        self._repo.update(assignment)

    def sortAssign(self, assign):
        '''
        sortAssign Function to sort by grade for given assignment
        
        Arguments:
            assign {string} -- assignment id
        
        Raises:
            AssignmentException: Invalid ID
            AssignmentException: Assignment does not exist
            GradeException: No students have that assignment
        
        Returns:
            list -- sorted list of students that have given assignment
        '''
        ok = 0
        if not assign.isdigit():
            raise AssignmentException('Invalid ID')
        assign = int(assign)
        for i in self._repo.getAll:
            if i.Id == assign:
                ok = 1
        if not ok:
            raise AssignmentException('Assignment does not exist')
        ok = 0
        l = []
        for i in self._grades.getAll:
            if i.IdAssignment == assign:
                l.append(i)
                ok = 1
        if not ok:
            raise GradeException('No students have that assignment')
        l = IterableObject.sortFunction(l, key=lambda x, y: x.Grade < y.Grade, reverse=True)
        r = ''
        for i in l:
            if i.Grade != -1:
                r += str(i)
                r += '\n'
        return r

    def sortDeadline(self):
        '''
        sortDeadline Function to show all students that are late
        
        Raises:
            GradeException: All students have their assignments graded
            GradeException: There are no students that are late
        
        Returns:
            list -- list of students that are late
        '''
        ok = 0
        for i in self._grades.getAll:
            if i.Grade == -1:
                ok = 1
        if not ok:
            raise GradeException('All students have their assignment graded')
        ok = 0
        for i in self._repo.getAll:
            if i.Deadline < datetime.date.today():
                if any(x.IdAssignment == i.Id and x.Grade == -1 for x in self._grades.getAll):
                    ok = 1
        if not ok:
            raise GradeException('There are no students that are late')
        l = []
        for i in self._repo.getAll:
            if i.Deadline < datetime.date.today():
                for j in self._grades.getAll:
                    if i.Id == j.IdAssignment and j.Grade == -1:
                        l.append(j)
        r = ''
        for i in l:
            r += str(i)
            r += '\n'
        return r

    def __str__(self):
        return str(self._repo)

