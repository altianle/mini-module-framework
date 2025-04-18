#include "AppFrameworkImpl.h"
#include "AppFramework.h"
#include "AppMetaFlash.h"
#include "AppQmlExtension.h"
#include "AppSourceExtension.h"
#include "HttpClient.h"
#include "Logger.h"
#include "PgsqlHelper.h"
#include "SolutionDynamic.h"
#include "Utils.h"
#include <QQmlContext>
#include <cstdint>
#include <memory>
#include <opencv2/core/mat.hpp>
#include <qdebug.h>
#include <string>
#include <vector>

using namespace AppFrame;
AppFramework &AppFramework::instance()
{
    return AppFrameworkImpl::instance();
}

AppFrame::AppFrameworkImpl::AppFrameworkImpl()
{
}

AppFrame::AppFrameworkImpl::~AppFrameworkImpl() noexcept
{
    if (plcWorkThread.isRunning())
    {
        plcWorkThread.quit();
        plcWorkThread.wait();
    }
}

int AppFrame::AppFrameworkImpl::run(QQmlApplicationEngine *engine)
{
    // 软件开启前的初始化 顺序不可修改
    // initAsyncTask();
    initMetaFlash();
    loadConfig(); // 1 加载配置文件
    initFilePath();
    initLogger();      // 2 初始化日志模块
    initExpectation(); // 3 初始化qml扩展调用模块
    // engineLoad(engine); // 4 qml界面加载
    runSolution();
    afterInit(); // 初始化完成之后行为
    return 0;
}

void AppFrame::AppFrameworkImpl::runSolution()
{
    registerPlugin<SolutionDynamic>(std::make_unique<SolutionDynamic>());
    const auto &solution = getPlugin<SolutionDynamic>();
    std::vector<int> starirs{2, 2, 3, 3, 3, 4};
    std::vector<std::vector<int>> iiVec;
    std::vector<int> vec1{1, 3, 1};
    std::vector<int> vec2{1, 5, 1};
    std::vector<int> vec3{4, 2, 1};
    iiVec.push_back(vec1);
    iiVec.push_back(vec2);
    iiVec.push_back(vec3);
    int res = solution->minPathSum(iiVec);
    LogInfo("last res: {}", res);
}

QQmlApplicationEngine *AppFrame::AppFrameworkImpl::getEngine()
{
    return engine_;
}
QObject *AppFrame::AppFrameworkImpl::getMeta()
{
    return appMeta_.get();
}
void AppFrame::AppFrameworkImpl::runAfter(std::string &&taskName, const std::function<void(void)> &task,
                                          uint32_t milliseconds)
{
    taskActuators_->runAfter(taskName, task, milliseconds);
}
void AppFrame::AppFrameworkImpl::runEvery(std::string &&taskName, const std::function<void(void)> &task,
                                          uint32_t milliseconds)
{
    taskActuators_->runEvery(taskName, task, milliseconds);
}

std::string AppFrame::AppFrameworkImpl::expected(const ExpectedFunction &expectedType, const std::string &jsValue)
{
    // 使用 find 查找迭代器

    auto it = mapExpectedFunction_.find(expectedType);

    // 如果找到，直接调用对应函数
    if (it != mapExpectedFunction_.end())
    {
        return it->second(jsValue);
    }

    // 否则返回默认的错误信息
    return Utils::makeResponse(false, "function not found");
}

bool AppFrame::AppFrameworkImpl::registerExpectation(const ExpectedFunction &expectedType,
                                                     std::function<std::string(const std::string &)> &&api)
{
    // 使用结构化绑定和emplace优化插入
    auto [it, inserted] = mapExpectedFunction_.emplace(expectedType, std::move(api));
    // 返回插入是否成功
    return inserted;
}
void initUdpCamera()
{
}

void AppFrame::AppFrameworkImpl::initExpectation()
{
    registerExpectation(ExpectedFunction::RefreshMainPage, &AppQmlExtension::refreshMainPage);
}

void AppFrame::AppFrameworkImpl::quitProgram()
{
    // 程序关闭
    QCoreApplication::quit();
}
void AppFrame::AppFrameworkImpl::stop()
{
    beforClose();
    if (taskActuators_ != nullptr)
    {
        taskActuators_->stop();
    }
    mapExpectedFunction_.clear();
}

