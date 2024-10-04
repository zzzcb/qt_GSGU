#include "planegeometry.h"

#include <QSize>

PlaneGeometry::PlaneGeometry(QNode* parent /*= nullptr*/)
	:QGeometry(parent)
	, m_width(1.0f)
	, m_height(1.0f)
	, m_meshResolution(QSize(2, 2))
	, m_mirrored(false)
	, m_positionAttribute(nullptr)
	, m_normalAttribute(nullptr)
	, m_texCoordAttribute(nullptr)
	, m_tangentAttribute(nullptr)
	, m_indexAttribute(nullptr)
	, m_vertexBuffer(nullptr)
	, m_indexBuffer(nullptr)
{
	m_positionAttribute = new Qt3DCore::QAttribute(this);
	m_normalAttribute = new Qt3DCore::QAttribute(this);
	m_texCoordAttribute = new Qt3DCore::QAttribute(this);
	m_tangentAttribute = new Qt3DCore::QAttribute(this);
	m_indexAttribute = new Qt3DCore::QAttribute(this);
	m_vertexBuffer = new Qt3DCore::QBuffer(this);
	m_indexBuffer = new Qt3DCore::QBuffer(this);

	const int nVerts = m_meshResolution.width() * m_meshResolution.height();
	const int stride = (3 + 2 + 3 + 4) * sizeof(float);
	const int faces = 2 * (m_meshResolution.width() - 1) * (m_meshResolution.height() - 1);

	m_positionAttribute->setName(Qt3DCore::QAttribute::defaultPositionAttributeName());
	m_positionAttribute->setVertexBaseType(Qt3DCore::QAttribute::Float);
	m_positionAttribute->setVertexSize(3);
	m_positionAttribute->setAttributeType(Qt3DCore::QAttribute::VertexAttribute);
	m_positionAttribute->setBuffer(m_vertexBuffer);
	m_positionAttribute->setByteStride(stride);
	m_positionAttribute->setCount(nVerts);

	m_texCoordAttribute->setName(Qt3DCore::QAttribute::defaultTextureCoordinateAttributeName());
	m_texCoordAttribute->setVertexBaseType(Qt3DCore::QAttribute::Float);
	m_texCoordAttribute->setVertexSize(2);
	m_texCoordAttribute->setAttributeType(Qt3DCore::QAttribute::VertexAttribute);
	m_texCoordAttribute->setBuffer(m_vertexBuffer);
	m_texCoordAttribute->setByteStride(stride);
	m_texCoordAttribute->setByteOffset(3 * sizeof(float));
	m_texCoordAttribute->setCount(nVerts);

	m_normalAttribute->setName(Qt3DCore::QAttribute::defaultNormalAttributeName());
	m_normalAttribute->setVertexBaseType(Qt3DCore::QAttribute::Float);
	m_normalAttribute->setVertexSize(3);
	m_normalAttribute->setAttributeType(Qt3DCore::QAttribute::VertexAttribute);
	m_normalAttribute->setBuffer(m_vertexBuffer);
	m_normalAttribute->setByteStride(stride);
	m_normalAttribute->setByteOffset(5 * sizeof(float));
	m_normalAttribute->setCount(nVerts);

	m_tangentAttribute->setName(Qt3DCore::QAttribute::defaultTangentAttributeName());
	m_tangentAttribute->setVertexBaseType(Qt3DCore::QAttribute::Float);
	m_tangentAttribute->setVertexSize(4);
	m_tangentAttribute->setAttributeType(Qt3DCore::QAttribute::VertexAttribute);
	m_tangentAttribute->setBuffer(m_vertexBuffer);
	m_tangentAttribute->setByteStride(stride);
	m_tangentAttribute->setByteOffset(8 * sizeof(float));
	m_tangentAttribute->setCount(nVerts);

	m_indexAttribute->setAttributeType(Qt3DCore::QAttribute::IndexAttribute);
	m_indexAttribute->setVertexBaseType(Qt3DCore::QAttribute::UnsignedShort);
	m_indexAttribute->setBuffer(m_indexBuffer);

	// Each primitive has 3 vertives
	m_indexAttribute->setCount(faces * 3);

	m_vertexBuffer->setData(generateVertexData());
	m_indexBuffer->setData(generateIndexData());

	addAttribute(m_positionAttribute);
	addAttribute(m_texCoordAttribute);
	addAttribute(m_normalAttribute);
	addAttribute(m_tangentAttribute);
	addAttribute(m_indexAttribute);
}

