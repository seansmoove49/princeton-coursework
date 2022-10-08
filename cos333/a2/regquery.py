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

                return format(cursor.fetchall())




    except Exception as ex:
        print(ex, file=sys.stderr)
        sys.exit(1)

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
                cursor.execute(select_stmt_1, [args['classid']])

                rows = cursor.fetchall()
                if len(rows) == 0:
                    error_message = f"no class with classid {args['classid']}"
                    # need more stuff later

                



                select_stmt_2 = '''SELECT profs.profname
                FROM profs 
                JOIN coursesprofs on profs.profid = coursesprofs.profid 
                JOIN courses on coursesprofs.courseid = courses.courseid 
                JOIN classes on courses.courseid = classes.courseid '''
                select_stmt_2 += '''WHERE classes.classid =
                ? ORDER BY profs.profname'''
                cursor.execute(select_stmt_2, [args['classid']])





    except Exception as ex:
        print(ex, file=sys.stderr)
        sys.exit(1)

def format(rows):
    formatted_rows = []
    # left align to add white space
    for row in rows:
        formatted_rows.append('{:<8} {:<7} {:<7} {:<4} {}'.format(row[0], 
        row[1], row[2], row[3], row[4]))
    return formatted_rows



def __replace_var(args_var, prepared_variables):
    variable = args_var.lower()
    if "_" in variable:
        variable = variable.replace('_', '+_')
    if "%" in variable:
        variable = variable.replace('%', '+%')
    prepared_variables.append(f"%{variable}%")
    
