#include <iostream>
#include <cstring>
#include "swap_list.h"

using namespace std;

Swap::Swap(const char *const original_course_name, const char *const target_course_name, Swap *const next)
{
    // TODO
    this->original_course_name = new char[strlen(original_course_name) + 1];
    strcpy(this->original_course_name, original_course_name);

    this->target_course_name = new char[strlen(target_course_name) + 1];
    strcpy(this->target_course_name, target_course_name);
    this->next = next;
}

Swap::~Swap()
{
    // TODO
    if (original_course_name != nullptr)
    {
        delete[] original_course_name;
    }
    if (target_course_name != nullptr)
    {
        delete[] target_course_name;
    }
}

Swap_List::Swap_List()
{
    // TODO
    head = nullptr;
}

Swap_List::Swap_List(const Swap_List &swap_list)
{
    // TODO
    if (swap_list.head == nullptr)
    {
        head = nullptr;
    }
    else
    {
        head = new Swap(swap_list.head->original_course_name, swap_list.head->target_course_name, nullptr);
        Swap *object_p = head;
        Swap *other_p = swap_list.head->next;
        while (other_p != nullptr)
        {
            object_p->next = new Swap(other_p->original_course_name, other_p->target_course_name, nullptr);
            other_p = other_p->next;
            object_p = object_p->next;
        }
        object_p = nullptr;
    }
}

Swap_List::~Swap_List()
{
    // TODO
    if (head != nullptr)
    {
        Swap *temp = head->next;
        while (head != nullptr)
        {
            delete head;
            head = temp;
            if (temp != nullptr)
                temp = temp->next;
        }
        temp = nullptr;
        head = nullptr;
    }
}

void Swap_List::print_list() const
{
    Swap *temp = this->head;
    int index = 0;
    while (temp)
    {
        cout << "Swap: " << index++ << endl;
        cout << "Original Course: " << temp->original_course_name << endl;
        cout << "Target Course: " << temp->target_course_name << endl;
        temp = temp->next;
    }
}

Swap *Swap_List::get_head() const
{
    return head;
}

void Swap_List::set_head(Swap *const head)
{
    this->head = head;
}