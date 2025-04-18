#include "AppQmlExtension.h"
#include "AppFramework.h"
#include "AppMetaFlash.h"
#include "LogWapper.h"
#include "Logger.h"
#include "Utils.h"
#include <cstdint>
#include <fmt/chrono.h>
#include <qobject.h>
#include <string>
#include <vector>

std::string AppFrame::AppQmlExtension::refreshMainPage(const std::string &)
{
    appFramework().runAfter("refreshMainPage", [] {
        Json::Value jsMainVal;
        jsMainVal["context"] = "null";
        std::string resJson = Utils::makeResponse(true, std::move(jsMainVal), "refreshMainPage");
        // 调用"runtimeRoutine"函数，传入PageHome和jsonSingleValue
        appFramework().invokeCpp(appFramework().getMeta(), "runtimeRoutine", PageIndex::PageMain,
                                 QString::fromStdString(resJson));
    });

    return Utils::makeResponse(true);
}