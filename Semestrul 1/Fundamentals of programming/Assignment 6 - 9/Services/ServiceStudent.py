from utils.exceptions import StudentException
from domain.Student import Student
from Services.undo import FunctionCall, Operation, CascadeOperation
from copy import deepcopy


class ServiceStudent:
    def __init__(self, studRepo, gradesRepo, ServiceUndo):
        self._repo = studRepo
        self._grades = gradesRepo
        self._undo = ServiceUndo

    def store(self, sid, name, group):
        '''
        store Function to store a student
        
        Arguments:
            sid {string} -- id of student
            name {strinf} -- name of studebt
            group {string} -- group of student
        
        Raises:
            StudentException: ID must be a number
            StudentException: ID already exists
            StudentException: Group must be a number
        
        Returns:
            student -- stored student
        '''
        if not sid.isdigit():
            raise StudentException('ID must be a number')
        sid = int(sid)
        elem = self._repo.find(sid)
        if elem is not None:
            raise StudentException('The ID already exists')
        if not group.isdigit():
            raise StudentException('Group must be a number')
        group = int(group)
        stud = Student(sid, name, group)
        self._repo.store(stud)
        redo = FunctionCall(self._repo.store, stud)
        undo = FunctionCall(self._repo.delete, sid)
        op = Operation(undo, redo)
        self._undo.recordOperation(op)
        return stud

    def delete(self, sid):
        '''
        delete Function to delete a student from list of students
        
        Arguments:
            sid {string} -- id of student
        
        Raises:
            StudentException: Invalid ID
        '''
        if type(sid) != int:
            if not sid.isdigit():
                raise StudentException('Invalid ID')
        sid = int(sid)
        stud = self._repo.delete(sid)
        casc = CascadeOperation()
        undo = FunctionCall(self._repo.store, stud)
        redo = FunctionCall(self._repo.delete, sid)
        op = Operation(undo, redo)
        casc.append(op)
        le = len(self._grades.getAll)
        i = 0
        nr = 0
        while i < le:
            if self._grades.getAll[i].IdStud == stud.Id:
                redo1 = FunctionCall(self._grades.delete, self._grades.getAll[i].Id)
                undo1 = FunctionCall(self._grades.store, self._grades.getAll[i])
                casc.append(Operation(undo1, redo1))
                self._grades.delete(self._grades.getAll[i].Id)
                le -= 1
                continue
            i += 1
        self._undo.recordOperation(casc)

    def find(self, s):
        '''
        find Function to find an item
        
        Arguments:
            s {int} -- id
        
        Returns:
            student -- student found
        '''
        return self._repo.find(s)

    def update(self, sid, name, group):
        '''
        update Function to update a student
        
        Arguments:
            sid {strign} -- id
            name {string} -- name
            group {string} -- group
        
        Raises:
            StudentException: Invalid data
            StudentException: Student does not exist
        '''
        if not sid.isdigit() or not group.isdigit():
            raise StudentException('Invalid data')
        sid = int(sid)
        group = int(group)
        stud = self._repo.find(sid)
        if stud is None:
            raise StudentException('Student does not exist')
        undo = FunctionCall(self._repo.update, deepcopy(stud))
        if name == '0':
            stud.Group = group
            redo = FunctionCall(self._repo.update, stud)
        elif group == 0:
            stud.Name = name
            redo = FunctionCall(self._repo.update, stud)
        else:
            stud.Name = name
            stud.Group = group
            redo = FunctionCall(self._repo.update, stud)
        op = Operation(undo, redo)
        self._undo.recordOperation(op)
        self._repo.update(stud)

    def __str__(self):
        return str(self._repo)



