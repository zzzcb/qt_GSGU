#include <QApplication>

#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>

#include <Qt3DRender/QPointLight>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QGeometryRenderer>
#include <Qt3DRender/QMesh>

#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DExtras/QForwardRenderer>
#include <Qt3DExtras/QPhongMaterial>

#include "gridgeometry.h"
#include <Qt3DRender/QGeometryRenderer>


Qt3DCore::QEntity* createGrid(Qt3DCore::QEntity* parent,int count,float length)
{
	auto gridEntity = new Qt3DCore::QEntity(parent);

	// geometry render
	auto gridGeometry = new GridGeometry(count, length);
	auto gridGeometryRender = new Qt3DRender::QGeometryRenderer;
	gridGeometryRender->setPrimitiveType(Qt3DRender::QGeometryRenderer::Lines);

	gridGeometryRender->setGeometry(gridGeometry);

	// red material
	auto redMaterial = new Qt3DExtras::QPhongMaterial;
	redMaterial->setDiffuse(QColor(255, 0, 0));

	gridEntity->addComponent(gridGeometryRender);
	gridEntity->addComponent(redMaterial);

	return gridEntity;
}

int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	
	// 3d 窗口
	auto window3d = new Qt3DExtras::Qt3DWindow;
	window3d->defaultFrameGraph()->setClearColor(QColor(QRgb(0xdadada)));

	// 相机实体(Qt3DWindow自带)
	auto cameraEntity = window3d->camera();
	cameraEntity->setPosition(QVector3D(0, 5, 5));
	cameraEntity->setViewCenter(QVector3D(0, 0, 0));


	// 以下均为场景内容
	// 根实体
	auto rootEntity = new Qt3DCore::QEntity;

	// 自定义平面
	createGrid(rootEntity,20,0.2);

	// 灯实体
	auto lightEntity = new Qt3DCore::QEntity(rootEntity);
	auto light = new Qt3DRender::QPointLight;
	light->setColor("white");
	light->setIntensity(1);

	auto lightTransform = new Qt3DCore::QTransform;
	lightTransform->setTranslation(cameraEntity->position());

	lightEntity->addComponent(light);
	lightEntity->addComponent(lightTransform);


	// 设置根实体
	window3d->setRootEntity(rootEntity);
	window3d->show();

	return app.exec();
}
