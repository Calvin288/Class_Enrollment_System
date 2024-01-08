#include <iostream>
#include <cstring>
#include "system.h"
#include "student.h"
#include "course.h"
#include "course_database.h"
#include "student_database.h"
#include "wait_list.h"
#include "swap_list.h"

using namespace std;

/*
The following 3 helper functions may be useful in add/swap/drop function. You may implement them if you find them useful.
If not, you can remove these 3 helper functions as we will NOT set any test case testing these helper functions.
*/

// Helper function: add the Student to the end of the waitlist of the Course.
void join_waitlist(const int student_id, Course *course)
{
    Wait_List *wait_list = course->get_wait_list();
    Student_ListNode *new_node = new Student_ListNode(student_id, nullptr);

    if (wait_list->get_head() == nullptr)
    {
        wait_list->set_head(new_node);
        wait_list->set_end(new_node);
    }
    else
    {
        wait_list->get_end()->next = new_node;
        wait_list->set_end(new_node);
    }
}

// Helper function: find the index of a course within the enrolled course list of a student.
int search_course_index(const Student *const student, const char *const course_name)
{
    int num_enrolled_course = student->get_num_enrolled_course();
    char **enrolled_courses = student->get_enrolled_courses();
    for (int i = 0; i < num_enrolled_course; i++)
        if (strcmp(enrolled_courses[i], course_name) == 0)
            return i;
    return -1;
}

// Helper function: find the index of the student_id in the enrolled student list
int search_student_id(const int student_id, const Course *const course)
{
    int *sid_list = course->get_students_enrolled();
    for (int i = 0; i < course->get_size(); i++)
        if (student_id == sid_list[i])
            return i;
    return -1;
}

System::System(const int max_num_course, const int max_num_student)
{
    course_database = new Course_Database(max_num_course);
    student_database = new Student_Database(max_num_student);
}

System::System(const System &system)
{
    this->course_database = new Course_Database(*system.course_database);
    this->student_database = new Student_Database(*system.student_database);
}

System::~System()
{
    delete course_database;
    delete student_database;
}

void System::admit(const char *const name, const int student_id, const double gpa)
{
    this->student_database->create_entry(name, student_id, gpa);
}

bool System::apply_overload(const int student_id, const int request_credit)
{
    if (request_credit > 30)
        return false;
    Student *student = student_database->get_student_by_id(student_id);
    if (request_credit >= 24 && student->get_gpa() >= 3.7)
    {
        student->set_max_credit(request_credit);
        return true;
    }
    else if (request_credit > 18 && student->get_gpa() >= 3.3)
    {
        student->set_max_credit(request_credit);
        return true;
    }
    else
        return false;
}

bool System::add(const int student_id, const char *const course_name)
{
    int pending_credits = 0;
    Student *student = student_database->get_student_by_id(student_id);
    Course *course = course_database->get_course_by_name(course_name);

    // Count Pending Credits from Swap
    Swap_List *swap_list = student->get_swap_list();
    Swap *swap_p = swap_list->get_head();
    while (swap_p != nullptr)
    {
        char *og = swap_p->original_course_name;
        char *tgt = swap_p->target_course_name;
        int og_credit = course_database->get_course_by_name(og)->get_num_credit();
        int tgt_credit = course_database->get_course_by_name(tgt)->get_num_credit();
        if (tgt_credit > og_credit)
        {
            pending_credits += tgt_credit;
            pending_credits -= og_credit;
        }
        swap_p = swap_p->next;
    }

    // Count Pending Credit from wait_list
    Course **course_list = course_database->get_courses();
    for (int i = 0; i < course_database->get_size(); i++)
    {
        Swap *sp = swap_list->get_head();
        bool flag = false;
        while (sp != nullptr)
        {
            if (strcmp(sp->target_course_name, course_list[i]->get_name()) == 0)
            {
                flag = true;
                break;
            }
        }
        if (flag)
            continue;

        Wait_List *wait_list = course_list[i]->get_wait_list();
        Student_ListNode *p = wait_list->get_head();
        while (p != nullptr)
        {
            if (p->student_id == student_id)
            {
                pending_credits += course_list[i]->get_num_credit();
                break;
            }
            p = p->next;
        }
    }

    int course_credit = course->get_num_credit();
    student->set_pending_credit(pending_credits);

    // Checking whether adding course is possible
    if ((student->get_pending_credit() + student->get_curr_credit() + course_credit) > student->get_max_credit())
    {
        return false;
    }
    else
    {
        if (course->get_capacity() == course->get_size())
        {
            // Join waitlit
            join_waitlist(student_id, course);

            // Update Pending Credit
            student->set_pending_credit(student->get_pending_credit() + course->get_num_credit());
        }
        else
        {
            // Update Course Size
            course->set_size(course->get_size() + 1);

            // Update Course Enrolled Students
            int *SID_list = course->get_students_enrolled();
            SID_list[course->get_size() - 1] = student_id;

            // Update student's number of enrolled courses
            student->set_num_enrolled_course(student->get_num_enrolled_course() + 1);

            // Update student's current credit
            student->set_curr_credit(student->get_curr_credit() + course->get_num_credit());

            // Update student's enrolled courses
            char **enrolled_courses = student->get_enrolled_courses();
            int last_idx = student->get_num_enrolled_course() - 1;
            enrolled_courses[last_idx] = new char[strlen(course_name) + 1];
            strcpy(enrolled_courses[last_idx], course_name);
        }
        return true;
    }
}

