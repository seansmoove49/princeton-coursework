import sys
import contextlib
import sqlite3
import argparse
import textwrap
import os
DATABASE_URL = 'file:reg.sqlite?mode=ro'

def main():

    try:
        with sqlite3.connect(DATABASE_URL, isolation_level=None,
            uri=True) as connection:

            with contextlib.closing(connection.cursor()) as cursor:
                select_stmt = '''SELECT classes.classid FROM classes'''
                cursor.execute(select_stmt)
                all = cursor.fetchall()
                for row in all:
                    class_id = row[0]
                    print(class_id)
                    os.system(f"python regdetails.py {class_id} > a.txt")
                    os.system(f"python ref_regdetails.pyc {class_id} > b.txt")
                    os.system("diff a.txt b.txt")





    except Exception as ex:
        print(ex, file=sys.stderr)
        sys.exit(1)

#-----------------------------------------------------------------------



if __name__ == '__main__':
    main()
