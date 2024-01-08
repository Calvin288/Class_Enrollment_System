# Class_Enrollment_System

There are 7 classes implemented for the Class Enrollment System:

1. Student

The Student class consists of general information, such as name, student ID, GPA, maximum number of credits for the semester, current number of credits taken, and a 2D array consisting of enrolled courses and pending courses for potential swaps.

2. SwapListThe SwapList class enables swapping from the originally enrolled course to a target course once the target course becomes available (e.g., when a student's waitlist position changes).

3. Course

The Course class contains the name, number of credits associated with the course, course capacity, current number of enrolled students, a linked list of waitlisted students, and the list of students already enrolled.

4. WaitList

The WaitList class stores a linked list of students who are on the waitlist for a particular course.

5. Student_database

The student_database holds the maximum capacity of students, current size (number) of students, and an array of Student objects registered under the class enrollment system.

6. Course_database

Similar to the student_database, the course_database holds the maximum course capacity, current size (number) of enrolled courses, and an array of available courses within the class enrollment system.

7. System

The System class contains the student and course databases and is responsible for core features such as student admission, course registration, and the enrollment, swapping, and dropping of classes for each student.

Sample Test Case Outputs from main.cpp:

## Test Case: 6

Apply Overload Successfully.
PRINTING ALL COURSE INFORMATION:
PRINTING ALL STUDENT INFORMATION:

---

Student Name: Adam
Student ID: 1000 GPA: 3.4
Current Credit: 0 out of Max Credit: 21

Num Courses Enrolled: 0
Course Enrolled:

Pending swaps information:
Pending Credit: 0

## Test Case: 8

PRINTING ALL COURSE INFORMATION:

Course Name: COMP2012
Num Credit: 4
Current Size: 2 out of Capacity: 2

Student Enrolled:
1003
1001

Waitlist Information:

---

Course Name: COMP1000
Num Credit: 3
Current Size: 1 out of Capacity: 1

Student Enrolled:
1000

Waitlist Information:
Waitlist Number: 0
1002
Waitlist Number: 1
1003

---

Course Name: COMP1022P
Num Credit: 3
Current Size: 5 out of Capacity: 5

Student Enrolled:
1000
1002
1005
1003
1004

Waitlist Information:

---

Course Name: ECON1000
Num Credit: 3
Current Size: 4 out of Capacity: 5

Student Enrolled:
1000
1005
1004
1002

Waitlist Information:

---

Course Name: MATH1003
Num Credit: 2
Current Size: 1 out of Capacity: 1

Student Enrolled:
1004

Waitlist Information:
Waitlist Number: 0
1005
Waitlist Number: 1
1003
Waitlist Number: 2
1000

---

Course Name: LANG1002A
Num Credit: 3
Current Size: 1 out of Capacity: 1

Student Enrolled:
1000

Waitlist Information:
Waitlist Number: 0
1005
Waitlist Number: 1
1002

PRINTING ALL STUDENT INFORMATION:

Student Name: Adam
Student ID: 1000 GPA: 3
Current Credit: 12 out of Max Credit: 18

Num Courses Enrolled: 4
Course Enrolled:
COMP1000
COMP1022P
ECON1000
LANG1002A

Pending swaps information:
Pending Credit: 0
Swap: 0
Original Course: COMP1022P
Target Course: MATH1003

---

Student Name: B
Student ID: 1001 GPA: 1.1
Current Credit: 4 out of Max Credit: 18

Num Courses Enrolled: 1
Course Enrolled:
COMP2012

Pending swaps information:
Pending Credit: 0

---

Student Name: C
Student ID: 1002 GPA: 4.3
Current Credit: 6 out of Max Credit: 24

Num Courses Enrolled: 2
Course Enrolled:
COMP1022P
ECON1000

Pending swaps information:
Pending Credit: 6

---

Student Name: D
Student ID: 1003 GPA: 2.3
Current Credit: 7 out of Max Credit: 18

Num Courses Enrolled: 2
Course Enrolled:
COMP2012
COMP1022P

Pending swaps information:
Pending Credit: 5

---

Student Name: E
Student ID: 1004 GPA: 3.5
Current Credit: 8 out of Max Credit: 18

Num Courses Enrolled: 3
Course Enrolled:
MATH1003
ECON1000
COMP1022P

Pending swaps information:
Pending Credit: 0

---

Student Name: F
Student ID: 1005 GPA: 3.7
Current Credit: 6 out of Max Credit: 18

Num Courses Enrolled: 2
Course Enrolled:
COMP1022P
ECON1000

Pending swaps information:
Pending Credit: 5

## Test Case: 15

PRINTING ALL COURSE INFORMATION:

Course Name: COMP2012
Num Credit: 4
Current Size: 0 out of Capacity: 3

Student Enrolled:

Waitlist Information:

---

Course Name: ECON1000
Num Credit: 3
Current Size: 1 out of Capacity: 3

Student Enrolled:
1000

Waitlist Information:

PRINTING ALL STUDENT INFORMATION:

Student Name: Adam
Student ID: 1000 GPA: 3.8
Current Credit: 3 out of Max Credit: 18

Num Courses Enrolled: 1
Course Enrolled:
ECON1000

Pending swaps information:
Pending Credit: 0

## Test Case: 20

PRINTING ALL COURSE INFORMATION:

Course Name: COMP1022P
Num Credit: 3
Current Size: 1 out of Capacity: 2

Student Enrolled:
1000

Waitlist Information:

---

Course Name: MATH1000
Num Credit: 2
Current Size: 1 out of Capacity: 2

Student Enrolled:
1000

Waitlist Information:

---

Course Name: A_VERY_HARD_COURSE
Num Credit: 10
Current Size: 1 out of Capacity: 2

Student Enrolled:
1000

Waitlist Information:

---

Course Name: SOSC1960
Num Credit: 4
Current Size: 2 out of Capacity: 2

Student Enrolled:
1001
1002

Waitlist Information:
Waitlist Number: 0
1000

---

Course Name: COMP2012H
Num Credit: 5
Current Size: 0 out of Capacity: 2

Student Enrolled:

Waitlist Information:

PRINTING ALL STUDENT INFORMATION:

Student Name: Adam
Student ID: 1000 GPA: 2
Current Credit: 15 out of Max Credit: 18

Num Courses Enrolled: 3
Course Enrolled:
COMP1022P
A_VERY_HARD_COURSE
MATH1000

Pending swaps information:
Pending Credit: 2
Swap: 0
Original Course: MATH1000
Target Course: SOSC1960

---

Student Name: Brian
Student ID: 1001 GPA: 4.3
Current Credit: 4 out of Max Credit: 18

Num Courses Enrolled: 1
Course Enrolled:
SOSC1960

Pending swaps information:
Pending Credit: 0

---

Student Name: Cindy
Student ID: 1002 GPA: 4.3
Current Credit: 4 out of Max Credit: 18

Num Courses Enrolled: 1
Course Enrolled:
SOSC1960

Pending swaps information:
Pending Credit: 0
