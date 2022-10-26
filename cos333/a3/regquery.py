#!/usr/bin/env python

#-----------------------------------------------------------------------
# regquery.py
# Authors: Sean Wang, Alina Chen
#-----------------------------------------------------------------------


import sys
import contextlib
import sqlite3

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

                return {"error": False,
                "result":cursor.fetchall()}

    except Exception as ex:
        print(f"{sys.argv[0]}: {ex}", file=sys.stderr)
        return {"error": True, 'result': '''A server error occurred.
        Please contact the system administrator'''}



def __replace_var(args_var, prepared_variables):
    variable = args_var.lower()
    if "_" in variable:
        variable = variable.replace('_', '+_')
    if "%" in variable:
        variable = variable.replace('%', '+%')
    prepared_variables.append(f"%{variable}%")