bool System::swap(const int student_id, const char *const original_course_name, const char *const target_course_name)
{
    int pending_credits = 0;
    Student *student = student_database->get_student_by_id(student_id);
    Course *og_course = course_database->get_course_by_name(original_course_name);
    Course *tgt_course = course_database->get_course_by_name(target_course_name);

    // Count Pending Credits from Swap
    Swap_List *swap_list = student->get_swap_list();
    Swap *swap_p = swap_list->get_head();
    while (swap_p != nullptr)
    {
        char *og = swap_p->original_course_name;
        char *tgt = swap_p->target_course_name;
        int og_credit = course_database->get_course_by_name(og)->get_num_credit();
        int tgt_credit = course_database->get_course_by_name(tgt)->get_num_credit();
        if (tgt_credit > og_credit)
        {
            pending_credits += tgt_credit;
            pending_credits -= og_credit;
        }
        swap_p = swap_p->next;
    }

    // Count Pending Credit from wait_list
    Course **course_list = course_database->get_courses();
    for (int i = 0; i < course_database->get_size(); i++)
    {
        Swap *sp = swap_list->get_head();
        bool flag = false;
        while (sp != nullptr)
        {
            if (strcmp(sp->target_course_name, course_list[i]->get_name()) == 0)
                flag = true;
            break;
        }
        if (flag)
            continue;

        Wait_List *wait_list = course_list[i]->get_wait_list();
        Student_ListNode *sl_p = wait_list->get_head();
        while (sl_p != nullptr)
        {
            if (sl_p->student_id == student_id)
                pending_credits += course_list[i]->get_num_credit();
            sl_p = sl_p->next;
        }
    }

    student->set_pending_credit(pending_credits);
    int og_course_credit = og_course->get_num_credit();
    int tgt_course_credit = tgt_course->get_num_credit();
    int excess_credits = 0;
    if (tgt_course_credit > og_course_credit)
        excess_credits = tgt_course_credit - og_course_credit;

    // Checking whether adding course is possible
    if ((student->get_pending_credit() + student->get_curr_credit() + excess_credits) > student->get_max_credit())
    {
        return false;
    }
    else
    {
        if (tgt_course->get_capacity() > tgt_course->get_size())
        {
            // Update course Size
            tgt_course->set_size(tgt_course->get_size() + 1);

            // Update course's enrolled student
            int *enrolled_tgt_students = tgt_course->get_students_enrolled();
            enrolled_tgt_students[tgt_course->get_size() - 1] = student_id;

            // Update student's number of enrolled costudent->set_pending_credit(student->get_pending_credit()couturses
            student->set_num_enrolled_course(student->get_num_enrolled_course() + 1);

            // Update student's current credit
            student->set_curr_credit(student->get_curr_credit() + tgt_course->get_num_credit());

            // Update student's enrolled classes
            char **student_enrolled_courses = student->get_enrolled_courses();
            student_enrolled_courses[student->get_num_enrolled_course() - 1] = new char[strlen(target_course_name) + 1];
            strcpy(student_enrolled_courses[student->get_num_enrolled_course() - 1], target_course_name);

            // drop the course
            System::drop(student_id, original_course_name);
        }
        else if (tgt_course->get_capacity() == tgt_course->get_size())
        {
            // Join wait list
            join_waitlist(student_id, tgt_course);

            // Update pending credits
            student->set_pending_credit(student->get_pending_credit() + excess_credits);

            // new swap
            if (swap_list != nullptr)
            {
                Swap *new_swap = new Swap(original_course_name, target_course_name, swap_list->get_head());
                student->get_swap_list()->set_head(new_swap);
            }
            else
            {
                Swap *new_swap = new Swap(original_course_name, target_course_name, nullptr);
                student->get_swap_list()->set_head(new_swap);
            }
        }
        return true;
    }
}

