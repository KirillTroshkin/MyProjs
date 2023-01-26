#include "sort_students.h"

#include <tuple>

bool comparing_based_on_date(Student student1, Student student2) {
    return std::tie(student1.birth_date.year, student1.birth_date.month, student1.birth_date.day, student1.last_name,
                    student1.name) < std::tie(student2.birth_date.year, student2.birth_date.month,
                                              student2.birth_date.day, student2.last_name, student2.name);
}

bool comparing_based_on_name(Student student1, Student student2) {
    return std::tie(student1.last_name, student1.name, student1.birth_date.year, student1.birth_date.month,
                    student1.birth_date.day) < std::tie(student2.last_name, student2.name,
                                              student2.birth_date.year, student2.birth_date.month, student2.birth_date.day);
}

void SortStudents(std::vector<Student>& students, SortKind sortKind) {
    if (sortKind == SortKind::Date) {
        sort(students.begin(), students.end(), comparing_based_on_date);
    } else if (sortKind == SortKind::Name) {
        sort(students.begin(), students.end(), comparing_based_on_name);
    }
}
