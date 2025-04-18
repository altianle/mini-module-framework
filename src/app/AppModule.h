#pragma once
#include <qobject.h>
namespace DTFS_Framework
{
class AppModule : public QObject
{
  public:
    explicit AppModule(QObject *parent = nullptr);
    virtual ~AppModule();
    virtual bool init(const YAML::Node &config) = 0;
    virtual bool start() = 0;
};
} // namespace DTFS_Framework