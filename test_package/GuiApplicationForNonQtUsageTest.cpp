#include <Mdt/GuiApplicationForNonQtUsage>
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
  Mdt::GuiApplicationForNonQtUsage<BasicToyWorker> app;

  return 0;
}

