#include <iostream>
#include "wait_list.h"

using namespace std;

Student_ListNode::Student_ListNode(const int student_id, Student_ListNode *const next)
{
    this->student_id = student_id;
    this->next = next;
}

Wait_List::Wait_List()
{
    head = nullptr;
    end = nullptr;
}

Wait_List::Wait_List(const Wait_List &wait_list)
{
    if (wait_list.head == nullptr)
    {
        head = nullptr;
        end = nullptr;
    }
    else
    {
        head = new Student_ListNode(wait_list.head->student_id, nullptr);
        end = head;
        Student_ListNode *other_p = wait_list.head->next;
        while (other_p != nullptr)
        {
            end->next = new Student_ListNode(other_p->student_id, nullptr);
            end = end->next;
            other_p = other_p->next;
        }
    }
}

Wait_List::~Wait_List()
{
    while (head != nullptr)
    {
        Student_ListNode *tmp = head->next;
        delete head;
        head = tmp;
    }
    end = nullptr;
}

void Wait_List::print_list() const
{
    Student_ListNode *temp = this->head;
    int index = 0;
    while (temp)
    {
        cout << "Waitlist Number: " << index++ << endl;
        cout << temp->student_id << endl;
        temp = temp->next;
    }
}

Student_ListNode *Wait_List::get_head() const
{
    return head;
}

Student_ListNode *Wait_List::get_end() const
{
    return end;
}

void Wait_List::set_head(Student_ListNode *const head)
{
    this->head = head;
}

void Wait_List::set_end(Student_ListNode *const end)
{
    this->end = end;
}