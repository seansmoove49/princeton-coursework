from msilib.schema import Class
import sys
import contextlib
import sqlite3
import course as coursemod
import regclass as regclassmod


DATABASE_URL = 'file:reg.sqlite?mode=ro'

def get_details(class_id):
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
            cursor.execute(select_stmt_1, [class_id])

            rows = cursor.fetchall()
            # class id does not exist
            if len(rows) == 0:
                err = f"no class with classid {[class_id]}"
                print(f"{sys.argv[0]}: {err}", file=sys.stderr)
                return {"error": True, "result": err}

            select_stmt_2 = '''SELECT profs.profname
            FROM profs 
            OIN coursesprofs on profs.profid = coursesprofs.profid 
            JOIN courses on coursesprofs.courseid = courses.courseid 
            JOIN classes on courses.courseid = classes.courseid '''
            select_stmt_2 += '''WHERE classes.classid =
            ? ORDER BY profs.profname'''
            cursor.execute(select_stmt_2, [class_id])
            prof_rows = cursor.fetchall()
            profs = []
            for row in prof_rows: 
                profs.append(str(row[0]))
    
            #res += format_details(rows)
            row = rows[0]
            reg_class = regclassmod.Class(
                str(class_id), str(row[0]), str(row[1]), str(row[2]), str(row[3]), str(row[4]), str(row[5]))
            
            dept_nums = []
            for dept_row in rows:
                dept_nums.append(str(dept_row[6]) + " " + str(dept_row[7]))
            course = coursemod.Course(
                str(row[0]), dept_nums, str(row[8]), str(row[9]), str(row[10]), str(row[11]), profs) 
            return (reg_class, course)

def __replace_var(args_var, prepared_variables):
    variable = args_var.lower()
    if "_" in variable:
        variable = variable.replace('_', '+_')
    if "%" in variable:
        variable = variable.replace('%', '+%')
    prepared_variables.append(f"%{variable}%")