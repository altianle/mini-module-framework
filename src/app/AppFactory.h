#pragma once
#include "AppFramework.h"
#include "AppModule.h"
#include "NonCopyable.h"
#include <memory>
namespace DTFS_Framework
{
class AppFactory : AppFrame::NonCopyable
{
  public:
    static std::unique_ptr<AppModule> createModule(AppFrame::AppFramework &app, const YAML::Node &config)
    {
#ifdef CAMERA
        if (config["Camera"])
        {
        }
#endif
    }
};
} // namespace DTFS_Framework