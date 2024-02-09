# To test the Course Enrolment System!:

1. Clone the repository
2. From the terminal, run "make all"
3. Enter the test case or create new test cases from the main.cpp file

## Operations that can be done from the system:

1. Admit new student to teh student_database

Syntax: system->admit("Adam", 1000, 3.8);

2. Add new courses to the course_database:

Syntax: system->add_course("COMP2012", 4, 3);

3. Allow students to swap courses:

Syntax: system->swap(1000, "COMP2012", "COMP2012H");

4. Allow students to drop course:

Syntax: system->drop(1004, "COMP2012");

5. Allow students to overload credits if GPA > 3.3:

Syntax: system->apply_overload(1000, 21);

6. Print student and course information:

Syntax: system->print_info();
