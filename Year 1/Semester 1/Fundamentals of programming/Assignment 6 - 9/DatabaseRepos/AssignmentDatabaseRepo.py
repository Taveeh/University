from utils.repo import Repository
import sqlite3
from sqlite3 import Error
from domain.Assignment import Assignment
import time
import datetime


class AssignmentSqlRepo(Repository):
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
        current.execute('SELECT * FROM assignments')
        rows = current.fetchall()
        for row in rows:
            timp = datetime.datetime.fromtimestamp(row[2])
            self._objects.append(Assignment(row[0], row[1], timp))

    def store(self, obj):
        Repository.store(self, obj)
        obj = (obj.Id, obj.Description, time.mktime(obj.Deadline.timetuple()))
        sql = '''INSERT INTO assignments (id, description, deadline) VALUES (?, ?, ?)'''
        current = self._connection.cursor()
        current.execute(sql, obj)
        self._connection.commit()

    def update(self, obj):
        Repository.update(self, obj)
        obj = (obj.Description, time.mktime(obj.Deadline.timetuple()), obj.Id)
        sql = '''UPDATE assignments
                        SET description = ? ,
                            deadline = ? 
                        WHERE id = ?'''
        current = self._conn.cursor()
        current.execute(sql, obj)
        self._connection.commit()

    def delete(self, objID):
        Repository.delete(self, objID)
        sql = 'DELETE FROM assignments WHERE id = ?'
        current = self._connection.cursor()
        current.execute(sql, (objID,))
        self._connection.commit()
