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
                select_stmt_1 = '''SELECT classes.courseid,
                classes.days, classes.starttime,
                classes.endtime, classes.bldg,
                classes.roomnum, crosslistings.dept, crosslistings.coursenum,
                courses.area,  courses.title,  courses.descrip, courses.prereqs
                FROM courses
                INNER JOIN crosslistings on courses.courseid =
                crosslistings.courseid
                INNER JOIN classes on crosslistings.courseid = classes.courseid'''
                select_stmt_1 += " WHERE classes.classid = ?"
                select_stmt_1 += ''' ORDER BY crosslistings.dept,
                crosslistings.coursenum'''
                cursor.execute(select_stmt_1, [str(args.classid)])
                __print_details(cursor, args)



                select_stmt_2 = '''SELECT profs.profname
                FROM profs 
                JOIN coursesprofs on profs.profid = coursesprofs.profid 
                JOIN courses on coursesprofs.courseid = courses.courseid 
                JOIN classes on courses.courseid = classes.courseid '''
                select_stmt_2 += '''WHERE classes.classid =
                ? ORDER BY profs.profname'''
                cursor.execute(select_stmt_2, [str(args.classid)])

                __print_professor(cursor)




    except Exception as ex:
        print(ex, file=sys.stderr)
        sys.exit(1)

#-----------------------------------------------------------------------
def parse_args():
    parser = argparse.ArgumentParser(description='''Registrar
    application: show details about a class ''', allow_abbrev=False)
    parser.add_argument('classid', type=int,
    help='the id of the class whose details should be shown')
    args = parser.parse_args()
    return args

def __print_tw(title, element):
    line_list = textwrap.wrap(text=title + str(element), width = 72)
    for _, line in enumerate(line_list):
        print(line)

def __print_details(cursor, args):
    depts_nums = {}
    row = cursor.fetchone()
    row_print = row

    if row is None:
        raise Exception(f"no class with classid {args.classid}")

    while row is not None:
        if row[6] not in depts_nums:
            depts_nums[row[6]] = row[7]
        row = cursor.fetchone()
    depts_nums = sorted(depts_nums.items())
    __print_row("Course Id", row_print, 0)
    print()
    __print_row("Days", row_print, 1)
    __print_row("Start time", row_print, 2)
    __print_row("End time", row_print, 3)
    __print_row("Building", row_print, 4)
    __print_row("Room", row_print, 5)
    print()
    for _, dept in enumerate(depts_nums):
        __print_tw('Dept and Number: ',
        str(dept[0] + " " + dept[1]))
    print()

    __print_row("Area", row_print, 8)

    print()
    __print_row('Title', row_print, 9)
    print()
    __print_row("Description", row_print, 10)
    print()
    __print_row("Prerequisites", row_print, 11)

    print()

def __print_professor(cursor):
    row = cursor.fetchone()
    while row is not None:
        __print_tw('Professor: ', row[0])
        row = cursor.fetchone()

def __print_row(text, row_print, num):
    if row_print[num]:
        __print_tw(f'{text}: ', row_print[num])
    else:
        if num in (10, 11):
            print(f"{text}:")
        else:
            print(f"{text}: ")


if __name__ == '__main__':
    main()
