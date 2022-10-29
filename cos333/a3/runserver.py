#!/usr/bin/env python

#-----------------------------------------------------------------------
# runserver.py
# Author: Sean Wang, Alina Chen
#-----------------------------------------------------------------------
import sys
import app
import argparse


def args_parser():
    parser = argparse.ArgumentParser(description=
        '''The registrar application''', allow_abbrev=False)

    parser.add_argument(dest='port',
    help='''the port at which the server should listen''', type=int)

    args = parser.parse_args()
    return args

def main():
    args = args_parser()
    port = int(args.port)
    try:
        app.app.run(host='0.0.0.0', port=port, debug=True)
    except Exception as ex:
        print(f"{sys.argsv[0]}: {str(ex)}", file=sys.stderr)
        sys.exit(1)

if __name__ == '__main__':
    main()
