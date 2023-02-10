#include "admission.h"
#include <tuple>

std::vector<std::string> GetSurandname(const std::string& name_of_person) {
    std::vector<std::string> surname_and_name;
    size_t i = 0;
    while (name_of_person[i] != ' ') {
        ++i;
    }
    surname_and_name.emplace_back(name_of_person.substr(i + 1, name_of_person.size() - i - 1));
    surname_and_name.emplace_back(name_of_person.substr(0, i));
    return surname_and_name;
}

bool ComparatorWithPoints(const Applicant* applicant1, const Applicant* applicant2) {
    auto negative_applicant1_points = -(*applicant1).points;
    auto negative_applicant2_points = -(*applicant2).points;
    return std::tie(negative_applicant1_points, (*applicant1).student.birth_date.year,
                    (*applicant1).student.birth_date.month, (*applicant1).student.birth_date.day,
                    GetSurandname((*applicant1).student.name)[0], GetSurandname((*applicant1).student.name)[1]) <
           std::tie(negative_applicant2_points, (*applicant2).student.birth_date.year,
                    (*applicant2).student.birth_date.month, (*applicant2).student.birth_date.day,
                    GetSurandname((*applicant2).student.name)[0], GetSurandname((*applicant2).student.name)[1]);
}

bool ComparatorInAlphabet(const Student* student1, const Student* student2) {
    return std::tie(GetSurandname((*student1).name)[1], (*student1).birth_date.year, (*student1).birth_date.month,
                    (*student1).birth_date.day) < std::tie(GetSurandname((*student2).name)[1],
                                                           (*student2).birth_date.year, (*student2).birth_date.month,
                                                           (*student2).birth_date.day);
}

AdmissionTable FillUniversities(const std::vector<University>& universities, const std::vector<Applicant>& applicants) {
    std::unordered_map<std::string, std::vector<const Student*>> admission_results;
    std::vector<const Applicant*> sorted_applicants;
    std::unordered_map<std::string, size_t> universities_number;
    for (auto& university : universities) {
        std::vector<const Student*> applicants_in_university;
        admission_results[university.name] = applicants_in_university;
        universities_number[university.name] = university.max_students;
    }
    for (const auto& applicant : applicants) {
        sorted_applicants.emplace_back(&applicant);
    }
    sort(sorted_applicants.begin(), sorted_applicants.end(), ComparatorWithPoints);
    for (auto it_stud = sorted_applicants.begin(); it_stud != sorted_applicants.end(); ++it_stud) {
        for (auto it_univ = (*it_stud)->wish_list.begin(); it_univ != (*it_stud)->wish_list.end(); ++it_univ) {
            if (universities_number[*(it_univ)] >= 1) {
                admission_results[*(it_univ)].push_back(&(*it_stud)->student);
                --universities_number[*(it_univ)];
                break;
            }
        }
    }
    for (auto it_map = admission_results.begin(); it_map != admission_results.end(); ++it_map) {
        sort(it_map->second.begin(), it_map->second.end(), ComparatorInAlphabet);
    }
    return admission_results;
}