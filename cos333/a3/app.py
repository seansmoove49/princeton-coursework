#!/usr/bin/env python
import flask
from regquery import query_courses
from regquerydetails import get_details
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

@app.route('/classdetails', methods=['GET'])
def class_details():
    class_id = flask.request.args.get('class_id')
    if class_id is None:
        class_id = ''
    class_id = class_id.strip()

    regclass, course = get_details(class_id)
    html_code = flask.render_template('classdetails.html', regclass=regclass, course=course)
    response = flask.make_response(html_code)
    return response
    

    

    
    
    
    
    