import py_compile
#-----------------------------------------------------------------------
# course.py
# Author: Alina Chen, Sean Wang
#-----------------------------------------------------------------------

class Class:

    def __init__(self, class_id, course_id, days, start_time, end_time, building, room):
        self._class_id = class_id
        self._course_id = course_id
        self._days = days
        self._start_time = start_time
        self._end_time = end_time
        self._building = building
        self._room = room
    
    def get_class_id(self):
        return self._class_id
    
    def get_course_id(self):
        return self._course_id

    def get_days(self):
        return self._days

    def get_start_time(self):
        return self._start_time
    
    def get_end_time(self):
        return self._end_time

    def get_building(self):
        return self._building
    
    def get_room(self):
        return self._room
    