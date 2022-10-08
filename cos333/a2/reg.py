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
        port = sys.argv[2]

        with socket.socket() as sock:
            sock.connect((host, port))
            # write request to socket
            out_flo = sock.makefile(mode = 'wb')
            #pickle.dump(out_args, out_flo)
            out_flo.flush()
            
            # read request from socket
            in_flo = sock.makefile(mode='rb')
            
            in_args = pickle.load(in_flo)

            app = PyQt5.QtWidgets.QApplication(sys.argv)
            




    except Exception as ex:
        print(ex, file=sys.stderr)
        sys.exit(1)

#-----------------------------------------------------------------------

if __name__ == '__main__':
    main()
