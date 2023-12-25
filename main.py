import sys
import subprocess
import logging

from PyQt5 import QtWidgets
from PyQt5.QtWidgets import *

from myform import Ui_MainWindow


class MyWindow(QtWidgets.QMainWindow):
    def __init__(self) -> None:
        """
        Constructor for initializing variables
        """
        super(MyWindow, self).__init__()
        self.logger = self.create_logger()
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
        self.count_click = 0
        self.ui.pushButton.clicked.connect(self.btn_check)

    def btn_check(self) -> None:
        """
        The method checks whether the number
        of runs passes the limit value
        """
        self.count_click += 1
        if self.count_click <= 3:
            self.btn_clicked()
        else:
            self.btn_error()

    def btn_clicked(self) -> None:
        """
        The method runs the main cpp file and 
        outputs the result to the output window
        """
        mytext = self.ui.textEdit.toPlainText()
        try:
            with open('text_code.txt', 'w+') as f:
                f.write(mytext)
                self.logger.info(f"writing data in: {f}")
        except FileNotFoundError:
            self.logger.warning(f"File '{f}' was not found")
        try:
            name_cpp = "interpretator.cpp"
            subprocess.run(["g++", name_cpp, "-o", "program"])
            self.logger.info(f"running cpp-file: {name_cpp}")
            subprocess.run('./program')
        except Exception as e:
            self.logger.warning(
                "the occurrence of an error when running of cpp-file: " + f"{str(e)}")
        output = []
        try:
            with open('text_out.txt', 'r') as f:
                output = f.readlines()
                self.logger.info(f"reading data from: {f}")
        except FileNotFoundError:
            self.logger.warning(f"File '{f}' was not found")
        out_string = ""
        for i in output:
            out_string += i
        self.ui.textEdit_2.setText(out_string)
        self.logger.info(f"writing data in window app")
        self.ui.label.adjustSize()

    def btn_error(self) -> None:
        """
        The method displays an error window when 
        the number of launch attempts has exceeded the limit
        """
        self.logger.info(
            f"number of launch attempts exceeded the allowed limit")
        self.msg = QMessageBox()
        self.msg.setIcon(QMessageBox.Critical)
        self.msg.setText(
            "ОШИБКА: Количество запусков превысило\n допустимо значение")
        self.msg.setWindowTitle("Critical MessageBox")
        self.msg.setStandardButtons(QMessageBox.Ok | QMessageBox.Cancel)
        retval = self.msg.exec_()

    def create_logger(self) -> logging.LoggerAdapter:
        """
        The method creating logger for event tracking
        """
        logger = logging.getLogger("logger")
        logger.setLevel(logging.INFO)
        file = logging.FileHandler('py_logger.log')
        file.setLevel(logging.DEBUG)
        formatter = logging.Formatter(
            '[%(asctime)s]: [%(name)s] - [%(levelname)s] - [%(message)s]')
        file.setFormatter(formatter)
        logger.addHandler(file)
        return logger


if __name__ == '__main__':
    try:
        app = QtWidgets.QApplication([])
        application = MyWindow()
        application.show()
        sys.exit(app.exec())
    except Exception as e:
        logging.warning("the occurrence of an error: " + f"{str(e)}")
