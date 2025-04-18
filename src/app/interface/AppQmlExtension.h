#pragma once
#include "NonCopyable.h"
#include <string>
namespace AppFrame
{
class AppQmlExtension : public NonCopyable
{
  public:
    // 统一调用 接口区域
    static std::string refreshMainPage(const std::string &data = "");
};
} // namespace AppFrame