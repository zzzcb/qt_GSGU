#include <QApplication>

#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>

#include <Qt3DRender/QPointLight>
#include <Qt3DRender/QCamera>

#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DExtras/QForwardRenderer>
#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DExtras/QPhongMaterial>

Qt3DCore::QEntity* createAxis(Qt3DCore::QEntity* parent, const QVector3D& direction, const QColor& color)
{
	// 轴实体
	auto axisEntity = new Qt3DCore::QEntity(parent);

	auto cylinder = new Qt3DExtras::QCylinderMesh;
	cylinder->setRadius(0.05); 
	cylinder->setLength(1); 

	auto material = new Qt3DExtras::QPhongMaterial;
	material->setDiffuse(color);

	auto transform = new Qt3DCore::QTransform;
	if (direction == QVector3D(1, 0, 0))
	{
		transform->setRotation(QQuaternion::fromEulerAngles(0, 0, 90)); 
		transform->setTranslation(QVector3D(cylinder->length() / 2.0, 0, 0));
	}
	else if (direction == QVector3D(0, 1, 0)) 
	{
		transform->setTranslation(QVector3D(0, cylinder->length() / 2.0, 0));
	}
	else if (direction == QVector3D(0, 0, 1))
	{
		transform->setRotation(QQuaternion::fromEulerAngles(90, 0, 0));
		transform->setTranslation(QVector3D(0, 0, cylinder->length() / 2.0));
	}


	axisEntity->addComponent(cylinder);
	axisEntity->addComponent(material);
	axisEntity->addComponent(transform);

	return axisEntity;
}
		
int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	
	// 3d 窗口
	auto window3d = new Qt3DExtras::Qt3DWindow;
	window3d->defaultFrameGraph()->setClearColor(QColor(QRgb(0x4d4d4f)));

	// 相机实体(Qt3DWindow自带)
	auto cameraEntity = window3d->camera();
	cameraEntity->setPosition(QVector3D(2, 0, 5));
	cameraEntity->setViewCenter(QVector3D(0, 0, 0));


	// 以下均为场景内容
	// 根实体
	auto rootEntity = new Qt3DCore::QEntity;

	// 世界坐标系
	createAxis(rootEntity, QVector3D(1, 0, 0), QColor(255, 0, 0)); 
	createAxis(rootEntity, QVector3D(0, 1, 0), QColor(0, 255, 0));
	createAxis(rootEntity, QVector3D(0, 0, 1), QColor(0, 0, 255));

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
