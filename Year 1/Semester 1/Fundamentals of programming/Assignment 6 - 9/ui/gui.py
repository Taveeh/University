from PyQt5 import QtWidgets, QtCore
import datetime


def screenSize():
    for display in range(QtWidgets.QDesktopWidget().screenCount()):
        size = QtWidgets.QDesktopWidget().screenGeometry(display)
        return (size.width(), size.height())


class Item:
    def __init__(self, title, actionType, textfieldCount=None, action=None, onClick=None, labels=[], toShow=None):
        self.title = title
        self.actionType = actionType
        self.textfieldCount = textfieldCount
        self.action = action
        self.onClick = onClick
        self.labels = labels
        self.toShow = toShow


class ButtonStack(QtWidgets.QWidget):
    def __init__(self, function, serviceStudent, serviceAssign, serviceGrade, serviceUndo):
        super().__init__()
        self.function = function
        self._students = serviceStudent
        self._assigns = serviceAssign
        self._grades = serviceGrade
        self._undo = serviceUndo
        vbox = QtWidgets.QVBoxLayout()
        items = [
            Item(
                title="Add Student",
                actionType="edit",
                textfieldCount=3,
                onClick=lambda textArray: self._students.store(textArray[0], textArray[1], textArray[2]),
                labels=["ID", "Name", "Group"]
            ),
            Item(
                title="Remove Student",
                actionType="edit",
                textfieldCount=1,
                onClick=lambda textArray: self._students.delete(textArray[0]),
                labels=["ID"]
            ),
            Item(
                title="Update Student Name",
                actionType="edit",
                textfieldCount=2,
                onClick=lambda params: self._students.update(params[0], params[1], '0'),
                labels=["ID", "Name"]
            ),
            Item(
                title="Update Student Group",
                actionType="edit",
                textfieldCount=2,
                onClick=lambda params: self._students.update(params[0], '0', params[1]),
                labels=["ID", "Group"]
            ),
            Item(
                title="Update Student",
                actionType="edit",
                textfieldCount=3,
                onClick=lambda params: self._students.update(params[0], params[1], params[2]),
                labels=["ID", "Name", "Group"]
            ),
            Item(
                title="Show Students",
                actionType="show",
                toShow=lambda students=self._students: str(students)
            ),
            Item(
                title="Add Assignments",
                actionType="edit",
                textfieldCount=5,
                onClick=lambda params: self._assigns.store(params[0], params[1], params[2], params[3], params[4]),
                labels=['ID', 'Description', 'Deadline day', 'Deadline month', 'Deadline year']

            ),
            Item(
                title="Remove assignment",
                actionType="edit",
                textfieldCount=1,
                onClick=lambda params: self._assigns.delete(params[0]),
                labels=['ID']
            ),
            Item(
                title="Update assignment description",
                actionType="edit",
                textfieldCount=2,
                onClick=lambda params: self._assigns.update(params[0], params[1], '0'),
                labels=['ID', 'Description']
            ),
            Item(
                title="Update assignment deadline",
                actionType="edit",
                textfieldCount=4,
                onClick=lambda params: self._assigns.update(params[0], '0',
                                                            datetime.date(int(params[3]), int(params[2]),
                                                                          int(params[1]))),
                labels=['ID', 'Deadline day', 'Deadline month', 'Deadline year']
            ),
            Item(
                title="Update assignment",
                actionType="edit",
                textfieldCount=5,
                onClick=lambda params: self._assigns.update(params[0], params[1],
                                                            datetime.date(int(params[4]), int(params[3]),
                                                                          int(params[2]))),
                labels=['ID', 'Description', 'Deadline day', 'Deadline month', 'Deadline year']
            ),
            Item(
                title="Show Assignments",
                actionType="show",
                toShow=lambda assignments=self._assigns: str(assignments)
            ),
            Item(
                title="Add assignment to student",
                actionType="edit",
                textfieldCount=2,
                onClick=lambda params: self._grades.addAssignmentToStud(params[0], params[1]),
                labels=['Student ID', 'Assignment ID']
            ),
            Item(
                title="Add assignment to group",
                actionType="edit",
                textfieldCount=2,
                onClick=lambda params: self._grades.addAssignmentToGroup(params[0], params[1]),
                labels=['Group', 'Assignment ID']
            ),
            Item(
                title='List Grades',
                actionType='show',
                toShow=lambda grades=self._grades: grades.getGraded()
            ),
            Item(
                title='List Ongoing Assignments',
                actionType='show',
                toShow=lambda grades=self._grades: grades.getUnGraded()
            ),
            Item(
                title='Grade student',
                actionType='edit',
                textfieldCount=3,
                onClick=lambda params: self._grades.gradeStud(params[0], params[1], params[2]),
                labels=['Student ID', 'Assignment ID', 'Grade']
            ),
            Item(
                title='Sort students by grade for assignment - ????',
                actionType='filter',
                textfieldCount=1,
                onClick=lambda text: self._assigns.sortAssign(text),
                labels=['Assignment'],
            ),
            Item(
                title='Show students that are late in handling assignments',
                actionType='show',
                toShow=lambda assig=self._assigns: assig.sortDeadline(),
            ),
            Item(
                title='Show students ordered by their school situation',
                actionType='show',
                toShow=lambda grades=self._grades: grades.sortStuds()
            ),
            Item(
                title='Undo',
                actionType='undo',
                action=self._undo.undo
            ),
            Item(
                title='Redo',
                actionType='undo',
                action=self._undo.redo
            )



        ]
        for item in items:
            button = self.renderButton(item)
            vbox.addWidget(button)
        self.setLayout(vbox)

    def renderButton(self, item):
        button = QtWidgets.QPushButton(item.title, self)
        button.clicked.connect(lambda: self.onClick(item))
        return button

    @QtCore.pyqtSlot()
    def onClick(self, item):
        self.function(item)


