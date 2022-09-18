import sys
import contextlib
import sqlite3

DATABASE_URL = 'file:reg.sqlite?mode=ro'

def main():
    try:
        with sqlite3.connect(DATABASE_URL, isolation_level=None,
            uri=True) as connection:

            with contextlib.closing(connection.cursor()) as cursor:
                cursor.execute("SELECT classes.classid, crosslistings.dept, crosslistings.coursenum, courses.area, courses.title from classes inner join courses on classes.courseid = courses.courseid inner join crosslistings on crosslistings.courseid = classes.courseid order by crosslistings.dept, crosslistings.coursenum, classes.classid")
                
                titles = ["ClsId", "Dept", "CrsNum", "Area", "Title"]
                underline = ["_"*len(title) for title in titles]

                res = '  '.join(titles) + "\n" + '  '.join(underline)+"\n"
                row = cursor.fetchone()
                while row is not None:
                    res+=(('  '.join(map(str, row))) +"\n")
                    row = cursor.fetchone()
                print(res)

    except Exception as ex:
        print(ex, file=sys.stderr)
        sys.exit(1)

#-----------------------------------------------------------------------

if __name__ == '__main__':
    main()