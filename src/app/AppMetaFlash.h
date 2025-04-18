#pragma once
#include "AppFramework.h"
#include <QCoreApplication>
#include <QObject>
#include <QString>
#include <QVariant>

namespace AppFrame
{
enum class PageIndex
{
    PageMain = 0,
    PageNull = 999
};
class AppMetaFlash : public QObject
{
    Q_OBJECT
  signals:
    // qml 中响应
    void pageMainChange(const QString &value);

  public:
    explicit AppMetaFlash(QObject *parent = nullptr);
    virtual ~AppMetaFlash()
    {
    }
    virtual PageIndex getPageIndex(const std::string &) const;
    std::string getWindName(const std::string &) const;
  public slots:
    // qml 调用c++接口区域
    QString qmlCallExpected(const ExpectedFunction &functionType, const QString &jsValue);
    // cpp 调用qml接口区域

    /**
     * @brief 将JSON格式的字符串转换为Json::Value对象
     * @param itemName 为每个页面取的title，在本类成员中已经定义
     * @param itemName 对应页面实时数据的json字符串
     * @return 返回转换后的Json::Value对象
     */
    void runtimeRoutine(PageIndex itemKey, const QString &itemValue);

  private:
    // qml (5) Q_PROPERTY 中 属性类型 属性名称 必须一致
    AppMetaFlash(const AppMetaFlash &) = delete;
    AppMetaFlash &operator=(const AppMetaFlash &) = delete;
    std::unordered_map<std::string, PageIndex> mapPageName_;
    std::unordered_map<std::string, std::string> mapImageWind_;
};
} // namespace AppFrame