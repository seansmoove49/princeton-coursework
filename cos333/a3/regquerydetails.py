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
                    print(f"{sys.argv[0]}: {err}", file=sys.stderr)
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
        print(f"{sys.argv[0]}: {ex}", file=sys.stderr)
        return {"error": True, 'result': '''A server error occurred.
        Please contact the system administrator'''}


def format_details(rows):
    res = ""
    row = rows[0]

    res += f"Course Id: {row[0]}\n\n"
    res += f"Days: {row[1]}\n"
    res += f"Start time: {row[2]}\n"
    res += f"End time: {row[3]}\n"
    res += f"Building: {row[4]}\n"
    res += f"Room: {row[5]}\n\n"

    for dept_row in rows:
        res += f"Dept and Number: {dept_row[6]} {dept_row[7]}\n"
    res += '\n'
    res += f"Area: {row[8]}\n\n"

    res += f"Title: {row[9]}\n\n"
    res += f"Description: {row[10]}\n\n"
    res += f"Prerequisites: {row[11]}\n\n"

    return res

def format_profs(rows):
    res = ""
    for row in rows:
        res += f"Professor: {row[0]}\n"
    return res
def __replace_var(args_var, prepared_variables):
    variable = args_var.lower()
    if "_" in variable:
        variable = variable.replace('_', '+_')
    if "%" in variable:
        variable = variable.replace('%', '+%')
    prepared_variables.append(f"%{variable}%")