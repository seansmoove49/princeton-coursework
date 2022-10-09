#!/usr/bin/env python

#-----------------------------------------------------------------------
# regquery.py
# Authors: Sean Wang, Alina Chen
#-----------------------------------------------------------------------


import sys
import contextlib
import sqlite3
import argparse
import textwrap

#-----------------------------------------------------------------------


DATABASE_URL = 'file:reg.sqlite?mode=ro'


def query_courses(args):
    try:
        with sqlite3.connect(DATABASE_URL, isolation_level=None,
            uri=True) as connection:

            with contextlib.closing(connection.cursor()) as cursor:
                select_stmt = '''SELECT classes.classid,
                crosslistings.dept, crosslistings.coursenum, 
                courses.area, courses.title 
                FROM classes 
                INNER JOIN courses 
                ON classes.courseid = courses.courseid 
                INNER JOIN crosslistings 
                ON crosslistings.courseid = classes.courseid '''

                is_first = True
                prepared_variables = []

                if 'd' in args.keys():
                    __replace_var(args['d'], prepared_variables)
                    w_or_a = "WHERE " if is_first else "AND "
                    if is_first:
                        is_first = False

                    select_stmt += w_or_a + '''crosslistings.dept
                    LIKE ? ESCAPE '+' '''

                if 'n' in args.keys():
                    __replace_var(args['n'], prepared_variables)
                    w_or_a = "WHERE " if is_first else "AND "
                    if is_first:
                        is_first = False

                    select_stmt += w_or_a + '''crosslistings.coursenum
                    LIKE ? ESCAPE '+' '''

                if 'a' in args.keys():
                    __replace_var(args['a'], prepared_variables)
                    w_or_a = "WHERE " if is_first else "AND "
                    if is_first:
                        is_first = False

                    select_stmt += w_or_a + '''courses.area
                    LIKE ? ESCAPE '+' '''

                if 't' in args.keys():
                    __replace_var(args['t'], prepared_variables)
                    w_or_a = "WHERE " if is_first else "AND "
                    if is_first:
                        is_first = False

                    select_stmt += w_or_a +  '''courses.title
                    LIKE ? ESCAPE '+' '''


                select_stmt += '''ORDER BY crosslistings.dept,
                crosslistings.coursenum, 
                classes.classid'''

                cursor.execute(select_stmt, prepared_variables)

                return {"error": False, "result":format_table(cursor.fetchall())}

    except Exception as ex:
        print(ex, file=sys.stderr)
        return {"error": True, 'result': '''A server error occurred. 
        Please contact the system administrator'''}

def query_details(args):
    try:
        with sqlite3.connect(DATABASE_URL, isolation_level=None,
            uri=True) as connection:

            with contextlib.closing(connection.cursor()) as cursor:

                res = ""

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
                cursor.execute(select_stmt_1, [args['class_id']])

                rows = cursor.fetchall()
                # class id does not exist
                if len(rows) == 0:
                    err = f"no class with classid {args['class_id']}"
                    print(err, file=sys.stderr)
                    return {"error": True, "result": err}
                
                res += format_details(rows)

                select_stmt_2 = '''SELECT profs.profname
                FROM profs 
                JOIN coursesprofs on profs.profid = coursesprofs.profid 
                JOIN courses on coursesprofs.courseid = courses.courseid 
                JOIN classes on courses.courseid = classes.courseid '''
                select_stmt_2 += '''WHERE classes.classid =
                ? ORDER BY profs.profname'''
                cursor.execute(select_stmt_2, [args['class_id']])

                rows = cursor.fetchall()
                res += format_profs(rows)

                return {"error": False, "result": res}


    except Exception as ex:
        print(ex, file=sys.stderr)
        return {"error": True, 'result': '''A server error occurred. 
        Please contact the system administrator'''}

def format_table(rows):
    formatted_rows = []
    # left align to add white space
    for row in rows:
        formatted_rows.append('{:<8} {:<7} {:<7} {:<4} {}'.format(row[0], 
        row[1], row[2], row[3], row[4]))
    return formatted_rows

def format_details(rows):
    res = ""
    row = rows[0]

    res += "Course Id: {}\n\n".format(str(row[0]))
    res += "Days: {}\n".format(str(row[1]))
    res += "Start time: {}\n".format(str(row[2]))
    res += "End time: {}\n".format(str(row[3]))
    res += "Building: {}\n".format(str(row[4]))
    res += "Room: {}\n\n".format(str(row[5]))
    for r in rows:
        res += "Dept and Number: {} {}".format(str(r[6]), 
        str(r[7])) + '\n'
    res += '\n'
    res += "Area: {}\n\n".format(str(row[8]))

    if len(row[9]) == 0:
        res += "Title:\n"
    else:
        res += "Title: {}".format(str(row[9])) + '\n'
    res += '\n'
    if len(row[10]) == 0:
        res += "Description:\n"
    else:
        res += "Description: {}".format(
            str(row[10])) + '\n'
    res += '\n'
    if len(row[11]) == 0:
        res += "Prerequisites:\n"
    else:
        res += "Prerequisites: {}".format(
            str(row[11])) + '\n'
    res += '\n'
    return res

def format_profs(rows):
    res = ""
    for row in rows:
        res += "Professor: {}".format(str(row[0])) + '\n'
    return res
def __replace_var(args_var, prepared_variables):
    variable = args_var.lower()
    if "_" in variable:
        variable = variable.replace('_', '+_')
    if "%" in variable:
        variable = variable.replace('%', '+%')
    prepared_variables.append(f"%{variable}%")
    
