#pragma once
#include "AppFramework.h"
#include "AppMetaFlash.h"
#include "ConcurrentPool.h"
#include "Logger.h"
#include "Utils.h"
#include <yaml-cpp/yaml.h>

namespace AppFrame
{

class AppFrameworkImpl final : public AppFramework
{
  public:
    AppFrameworkImpl();
    ~AppFrameworkImpl() noexcept override;
    inline static AppFrameworkImpl &instance()
    {
        static AppFrameworkImpl instance;
        return instance;
    }
    virtual int run(QQmlApplicationEngine *engine) override;
    virtual QQmlApplicationEngine *getEngine() override;
    virtual QObject *getMeta() override;
    virtual void runAfter(std::string &&taskName, const std::function<void(void)> &task,
                          uint32_t milliseconds = 0) override;
    virtual void runEvery(std::string &&taskName, const std::function<void(void)> &task,
                          uint32_t milliseconds = 0) override;
    virtual std::string expected(const ExpectedFunction &expectedType, const std::string &jsValue) override;
    virtual bool registerExpectation(const ExpectedFunction &expectedType,
                                     std::function<std::string(const std::string &)> &&api) override;
    virtual void quitProgram() override;
    virtual void stop() override;
    virtual void runSolution() override;

  protected:
    // 初始化接口区域
    void loadConfig();
    void initFilePath();
    void initLogger();
    void initSqlHelper();
    void initMetaFlash();
    void initAsyncTask();
    void initNetworkClient();
    void initNetworkServer();
    void initExpectation();                         // 初始化qml扩展调用模块
    void engineLoad(QQmlApplicationEngine *engine); // 加载engine
    void afterInit();                               // 初始化后行为
    void beforClose();                              // 程序关闭前行为

  private:
    // 私有变量区域
    YAML::Node config_;
    std::unordered_map<ExpectedFunction, std::function<std::string(const std::string &)>> mapExpectedFunction_;
    QQmlApplicationEngine *engine_;
    std::unique_ptr<AppMetaFlash> appMeta_ = {};
    std::unique_ptr<ConcurrentPool> taskActuators_ = {};

    QThread plcWorkThread;
};

} // namespace AppFrame