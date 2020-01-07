import unittest


class SirIndian:
    def __init__(self, sir=None):
        if sir is None:
            self._list = []
        else:
            self._list = sir
        self._len = len(self._list)
        self._current = 0

    def __setitem__(self, index, value):
        self._list[index] = value

    def __getitem__(self, index):
        return self._list[index]

    def __delitem__(self, index):
        del self._list[index]
        self._len -= 1

    def __next__(self):
        self._current += 1
        if self._current <= self._len:
            return self._list[self._current - 1]
        raise StopIteration

    def __iter__(self):
        for i in self._list:
            yield i

    def __len__(self):
        return self._len

    def append(self, obj):
        self._list.append(obj)
        self._len += 1

    def __str__(self):
        return str(self._list)

    def remove(self, obj):
        self._list.remove(obj)
        self._len -= 1

    def index(self, obj):
        return self._list.index(obj)

    def insert(self, idx, obj):
        self._list.insert(idx, obj)


def sortFunction(array, key=lambda x, y: x < y, reverse=False):
    # Stooge Sort
    """
    This sorting algorithm swaps first with last element if first > last, then recursively sorts the first 2/3 of the
    array, then last 2/3 of the array, and then first 2/3 again
    """
    initial = 0
    final = len(array) - 1
    array = stoogeSort(array, initial, final, key)
    if reverse is True:
        return array[::-1]
    return array


def stoogeSort(array, initial, final, key):
    if not key(array[initial], array[final]):
        aux = array[initial]
        array[initial] = array[final]
        array[final] = aux

    # If len(array) == 2 stop, else recursion
    if final - initial + 1 > 2:
        aux = (final - initial + 1) // 3
        # first 2/3
        stoogeSort(array, initial, final - aux, key)
        # second 2/3
        stoogeSort(array, initial + aux, final, key)
        # third 2/3 - for verification
        stoogeSort(array, initial, final - aux, key)

    return array


def filterFunction(array, function=lambda x: x == x):
    index = 0
    length = len(array)
    while index < length:
        if not function(array[index]):
            del array[index]
            length -= 1
            continue
        index += 1
    return array


class SirIndianTest(unittest.TestCase):
    def test_len(self):
        arr = SirIndian([123, 234, 345, 456, 567, 678, 789, 890])
        self.assertEqual(len(arr), 8)

    def test_setItem(self):
        arr = SirIndian([123, 234, 345, 456, 567, 678, 789, 890])
        arr[3] = 12
        self.assertEqual(arr[3], 12)

    def test_delItem(self):
        arr = SirIndian([123, 234, 345, 456, 567, 678, 789, 890])
        del arr[3]
        print(arr)
        self.assertEqual(len(arr), 7)
        self.assertEqual(arr[3], 567)

    def test_iteration(self):
        sir = [123, 234, 345, 456, 567, 678, 789, 890]
        arr = SirIndian(sir)
        print(arr)
        for i in arr:
            print(i)
            self.assertGreater(i, 0)

    def test_append(self):
        arr = SirIndian([123, 234, 345, 456, 567, 678, 789, 890])
        arr.append(9999)
        print('Array:', arr)
        print('Length:', len(arr))
        self.assertEqual(len(arr), 9)
        self.assertEqual(arr[-1], 9999)

    def test_remove(self):
        arr = SirIndian([123, 234, 345, 456, 567, 678, 789, 890])
        arr.remove(123)
        self.assertEqual(arr[0], 234)


# sir = [123, 234, 345, 456, 567, 678, 789, 890]
# a = SirIndian()
# print(a)
# print()
# a.append(123)
# a.append(234)
# a.append(345)
# a.append(456)
# a.append(567)
# a.append(678)
# a.append(789)
# a.append(890)
# print(a)
# print()
# print(a[2])
# print()
# a.append(777)
# print(a[7])
# print()
# print(len(a))
# print()
# for i in a:
#     print(i)
# print()
# del a[3]
# print(a)
# print()
# a[5] = 12
# print(a)
# b = sortFunction(a, lambda x, y: x > y)
# print(a)
# print(b)
# a.append(19992)
# b = filterFunction(a, lambda x: x % 2 == 0)
# print(a)
# print(b)
# b = sortFunction(sir)
# print(b)