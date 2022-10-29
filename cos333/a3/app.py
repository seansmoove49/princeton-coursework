#!/usr/bin/env python

#-----------------------------------------------------------------------
# app.py
# Author: Sean Wang, Alina Chen
#-----------------------------------------------------------------------

import flask
from regquery import query_courses
from regdetailsquery import query_details


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
    courses_query = query_courses(search)
    if not courses_query["error"]:
        courses = courses_query['courses']
        html_code = flask.render_template('index.html', 
        courses = courses, dept = dept, num = num, 
        area = area, title = title, error=False)
        response = flask.make_response(html_code)
        response.set_cookie('dept', dept)
        response.set_cookie('num', num)
        response.set_cookie('area', area)
        response.set_cookie('title', title)
        return response

    html_code = flask.render_template('index.html', error=True)
    response = flask.make_response(html_code)
    return response

@app.route('/regdetails', methods=['GET'])
def reg_details():
    class_id = flask.request.args.get('classid')
    dept = flask.request.cookies.get('dept')
    if dept is None:
        dept = ''
    num = flask.request.cookies.get('num')
    if num is None:
        num = ''
    area = flask.request.cookies.get('area')
    if area is None:
        area = ''
    title = flask.request.cookies.get('title')
    if title is None:
        title = ''

    if class_id is None or len(class_id) == 0:
        html_code = flask.render_template("classid_error.html",
        message = "missing classid")
        response = flask.make_response(html_code)
        return response

    if not class_id.isdigit():
        html_code = flask.render_template("classid_error.html",
        message = "non-integer classid")
        response = flask.make_response(html_code)
        return response

    details_query = query_details(class_id)

    if not details_query["error"]:
        class_details = details_query["class_details"]
        course_details = details_query["course_details"]

        return_link = f"/?dept={dept}&coursenum={num}&area={area}&title={title}"

        html_code = flask.render_template('regdetails.html', 
        class_details=class_details, 
        course_details=course_details, return_link=return_link)
    else:
        if details_query["database_error"]:
            html_code = flask.render_template("index.html", error=True)
        else:

            html_code = flask.render_template("classid_error.html", 
            message=details_query["result"])

    response = flask.make_response(html_code)
    return response
    

    

    
    
    
    
    