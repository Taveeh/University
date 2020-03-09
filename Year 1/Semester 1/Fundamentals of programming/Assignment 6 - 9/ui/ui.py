import datetime


class UI:
    def __init__(self, serviceStudent, serviceAssignment, serviceGrade, servicUndo):
        self._students = serviceStudent
        self._assignments = serviceAssignment
        self._grades = serviceGrade
        self._undo = servicUndo
        self.string = ''

    # feature lab imre
    def newFeature(self, string):
        string = string.replace(self.string,'')
        return string

    @staticmethod
    def printMenu():
        print('\n')
        print('Student Lab Assignment')
        print('1. Add student')
        print('2. Remove student')
        print('3. Update student')
        print('4. List students')
        print('5. Add assignment')
        print('6. Remove assignment')
        print('7. Update assignment')
        print('8. List assignments')
        print('9. Add assignment to student or group of students')
        print('10. List grades')
        print('11. List ongoing assignments')
        print('12. Grade student for assignment')
        print('13. Sort students by grade for assignment')
        print('14. Show students that are late in handling assignments')
        print('15. Show students ordered by their school situation(descending)')
        print('16. Undo')
        print('17. Redo')
        print('0. Exit')
        print('\n')

    def addStudent(self):
        sid = input('Student ID: ')
        name = input('Student name: ')
        name = self.newFeature(name)
        group = input('Student group: ')
        self._students.store(sid, name, group)

    def removeStudent(self):
        sid = input('Student ID: ')
        self._students.delete(sid)

    def updateStudent(self):
        sid = input('Student ID: ')
        print('To change name press 1, to change group press 2 and for both press 3')
        cmd = input('Command: ')
        name = '0'
        group = '0'
        if cmd == '1':
            name = input('Name: ')
            name = self.newFeature(name)
        elif cmd == '2':
            group = input('Group: ')
        elif cmd == '3':
            name = input('Name: ')
            group = input('Group: ')
        else:
            print('Invalid command')
            return

        self._students.update(sid, name, group)

    def listStudents(self):
        print(self._students)

    def addAssignment(self):
        aid = input('Assignment ID: ')
        desc = input('Description: ')
        desc = self.newFeature(desc)
        day = input('Deadline day: ')
        month = input('Deadline month: ')
        year = input('Deadline year: ')
        self._assignments.store(aid, desc, day, month, year)

    def removeAssignment(self):
        aid = input('Assignment ID: ')
        self._assignments.delete(aid)

    def updateAssignment(self):
        aid = input('Assignment ID: ')
        print('To change description type 1, to change date type 2, to change both type 3')
        desc = '0'
        date = '0'
        cmd = input('Command: ')
        if cmd == '1':
            desc = input('Description: ')
            desc = self.newFeature(desc)
        elif cmd == '2':
            dd = input('Deadline day: ')
            dm = input('Deadline month: ')
            dy = input('Deadline year: ')
            date = datetime.date(int(dy), int(dm), int(dd))
        elif cmd == '3':
            desc = input('Description: ')
            desc = self.newFeature(desc)
            dd = input('Deadline day: ')
            dm = input('Deadline month: ')
            dy = input('Deadline year: ')
            date = datetime.date(int(dy), int(dm), int(dd))
        else:
            print('Invalid Command')
            return
        self._assignments.update(aid, desc, date)

    def listAssignments(self):
        print(self._assignments)

    def addAssignmentToStud(self):
        aid = input('Assignment ID: ')
        print('For student type 1, for group type 2')
        cmd = input('Command: ')
        if cmd == '1':
            sid = input('Student ID: ')
            self._grades.addAssignmentToStud(sid, aid)
        elif cmd == '2':
            sg = input('Group: ')
            self._grades.addAssignmentToGroup(sg, aid)
        else:
            print('Invalid command')

    def listGrades(self):
        for i in self._grades.getAssigned.getAll:
            if i.Grade != -1:
                print(i)

    def listOngoingAssignments(self):
        for i in self._grades.getAssigned.getAll:
            if i.Grade == -1:
                print(i)

    def gradeStud(self):
        sid = input('Student ID: ')
        aid = input('Assignment ID: ')
        grade = input('Grade: ')
        self._grades.gradeStud(sid, aid, grade)

    def sortAssignments(self):
        assign = input('Assignment ID: ')
        l = []
        print(l:= self._assignments.sortAssign(assign))
        # for i in l:
        #     if i.Grade != -1:
        #         print(i)

    def sortLate(self):
        print(l:= self._assignments.sortDeadline())
        # for i in l:
        #     print(self._students.find(i.IdStud))

    def sortAllStuds(self):
        print(reslist:= self._grades.sortStuds())
        # for i in range(len(reslist[0])):
        #     if reslist[1][reslist[0][i].Id] > 0:
        #         print('Student ' + str(reslist[0][i]) + ' has the average grade ' + str(format(reslist[1][reslist[0][i].Id], '.2f')))


    def undo(self):
        self._undo.undo()

    def redo(self):
        self._undo.redo()

    def start(self):
        self.string = input("What word do you want to replace? ")
        commands = {'1': self.addStudent,
                    '2': self.removeStudent,
                    '3': self.updateStudent,
                    '4': self.listStudents,
                    '5': self.addAssignment,
                    '6': self.removeAssignment,
                    '7': self.updateAssignment,
                    '8': self.listAssignments,
                    '9': self.addAssignmentToStud,
                    '10': self.listGrades,
                    '11': self.listOngoingAssignments,
                    '12': self.gradeStud,
                    '13': self.sortAssignments,
                    '14': self.sortLate,
                    '15': self.sortAllStuds,
                    '16': self.undo,
                    '17': self.redo}
        while True:
            self.printMenu()
            cmd = input('Command: ')
            if cmd == '0':
                return
            elif cmd in commands.keys():
                try:
                    commands[cmd]()
                except Exception as ex:
                    print(ex)
            else:
                print('Invalid command')





'''
# Initialise repository
StudentRepo = Repository(GenerateStudents())
AssignmentRepo = Repository(GenerateAssignments())
GradesRepo = Repository(GenerateGrades(StudentRepo.getAll, AssignmentRepo.getAll))


# Initialise service
u = Undo()
StudentService = ServiceStudent(StudentRepo, GradesRepo, u)
AssignmentService = ServiceAssignment(AssignmentRepo, GradesRepo, u)
GradesService = ServiceGrade(GradesRepo, StudentRepo, AssignmentRepo, u)
# Start UI
u = UI(StudentService, AssignmentService, GradesService, u)
u.start()
'''
