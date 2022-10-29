#-----------------------------------------------------------------------
# coursedetails.py
# Author: Alina Chen, Sean Wang
#-----------------------------------------------------------------------

class CourseDetails:

    def __init__(self, course_id, dept_nums, area, 
    title, description, prerequisites, professors):
    
        self._course_id = course_id
        self._dept_nums = dept_nums
        self._area = area
        self._title = title
        self._description = description
        self._prerequisites = prerequisites
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
    