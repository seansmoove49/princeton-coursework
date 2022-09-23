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

                booleans = {"d":False, "n":False, "a":False, "t":False}
                if args.d:
                    department = args.d.lower()
                    if "_" in department:
                        department.replace('_', '+_')
                    if True in list(booleans.values()):
                        select_stmt += "AND crosslistings.dept LIKE '%" + department + "%' ESCAPE '+' "
                    
                    else:
                        select_stmt += "WHERE crosslistings.dept LIKE '%" + department + "%' ESCAPE '+' "
                        booleans["d"] = True
                if args.n:
                    number = args.n.lower()
                    if "_" in number:
                        number.replace('_', '+_')
                    if True in list(booleans.values()):
                        select_stmt += "AND crosslistings.coursenum LIKE '%" + number + "%' ESCAPE '+' "
                    
                    else:
                        select_stmt += "WHERE crosslistings.coursenum LIKE '%" + number + "%' ESCAPE '+' "
                        booleans["n"] = True
                
                if args.a:
                    area = args.a.lower()
                    if "_" in number:
                        area.replace('_', '+_')
                    if True in list(booleans.values()):
                        select_stmt += "AND courses.area LIKE '%" + area + "%' ESCAPE '+' "
                    
                    else:
                        select_stmt += "WHERE courses.area LIKE '%" + area + "%' ESCAPE '+' "
                        booleans["a"] = True
                
                if args.t:
                    title = args.t.lower()
                    if "_" in number:
                        number.replace('_', '+_')
                    if True in list(booleans.values()):
                        select_stmt += "AND courses.title LIKE '%" + title + "%' ESCAPE '+' "
                    
                    else:
                        select_stmt += "WHERE courses.title LIKE '%" + title + "%' ESCAPE '+' "
                        booleans["t"] = True


                
                select_stmt += "ORDER BY crosslistings.dept, crosslistings.coursenum, classes.classid"
                cursor.execute(select_stmt)
                print_table(cursor, args)




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