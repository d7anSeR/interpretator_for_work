import sys
import ctypes
import subprocess


from PyQt5 import QtWidgets
from PyQt5.QtWidgets import *
from myform import Ui_MainWindow

class mywindow(QtWidgets.QMainWindow):
    def __init__(self):
        super(mywindow, self).__init__()
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
        self.count_click = 0
        self.ui.pushButton.clicked.connect(self.btnCheck)

    def btnCheck(self):
        self.count_click += 1
        if self.count_click <= 3:
            self.btnClicked()
        else:
            self.btnError()

    def btnClicked(self):
        mytext = self.ui.textEdit.toPlainText()
        with open('text_code.txt', 'w+') as f:
            f.write(mytext)
        subprocess.run(["g++", "interpretator.cpp", "-o", "program"])
        subprocess.run('./program')
        output = []
        with open('text_out.txt', 'r') as f:
            output = f.readlines()
        string = ""
        for i in output:
            string += i
        self.ui.textEdit_2.setText(string)
        self.ui.label.adjustSize()

    def btnError(self):
        self.msg = QMessageBox() 
        self.msg.setIcon(QMessageBox.Critical) 
        self.msg.setText("ОШИБКА: Количество запусков превысило\n допустимо значение") 
        self.msg.setWindowTitle("Critical MessageBox") 
        self.msg.setStandardButtons(QMessageBox.Ok | QMessageBox.Cancel) 
        retval = self.msg.exec_()
        # sys.exit(app.exec_())
 
 
app = QtWidgets.QApplication([])
application = mywindow()
application.show()


sys.exit(app.exec())
# if __name__ == '__main__':
#     app = QApplication(sys.argv)
#     ex = MainWindow()
#     sys.exit(app.exec_())