PlaneGeometry::~PlaneGeometry()
{

}

QByteArray createPlaneVertexData(float w, float h, const QSize& resolution, bool mirrored)
{
	Q_ASSERT(w > 0.0f);
	Q_ASSERT(h > 0.0f);
	Q_ASSERT(resolution.width() >= 2);
	Q_ASSERT(resolution.height() >= 2);

	const int nVerts = resolution.width() * resolution.height();

	// Populate a buffer with the interleaved per-vertex data with
	// vec3 pos, vec2 texCoord, vec3 normal, vec4 tangent
	const quint32 elementSize = 3 + 2 + 3 + 4;
	const quint32 stride = elementSize * sizeof(float);
	QByteArray bufferBytes;
	bufferBytes.resize(stride * nVerts);
	float* fptr = reinterpret_cast<float*>(bufferBytes.data());

	const float x0 = -w / 2.0f;
	const float z0 = -h / 2.0f;
	const float dx = w / (resolution.width() - 1);
	const float dz = h / (resolution.height() - 1);
	const float du = 1.0 / (resolution.width() - 1);
	const float dv = 1.0 / (resolution.height() - 1);

	// Iterate over z
	for (int j = 0; j < resolution.height(); ++j) {
		const float z = z0 + static_cast<float>(j) * dz;
		const float v = static_cast<float>(j) * dv;

		// Iterate over x
		for (int i = 0; i < resolution.width(); ++i) {
			const float x = x0 + static_cast<float>(i) * dx;
			const float u = static_cast<float>(i) * du;

			// position
			*fptr++ = x;
			*fptr++ = 0.0;
			*fptr++ = z;

			// texture coordinates
			*fptr++ = u;
			*fptr++ = mirrored ? 1.0f - v : v;

			// normal
			*fptr++ = 0.0f;
			*fptr++ = 1.0f;
			*fptr++ = 0.0f;

			// tangent
			*fptr++ = 1.0f;
			*fptr++ = 0.0f;
			*fptr++ = 0.0f;
			*fptr++ = 1.0f;
		}
	}

	return bufferBytes;
}

QByteArray createPlaneIndexData(const QSize& resolution)
{
	// Create the index data. 2 triangles per rectangular face
	const int faces = 2 * (resolution.width() - 1) * (resolution.height() - 1);
	const qsizetype indices = 3 * faces;
	Q_ASSERT(indices < std::numeric_limits<quint16>::max());
	QByteArray indexBytes;
	indexBytes.resize(indices * sizeof(quint16));
	quint16* indexPtr = reinterpret_cast<quint16*>(indexBytes.data());

	// Iterate over z
	for (int j = 0; j < resolution.height() - 1; ++j) {
		const int rowStartIndex = j * resolution.width();
		const int nextRowStartIndex = (j + 1) * resolution.width();

		// Iterate over x
		for (int i = 0; i < resolution.width() - 1; ++i) {
			// Split quad into two triangles
			*indexPtr++ = rowStartIndex + i;
			*indexPtr++ = nextRowStartIndex + i;
			*indexPtr++ = rowStartIndex + i + 1;

			*indexPtr++ = nextRowStartIndex + i;
			*indexPtr++ = nextRowStartIndex + i + 1;
			*indexPtr++ = rowStartIndex + i + 1;
		}
	}

	return indexBytes;
}


QByteArray PlaneGeometry::generateVertexData() const
{
	return createPlaneVertexData(m_width, m_height, m_meshResolution, m_mirrored);
}

QByteArray PlaneGeometry::generateIndexData() const
{
	return createPlaneIndexData(m_meshResolution);
}