void AppFrame::AppFrameworkImpl::loadConfig()
{
    try
    {
        std::string filePath = qApp->applicationDirPath().toStdString() + "/config.yaml";
        config_ = YAML::LoadFile(filePath);
    }
    catch (const YAML::Exception &e)
    {
        Utils::appExit(-1);
    }
}

void AppFrame::AppFrameworkImpl::initLogger()
{
    // 初始化日志记录器
    std::string logPath = qApp->applicationDirPath().toStdString() + std::string("/logs/") +
                          config_["app"]["log"]["log_file_name"].as<std::string>();
    size_t logLevel = config_["app"]["log"]["log_level"].as<size_t>();
    size_t logFileCount = config_["app"]["log"]["log_file_count"].as<size_t>();
    size_t logFileSize = Utils::anyFromString<size_t>(config_["app"]["log"]["log_file_size"].as<std::string>());
    CLogger::GetLogger().initLogger(logPath, logLevel, logFileSize, logFileCount);
    // appTest().test_s7Client();
}

void AppFrame::AppFrameworkImpl::initSqlHelper()
{
    std::string host = config_["app"]["database"]["host"].as<std::string>();
    uint16_t port = config_["app"]["database"]["port"].as<uint16_t>();
    std::string dbName = config_["app"]["database"]["dbname"].as<std::string>();
    std::string user = config_["app"]["database"]["user"].as<std::string>();
    std::string pwd = "~!dtfs@#";
    if (!PgsqlHelper::getSqlHelper().initSqlHelper(host, port, dbName, user, pwd))
    {
        LogInfo("sqlhelper init failed.");
        Utils::appExit(-1);
    }
}

void AppFrame::AppFrameworkImpl::initFilePath()
{
    uint16_t image_normal_time = config_["app"]["resource"]["image_normal_time"].as<uint16_t>();
    uint16_t image_ng_time = config_["app"]["resource"]["image_ng_time"].as<uint16_t>();
    AppSourceExtension::initFilePath(qApp->applicationDirPath());
    // AppSourceExtension::deleteImage(image_normal_time, image_ng_time, qApp->applicationDirPath());
}

void AppFrame::AppFrameworkImpl::initMetaFlash()
{
    appMeta_ = std::make_unique<AppMetaFlash>();
}
void AppFrame::AppFrameworkImpl::initAsyncTask()
{
    taskActuators_ = std::make_unique<ConcurrentPool>();
    taskActuators_->start();
}

void AppFrame::AppFrameworkImpl::initNetworkClient()
{
}

void AppFrame::AppFrameworkImpl::initNetworkServer()
{
}

void AppFrame::AppFrameworkImpl::afterInit()
{
}

void AppFrame::AppFrameworkImpl::beforClose()
{
}

void AppFrame::AppFrameworkImpl::engineLoad(QQmlApplicationEngine *engine)
{
    // std::string strType = config_["product"]["type"].as<std::string>();
    std::string strType = "line";
    // 加载qml文件
    // Define a mapping for product type to title name and module name
    const std::unordered_map<std::string, std::pair<QString, QString>> productTypeMap = {
        {"line", {"尖庄100毫升光瓶瓶盖数据采集激光打码检测设备", "MainWindow"}},
        {"circle", {"尖庄500毫升光瓶瓶盖数据采集激光打码检测设备", "MainWindow"}},
        {"crossPage", {"RFID读写打骑缝码设备", "MainWindow"}},
        {"lineLabel", {"瓶盒关联贴标打激光码设备", "MainWindow"}},
        {"cap", {"尖庄100毫升光瓶瓶盖在线检测设备", "MainWindow"}},
        {"impurity", {"酒内异物检测设备", "MainWindow"}},
        {"boxApp", {"酒盒外观缺陷检测设备", "MainWindow"}}
        // Add more mappings as needed
    };

    auto it = productTypeMap.find(strType);
    if (it != productTypeMap.end())
    {
        const auto &[titleName, moduleName] = it->second;

        // 注册MyObject类
        engine->rootContext()->setContextProperty("appMetaFlash", getMeta());
        engine->rootContext()->setContextProperty("iconDir",
                                                  "file:///" + qApp->applicationDirPath() + "/ico/"); // 获取当前路径
        engine->rootContext()->setContextProperty("pname", titleName);
        engine->rootContext()->setContextProperty("deviceName", strType.c_str());
        engine->loadFromModule("MiniModuleFramework", moduleName);
        engine_ = engine;
    }
    else
    {
        LogError("product type in config error so engine loadFromModule failed");
        Utils::appExit(-1);
    }
}