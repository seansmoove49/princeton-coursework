#-----------------------------------------------------------------------
# coursedetails.py
# Author: Alina Chen, Sean Wang
#-----------------------------------------------------------------------

class CourseDetails:

    def __init__(self, row, dept_nums, professors):
        self._course_id = str(row[0])
        self._dept_nums = dept_nums
        self._area = str(row[8])
        self._title = str(row[9])
        self._description = str(row[10])
        self._prerequisites = str(row[11])
        self._professors = professors
    def get_course_id(self):
        return self._course_id
    def get_dept_nums(self):
        return self._dept_nums
    def get_area(self):
        return self._area
    def get_title(self):
        return self._title
    def get_description(self):
        return self._description
    def get_prerequisites(self):
        return self._prerequisites
    def get_professors(self):
        return self._professors
