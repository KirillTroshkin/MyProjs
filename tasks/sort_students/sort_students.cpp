#include "sort_students.h"

bool comparing_based_on_date(Student student1, Student student2) {
    if ((student1.birth_date.year < student2.birth_date.year) ||
        (student1.birth_date.year == student2.birth_date.year &&
         student1.birth_date.month < student2.birth_date.month) ||
        (student1.birth_date.year == student2.birth_date.year &&
         student1.birth_date.month == student2.birth_date.month && student1.birth_date.day < student2.birth_date.day)) {
        return true;
    }
    if ((student1.birth_date.year > student2.birth_date.year) ||
        (student1.birth_date.year == student2.birth_date.year &&
         student1.birth_date.month > student2.birth_date.month) ||
        (student1.birth_date.year == student2.birth_date.year &&
         student1.birth_date.month == student2.birth_date.month && student1.birth_date.day > student2.birth_date.day)) {
        return false;
    }
    if ((student1.last_name < student2.last_name) ||
        (student1.last_name == student2.last_name && student1.last_name < student2.last_name)) {
        return true;
    }
    if ((student1.last_name > student2.last_name) ||
        (student1.last_name == student2.last_name && student1.last_name > student2.last_name)) {
        return false;
    }
    return true;
}

bool comparing_based_on_name(Student student1, Student student2) {
    if ((student1.last_name < student2.last_name) ||
        (student1.last_name == student2.last_name && student1.last_name < student2.last_name)) {
        return true;
    }
    if ((student1.last_name > student2.last_name) ||
        (student1.last_name == student2.last_name && student1.last_name > student2.last_name)) {
        return false;
    }
    if ((student1.birth_date.year < student2.birth_date.year) ||
        (student1.birth_date.year == student2.birth_date.year &&
         student1.birth_date.month < student2.birth_date.month) ||
        (student1.birth_date.year == student2.birth_date.year &&
         student1.birth_date.month == student2.birth_date.month && student1.birth_date.day < student2.birth_date.day)) {
        return true;
    }
    if ((student1.birth_date.year > student2.birth_date.year) ||
        (student1.birth_date.year == student2.birth_date.year &&
         student1.birth_date.month > student2.birth_date.month) ||
        (student1.birth_date.year == student2.birth_date.year &&
         student1.birth_date.month == student2.birth_date.month && student1.birth_date.day > student2.birth_date.day)) {
        return false;
    }
    return true;
}

void SortStudents(std::vector<Student>& students, SortKind sortKind) {
    if (sortKind == SortKind::Date) {
        sort(students.begin(), students.end(), comparing_based_on_date);
    } else if (sortKind == SortKind::Name) {
        sort(students.begin(), students.end(), comparing_based_on_name);
    }
}
