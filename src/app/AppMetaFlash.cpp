#include "AppMetaFlash.h"
#include <QDebug>

AppFrame::AppMetaFlash::AppMetaFlash(QObject *parent) : QObject(parent)
{
    // pageMap初始化
    mapPageName_["main"] = PageIndex::PageMain;
}

QString AppFrame::AppMetaFlash::qmlCallExpected(const ExpectedFunction &functionType, const QString &jsValue)
{
    return appFramework().expected(functionType, jsValue.toStdString()).c_str();
}

void AppFrame::AppMetaFlash::runtimeRoutine(PageIndex itemKey, const QString &value)
{
    static std::unordered_map<PageIndex, std::function<void(const QString &)>> mapSignals_{
        {PageIndex::PageMain, [this](const QString &value) { emit pageMainChange(value); }}};
    auto signal = mapSignals_.find(itemKey);
    if (signal != mapSignals_.end())
    {
        signal->second(value);
    }
}

AppFrame::PageIndex AppFrame::AppMetaFlash::getPageIndex(const std::string &pageName) const
{
    auto iter = mapPageName_.find(pageName);
    if (iter != mapPageName_.end())
    {
        return iter->second;
    }
    return PageIndex::PageNull;
}

std::string AppFrame::AppMetaFlash::getWindName(const std::string &winName) const
{
    auto iter = mapImageWind_.find(winName);
    if (iter != mapImageWind_.end())
    {
        return iter->second;
    }
    return "";
}