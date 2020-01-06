class Repository:
    def __init__(self):
        self._objects = []

    def store(self, obj):
        self._objects.append(obj)

    @property
    def getAll(self):
        return self._objects