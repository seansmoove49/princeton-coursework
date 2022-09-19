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
                select_stmt = "SELECT classes.classid, crosslistings.dept, crosslistings.coursenum, courses.area, courses.title from classes inner join courses on classes.courseid = courses.courseid inner join crosslistings on crosslistings.courseid = classes.courseid "

                if args.d:
                    department = args.d
                    select_stmt += "and crosslistings.dept='" + department + "' "
                    
                select_stmt += "order by crosslistings.dept, crosslistings.coursenum, classes.classid"
                cursor.execute(select_stmt)
                print_table(cursor, args)
            #if not any(vars(args).values()): <--- No args (full table)

    except Exception as ex:
        print(ex, file=sys.stderr)
        sys.exit(1)

#-----------------------------------------------------------------------
def parse_args():
    parser = argparse.ArgumentParser(description='Registrar application: show overview of classes', allow_abbrev=False)
    
    parser.add_argument('-d', metavar='dept',
                    help='show only those classes whose department contains dept')
    parser.add_argument('-n', metavar='num',
                    help='show only those classes whose course number contains num')
    parser.add_argument('-a', metavar='area',
                    help='show only those classes whose distrib area contains area')
    parser.add_argument('-t', metavar='title',
                    help='show only those classes whose course title contains title')
    args = parser.parse_args()
    return args
    
def print_table(cursor, args):
    titles = ["ClsId", "Dept", "CrsNum", "Area", "Title"]
    underline = ["_"*len(title) for title in titles]
                    
    print('  '.join(titles))
    print('  '.join(underline))
    row = cursor.fetchone()


    while row is not None:
        row_print = '  '.join(map(str, row))
        row = cursor.fetchone()
        wrapper = textwrap.TextWrapper(width=72)
        
        word_list = wrapper.wrap(text=row_print)

        for element in word_list:
            print(element) 
if __name__ == '__main__':
    main()