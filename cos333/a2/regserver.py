
#-----------------------------------------------------------------------
# regserver.py
# Authors: Sean Wang, Alina Chen
#-----------------------------------------------------------------------

import os
import sys
import socket
import argparse

def handle_client(sock):
    in_flo = sock.makefile(mode='r')
    

def main():
    parser = argparse.ArgumentParser(description='''Server for the registrar 
    application''', allow_abbrev=False)

    parser.add_argument(dest='port',
                    help='''the port at which the server should listen''')
                    