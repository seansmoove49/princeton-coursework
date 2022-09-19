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
                
                print('  '.join(titles))
                print('  '.join(underline))
                row = cursor.fetchone()


                while row is not None:
                    row_print = ''.join(map(str, row))
                    row = cursor.fetchone()
                    wrapper = textwrap.TextWrapper(width = 72, subsequent_indent = 20)
    
                    word_list = wrapper.wrap(text=row_print)

                    for i,element in enumerate(word_list):
                        if i == 0:
                            print('{:>5}'.format(element)+"  ")
                        elif i==1:
                             print('{:>3}'.format(element)+"  ")
                        elif i==2:
                             print('{:>4}'.format(element)+"  ")
                        else:
                            print(element)


    except Exception as ex:
        print(ex, file=sys.stderr)
        sys.exit(1)

#-----------------------------------------------------------------------

if __name__ == '__main__':
    main()