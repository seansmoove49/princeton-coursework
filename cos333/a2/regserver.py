#!/usr/bin/env python

#-----------------------------------------------------------------------
# regserver.py
# Authors: Sean Wang, Alina Chen
#-----------------------------------------------------------------------

import os
import sys
import socket
import argparse
import pickle

from regquery import query_courses, query_details

#-----------------------------------------------------------------------


def handle_client(sock):
    # read from socket to see what type of request
    # as we could be requesting courses or details
    in_flo = sock.makefile(mode="rb")
    in_args = pickle.load(in_flo)

    if in_args["request"] == "query_courses":
        out_args = query_courses(in_args)
    elif in_args["request"] == "query_details":
        out_args = query_details(in_args)
    else:
        print(f"{sys.argv[0]}: wrong type of request from socket",
        sys.stderr)
        # return to avoid writing to socket
        return

    # write to socket data from server side
    out_flo = sock.makefile(mode='wb')
    pickle.dump(out_args, out_flo)
    out_flo.flush()
    print('Wrote results to client')

def args_parser():
    parser = argparse.ArgumentParser(description=
        '''Server for the registrar application''', allow_abbrev=False)

    parser.add_argument(dest='port',
    help='''the port at which the server should listen''', type=int)

    args = parser.parse_args()
    return args

def main():
    try:
        args = args_parser()

        port = int(args.port)

        server_sock = socket.socket()
        print('Opened server socket')
        if os.name != 'nt':
            server_sock.setsockopt(
                socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        server_sock.bind(('', port))
        print('Bound server socket to port')
        server_sock.listen()
        print('Listening')

        while True:
            try:
                sock, client_addr = server_sock.accept()
                with sock:
                    print('Accepted connection')
                    print('Opened socket')
                    print('Server IP addr and port:',
                        sock.getsockname())
                    print('Client IP addr and port:', client_addr)
                    handle_client(sock)
            except Exception as ex:
                print(f"{sys.argv[0]}: {ex}", file=sys.stderr)

    except Exception as ex:
        print(f"{sys.argv[0]}: {ex}", file=sys.stderr)
        sys.exit(1)

if __name__ == '__main__':
    main()