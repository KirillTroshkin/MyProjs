#include "tests_checking.h"
#include <deque>

std::vector<std::string> StudentsOrder(const std::vector<StudentAction>& student_actions,
                                       const std::vector<size_t>& queries) {
    std::deque<std::string> work_order;
    std::vector<std::string> required_names;
    for (auto& students_act : student_actions) {
        if (students_act.side == Side::Top) {
            work_order.push_front(students_act.name);
        } else {
            work_order.push_back(students_act.name);
        }
    }
    for (auto& query : queries) {
        required_names.push_back(work_order[query - 1]);
    }
    return required_names;
}
