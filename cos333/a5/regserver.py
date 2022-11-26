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
from multiprocessing import Process, cpu_count
from time import process_time

#-----------------------------------------------------------------------

def consume_cpu_time(delay):
    initial_time = process_time()
    while (process_time() - initial_time) < delay:
        pass

def handle_client(sock, delay):
    # read from socket to see what type of request
    # as we could be requesting courses or details
    in_flo = sock.makefile(mode="rb")
    in_args = pickle.load(in_flo)

    # Consume delay seconds of CPU time.
    consume_cpu_time(delay)
    if in_args["request"] == "query_courses":
        out_args = query_courses(in_args)
    elif in_args["request"] == "query_details":
        out_args = query_details(in_args)
    else:
        print(f"{sys.argv[0]}: unknown input from socket",
        sys.stderr)
        # return to avoid writing to socket
        return
    # write to socket data from server side
    out_flo = sock.makefile(mode='wb')
    pickle.dump(out_args, out_flo)
    out_flo.flush()
    print('Wrote results to client')

def main():
    try:
        parser = argparse.ArgumentParser(description=
        '''Server for the registrar application''', allow_abbrev=False)

        parser.add_argument(dest='port',
        help='''the port at which the server should listen''', type=int)

        parser.add_argument(dest='delay', help='''the number of
        seconds that the server should delay before responding
        to each client request''', type=int)

        args = parser.parse_args()

        port = int(args.port)
        delay = int(args.delay)


        print('CPU count:', cpu_count())

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

                    process = Process(target=handle_client, args=[sock, delay])
                    process.start()

            except Exception as ex:
                print(f"{sys.argv[0]}: {ex}", file=sys.stderr)

    except Exception as ex:
        print(f"{sys.argv[0]}: {ex}", file=sys.stderr)
        sys.exit(1)

if __name__ == '__main__':
    main()