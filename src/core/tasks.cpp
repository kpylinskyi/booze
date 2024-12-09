#include "core/tasks.h"
#include "logger/logger.hpp"

#include <string>
#include <iostream>
#include <chrono>

Tasks::Tasks() {}

Tasks &Tasks::getInstance()
{
    static Tasks instance;
    return instance;
}

void Tasks::addCmdTask(std::future<const CmdResult &> &&cmd_task)
{
    std::lock_guard<std::mutex> lock(mutex_);
    pending_cmd_tasks_.emplace_back(std::move(cmd_task));
}

void Tasks::processPendingTasks()
{
    std::lock_guard<std::mutex> lock(mutex_);
    for (auto it = pending_cmd_tasks_.begin(); it != pending_cmd_tasks_.end();)
    {
        if (it->wait_for(std::chrono::milliseconds(0)) == std::future_status::ready)
        {
            try
            {
                const CmdResult &result = it->get();

                if (result.exit_code == 0)
                {
                    Logger::getInstance().log(LOG_LVL::INF, "cmd: " + result.command);
                    Logger::getInstance().log(LOG_LVL::INF, result.output);
                }
                else
                {
                    Logger::getInstance().log(LOG_LVL::WRN, "cmd: " + result.command);
                    Logger::getInstance().log(LOG_LVL::ERR, "cmd: " + result.error);
                }
            }
            catch (const std::exception &ex)
            {
                Logger::getInstance().log(LOG_LVL::ERR, "exception: " + std::string(ex.what()));
            }

            it = pending_cmd_tasks_.erase(it);
        }
        else
        {
            ++it;
        }
    }
}
