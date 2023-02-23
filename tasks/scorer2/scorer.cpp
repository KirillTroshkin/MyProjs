#include "scorer.h"

void Scorer::OnCheckFailed(const StudentName& student_name, const TaskName& task_name) {
    (checking_results[student_name])[task_name].checking_approved = false;
    if (results[student_name].count(task_name)) {
        results[student_name].erase(task_name);
    }
    if (results[student_name].empty()) {
        results.erase(student_name);
    }
}
void Scorer::OnCheckSuccess(const StudentName& student_name, const TaskName& task_name) {
    (checking_results[student_name])[task_name].checking_approved = true;
    if ((checking_results[student_name])[task_name].request_merged) {
        results[student_name].insert(task_name);
    }
}
void Scorer::OnMergeRequestClosed(const StudentName& student_name, const TaskName& task_name) {
    (checking_results[student_name])[task_name].request_merged = true;
    if ((checking_results[student_name])[task_name].checking_approved) {
        results[student_name].insert(task_name);
    }
}
void Scorer::OnMergeRequestOpen(const StudentName& student_name, const TaskName& task_name) {
    (checking_results[student_name])[task_name].request_merged = false;
    if (results[student_name].count(task_name)) {
        results[student_name].erase(task_name);
    }
    if (results[student_name].empty()) {
        results.erase(student_name);
    }
}
void Scorer::Reset() {
    results.clear();
}

ScoreTable Scorer::GetScoreTable() const {
    return results;
}
