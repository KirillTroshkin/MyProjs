#include "scorer.h"

struct TaskInf {
    StudentName studentname;
    TaskName taskname;
    bool checking_approved = false;
    bool request_merged = true;
};

bool TimeComp(const Event& event1, const Event& event2) {
    return event1.time < event2.time;
}

ScoreTable GetScoredStudents(const Events& events, time_t score_time) {
    std::map<StudentName, std::map<TaskName, TaskInf>> checking_results;
    std::map<StudentName, std::set<TaskName>> results;
    Events sorted_events;
    for (const auto& event : events) {
        if (event.time <= score_time) {
            sorted_events.push_back(event);
        }
    }
    sort(sorted_events.begin(), sorted_events.end(), TimeComp);
    for (auto it = sorted_events.begin(); it != sorted_events.end(); ++it) {
        TaskInf checking_task;
        checking_task.studentname = (*it).student_name;
        checking_task.taskname = (*it).task_name;
        (checking_results[(*it).student_name])[(*it).task_name] = checking_task;
    }
    for (auto it = sorted_events.begin(); it != sorted_events.end(); ++it) {
        if ((*it).event_type == EventType::CheckFailed) {
            (checking_results[(*it).student_name])[(*it).task_name].checking_approved = false;
        } else if ((*it).event_type == EventType::CheckSuccess) {
            (checking_results[(*it).student_name])[(*it).task_name].checking_approved = true;
        } else if ((*it).event_type == EventType::MergeRequestOpen) {
            (checking_results[(*it).student_name])[(*it).task_name].request_merged = false;
        } else if ((*it).event_type == EventType::MergeRequestClosed) {
            (checking_results[(*it).student_name])[(*it).task_name].request_merged = true;
        }
    }
    for (auto it_students = checking_results.begin(); it_students != checking_results.end(); ++it_students) {
        for (auto it_tasks = checking_results[it_students->first].begin();
             it_tasks != checking_results[it_students->first].end(); ++it_tasks) {
            if (checking_results[it_students->first][it_tasks->first].checking_approved &&
                checking_results[it_students->first][it_tasks->first].request_merged) {
                results[it_students->first].insert(it_tasks->first);
            }
        }
    }
    return results;  // test
}
