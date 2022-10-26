#!/usr/bin/env python
import flask
from regquery import query_courses
# current directory
app = flask.Flask(__name__, template_folder='./')


@app.route('/', methods=['GET'])
def index():
    dept = flask.request.args.get('dept')
    if dept is None:
        dept = ''
    num = flask.request.args.get('num')
    if num is None:
        num = ''
    area = flask.request.args.get('area')
    if area is None:
        area = ''
    title = flask.request.args.get('title')
    if title is None:
        title = ''
    
    search = {
        "d": dept,
        "n": num,
        "a": area,
        "t": title
    }
    
    courses = query_courses(search)
    html_code = flask.render_template('index.html')


    response = flask.make_response(html_code)
    return response

@app.route('/class_details', methods=['GET'])
def class_details():
    course_id = flask.request.args.get('course_id')
    if course_id is None:
        course_id = ''

    days = flask.request.args.get('days')
    if days is None:
        days = ''

    start_time = flask.request.args.get('start_time')
    if start_time is None:
        start_time = ''   
    
    end_time = flask.request.args.get('end_time')
    if end_time is None:
        end_time = ''   
    
    building = flask.request.args.get('building')
    if building is None:
        building = ''   
    
    room = flask.request.args.get('room')
    if room is None:
        room = ''   
    
    
    
    
    