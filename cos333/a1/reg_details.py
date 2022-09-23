import sys
import contextlib
import sqlite3
import argparse
import textwrap
DATABASE_URL = 'file:reg.sqlite?mode=ro'

def main():
    args = parse_args()

    try:            
        with sqlite3.connect(DATABASE_URL, isolation_level=None,
            uri=True) as connection:
            
            with contextlib.closing(connection.cursor()) as cursor:
                select_stmt = "SELECT classes.courseid, classes.days, classes.starttime, classes.endtime, classes.bldg, classes.roomnum,crosslistings.dept, crosslistings.coursenum,courses.area, courses.title, courses.descrip, courses.prereqs,profs.profname FROM profs JOIN coursesprofs on profs.profid = coursesprofs.profid JOIN courses on coursesprofs.courseid = courses.courseid JOIN crosslistings on courses.courseid = crosslistings.courseid JOIN classes on crosslistings.courseid = classes.courseid"
                select_stmt += "WHERE classes.classid = ?"
                select_stmt += "ORDER BY crosslistings.dept, crosslistings.coursenum"
                print(select_stmt)
                cursor.execute(select_stmt, args.classid)
                print_details(cursor)




    except Exception as ex:
        print(ex, file=sys.stderr)
        sys.exit(1)

#-----------------------------------------------------------------------
def parse_args():
    parser = argparse.ArgumentParser(description='Registrar application: show details about a class ', allow_abbrev=False)
    parser.add_argument('classid', type=int, help='the id of the class whose details should be shown')
    args = parser.parse_args()
    return args
    
def print_details(cursor):                
    row = cursor.fetchone()

    
    while row is not None:
        row = cursor.fetchone()
if __name__ == '__main__':
    main()