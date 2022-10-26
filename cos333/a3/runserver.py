#!/usr/bin/env python

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

    if len(sys.argv) != 2:
        print('Usage: ' + sys.argv[0] + ' port', file=sys.stderr)
        sys.exit(1)

    try:
        args = args_parser()
        port = int(args.port)
    except Exception:
        print('Port must be an integer.', file=sys.stderr)
        sys.exit(1)

    try:
        app.app.run(host='0.0.0.0', port=port, debug=True)
    except Exception as ex:
        print(ex, file=sys.stderr)
        sys.exit(1)

if __name__ == '__main__':
    main()
