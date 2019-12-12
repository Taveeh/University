class Plane:
    def __init__(self, center):
        self._center = center
        self.plane = self._createPlane()

    def _createPlane(self):
        cx = self._center.X
        cy = self._center.Y
        coords = [self._center,
                  Point(cx - 2, cy - 1),
                  Point(cx - 1, cy - 1),
                  Point(cx, cy - 1),
                  Point(cx + 1, cy - 1),
                  Point(cx + 2, cy - 1),
                  Point(cx, cy - 2),
                  Point(cx - 1, cy - 3),
                  Point(cx, cy - 3),
                  Point(cx + 1, cy - 3)]
        return coords


class Point:
    def __init__(self, x, y):
        self.X = x
        self.Y = y

