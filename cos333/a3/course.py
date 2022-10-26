import py_compile
#-----------------------------------------------------------------------
# course.py
# Author: Alina Chen, Sean Wang
#-----------------------------------------------------------------------

class Course:

    def __init__(self, id, dept_nums, area, title, description, professors):
        self._id = id
        self._dept_nums = dept_nums
        self._area = area
        self._title = title
        self._description = description
        self._professors = professors
    
    def get_id(self):
        return self._id

    def get_dept_nums(self):
        return self._dept_nums

    def get_area(self):
        return self._area
    
    def get_title(self):
        return self._title

    def get_description(self):
        return self._description
    
    def get_professors(self):
        return self._professors
    