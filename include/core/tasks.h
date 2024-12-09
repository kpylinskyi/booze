#ifndef TASKS_H
#define TASKS_H

#include "core/cmd/cmd.h"

#include <vector>
#include <future>

class Tasks
{
public:
    static Tasks &getInstance();

    void addCmdTask(std::future<const CmdResult &> &&cmd_task);

    void processPendingTasks();

private:
    Tasks();

    std::vector<std::future<const CmdResult &>> pending_cmd_tasks_;
    std::mutex mutex_;
};

#endif // TASKS_H