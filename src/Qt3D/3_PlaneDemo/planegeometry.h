#include <Qt3DCore/QGeometry>
#include <QSize>

class PlaneGeometry : public Qt3DCore::QGeometry
{
	Q_OBJECT
public:
	explicit PlaneGeometry(QNode* parent = nullptr);
	~PlaneGeometry();


private:

	QByteArray generateVertexData() const;
	QByteArray generateIndexData() const;


	Qt3DCore::QAttribute* m_positionAttribute;
	Qt3DCore::QAttribute* m_texCoordAttribute;
	Qt3DCore::QAttribute* m_normalAttribute;
	Qt3DCore::QAttribute* m_tangentAttribute;
	Qt3DCore::QAttribute* m_indexAttribute;
	Qt3DCore::QBuffer* m_vertexBuffer;
	Qt3DCore::QBuffer* m_indexBuffer;

	float m_width;
	float m_height;
	QSize m_meshResolution;
	bool m_mirrored;
};
