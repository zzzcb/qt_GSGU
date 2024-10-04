#include <Qt3DCore/QGeometry>
#include <QSize>

class GridGeometry : public Qt3DCore::QGeometry
{
	Q_OBJECT
public:
	explicit GridGeometry(int count,float length,QNode* parent = nullptr);
	~GridGeometry();

private:

	QByteArray generateVertexData() const;
	QByteArray generateIndexData() const;

	Qt3DCore::QAttribute* m_positionAttribute;
	Qt3DCore::QAttribute* m_normalAttribute;
	Qt3DCore::QBuffer* m_vertexBuffer;

	Qt3DCore::QAttribute* m_indexAttribute;
	Qt3DCore::QBuffer* m_indexBuffer;
	
	int m_count;
	float m_length;
};
