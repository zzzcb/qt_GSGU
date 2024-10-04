#include "linegeometry.h"

#include <QSize>

LineGeometry::LineGeometry(QNode* parent /*= nullptr*/)
	:QGeometry(parent)
	, m_positionAttribute(nullptr)
	, m_normalAttribute(nullptr)
	, m_vertexBuffer(nullptr)
	, m_indexAttribute(nullptr)
	, m_indexBuffer(nullptr)
{
	m_positionAttribute = new Qt3DCore::QAttribute(this);
	m_normalAttribute = new Qt3DCore::QAttribute(this);
	m_vertexBuffer = new Qt3DCore::QBuffer(this);
	m_indexAttribute = new Qt3DCore::QAttribute(this);
	m_indexBuffer = new Qt3DCore::QBuffer(this);

	const int nVerts = 2;
	const int stride = (3+3) * sizeof(float);

	m_vertexBuffer->setData(generateVertexData());

	m_positionAttribute->setName(Qt3DCore::QAttribute::defaultPositionAttributeName());
	m_positionAttribute->setVertexBaseType(Qt3DCore::QAttribute::Float);
	m_positionAttribute->setVertexSize(3);
	m_positionAttribute->setAttributeType(Qt3DCore::QAttribute::VertexAttribute);
	m_positionAttribute->setBuffer(m_vertexBuffer);
	m_positionAttribute->setByteStride(stride);
	m_positionAttribute->setCount(nVerts);
	addAttribute(m_positionAttribute);

	m_normalAttribute->setName(Qt3DCore::QAttribute::defaultNormalAttributeName());
	m_normalAttribute->setVertexBaseType(Qt3DCore::QAttribute::Float);
	m_normalAttribute->setVertexSize(3);
	m_normalAttribute->setAttributeType(Qt3DCore::QAttribute::VertexAttribute);
	m_normalAttribute->setBuffer(m_vertexBuffer);
	m_normalAttribute->setByteStride(stride);
	m_normalAttribute->setByteOffset(3 * sizeof(float));
	m_normalAttribute->setCount(nVerts);
	addAttribute(m_normalAttribute);

	m_indexBuffer->setData(generateIndexData());
	m_indexAttribute->setAttributeType(Qt3DCore::QAttribute::IndexAttribute);
	m_indexAttribute->setVertexBaseType(Qt3DCore::QAttribute::UnsignedShort);
	m_indexAttribute->setBuffer(m_indexBuffer);
	m_indexAttribute->setCount(2);
	addAttribute(m_indexAttribute);
}

LineGeometry::~LineGeometry()
{

}

QByteArray LineGeometry::generateVertexData() const
{
	QByteArray bufferBytes;

	const int nVerts = 2;
	const quint32 elementSize = (3 + 3);
	const quint32 stride = elementSize * sizeof(float);
	bufferBytes.resize(stride * nVerts);
	float* fptr = reinterpret_cast<float*>(bufferBytes.data());

	*fptr++ = -1;
	*fptr++ = 0;
	*fptr++ = 0;

	*fptr++ = 0;
	*fptr++ = 1;
	*fptr++ = 0;

	*fptr++ = 1;
	*fptr++ = 0;
	*fptr++ = 0;

	*fptr++ = 0;
	*fptr++ = 1;
	*fptr++ = 0;

	return bufferBytes;
}

QByteArray LineGeometry::generateIndexData() const
{
	QByteArray indexBytes;
	indexBytes.resize(2 * sizeof(quint16));
	quint16* indexPtr = reinterpret_cast<quint16*>(indexBytes.data());

	indexPtr[0] = 0;
	indexPtr[1] = 1;

	return indexBytes;
}
