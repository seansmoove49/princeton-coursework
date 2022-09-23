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
                select_stmt = "SELECT classes.classid, crosslistings.dept, crosslistings.coursenum, courses.area, courses.title FROM classes INNER JOIN courses ON classes.courseid = courses.courseid INNER JOIN crosslistings ON crosslistings.courseid = classes.courseid "

                is_first = True
                prepared_variables = []
                if args.d:
                    department = args.d.lower()
                    if "_" in department:
                        department.replace('_', '+_')
                    
                    w_or_a = "WHERE " if is_first else "AND "
                    if is_first:
                        is_first = False
                    
                    select_stmt += w_or_a + "crosslistings.dept LIKE ? ESCAPE '+' "
                    
                    prepared_variables.append(f"%{department}%")
                if args.n:
                    number = args.n.lower()
                    if "_" in number:
                        number.replace('_', '+_')

                    w_or_a = "WHERE " if is_first else "AND "
                    if is_first:
                        is_first = False
                    
                    select_stmt += w_or_a + "crosslistings.coursenum LIKE ? ESCAPE '+' "
                    
                    prepared_variables.append(f"%{number}%")
                
                if args.a:
                    area = args.a.lower()
                    if "_" in number:
                        area.replace('_', '+_')
                    w_or_a = "WHERE " if is_first else "AND "
                    if is_first:
                        is_first = False
                    
                    select_stmt += w_or_a + "courses.area LIKE ? ESCAPE '+' "
                    
                    prepared_variables.append(f"%{area}%")
                
                if args.t:
                    title = args.t.lower()
                    if "_" in title:
                        title.replace('_', '+_')
                    w_or_a = "WHERE " if is_first else "AND "
                    if is_first:
                        is_first = False
                    
                    select_stmt += w_or_a +  "courses.title LIKE ? ESCAPE '+' "
                    prepared_variables.append(f"%{title}%")


                
                select_stmt += "ORDER BY crosslistings.dept, crosslistings.coursenum, classes.classid"
                print(select_stmt)
                print(prepared_variables)
                cursor.execute(select_stmt, prepared_variables)
                print_table(cursor)




    except Exception as ex:
        print(ex, file=sys.stderr)
        sys.exit(1)

#-----------------------------------------------------------------------
def parse_args():
    parser = argparse.ArgumentParser(description='Registrar application: show overviews of classes', allow_abbrev=False)
    
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
    
def print_table(cursor):                
    titles = ["ClsId", "Dept", "CrsNum", "Area", "Title"]
    underline = ["-"*len(title) for title in titles]
    
    print(' '.join(titles))
    print(' '.join(underline))
    row = cursor.fetchone()

    
    while row is not None:
        for i, element in enumerate(list(row)):
            if i < len(titles) - 1:
                print(('{:>' + str(len(titles[i])) +'}').format(element), end=" ")

            else:
                line_list = textwrap.wrap(text=element, width = 72-23)
                for j, line in enumerate(line_list):
                    if j != 0:
                        print(23*" ", end="")
                    print(line)
        row = cursor.fetchone()
if __name__ == '__main__':
    main()