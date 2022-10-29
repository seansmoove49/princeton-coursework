#-----------------------------------------------------------------------
# classdetails.py
# Author: Alina Chen, Sean Wang
#-----------------------------------------------------------------------

class ClassDetails:

    def __init__(self, row, class_id):
        self._class_id = class_id
        self._course_id = str(row[0])
        self._days = str(row[1])
        self._start_time = str(row[2])
        self._end_time = str(row[3])
        self._building = str(row[4])
        self._room = str(row[5])

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
