#ifndef MY_CAMERA_CONTROLLER_H
#define MY_CAMERA_CONTROLLER_H

#include <Qt3DExtras/QAbstractCameraController>
#include <Qt3DInput/QWheelEvent>
#include <Qt3DInput/QMouseEvent>
#include <QSize>
#include <QPoint>

class MyCameraController :public Qt3DExtras::QAbstractCameraController
{
	Q_OBJECT
public:
	explicit MyCameraController(Qt3DCore::QNode* parent = nullptr);
	virtual ~MyCameraController();

private slots:
	void slot_wheelEvent(Qt3DInput::QWheelEvent* wheel);

	void slot_mousePressEvent(Qt3DInput::QMouseEvent* mouse);
	void slot_mouseMoveEvent(Qt3DInput::QMouseEvent* mouse);

private:
	void moveCamera(const InputState& state, float dt) override;

	QPoint m_mouseLastPosition, m_mouseCurrentPosition;
};








#endif 