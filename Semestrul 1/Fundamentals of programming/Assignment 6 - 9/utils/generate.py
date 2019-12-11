from domain.Student import Student
from domain.Assignment import Assignment
from domain.Grade import Grade
import random
import datetime
import names


def GenerateAssignments():
    """
    GenerateAssignments Function that generates a list of assignments randomly

    Returns:
        list -- list of assignments
    """
    idlist = []
    alist = []
    for i in range(20):
        sid = random.randint(201, 400)
        while sid in idlist:
            sid = random.randint(201, 400)
        idlist.append(sid)
    desclist = ['delete', 'insert', 'add', 'list', 'update', 'remove', 'implement', 'use classes', 'use modules',
                'sort', 'filter', 'undo', 'redo', 'test', 'create GUI', 'implement PyUnit tests', ' do something']
    for i in range(20):
        start_dt = datetime.date.today().replace(day=31, month=1, year=2019).toordinal()
        end_dt = datetime.date.today().replace(day=31, month=12, year=2020).toordinal()
        random_day = datetime.date.fromordinal(random.randint(start_dt, end_dt))
        alist.append(Assignment(idlist[i], random.choice(desclist), random_day))
    return alist


def GenerateStudents():
    """
    GenerateStudents Function that generates randomly a list of students

    Returns:
        list -- list of students
    """
    slist = []
    idlist = []
    for i in range(20):
        sid = random.randint(1, 200)
        while sid in idlist:
            sid = random.randint(1, 500)
        idlist.append(sid)
    for i in range(20):
        sgroup = random.randint(1, 12)
        sname = names.get_full_name()
        slist.append(Student(idlist[i], sname, sgroup))
    return slist


def GenerateGrades(studs, assigns):
    """
    Function that generates randomly a list of grades
    :return: list of grades
    """
    glist = []
    idlist = []
    for i in range(35):
        sid = random.choice(studs)
        aid = random.choice(assigns)
        gr = random.randint(-1, 10)
        while gr == 0:
            gr = random.randint(-1, 10)
        # gr = -1
        gid = random.randint(1000, 1999)
        while gid in idlist:
            gid = random.randint(1000, 1999)
        idlist.append(gid)
        glist.append(Grade(sid, aid, gid, gr))
        while any(x.IdAssignment == glist[i].IdAssignment and x.IdStud == glist[i].IdStud for x in glist if glist.index(x) != i):
            aid = random.choice(assigns)
            glist[i] = Grade(sid, aid, gid, gr)
    return glist


