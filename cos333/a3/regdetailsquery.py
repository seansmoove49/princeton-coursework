#!/usr/bin/env python

#-----------------------------------------------------------------------
# regdetailsquery.py
# Author: Sean Wang, Alina Chen
#-----------------------------------------------------------------------


import sys
import contextlib
import sqlite3
from classdetails import ClassDetails
from coursedetails import CourseDetails



DATABASE_URL = 'file:reg.sqlite?mode=ro'

def query_details(class_id):
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
                INNER JOIN classes on 
                crosslistings.courseid = classes.courseid'''
                select_stmt_1 += " WHERE classes.classid = ?"
                select_stmt_1 += ''' ORDER BY crosslistings.dept,
                crosslistings.coursenum'''
                cursor.execute(select_stmt_1, [class_id])

                rows = cursor.fetchall()

                row = rows[0]

                class_details = ClassDetails(row, str(class_id))
                # class id does not exist
                if len(rows) == 0:
                    err = f"no class with classid {class_id} exists"
                    print(f"{sys.argv[0]}: {err}", file=sys.stderr)
                    return {"error": True, "result": err, "database_error":False}
                select_stmt_2 = '''SELECT profs.profname
                FROM profs 
                JOIN coursesprofs on profs.profid = coursesprofs.profid 
                JOIN courses on coursesprofs.courseid = courses.courseid 
                JOIN classes on courses.courseid = classes.courseid '''
                select_stmt_2 += '''WHERE classes.classid =
                ? ORDER BY profs.profname'''
                cursor.execute(select_stmt_2, [class_id])
                
                prof_rows = cursor.fetchall()
                profs = []
                for prof_row in prof_rows: 
                    profs.append(str(prof_row[0]))
    
                
                dept_nums = []
                for dept_row in rows:
                    dept_nums.append(str(dept_row[6]) + " " + str(dept_row[7]))

                course_details = CourseDetails(row, dept_nums, profs) 
                
                return {"error":False, "class_details": class_details, 
                "course_details":course_details}

    except Exception as ex:
        print(sys.argv[0] + ': ' + str(ex), file=sys.stderr)
        return {'error': True, "result": '''A server error occurred.Please 
        contact the system administrator.''', 'database_error':True} 