void System::drop(const int student_id, const char *const course_name)
{
    Student *student = student_database->get_student_by_id(student_id);
    Course *course = course_database->get_course_by_name(course_name);

    // Update student's enrolled classes
    int course_idx = search_course_index(student, course_name);
    if (course_idx == -1)
        return;
    int num_courses = student->get_num_enrolled_course();
    char **enrolled_courses = student->get_enrolled_courses();
    delete[] enrolled_courses[course_idx];
    if (course_idx != (num_courses - 1))
    {
        enrolled_courses[course_idx] = new char[strlen(enrolled_courses[num_courses - 1]) + 1];
        strcpy(enrolled_courses[course_idx], enrolled_courses[num_courses - 1]);
        delete[] enrolled_courses[num_courses - 1];
    }

    // Update student's number of enrolled courses
    student->set_num_enrolled_course(student->get_num_enrolled_course() - 1);

    // Update student's current credits
    student->set_curr_credit(student->get_curr_credit() - course->get_num_credit());

    Wait_List *course_wait_list = course->get_wait_list();
    Student_ListNode *head = course_wait_list->get_head();

    if (head != nullptr)
    {
        int add_student_sid = head->student_id;
        Student *add_student = student_database->get_student_by_id(add_student_sid);

        // Update enrolled student of the class     WE ALREADY INITIALIZE SID HEREE. Mending awal ato akhir??
        int sid_idx = search_student_id(student_id, course);
        if (sid_idx == -1)
            return;
        int *enrolled_students = course->get_students_enrolled();
        enrolled_students[sid_idx] = add_student_sid;

        // remove add_student node from waitlist
        Student_ListNode *temp = head;
        course->get_wait_list()->set_head(head->next);
        if (course->get_wait_list()->get_head() == nullptr)
            course->get_wait_list()->set_end(nullptr);
        delete temp;
        temp = nullptr;

        // Update add_student number of enrolled courses
        add_student->set_num_enrolled_course(add_student->get_num_enrolled_course() + 1);

        // Update add_student current credit
        add_student->set_curr_credit(add_student->get_curr_credit() + course->get_num_credit());

        // Updated add_student's enrolled courses
        char **enrolled_courses = add_student->get_enrolled_courses();
        enrolled_courses[add_student->get_num_enrolled_course() - 1] = new char[strlen(course_name) + 1];
        strcpy(enrolled_courses[add_student->get_num_enrolled_course() - 1], course_name);

        Swap *swap_p = add_student->get_swap_list()->get_head();
        if (swap_p != nullptr)
        {
            if (strcmp(swap_p->target_course_name, course_name) == 0)
            {
                add_student->get_swap_list()->set_head(swap_p->next);
                System::drop(add_student_sid, swap_p->original_course_name);
            }
            else
            {
                Swap *prv = nullptr;
                while (swap_p != nullptr)
                {
                    if (strcmp(swap_p->target_course_name, course_name) == 0)
                    {
                        System::drop(add_student_sid, swap_p->original_course_name);
                        break;
                    }
                    prv = swap_p;
                    swap_p = swap_p->next;
                }
                if (swap_p != nullptr)
                {
                    prv->next = swap_p->next;
                }
            }

            if (swap_p != nullptr)
            {
                Course *original_course = course_database->get_course_by_name(swap_p->original_course_name);

                // Update pending credits
                int excess_credits = 0;
                if (course->get_num_credit() > original_course->get_num_credit())
                    excess_credits = course->get_num_credit() - original_course->get_num_credit();
                add_student->set_pending_credit(add_student->get_pending_credit() - excess_credits);

                // update target course sid list
                delete swap_p;
            }
            else
            {
                add_student->set_pending_credit(add_student->get_pending_credit() - course->get_num_credit());
            }

            // Update wait list
            Student_ListNode *head = course->get_wait_list()->get_head();
            Student_ListNode *end = course->get_wait_list()->get_end();
            if (head == end)
            {
                delete head;
                course->get_wait_list()->set_head(nullptr);
                course->get_wait_list()->set_end(nullptr);
            }
            else
            {
                course->get_wait_list()->set_head(head->next);
                delete head;
            }
        }
        else
        {
            // Update student pending credit
            add_student->set_pending_credit(add_student->get_pending_credit() - course->get_num_credit());
        }
    }
    else
    {
        // Update enroll student list
        int last_idx = course->get_size() - 1;
        int student_idx = search_student_id(student_id, course);
        if (student_idx == -1)
            return;
        int *sid_list = course->get_students_enrolled();
        sid_list[student_idx] = sid_list[last_idx];
        sid_list[last_idx] = 0;

        // Update course size
        course->set_size(last_idx);
    }
}

void System::add_course(const char *const name, const int num_credit, const int course_capacity)
{
    this->course_database->create_entry(name, num_credit, course_capacity);
}

void System::print_info() const
{
    this->course_database->print_all_course();
    this->student_database->print_all_students();
}

Course_Database *System::get_course_database() const
{
    return course_database;
}

Student_Database *System::get_student_database() const
{
    return student_database;
}

void System::set_course_database(Course_Database *const course_database)
{
    this->course_database = course_database;
}

void System::set_student_database(Student_Database *const student_database)
{
    this->student_database = student_database;
}
