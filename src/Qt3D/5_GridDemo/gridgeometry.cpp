#include "gridgeometry.h"

#include <QSize>

GridGeometry::GridGeometry(int count, float length, QNode* parent /*= nullptr*/)
	:QGeometry(parent)
	, m_positionAttribute(nullptr)
	, m_normalAttribute(nullptr)
	, m_vertexBuffer(nullptr)
	, m_indexAttribute(nullptr)
	, m_indexBuffer(nullptr)
	, m_count(count)
	, m_length(length)
{
	m_positionAttribute = new Qt3DCore::QAttribute(this);
	m_normalAttribute = new Qt3DCore::QAttribute(this);
	m_vertexBuffer = new Qt3DCore::QBuffer(this);
	m_indexAttribute = new Qt3DCore::QAttribute(this);
	m_indexBuffer = new Qt3DCore::QBuffer(this);

	const int nVerts = 2 * (m_count + 1) * 2;
	const int stride = (3 + 3) * sizeof(float);
	const int lines = 2 * (m_count + 1);

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
	m_indexAttribute->setCount(2 * lines);
	addAttribute(m_indexAttribute);
}

GridGeometry::~GridGeometry()
{

}

QByteArray GridGeometry::generateVertexData() const
{
	QByteArray bufferBytes;

	const int nVerts = 2 * (m_count + 1) * 2;
	const quint32 elementSize = (3 + 3);
	const quint32 stride = elementSize * sizeof(float);
	bufferBytes.resize(stride * nVerts);
	float* fptr = reinterpret_cast<float*>(bufferBytes.data());

	float z0 = -m_length * m_count / 2.;
	float x0 = z0;

	//along z 
	for (int i = 0; i < (m_count + 1); ++i)
	{
		float x = i * m_length + x0;

		//position
		*fptr++ = x;
		*fptr++ = 0.;
		*fptr++ = z0;
		//normal
		*fptr++ = 0.;
		*fptr++ = 1.;
		*fptr++ = 0.;

		//position
		*fptr++ = x;
		*fptr++ = 0.;
		*fptr++ = -z0;
		//normal
		*fptr++ = 0.;
		*fptr++ = 1.;
		*fptr++ = 0.;
	}


	//along x 
	for (int i = 0; i < (m_count + 1); ++i)
	{
		float z = i * m_length + z0;

		//position
		*fptr++ = x0;
		*fptr++ = 0.;
		*fptr++ = z;
		//normal
		*fptr++ = 0.;
		*fptr++ = 1.;
		*fptr++ = 0.;

		//position
		*fptr++ = -x0;
		*fptr++ = 0.;
		*fptr++ = z;
		//normal
		*fptr++ = 0.;
		*fptr++ = 1.;
		*fptr++ = 0.;
	}

	return bufferBytes;
}

QByteArray GridGeometry::generateIndexData() const
{
	QByteArray indexBytes;
	int lines = 2 * (m_count + 1);
	indexBytes.resize(2 * lines * sizeof(quint16));
	quint16* indexPtr = reinterpret_cast<quint16*>(indexBytes.data());

	for (int i = 0; i < 2*lines; ++i)
	{
		*indexPtr++ = i;
	}

	return indexBytes;
}