class Home(QtWidgets.QMainWindow):
    def __init__(self, serviceStudent, serviceAssign, serviceGrade, undo):
        super().__init__()
        self.setWindowTitle("App")
        (width, height) = screenSize()
        self.setGeometry(0, 0, width, height)
        self._students = serviceStudent
        self._assignments = serviceAssign
        self._grades = serviceGrade
        self._undo = undo
        self._initUI()


    def _initUI(self):
        self.stackedWidget = QtWidgets.QStackedWidget()
        self.setCentralWidget(self.stackedWidget)
        self.buttonStack = ButtonStack(lambda action: self.navigate(action), self._students, self._assignments,
                                       self._grades, self._undo)
        self.editPage = EditPage(
            back=lambda: self.stackedWidget.setCurrentWidget(self.buttonStack))
        self.infoPage = InfoPage(
            back=lambda: self.stackedWidget.setCurrentWidget(self.buttonStack))
        self.filterPage = FilterPage(
            back=lambda: self.stackedWidget.setCurrentWidget(self.buttonStack))
        self.stackedWidget.addWidget(self.buttonStack)
        self.stackedWidget.addWidget(self.editPage)
        self.stackedWidget.addWidget(self.infoPage)
        self.stackedWidget.addWidget(self.filterPage)
        self.stackedWidget.setCurrentWidget(self.buttonStack)

    def navigate(self, item):
        if item.action is not None:
            try:
                item.action()
            except Exception as e:
                box = QtWidgets.QMessageBox()
                box.setText((str(e)))
                box.exec_()
        if item.actionType == "edit":
            self.editPage.labels = item.labels
            self.editPage.onClick = item.onClick
            self.editPage.textfieldCount = item.textfieldCount
            self.stackedWidget.setCurrentWidget(self.editPage)
        elif item.actionType == "show":
            try:
                self.infoPage.text = item.toShow()
                self.stackedWidget.setCurrentWidget(self.infoPage)
            except Exception as e:
                box = QtWidgets.QMessageBox()
                box.setText(str(e))
                box.exec_()
        elif item.actionType == 'filter':
            self.filterPage.textfieldLabelText = item.labels[0]
            self.filterPage.onClick = item.onClick
            self.stackedWidget.setCurrentWidget(self.filterPage)


