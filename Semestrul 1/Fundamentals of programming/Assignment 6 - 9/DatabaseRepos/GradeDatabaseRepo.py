from utils.repo import Repository
import sqlite3
from sqlite3 import Error
from domain.Assignment import Assignment
from domain.Student import Student
from domain.Grade import Grade
import time
import datetime


class GradeSqlRepo(Repository):
    def __init__(self, database, table):
        super().__init__()
        self._database = database
        self._connection = self.create_connection()
        self._loadDatabase()

    def create_connection(self):
        conn = None
        try:
            conn = sqlite3.connect(self._database)
        except Error as e:
            raise e
        return conn

    def _loadDatabase(self):
        current = self._connection.cursor()
        current.execute("SELECT * FROM grades")
        rows = current.fetchall()
        for row in rows:
            self._objects.append(Grade(Student(row[1], '', ''), Assignment(row[2], '', ''), row[0], row[3]))

    def store(self, obj):
        Repository.store(self, obj)
        obj = (obj.Id, obj.IdStud, obj.IdAssignment, obj.Grade)
        sql = '''INSERT INTO grades (id, studId, assignId, grade) VALUES (?, ?, ?, ?)'''
        current = self._connection.cursor()
        current.execute(sql, obj)
        self._connection.commit()

    def update(self, obj):
        Repository.update(self, obj)
        obj = (obj.IdStud, obj.IdAssignment, obj.Grade, obj.Id)
        sql = '''UPDATE grades
                SET studId = ?,
                assignId = ?,
                grade = ?
                WHERE id = ?'''
        current = self._connection.cursor()
        current.execute(sql, obj)
        self._connection.commit()

    def delete(self, objID):
        Repository.delete(self, objID)
        current = self._connection.cursor()
        sql = 'DELETE FROM grades WHERE id = ?'
        current = self._connection.cursor()
        current.execute(sql, (objID,))
        self._connection.commit()
