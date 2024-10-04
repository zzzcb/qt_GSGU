#include <QApplication>

#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>

#include <Qt3DRender/QPointLight>
#include <Qt3DRender/QCamera>

#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DExtras/QForwardRenderer>
#include <Qt3DExtras/QCuboidMesh>
#include <Qt3DExtras/QPhongMaterial>
		
int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	
	// 3d 窗口
	auto window3d = new Qt3DExtras::Qt3DWindow;
	window3d->defaultFrameGraph()->setClearColor(QColor(QRgb(0x4d4d4f)));

	// 相机实体(Qt3DWindow自带)
	auto cameraEntity = window3d->camera();
	cameraEntity->setPosition(QVector3D(0, 0, 5.0f));
	cameraEntity->setViewCenter(QVector3D(0, 0, 0));

	// 以下均为场景内容
	// 根实体
	auto rootEntity = new Qt3DCore::QEntity;

	// 灯实体
	auto lightEntity = new Qt3DCore::QEntity(rootEntity);
	auto light = new Qt3DRender::QPointLight;
	light->setColor("white");
	light->setIntensity(1);

	auto lightTransform = new Qt3DCore::QTransform;
	lightTransform->setTranslation(cameraEntity->position());

	lightEntity->addComponent(light);
	lightEntity->addComponent(lightTransform);

	// 正方体
	auto cuboidEntity = new Qt3DCore::QEntity(rootEntity);

	auto cuboid = new Qt3DExtras::QCuboidMesh;

	auto cuboidTransform = new Qt3DCore::QTransform;
	cuboidTransform->setTranslation(QVector3D(0,0,0));

	auto cuboidMaterial = new Qt3DExtras::QPhongMaterial();
	cuboidMaterial->setDiffuse(QColor(QRgb(0x665423)));

	cuboidEntity->addComponent(cuboid);
	cuboidEntity->addComponent(cuboidMaterial);
	cuboidEntity->addComponent(cuboidTransform);

	// 设置根实体
	window3d->setRootEntity(rootEntity);
	window3d->show();

	return app.exec();
}
