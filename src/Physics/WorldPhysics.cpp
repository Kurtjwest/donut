#include <P3D/Intersect.h>
#include <Physics/WorldPhysics.h>

namespace Donut
{
WorldPhysics::WorldPhysics(LineRenderer* lineRenderer)
{
	_collisionConfiguration = new btDefaultCollisionConfiguration();
	_collisionDispatcher    = new btCollisionDispatcher(_collisionConfiguration);
	_broadphase             = new btDbvtBroadphase();

	_collisionWorld = new btCollisionWorld(_collisionDispatcher, _broadphase, _collisionConfiguration);

	_debugDraw = std::make_unique<BulletDebugDraw>(lineRenderer);
	_debugDraw->setDebugMode(true);

	_collisionWorld->setDebugDrawer(_debugDraw.get());
}

WorldPhysics::~WorldPhysics()
{
	for (auto i = 0; i < _allocatedCollisionObjects.size(); i++)
	{
		if (_collisionWorld != nullptr)
			_collisionWorld->removeCollisionObject(_allocatedCollisionObjects[i]);

		delete _allocatedCollisionObjects[i];
	}

	_allocatedCollisionObjects.clear();

	for (auto i = 0; i < _allocatedVertexArrays.size(); i++)
		delete _allocatedVertexArrays[i];

	_allocatedVertexArrays.clear();

	for (auto i = 0; i < _allocatedIndexArrays.size(); i++)
		delete _allocatedIndexArrays[i];

	_allocatedIndexArrays.clear();

	delete _collisionWorld;
	delete _collisionConfiguration;
	delete _collisionDispatcher;
	delete _broadphase;
}

void WorldPhysics::DebugDraw() const
{
	_collisionWorld->debugDrawWorld();
}

void WorldPhysics::AddIntersect(const P3D::Intersect& intersect)
{
	// copy this shit over first (todo: free it?)
	auto verts   = new std::vector<glm::vec3>(intersect.GetPositions());
	auto indices = new std::vector<uint32_t>(intersect.GetIndices());

	btIndexedMesh indexedMesh;
	indexedMesh.m_vertexBase          = reinterpret_cast<const unsigned char*>(verts->data());
	indexedMesh.m_vertexStride        = sizeof(glm::vec3);
	indexedMesh.m_numVertices         = verts->size();
	indexedMesh.m_triangleIndexBase   = reinterpret_cast<const unsigned char*>(indices->data());
	indexedMesh.m_triangleIndexStride = sizeof(uint32_t) * 3;
	indexedMesh.m_numTriangles        = indices->size() / 3;

	auto meshInterface = new btTriangleIndexVertexArray();
	meshInterface->addIndexedMesh(indexedMesh, PHY_INTEGER);

	auto trimeshShape = new btBvhTriangleMeshShape(meshInterface, true);

	auto colObj = new btCollisionObject();
	colObj->setCollisionShape(trimeshShape);

	_collisionWorld->addCollisionObject(colObj);

	// add for cleanup
	_allocatedCollisionObjects.push_back(colObj);
	_allocatedVertexArrays.push_back(verts);
	_allocatedIndexArrays.push_back(indices);
}

} // namespace Donut