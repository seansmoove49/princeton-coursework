import sys
import PyQt5.QtWidgets

#-----------------------------------------------------------------------
def create_label(text):
    label = PyQt5.QtWidgets.QLabel(text)
    label.setAlignment(PyQt5.QtCore.Qt.AlignCenter) # prolly need to change this
    return label

#-----------------------------------------------------------------------

def main():
    app = PyQt5.QtWidgets.QApplication(sys.argv)

    dept_label = create_label("Dept:")
    number_label = create_label("Number:")
    area_label = create_label("Area:")
    title_label = create_label("Title:")

    