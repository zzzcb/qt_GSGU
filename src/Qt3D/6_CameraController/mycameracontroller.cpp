#include "mycameracontroller.h"

#include <Qt3DRender/QCamera>
#include <Qt3DInput/QMouseHandler>

QSize m_windowSize(1920, 1080);

MyCameraController::MyCameraController(Qt3DCore::QNode* parent /*= nullptr*/)
	:QAbstractCameraController(parent)
{
	auto mouseHandler = new Qt3DInput::QMouseHandler(this);
	mouseHandler->setSourceDevice(mouseDevice());

	QObject::connect(mouseHandler, &Qt3DInput::QMouseHandler::wheel, this,&MyCameraController::slot_wheelEvent);

	QObject::connect(mouseHandler, &Qt3DInput::QMouseHandler::pressed, this, &MyCameraController::slot_mousePressEvent);
	QObject::connect(mouseHandler, &Qt3DInput::QMouseHandler::positionChanged, this, &MyCameraController::slot_mouseMoveEvent);
}

MyCameraController::~MyCameraController()
{

}

void MyCameraController::slot_wheelEvent(Qt3DInput::QWheelEvent* wheel)
{
	return;
	// wheel->x() << wheel->y();  鼠标的位置

	auto theCamera = camera();
	if (theCamera == nullptr)
		return;

	// 获取滚轮增量 120
	int delta = wheel->angleDelta().y(); 

	// 设定缩放速度，调整这个值以控制缩放的灵敏度
	float zoomSpeed = 0.01f;

	QVector3D newPosition = theCamera->position() + QVector3D(0, 0, -delta* zoomSpeed);

	// 更新相机位置
	theCamera->setPosition(newPosition);
}

void MyCameraController::slot_mousePressEvent(Qt3DInput::QMouseEvent* mouse)
{
	mouse->setAccepted(true);
	m_mouseLastPosition = QPoint(mouse->x(), mouse->y());
	m_mouseCurrentPosition = m_mouseLastPosition;

}

void MyCameraController::slot_mouseMoveEvent(Qt3DInput::QMouseEvent* mouse)
{
	mouse->setAccepted(true);
	m_mouseCurrentPosition = QPoint(mouse->x(),mouse->y());
}

QVector3D projectToTrackball(const QPoint& screenCoords)
{
	float m_trackballSize = 1.0;

	float sx = screenCoords.x(), sy = m_windowSize.height() - screenCoords.y();

	QVector2D p2d(sx / m_windowSize.width() - 0.5f, sy / m_windowSize.height() - 0.5f);
	//qDebug()<<p2d;

	float z = 0.0f;
	float r2 = m_trackballSize * m_trackballSize;
	if (p2d.lengthSquared() <= r2 * 0.5f) {
		z = sqrt(r2 - p2d.lengthSquared());
	}
	else {
		z = r2 * 0.5f / p2d.length();
	}
	QVector3D p3d(p2d, z);
	//qDebug()<<p3d;
	return p3d;
}

float clamp(float x)
{
	return x > 1 ? 1 : (x < -1 ? -1 : x);
}

void createRotation(const QPoint& firstPoint, const QPoint& nextPoint,
	QVector3D& dir, float& angle)
{
	auto lastPos3D = projectToTrackball(firstPoint).normalized();
	auto currentPos3D = projectToTrackball(nextPoint).normalized();

	// Compute axis of rotation:
	dir = QVector3D::crossProduct(currentPos3D, lastPos3D);

	// Approximate rotation angle:
	//qDebug()<<"dot:"<<QVector3D::dotProduct(currentPos3D, lastPos3D);
	angle = acos(clamp(QVector3D::dotProduct(currentPos3D, lastPos3D)));

	//qDebug()<<"dir:"<<dir<<"angle:"<<angle;
}

void MyCameraController::moveCamera(const InputState& state, float dt)
{
	auto theCamera = camera();
	if (theCamera == nullptr)
		return;

	auto ls = linearSpeed();

	// 平移
	if (state.shiftKeyActive && state.leftMouseButtonActive)
	{
		auto offset = m_mouseCurrentPosition - m_mouseLastPosition;
		theCamera->translate(QVector3D(-offset.x() / float(m_windowSize.width()) * ls,
			offset.y() / float(m_windowSize.height()) * ls,
			0));
	}
	// 旋转
	else if (state.leftMouseButtonActive) 
	{
		QVector3D dir;
		float angle;
		createRotation(m_mouseLastPosition, m_mouseCurrentPosition, dir, angle);

		auto currentRotation = theCamera->transform()->rotation();

		auto rotatedAxis = currentRotation.rotatedVector(dir);
		float m_rotationSpeed = 5;
		angle *= m_rotationSpeed;

		theCamera->rotateAboutViewCenter(QQuaternion::fromAxisAndAngle(rotatedAxis, angle * M_1_PI * 180));
	}
	// 缩放
	else if (dt != 0)
	{
		theCamera->translate(QVector3D(state.txAxisValue * ls,
			state.tyAxisValue * ls,
			state.tzAxisValue * ls) * dt,
			Qt3DRender::QCamera::DontTranslateViewCenter);
	}

	m_mouseLastPosition = m_mouseCurrentPosition;
}
