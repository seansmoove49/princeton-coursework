import sys
import PyQt5.QtWidgets

#-----------------------------------------------------------------------
D = 0
N = 1
A = 2
T = 3
#-----------------------------------------------------------------------
def create_label(text):
    label = PyQt5.QtWidgets.QLabel(text)
    label.setAlignment(PyQt5.QtCore.Qt.AlignCenter) # prolly need to change this
    return label
#-----------------------------------------------------------------------
def create_labels():
    dept_label = create_label("Dept:")
    number_label = create_label("Number:")
    area_label = create_label("Area:")
    title_label = create_label("Title:")
    return (dept_label, number_label, area_label, title_label)
#-----------------------------------------------------------------------
def create_lineedits():
    dept_lineedit = PyQt5.QtWidgets.QLineEdit('')
    number_lineedit = PyQt5.QtWidgets.QLineEdit('')
    area_lineedit = PyQt5.QtWidgets.QLineEdit('')
    title_lineedit = PyQt5.QtWidgets.QLineEdit('')
    return (dept_lineedit, number_lineedit, area_lineedit, title_lineedit) 
#-----------------------------------------------------------------------

def create_controlframe(labels, lineedits):
    control_frame_layout = PyQt5.QtWidgets.QGridLayout
    control_frame_layout.addWidget(labels[D], 0, 0)
    control_frame_layout.addWidget(labels[N], 1, 0)
    control_frame_layout.addWidget(labels[A], 2, 0)
    control_frame_layout.addWidget(labels[T], 3, 0)

    control_frame_layout.addWidget(lineedits[D], 0, 1)
    control_frame_layout.addWidget(lineedits[N], 1, 1)
    control_frame_layout.addWidget(lineedits[A], 2, 1)
    control_frame_layout.addWidget(lineedits[T], 3, 1)

    control_frame = PyQt5.QtWidgets.QFrame()
    control_frame.setLayout(control_frame_layout)
    return control_frame
    
#-----------------------------------------------------------------------

def show_courses():
    app = PyQt5.QtWidgets.QApplication(sys.argv)

   

