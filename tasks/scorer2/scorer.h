#pragma once

#include "../scorer/scorer.h"
#include <map>
#include <set>
#include <string>
#include <vector>

using StudentName = std::string;
using TaskName = std::string;

using ScoreTable = std::map<StudentName, std::set<TaskName>>;

struct TaskInf {
    StudentName student_name;
    TaskName task_name;
    bool checking_approved = false;
    bool request_merged = true;
};

class Scorer {
public:
    void OnCheckFailed(const StudentName& student_name, const TaskName& task_name);
    void OnCheckSuccess(const StudentName& student_name, const TaskName& task_name);
    void OnMergeRequestOpen(const StudentName& student_name, const TaskName& task_name);
    void OnMergeRequestClosed(const StudentName& student_name, const TaskName& task_name);
    void Reset();
    std::map<StudentName, std::map<TaskName, TaskInf>> checking_results;
    std::map<StudentName, std::set<TaskName>> results;
    ScoreTable StudentsResults;

    ScoreTable GetScoreTable() const;
};
