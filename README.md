# Course Enrollment System

## To run the Course Enrollment System, follow these steps:

1. Clone the repository to your local machine.
2. Create new test cases in the main.cpp file (Optional).
3. Open the terminal and navigate to the project directory.
4. Run the command ```make all``` to compile the code.
5. Run ```./main``` to execute the program.
6. Choose a test case number when prompted and press enter to view the course and student information within the system.

## Here are the operations that can be performed within the system:

- Admit a new student to the student database:

Syntax: system->admit("Adam", 1000, 3.8);

- Add a new course to the course database:

Syntax: system->add_course("COMP2012", 4, 3);

- Allow a student to swap courses:

Syntax: system->swap(1000, "COMP2012", "COMP2012H");

- Allow a student to drop an enrolled course:

Syntax: system->drop(1004, "COMP2012");

- Allow a student to credit overload up to 23 credits if their GPA is greater than 3.3, and up to 30 credits if their GPA is greater than 3.7:

Syntax: system->apply_overload(1000, 21);

- Print student and course information:

Syntax: system->print_info();
