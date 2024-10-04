#include <QApplication>

#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>

#include <Qt3DRender/QPointLight>
#include <Qt3DRender/QCamera>

#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DExtras/QForwardRenderer>
#include <Qt3DExtras/QCuboidMesh>
#include <Qt3DExtras/QPhongMaterial>

#include "mycameracontroller.h"

		
int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	
	// 3d 窗口
	auto window3d = new Qt3DExtras::Qt3DWindow;
	window3d->defaultFrameGraph()->setClearColor(QColor(QRgb(0xdadada)));

	// 相机实体(Qt3DWindow自带)
	auto cameraEntity = window3d->camera();
	cameraEntity->setPosition(QVector3D(0.0, 0, 5.0f));
	cameraEntity->setViewCenter(QVector3D(0, 0, 0));


	// 以下均为场景内容
	// 根实体
	auto rootEntity = new Qt3DCore::QEntity;

	// 相机控制器
	auto cameraController = new MyCameraController(rootEntity);
	cameraController->setCamera(cameraEntity);

	// 灯实体
	auto lightEntity = new Qt3DCore::QEntity(rootEntity);
	auto light = new Qt3DRender::QPointLight;
	light->setColor("white");
	light->setIntensity(1);

	auto lightTransform = new Qt3DCore::QTransform;
	lightTransform->setTranslation(cameraEntity->position());

	lightEntity->addComponent(light);
	lightEntity->addComponent(lightTransform);

	// 立方体
	auto boxEntity = new Qt3DCore::QEntity(rootEntity);
	auto boxMesh = new Qt3DExtras::QCuboidMesh;
	auto boxMaterial = new Qt3DExtras::QPhongMaterial;
	boxMaterial->setDiffuse(QColor(255,0,0));
	boxEntity->addComponent(boxMesh);
	boxEntity->addComponent(boxMaterial);

	// 设置根实体
	window3d->setRootEntity(rootEntity);
	window3d->show();

	return app.exec();
}
