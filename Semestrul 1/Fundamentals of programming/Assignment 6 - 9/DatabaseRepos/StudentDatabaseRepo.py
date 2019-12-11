from utils.repo import Repository
import sqlite3
from sqlite3 import Error
from domain.Student import Student


class StudentSqlRepo(Repository):
    def __init__(self, databaseName, tableName):
        super().__init__()
        self._database = databaseName
        # self._tabel = tableName
        self._conn = self.create_connection()
        self._loadDatabase()

    def create_connection(self):
        conn = None
        try:
            conn = sqlite3.connect(self._database)
        except Error as e:
            raise e
        return conn

    def store(self, obj):
        Repository.store(self, obj)
        obj = (obj.Id, obj.Name, obj.Group)
        sql = '''INSERT INTO students (id, StudName, StudGroup) VALUES (?, ?, ?);'''
        current = self._conn.cursor()
        current.execute(sql, obj)
        self._conn.commit()

    def update(self, obj):
        Repository.update(self, obj)
        obj = (obj.Name, obj.Group, obj.Id)
        sql = '''UPDATE students
                SET StudName = ? ,
                    StudGroup = ? 
                WHERE id = ?'''
        current = self._conn.cursor()
        current.execute(sql, obj)
        self._conn.commit()

    def delete(self, objID):
        Repository.delete(self, objID)
        sql = 'DELETE FROM students WHERE id = ?'
        current = self._conn.cursor()
        current.execute(sql, (objID,))
        self._conn.commit()

    def _loadDatabase(self):
        current = self._conn.cursor()
        current.execute("SELECT * FROM students")
        rows = current.fetchall()
        for row in rows:
            self._objects.append(Student(row[0], row[1], row[2]))