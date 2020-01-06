class RepositoryException(Exception):
    def __init__(self, message):
        super().__init__(message)


class StudentException(Exception):
    def __init__(self, message):
        super().__init__(message)


class AssignmentException(Exception):
    def __init__(self, message):
        super().__init__(message)


class GradeException(Exception):
    def __init__(self, message):
        super().__init__(message)

