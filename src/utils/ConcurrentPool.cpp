#include "ConcurrentPool.h"
#include <Logger.h>
#include <QTimer>
#include <QtConcurrent/QtConcurrent>
#include <fmt/core.h>

ConcurrentPool::ConcurrentPool() : QObject(nullptr)
{
    auto threadPool = QThreadPool::globalInstance();
    threadSize_ = threadPool->maxThreadCount();

    auto maxCount = (threadSize_ >= 12 ? threadSize_ * 3 / 4 : threadSize_ / 2);
    threadPool->setMaxThreadCount(maxCount);
    LogInfo("ConcurrentPool maxSize: {},  maxCount: {}", threadSize_, maxCount);
}

ConcurrentPool::~ConcurrentPool()
{
}

void ConcurrentPool::runAfter(const std::string &funcName, const std::function<void(void)> &task, uint32_t milliseconds)
{
    if (milliseconds > 0)
    {
        QTimer::singleShot(milliseconds, [this, funcName, task]() mutable { runTask(funcName, task); });
    }
    else
    {
        runTask(funcName, task);
    }
}

void ConcurrentPool::runEvery(const std::string &funcName, const std::function<void(void)> &task, uint32_t milliseconds)
{
    QTimer *timer = new QTimer(this);
    mapTimers_[funcName] = timer;
    mapTasks_[funcName] = task;

    // 绑定定时器的超时信号和任务执行逻辑
    QObject::connect(timer, &QTimer::timeout, [this, funcName, timer]() {
        timer->stop();
        timerTask(funcName);
    });

    timer->setInterval(milliseconds);
    timer->start();
}

void ConcurrentPool::start()
{
    // thWatcher_ = std::thread([this]() -> void {
    //     std::unique_lock lock(mtxTask_);
    //     while (bRun_)
    //     {
    //         cvTask_.wait(lock, [this] { return !bRun_ || !inFutures_.empty(); });
    //         if (!bRun_)
    //             break;
    //         // 观察执行中的任务数量
    //         LogInfo("async thread task size:{}", inFutures_.size());

    //         for (auto iter = inFutures_.begin(); iter != inFutures_.end();)
    //         {
    //             if (!(*iter)->isRunning())
    //             {
    //                 iter = inFutures_.erase(iter);
    //             }
    //             else
    //             {
    //                 iter++;
    //             }
    //         }
    //     }
    // });
}

void ConcurrentPool::stop()
{
    bRun_ = false;
    for (auto [name, timer] : mapTimers_)
    {
        timer->stop();
    }
    cvTask_.notify_one();
    if (thWatcher_.joinable())
        thWatcher_.join();
}

void ConcurrentPool::runTask(const std::string &funcName, const std::function<void(void)> &task)
{
    if (!bRun_)
        return;
    auto future = QtConcurrent::run([task]() -> void { task(); });
    if (!future.isRunning())
    {
        LogError("async thread task start error:{}", funcName);
        return;
    }
    // std::unique_ptr<QFutureWatcher<void>> watcher = std::make_unique<QFutureWatcher<void>>();
    // watcher->setFuture(future);
    // std::lock_guard lock(mtxTask_);
    // inFutures_.push_back(std::move(watcher));
    // cvTask_.notify_one();
}
void ConcurrentPool::timerTask(const std::string &funcName)
{
    if (!bRun_)
        return;
    auto future = QtConcurrent::run([this, funcName]() -> void {
        auto iterTask = mapTasks_.find(funcName);
        auto iterTimer = mapTimers_.find(funcName);
        if (iterTask != mapTasks_.end() && iterTimer != mapTimers_.end())
        {
            iterTask->second();
            QMetaObject::invokeMethod(this, [timer = iterTimer->second]() {
                if (timer)
                    timer->start();
            });
        }
    });
}