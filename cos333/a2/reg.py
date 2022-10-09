#!/usr/bin/env python

#-----------------------------------------------------------------------
# reg.py
# Author: Sean Wang, Alina Chen
#-----------------------------------------------------------------------

import sys
import socket
import argparse
import pickle
import PyQt5.QtWidgets
import PyQt5.QtCore
import PyQt5.QtGui



#-----------------------------------------------------------------------


D = 0
N = 1
A = 2
T = 3

def socket_request(host, port, out_args):
    with socket.socket() as sock:
        sock.connect((host, port))
        out_flo = sock.makefile(mode='wb')
        pickle.dump(out_args, out_flo)
        out_flo.flush()
        print('Wrote request to server at ' + host + ':' +
            str(port))
        in_flo = sock.makefile(mode='rb')
        in_args = pickle.load(in_flo)
        return in_args


def create_label(text):
    label = PyQt5.QtWidgets.QLabel(text)
    label.setAlignment(PyQt5.QtCore.Qt.AlignRight | PyQt5.QtCore.Qt.AlignVCenter) 
    return label

def create_labels():
    dept_label = create_label("Dept:")
    number_label = create_label("Number:")
    area_label = create_label("Area:")
    title_label = create_label("Title:")
    return (dept_label, number_label, area_label, title_label)

def create_lineedits():
    dept_lineedit = PyQt5.QtWidgets.QLineEdit('')
    number_lineedit = PyQt5.QtWidgets.QLineEdit('')
    area_lineedit = PyQt5.QtWidgets.QLineEdit('')
    title_lineedit = PyQt5.QtWidgets.QLineEdit('')
    return (dept_lineedit, number_lineedit, area_lineedit, title_lineedit) 


def create_controlframe(labels, lineedits, button):
    control_frame_layout = PyQt5.QtWidgets.QGridLayout()
    control_frame_layout.addWidget(labels[D], 0, 0)
    control_frame_layout.addWidget(labels[N], 1, 0)
    control_frame_layout.addWidget(labels[A], 2, 0)
    control_frame_layout.addWidget(labels[T], 3, 0)

    control_frame_layout.addWidget(lineedits[D], 0, 1)
    control_frame_layout.addWidget(lineedits[N], 1, 1)
    control_frame_layout.addWidget(lineedits[A], 2, 1)
    control_frame_layout.addWidget(lineedits[T], 3, 1)

    control_frame_layout.addWidget(button, 0,2,4,1)

    control_frame = PyQt5.QtWidgets.QFrame()
    control_frame.setLayout(control_frame_layout)
    return control_frame
    

def create_button():
    button = PyQt5.QtWidgets.QPushButton("Submit")
    return button
def create_list():
    list = PyQt5.QtWidgets.QListWidget()
    list.setFont(PyQt5.QtGui.QFont("Courier", 10))
    return list
def create_listframe(list):
    grid_layout = PyQt5.QtWidgets.QGridLayout()
    grid_layout.addWidget(list)
    list_frame = PyQt5.QtWidgets.QFrame()
    list_frame.setLayout(grid_layout)
    return list_frame 
    
def create_centralframe(labels, lineedits, button, list):
    control_frame = create_controlframe(labels, lineedits, button)
    list_frame = create_listframe(list)   

    grid_layout = PyQt5.QtWidgets.QGridLayout()
    grid_layout.addWidget(control_frame, 0, 0)
    grid_layout.addWidget(list_frame, 1, 0)
    
    frame = PyQt5.QtWidgets.QFrame()
    frame.setLayout(grid_layout)

    return frame
    
def create_window(central_frame):
    window = PyQt5.QtWidgets.QMainWindow()
    window.setWindowTitle('Princeton University Class Search')
    window.setCentralWidget(central_frame)
    screen_size = PyQt5.QtWidgets.QDesktopWidget().screenGeometry()
    window.resize(screen_size.width()//2, screen_size.height()//2)
    return window

def show_courses(argv, host, port):
    app = PyQt5.QtWidgets.QApplication(argv)

    labels = create_labels()
    lineedits = create_lineedits()
    button = create_button()
    list = create_list()
    
    central_frame = create_centralframe(labels, lineedits, button, list)
    window = create_window(central_frame)
    
    window.show()

    # necessary as cannot input function with parameters
    def update_list_submit():
        update_list(window, lineedits, list, host, port)

    def course_details_clicked(list_item):
        show_course_details(list_item, window, host, port)
   
     
     # handle new searches when user clicks submit
    button.clicked.connect(update_list_submit)
    # handle new searches when users hits enter button
    for lineedit in lineedits:
        lineedit.returnPressed.connect(update_list_submit)
    # handle when user activates course details
    list.itemActivated.connect(course_details_clicked)


    # show initial list on start up
    update_list(window, lineedits, list, host, port)


     

    exit(app.exec_())


def show_error(window, error_message):
    PyQt5.QtWidgets.QMessageBox.critical(window, 
    'Server Error', error_message)

def update_list(window, lineedits, list, host, port):
    out_args = {
        "d": lineedits[D].text(),
        "n": lineedits[N].text(),
        "a": lineedits[A].text(),
        "t": lineedits[T].text(),
        "request": "query_courses"
    }
    # clear the list
    list.clear()

    in_args = socket_request(host, port, out_args)

    if in_args["error"]:
        show_error(window, in_args["result"])
    else:
        list.addItems(in_args["result"])
    
    # highlight first row in list
    list.setCurrentRow(0)
    
def show_course_details(list_item, window, host, port):
    class_id = list_item.text().split()[0]
    out_args = {"request": "query_details", "class_id": class_id}
    in_args = socket_request(host, port, out_args)

    if in_args['error']:
        show_error(window, in_args["result"])
    else:
        PyQt5.QtWidgets.QMessageBox.information(window, 'Class Details', in_args["result"])

def main():
    try:
        parser = argparse.ArgumentParser(description='''Client for 
        the registrar application''', allow_abbrev=False)

        parser.add_argument(dest='host', help='''the host on which the 
        server is running''')

        parser.add_argument(dest='port', help='''the port at which the 
        server is listening''', type=int)
        
        args = parser.parse_args()

        host = args.host
        port = int(args.port)
        
        show_courses(sys.argv, host, port)    

    except Exception as ex:
        print(f"{sys.argv[0]}: {ex}", file=sys.stderr)
        sys.exit(1)

#-----------------------------------------------------------------------

if __name__ == '__main__':
    main()
