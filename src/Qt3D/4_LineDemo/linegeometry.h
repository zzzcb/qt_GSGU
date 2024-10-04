#include <Qt3DCore/QGeometry>
#include <QSize>

class LineGeometry : public Qt3DCore::QGeometry
{
	Q_OBJECT
public:
	explicit LineGeometry(QNode* parent = nullptr);
	~LineGeometry();

private:

	QByteArray generateVertexData() const;
	QByteArray generateIndexData() const;

	Qt3DCore::QAttribute* m_positionAttribute;
	Qt3DCore::QAttribute* m_normalAttribute;
	Qt3DCore::QBuffer* m_vertexBuffer;

	Qt3DCore::QAttribute* m_indexAttribute;
	Qt3DCore::QBuffer* m_indexBuffer;
};
