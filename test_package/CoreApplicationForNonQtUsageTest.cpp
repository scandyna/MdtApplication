#include <Mdt/CoreApplicationForNonQtUsage>
#include <QDebug>

class BasicToyWorker
{
 public:

  BasicToyWorker()
  {
    qDebug() << "Worker start ...";
  }

  ~BasicToyWorker()
  {
    qDebug() << "Worker end";
  }

};

int main(int argc, char *argv[])
{
  Mdt::CoreApplicationForNonQtUsage<BasicToyWorker> app;

  return 0;
}

