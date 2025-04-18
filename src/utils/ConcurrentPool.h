#pragma once
#include <QFutureWatcher>
#include <condition_variable>
#include <cstdint>
#include <functional>
#include <qobject.h>
#include <qtmetamacros.h>
#include <string>
#include <unordered_map>

class ConcurrentPool : QObject
{
    Q_OBJECT
  public:
    explicit ConcurrentPool();
    virtual ~ConcurrentPool();
    void runAfter(const std::string &funcName, const std::function<void(void)> &task,
                  uint32_t milliseconds = 0); // 在经过毫秒数后执行任务，默认0立即执行
    void runEvery(const std::string &funcName, const std::function<void(void)> &task,
                  uint32_t milliseconds); // 间隔毫秒数后循环执行任务，0为无间隔
    void start();
    void stop();

  private:
    void runTask(const std::string &funcName, const std::function<void(void)> &task);
    void timerTask(const std::string &funcName);
    uint32_t threadSize_ = 0;
    bool bRun_ = true;
    QFutureWatcher<void> watcher_;
    std::unordered_map<std::string, QTimer *> mapTimers_;
    std::unordered_map<std::string, std::function<void(void)>> mapTasks_;
    std::list<std::unique_ptr<QFutureWatcher<void>>> inFutures_;

    std::condition_variable cvTask_;
    std::mutex mtxTask_;
    std::thread thWatcher_;
};
