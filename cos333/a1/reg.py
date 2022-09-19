import sys
import contextlib
import sqlite3
import textwrap

DATABASE_URL = 'file:reg.sqlite?mode=ro'

def main():
    try:
        with sqlite3.connect(DATABASE_URL, isolation_level=None,
            uri=True) as connection:

            with contextlib.closing(connection.cursor()) as cursor:
                cursor.execute("SELECT classes.classid, crosslistings.dept, crosslistings.coursenum, courses.area, courses.title from classes inner join courses on classes.courseid = courses.courseid inner join crosslistings on crosslistings.courseid = classes.courseid order by crosslistings.dept, crosslistings.coursenum, classes.classid")
                
                titles = ["ClsId", "Dept", "CrsNum", "Area", "Title"]
                underline = ["_"*len(title) for title in titles]
                
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


    except Exception as ex:
        print(ex, file=sys.stderr)
        sys.exit(1)

#-----------------------------------------------------------------------

if __name__ == '__main__':
    main()