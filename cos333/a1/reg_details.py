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
                select_stmt = '''SELECT classes.courseid, classes.days, classes.starttime, 
                classes.endtime, classes.bldg, classes.roomnum, 
                crosslistings.dept, crosslistings.coursenum,
                courses.area,  courses.title,  courses.descrip, courses.prereqs,
                profs.profname '''
                select_stmt += '''FROM profs 
                JOIN coursesprofs on profs.profid = coursesprofs.profid
                JOIN courses on coursesprofs.courseid = courses.courseid
                JOIN crosslistings on courses.courseid = crosslistings.courseid
                JOIN classes on crosslistings.courseid = classes.courseid '''
                select_stmt += "WHERE classes.classid = ? "
                select_stmt += "ORDER BY crosslistings.dept, crosslistings.coursenum"
                print(select_stmt)
                cursor.execute(select_stmt, [str(args.classid)])
                print_details(cursor)




    except Exception as ex:
        print(ex, file=sys.stderr)
        sys.exit(1)

#-----------------------------------------------------------------------
def parse_args():
    parser = argparse.ArgumentParser(description='Registrar application: show details about a class ', allow_abbrev=False)
    parser.add_argument('classid', type=int, help='the id of the class whose details should be shown')
    args = parser.parse_args()
    return args

def print_tw(title, element):
    line_list = textwrap.wrap(text=title + str(element), width = 72)
    for j, line in enumerate(line_list):
        print(line)
        
def print_details(cursor):      
    depts_nums = {}
    profs = set()
    row = cursor.fetchone() 
    row_print = row 

    while row is not None: 
        if row[6] not in depts_nums: 
            depts_nums[row[6]] = row[7]
        if row[12] not in profs: 
            profs.add(row[12])
        row = cursor.fetchone()
    depts_nums = sorted(depts_nums.items())
    profs = sorted(profs)
    print_tw('Course Id: ', row_print[0])
    print()
    print_tw('Days: ', row_print[1])
    print_tw('Start time: ', row_print[2])
    print_tw('End time: ', row_print[3])
    print_tw('Building: ', row_print[4])
    print_tw('Room: ', row_print[5])
    print()
    for i in range(len(depts_nums)):
        print_tw('Dept and Number: ', str(depts_nums[i][0] + " " + depts_nums[i][1]))
    print()
    print_tw('Area: ', row_print[8])
    print()
    print_tw('Title: ', row_print[9])
    print() 
    print_tw('Description: ', row_print[10])
    print()
    print_tw('Prerequisites: ', row_print[11])
    print()
    for i in range(len(profs)):
        print_tw('Professor: ', profs[i])


   


if __name__ == '__main__':
    main()