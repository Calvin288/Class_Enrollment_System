# How to run the Course Enrollment System

1. Clone the repository
2. Create new test cases in main.cpp using operations listed below (optional)
3. From the terminal, run "make all"
4. Afterwards, run "./main"
6. Enter the test case number to view course and student information in the system

## Operations that can be done from the system:
1. Admit new student to the student_database

Syntax: system->admit("Adam", 1000, 3.8);

2. Add new course to the course_database

Syntax: system->add_course("COMP2012", 4, 3);

3. Allow student to swap courses

Syntax: system->swap(1000, "COMP2012", "COMP2012H");

4. Allow student to drop enrolled course

Syntax: system->drop(1004, "COMP2012");

5. Allow student to credit overload up to 23 credits if their GPA is greater than 3.3, and up to 30 credits if their GPA is greater than 3.7

Syntax: system->apply_overload(1000, 21);

6. Print student and course information:

Syntax: system->print_info();
