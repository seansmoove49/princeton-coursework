
#-----------------------------------------------------------------------
# regserver.py
# Authors: Sean Wang, Alina Chen
#-----------------------------------------------------------------------

import os
import sys
import socket
import argparse
import pickle

def handle_client(sock):
    in_flo = sock.makefile(mode="rb")
    in_args = pickle.load(in_flo)
    
    
    

def main():
    parser = argparse.ArgumentParser(description='''Server for the registrar 
    application''', allow_abbrev=False)

    parser.add_argument(dest='port',
                    help='''the port at which the server should listen''', type=int)
    
    args = parser.parse_args()

    port = args.port

    
