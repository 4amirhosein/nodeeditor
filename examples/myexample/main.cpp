#include <nodes/NodeData>
#include <nodes/FlowScene>
#include <nodes/FlowView>
#include <QtWidgets/QApplication>
#include <nodes/DataModelRegistry>
#include <QProcess>
#include "FileInput.hpp"
#include "FileProcessor.hpp"
#include "FileOutput.hpp"
#include "TikaProcessor.hpp"
#include "AnyFileInput.hpp"


using QtNodes::DataModelRegistry;
using QtNodes::FlowScene;
using QtNodes::FlowView;


static std::shared_ptr<DataModelRegistry>
registerDataModels()
{
  auto ret = std::make_shared<DataModelRegistry>();

    ret->registerModel<FileInput>();

    ret->registerModel<FileProcessor>();

    ret->registerModel<FileOutput>();

    ret->registerModel<TikaProcessor>();

    ret->registerModel<AnyFileInput>();

  return ret;
}

int
main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  FlowScene scene(registerDataModels());

  FlowView view(&scene);

  view.setWindowTitle("Node-based flow editor");
  view.resize(800, 600);
  view.show();
//  QObject *parent;
//  QProcess *process = new QProcess(parent);
//  QString exec = "java";
//  QStringList params;
//  params << "-jar" << "/home/amir/Apps/tika-app-1.22.jar" << "/home/amir/Desktop/180.1.docx" ;
//  process->start(exec, params);
//  process->waitForFinished();
//  QString output(process->readAllStandardOutput());
//  QString error(process->readAllStandardError());
//  qDebug() << output;
//  qDebug() << error;

  return app.exec();
}