class FilterPage(QtWidgets.QWidget):
    @property
    def text(self):
        return self._text

    @text.setter
    def text(self, newValue):
        self.toShowLabel.setText(newValue)
        self.toShowLabel.repaint()

    @property
    def textfieldLabelText(self):
        return self._textfieldLabelText

    @textfieldLabelText.setter
    def textfieldLabelText(self, newValue):
        self.textfieldLabel.setText(newValue)

    def __init__(self, back):
        super().__init__()
        self.back = back
        vbox = QtWidgets.QVBoxLayout()

        backButton = QtWidgets.QPushButton("Back", self)
        backButton.clicked.connect(self.back)
        vbox.addWidget(backButton)

        itemHbox = QtWidgets.QHBoxLayout()
        self.textfield = QtWidgets.QLineEdit(self)
        self.textfieldLabel = QtWidgets.QLabel()
        self.textfieldLabel.setMinimumWidth(100)
        itemHbox.addWidget(self.textfieldLabel)
        itemHbox.addWidget(self.textfield)
        vbox.addLayout(itemHbox)

        self.toShowLabel = QtWidgets.QLabel()
        vbox.addWidget(self.toShowLabel)

        showButton = QtWidgets.QPushButton("Show", self)
        showButton.clicked.connect(self.onShowClick)
        vbox.addWidget(showButton)
        self.setLayout(vbox)

    @QtCore.pyqtSlot()
    def onShowClick(self):
        if self.onClick is not None:
            try:
                self.text = self.onClick(self.textfield.text())
            except Exception as e:
                box = QtWidgets.QMessageBox()
                box.setText(str(e))
                box.exec_()


class InfoPage(QtWidgets.QWidget):
    @property
    def text(self):
        return self._text

    @text.setter
    def text(self, newValue):
        self.label.setText(newValue)

    def __init__(self, back):
        super().__init__()
        self.back = back
        vbox = QtWidgets.QVBoxLayout()

        backButton = QtWidgets.QPushButton("Back", self)
        backButton.clicked.connect(self.back)
        vbox.addWidget(backButton)

        self.label = QtWidgets.QLabel()
        vbox.addWidget(self.label)

        self.setLayout(vbox)


class EditPage(QtWidgets.QWidget):
    @property
    def textfieldCount(self):
        return self._textfieldCount

    @textfieldCount.setter
    def textfieldCount(self, newValue):
        if newValue is not None:
            self.renderTextfields(newValue)

    def __init__(self, back):
        super().__init__()
        self._textfieldCount = None
        self.textfields = []
        self.labels = []
        self.back = back

        self.vbox = QtWidgets.QVBoxLayout()

        backButton = QtWidgets.QPushButton("Back", self)
        backButton.clicked.connect(self.back)
        self.vbox.addWidget(backButton)

        okButton = QtWidgets.QPushButton("OK", self)
        okButton.clicked.connect(self.onOkClick)
        self.vbox.addWidget(okButton)

        self.setLayout(self.vbox)

    def deleteItemsOfLayout(self, layout, hasButtons):
        if layout is not None:
            r = reversed(range(1, layout.count() - 1)
                         ) if hasButtons else reversed(range(layout.count()))
            for i in r:
                item = layout.takeAt(i)
                widget = item.widget()
                if widget is not None:
                    widget.setParent(None)
                else:
                    self.deleteItemsOfLayout(item.layout(), hasButtons=False)

    def renderTextfields(self, count):
        self.deleteItemsOfLayout(self.vbox, hasButtons=True)
        self.textfields = []
        for i in range(count):
            itemHbox = QtWidgets.QHBoxLayout()
            textfield = QtWidgets.QLineEdit(self)
            label = QtWidgets.QLabel()
            label.setText(self.labels[i])
            label.setMinimumWidth(100)
            itemHbox.addWidget(label)
            itemHbox.addWidget(textfield)
            self.textfields.append(textfield)
            self.vbox.insertLayout(self.vbox.count() - 1, itemHbox)

    @QtCore.pyqtSlot()
    def onOkClick(self):
        if self.onClick is not None:
            try:
                self.onClick(list(map(lambda textfield: textfield.text(), self.textfields)))
                self.back()
            except Exception as e:
                box = QtWidgets.QMessageBox()
                box.setText(str(e))
                box.exec_()

    @QtCore.pyqtSlot()
    def back(self):
        self.back()

