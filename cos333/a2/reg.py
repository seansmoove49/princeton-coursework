#!/usr/bin/env python

#-----------------------------------------------------------------------
# reg.py
# Author: Sean Wang, Alina Chen
#-----------------------------------------------------------------------

import os
import sys
import socket
import argparse
import pickle
import PyQt5.QtWidgets
import PyQt5.QtCore



#-----------------------------------------------------------------------

#-----------------------------------------------------------------------
D = 0
N = 1
A = 2
T = 3
#-----------------------------------------------------------------------
def show_label(text):
    label = PyQt5.QtWidgets.QLabel(text)
    label.setAlignment(PyQt5.QtCore.Qt.AlignCenter) # prolly need to change this
    return label

def show_labels():
    dept_label = show_label("Dept:")
    number_label = show_label("Number:")
    area_label = show_label("Area:")
    title_label = show_label("Title:")
    return (dept_label, number_label, area_label, title_label)

def show_lineedit():
    dept_lineedit = PyQt5.QtWidgets.QLineEdit('')
    number_lineedit = PyQt5.QtWidgets.QLineEdit('')
    area_lineedit = PyQt5.QtWidgets.QLineEdit('')
    title_lineedit = PyQt5.QtWidgets.QLineEdit('')
    return (dept_lineedit, number_lineedit, area_lineedit, title_lineedit) 

def create_frame(labels, lineedits):
    control_frame_layout = PyQt5.QtWidgets.QGridLayout()
    control_frame_layout.addWidget(labels[D], 0, 0)
    control_frame_layout.addWidget(labels[N], 1, 0)
    control_frame_layout.addWidget(labels[A], 2, 0)
    control_frame_layout.addWidget(labels[T], 3, 0)

    control_frame_layout.addWidget(lineedits[D], 0, 1)
    control_frame_layout.addWidget(lineedits[N], 1, 1)
    control_frame_layout.addWidget(lineedits[A], 2, 1)
    control_frame_layout.addWidget(lineedits[T], 3, 1)

    control_frame_layout.addWidget()

    control_frame = PyQt5.QtWidgets.QFrame()
    control_frame.setLayout(control_frame_layout)
    
    
    return control_frame
    
def create_window(frame):
    window = PyQt5.QtWidgets.QMainWindow()
    window.setWindowTitle('Princeton University Class Search')
    window.setCentralWidget(frame)
    screen_size = PyQt5.QtWidgets.QDesktopWidget().screenGeometry()
    window.resize(screen_size.width()//2, screen_size.height()//2)
    return window

def show_courses(argv):
    app = PyQt5.QtWidgets.QApplication(argv)

    


def main():
    try:
        parser = argparse.ArgumentParser(description='''Server for 
        the registrar application''', allow_abbrev=False)

        parser.add_argument(dest='host', help='''the host on which the 
        server is running''')

        parser.add_argument(dest='port', help='''the port at which the 
        server is listening''', type=int)
        
        args = parser.parse_args()

        host = sys.argv[1]
        port = int(sys.argv[2])

        with socket.socket() as sock:
            sock.connect((host, port))
            # # write request to socket
            # out_flo = sock.makefile(mode = 'wb')
            # #pickle.dump(out_args, out_flo)
            # out_flo.flush()
            
            # # read request from socket
            # in_flo = sock.makefile(mode='rb')
            
            # in_args = pickle.load(in_flo)
            
            print('hi')
            show_courses(sys.argv)

            
            




    except Exception as ex:
        print(ex, file=sys.stderr)
        sys.exit(1)

#-----------------------------------------------------------------------

if __name__ == '__main__':
    main()
