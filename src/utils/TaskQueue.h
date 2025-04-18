#pragma once
#include "NonCopyable.h"
#include <functional>
#include <future>
#include <string>
class TaskQueue : public AppFrame::NonCopyable
{
  public:
    virtual void runTaskInQueue(const std::string &, const std::function<void()> &task) = 0;
    virtual void runTaskInQueue(std::string &&, std::function<void()> &&task) = 0;
    virtual std::string getName() const
    {
        return "";
    };

    void syncTaskInQueue(const std::function<void()> &task)
    {
        std::promise<int> prom;
        std::future<int> fut = prom.get_future();
        runTaskInQueue("", [&]() {
            task();
            prom.set_value(1);
        });
        fut.get();
    };
    virtual ~TaskQueue()
    {
    }
};