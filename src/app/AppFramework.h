#pragma once
#include "NonCopyable.h"
#include <QObject>
#include <QQmlApplicationEngine>

namespace AppFrame
{

enum class ExpectedFunction
{
    RefreshMainPage = 1 // 刷新主页面数据
};

class AppFramework : public NonCopyable
{
  public:
    virtual ~AppFramework() = default;
    /**
     * @brief 获取应用程序框架的唯一实例
     * @details 该函数返回应用程序框架的唯一实例，是单例模式的实现。该函数不接收任何参数。
     * @return 返回AppFramework类型的引用，表示应用程序框架的唯一实例。
     */
    static AppFramework &instance();
    virtual int run(QQmlApplicationEngine *) = 0;
    virtual QQmlApplicationEngine *getEngine() = 0;
    virtual QObject *getMeta() = 0;
    virtual void runAfter(std::string &&taskName, const std::function<void(void)> &task, uint32_t milliseconds = 0) = 0;
    virtual void runEvery(std::string &&taskName, const std::function<void(void)> &task, uint32_t milliseconds = 0) = 0;
    virtual std::string expected(const ExpectedFunction &expectedType, const std::string &jsValue) = 0;
    virtual bool registerExpectation(const ExpectedFunction &expectedType,
                                     std::function<std::string(const std::string &)> &&api) = 0;
    virtual void stop() = 0;
    virtual void quitProgram() = 0;
    virtual void runSolution() = 0;

  public:
    // 注册插件
    template <typename InputType> void registerPlugin(std::unique_ptr<QObject> &&obj)
    {
        plugins_[InputType::staticMetaObject.className()] = std::move(obj);
    }

    // 获取插件
    template <typename NeedType> NeedType *getPlugin()
    {
        const auto &name = NeedType::staticMetaObject.className();
        auto it = plugins_.find(name);
        if (it != plugins_.end())
        {
            return qobject_cast<NeedType *>(it->second.get());
        }
        else
        {
            return nullptr;
        }
    }

    // 调用C++ 对象函数工具
    template <typename... Args> bool invokeCpp(QObject *object, const char *functionName, Args &&...arguments)
    {
        bool success = false;
        if (object)
        {
            // QVariantList vls{QVariant::fromValue(std::forward<Args>(arguments))...};
            success =
                QMetaObject::invokeMethod(object, functionName, Qt::AutoConnection, std::forward<Args>(arguments)...);
        }
        return success;
    }
    std::unordered_map<std::string, std::unique_ptr<QObject>> plugins_;
};
inline AppFramework &appFramework()
{
    return AppFramework::instance();
}
} // namespace AppFrame
