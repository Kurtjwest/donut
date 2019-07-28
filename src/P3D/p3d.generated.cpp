/*+---------------------------------------------------+
  |    _____        /--------------------------\\     |
  |   /     \\      |                            |    |
  | \\/\\/     |    /  file generated by         |    |
  |  |  (o)(o)    |                  donut tool  |    |
  |  C   .---_)   \\_   _________________________/    |
  |   | |.___|      | /                               |
  |   |  \\__/      <_/                               |
  |   /_____\\                                        |
  |  /_____/ \\                                       |
  | /         \\                                      |
  +---------------------------------------------------+
*/

#include "p3d.generated.h"
#include <Core/MemoryStream.h>
#include <iostream>

namespace Donut::P3D
{
    Animation::Animation(const P3DChunk& chunk)
    {
        assert(chunk.IsType(ChunkType::Animation));

        MemoryStream stream(chunk.GetData());
        _version = stream.Read<uint32_t>();
        _name = stream.ReadLPString();
        _type = stream.ReadString(4);
        _numFrames = stream.Read<float>();
        _frameRate = stream.Read<float>();
        _looping = stream.Read<uint32_t>();

        for (auto const& child : chunk.GetChildren())
        {
            switch (child->GetType())
            {
                case ChunkType::AnimationGroupList:
                    {
                        _groupList = std::make_unique<AnimationGroupList>(*child);
                        break;
                    }
                default:
                    break;
            }
        }
    }

    AnimationGroupList::AnimationGroupList(const P3DChunk& chunk)
    {
        assert(chunk.IsType(ChunkType::AnimationGroupList));

        MemoryStream stream(chunk.GetData());
        _version = stream.Read<uint32_t>();
        _numGroups = stream.Read<uint32_t>();

        for (auto const& child : chunk.GetChildren())
        {
            switch (child->GetType())
            {
                case ChunkType::AnimationGroup:
                    {
                        _groups.push_back(std::make_unique<AnimationGroup>(*child));
                        break;
                    }
                default:
                    break;
            }
        }
    }

    AnimationGroup::AnimationGroup(const P3DChunk& chunk)
    {
        assert(chunk.IsType(ChunkType::AnimationGroup));

        MemoryStream stream(chunk.GetData());
        _version = stream.Read<uint32_t>();
        _name = stream.ReadLPString();
        _groupId = stream.Read<uint32_t>();
        _numChannels = stream.Read<uint32_t>();

        for (auto const& child : chunk.GetChildren())
        {
            switch (child->GetType())
            {
                case ChunkType::Vector2Channel:
                    {
                        _vector2Channel = std::make_unique<Vector2Channel>(*child);
                        break;
                    }
                case ChunkType::Vector3Channel:
                    {
                        _vector3Channel = std::make_unique<Vector3Channel>(*child);
                        break;
                    }
                case ChunkType::QuaternionChannel:
                    {
                        _quaternionChannel = std::make_unique<QuaternionChannel>(*child);
                        break;
                    }
                case ChunkType::CompressedQuaternionChannel:
                    {
                        _compressedQuaternionChannel = std::make_unique<CompressedQuaternionChannel>(*child);
                        break;
                    }
                default:
                    break;
            }
        }
    }

    Vector2Channel::Vector2Channel(const P3DChunk& chunk)
    {
        assert(chunk.IsType(ChunkType::Vector2Channel));

        MemoryStream stream(chunk.GetData());
        _version = stream.Read<uint32_t>();
        _param = stream.ReadString(4);
        _mapping = stream.Read<uint16_t>();
        _constants = stream.Read<glm::vec3>();
        _numFrames = stream.Read<uint32_t>();
        _frames.resize(_numFrames);
        stream.ReadBytes(reinterpret_cast<uint8_t*>(_frames.data()), _frames.size() * sizeof(uint16_t));
        _values.resize(_numFrames);
        stream.ReadBytes(reinterpret_cast<uint8_t*>(_values.data()), _values.size() * sizeof(glm::vec2));
    }

    Vector3Channel::Vector3Channel(const P3DChunk& chunk)
    {
        assert(chunk.IsType(ChunkType::Vector3Channel));

        MemoryStream stream(chunk.GetData());
        _version = stream.Read<uint32_t>();
        _param = stream.ReadString(4);
        _numFrames = stream.Read<uint32_t>();
        _frames.resize(_numFrames);
        stream.ReadBytes(reinterpret_cast<uint8_t*>(_frames.data()), _frames.size() * sizeof(uint16_t));
        _values.resize(_numFrames);
        stream.ReadBytes(reinterpret_cast<uint8_t*>(_values.data()), _values.size() * sizeof(glm::vec3));
    }

    QuaternionChannel::QuaternionChannel(const P3DChunk& chunk)
    {
        assert(chunk.IsType(ChunkType::QuaternionChannel));

        MemoryStream stream(chunk.GetData());
        _version = stream.Read<uint32_t>();
        _param = stream.ReadString(4);
        _numFrames = stream.Read<uint32_t>();
        _frames.resize(_numFrames);
        stream.ReadBytes(reinterpret_cast<uint8_t*>(_frames.data()), _frames.size() * sizeof(uint16_t));
        _values.resize(_numFrames);
        stream.ReadBytes(reinterpret_cast<uint8_t*>(_values.data()), _values.size() * sizeof(glm::quat));
    }

    CompressedQuaternionChannel::CompressedQuaternionChannel(const P3DChunk& chunk)
    {
        assert(chunk.IsType(ChunkType::CompressedQuaternionChannel));

        MemoryStream stream(chunk.GetData());
        _version = stream.Read<uint32_t>();
        _param = stream.ReadString(4);
        _numFrames = stream.Read<uint32_t>();
        _frames.resize(_numFrames);
        stream.ReadBytes(reinterpret_cast<uint8_t*>(_frames.data()), _frames.size() * sizeof(uint16_t));
        _values.resize(_numFrames);
        stream.ReadBytes(reinterpret_cast<uint8_t*>(_values.data()), _values.size() * sizeof(uint64_t));
    }

    Mesh::Mesh(const P3DChunk& chunk)
    {
        assert(chunk.IsType(ChunkType::Mesh));

        MemoryStream stream(chunk.GetData());
        _name = stream.ReadLPString();
        _version = stream.Read<uint32_t>();
        _numPrimGroups = stream.Read<uint32_t>();

        for (auto const& child : chunk.GetChildren())
        {
            switch (child->GetType())
            {
                case ChunkType::PrimitiveGroup:
                    {
                        _primitiveGroups.push_back(std::make_unique<PrimitiveGroup>(*child));
                        break;
                    }
                default:
                    break;
            }
        }
    }

    PolySkin::PolySkin(const P3DChunk& chunk)
    {
        assert(chunk.IsType(ChunkType::PolySkin));

        MemoryStream stream(chunk.GetData());
        _name = stream.ReadLPString();
        _version = stream.Read<uint32_t>();
        _skeletonName = stream.ReadLPString();
        _numPrimGroups = stream.Read<uint32_t>();

        for (auto const& child : chunk.GetChildren())
        {
            switch (child->GetType())
            {
                case ChunkType::PrimitiveGroup:
                    {
                        _primitiveGroups.push_back(std::make_unique<PrimitiveGroup>(*child));
                        break;
                    }
                case ChunkType::BoundingBox:
                    {
                        _boundingBox = std::make_unique<BoundingBox>(*child);
                        break;
                    }
                case ChunkType::BoundingSphere:
                    {
                        _boundingSphere = std::make_unique<BoundingSphere>(*child);
                        break;
                    }
                default:
                    break;
            }
        }
    }

    BoundingBox::BoundingBox(const P3DChunk& chunk)
    {
        assert(chunk.IsType(ChunkType::BoundingBox));

        MemoryStream stream(chunk.GetData());
        _min = stream.Read<glm::vec3>();
        _max = stream.Read<glm::vec3>();
    }

    BoundingSphere::BoundingSphere(const P3DChunk& chunk)
    {
        assert(chunk.IsType(ChunkType::BoundingSphere));

        MemoryStream stream(chunk.GetData());
        _centre = stream.Read<glm::vec3>();
        _radius = stream.Read<float>();
    }

    PrimitiveGroup::PrimitiveGroup(const P3DChunk& chunk)
    {
        assert(chunk.IsType(ChunkType::PrimitiveGroup));

        MemoryStream stream(chunk.GetData());
        _version = stream.Read<uint32_t>();
        _shaderName = stream.ReadLPString();
        _primType = stream.Read<uint32_t>();
        _hasDataFlags = stream.Read<uint32_t>();
        _numVerts = stream.Read<uint32_t>();
        _numIndices = stream.Read<uint32_t>();
        _numMatrices = stream.Read<uint32_t>();

        for (auto const& child : chunk.GetChildren())
        {
            MemoryStream data(child->GetData());

            switch (child->GetType())
            {
                case ChunkType::PositionList:
                    {
                        _vertices.resize(data.Read<uint32_t>());
                        data.ReadBytes(reinterpret_cast<uint8_t*>(_vertices.data()), _vertices.size() * sizeof(glm::vec3));
                        break;
                    }
                case ChunkType::IndexList:
                    {
                        _indices.resize(data.Read<uint32_t>());
                        data.ReadBytes(reinterpret_cast<uint8_t*>(_indices.data()), _indices.size() * sizeof(uint32_t));
                        break;
                    }
                case ChunkType::NormalList:
                    {
                        _normals.resize(data.Read<uint32_t>());
                        data.ReadBytes(reinterpret_cast<uint8_t*>(_normals.data()), _normals.size() * sizeof(glm::vec3));
                        break;
                    }
                case ChunkType::UVList:
                    {
                        uint32_t length = data.Read<uint32_t>();
                        uint32_t channel = data.Read<uint32_t>();
                        _uvs.resize(channel + 1);
                        _uvs.at(channel).resize(length);
                        data.ReadBytes(reinterpret_cast<uint8_t*>(_uvs.at(channel).data()), length * sizeof(glm::vec2));
                        break;
                    }
                case ChunkType::MatrixList:
                    {
                        _matrixList.resize(data.Read<uint32_t>());
                        data.ReadBytes(reinterpret_cast<uint8_t*>(_matrixList.data()), _matrixList.size() * sizeof(uint32_t));
                        break;
                    }
                case ChunkType::WeightList:
                    {
                        _weightList.resize(data.Read<uint32_t>());
                        data.ReadBytes(reinterpret_cast<uint8_t*>(_weightList.data()), _weightList.size() * sizeof(glm::vec3));
                        break;
                    }
                case ChunkType::MatrixPalette:
                    {
                        _matrixPalette.resize(data.Read<uint32_t>());
                        data.ReadBytes(reinterpret_cast<uint8_t*>(_matrixPalette.data()), _matrixPalette.size() * sizeof(uint32_t));
                        break;
                    }
                case ChunkType::ColorList:
                    {
                        _colors.resize(data.Read<uint32_t>());
                        data.ReadBytes(reinterpret_cast<uint8_t*>(_colors.data()), _colors.size() * sizeof(uint32_t));
                        break;
                    }
                default:
                    break;
            }
        }
    }

    Skeleton::Skeleton(const P3DChunk& chunk)
    {
        assert(chunk.IsType(ChunkType::Skeleton));

        MemoryStream stream(chunk.GetData());
        _name = stream.ReadLPString();
        _version = stream.Read<uint32_t>();
        _numJoints = stream.Read<uint32_t>();

        for (auto const& child : chunk.GetChildren())
        {
            switch (child->GetType())
            {
                case ChunkType::SkeletonJoint:
                    {
                        _joints.push_back(std::make_unique<SkeletonJoint>(*child));
                        break;
                    }
                default:
                    break;
            }
        }
    }

    SkeletonJoint::SkeletonJoint(const P3DChunk& chunk)
    {
        assert(chunk.IsType(ChunkType::SkeletonJoint));

        MemoryStream stream(chunk.GetData());
        _name = stream.ReadLPString();
        _parent = stream.Read<uint32_t>();
        _dof = stream.Read<int32_t>();
        _freeAxis = stream.Read<int32_t>();
        _primaryAxis = stream.Read<int32_t>();
        _secondaryAxis = stream.Read<int32_t>();
        _twistAxis = stream.Read<int32_t>();
        _restPose = stream.Read<glm::mat4>();
    }

    StaticEntity::StaticEntity(const P3DChunk& chunk)
    {
        assert(chunk.IsType(ChunkType::StaticEntity));

        MemoryStream stream(chunk.GetData());
        _name = stream.ReadLPString();
        _version = stream.Read<uint32_t>();
        _renderOrder = stream.Read<uint32_t>();

        for (auto const& child : chunk.GetChildren())
        {
            switch (child->GetType())
            {
                case ChunkType::Mesh:
                    {
                        _mesh = std::make_unique<Mesh>(*child);
                        break;
                    }
                default:
                    break;
            }
        }
    }

    StaticPhysics::StaticPhysics(const P3DChunk& chunk)
    {
        assert(chunk.IsType(ChunkType::StaticPhysics));

        MemoryStream stream(chunk.GetData());
        _name = stream.ReadLPString();
    }

    InstancedStaticPhysics::InstancedStaticPhysics(const P3DChunk& chunk)
    {
        assert(chunk.IsType(ChunkType::InstancedStaticPhysics));

        MemoryStream stream(chunk.GetData());
        _name = stream.ReadLPString();

        for (auto const& child : chunk.GetChildren())
        {
            switch (child->GetType())
            {
                case ChunkType::Mesh:
                    {
                        _meshes.push_back(std::make_unique<Mesh>(*child));
                        break;
                    }
                case ChunkType::InstanceList:
                    {
                        _instanceList = std::make_unique<InstanceList>(*child);
                        break;
                    }
                default:
                    break;
            }
        }
    }

    DynamicPhysics::DynamicPhysics(const P3DChunk& chunk)
    {
        assert(chunk.IsType(ChunkType::DynamicPhysics));

        MemoryStream stream(chunk.GetData());
        _name = stream.ReadLPString();

        for (auto const& child : chunk.GetChildren())
        {
            switch (child->GetType())
            {
                case ChunkType::Mesh:
                    {
                        _meshes.push_back(std::make_unique<Mesh>(*child));
                        break;
                    }
                case ChunkType::InstanceList:
                    {
                        _instanceList = std::make_unique<InstanceList>(*child);
                        break;
                    }
                default:
                    break;
            }
        }
    }

    InstanceList::InstanceList(const P3DChunk& chunk)
    {
        assert(chunk.IsType(ChunkType::InstanceList));

        MemoryStream stream(chunk.GetData());
        _name = stream.ReadLPString();

        for (auto const& child : chunk.GetChildren())
        {
            switch (child->GetType())
            {
                case ChunkType::SceneGraph:
                    {
                        _sceneGraph = std::make_unique<SceneGraph>(*child);
                        break;
                    }
                default:
                    break;
            }
        }
    }

    SceneGraph::SceneGraph(const P3DChunk& chunk)
    {
        assert(chunk.IsType(ChunkType::SceneGraph));

        MemoryStream stream(chunk.GetData());
        _name = stream.ReadLPString();

        for (auto const& child : chunk.GetChildren())
        {
            switch (child->GetType())
            {
                case ChunkType::SceneGraphRoot:
                    {
                        _root = std::make_unique<SceneGraphRoot>(*child);
                        break;
                    }
                default:
                    break;
            }
        }
    }

    SceneGraphRoot::SceneGraphRoot(const P3DChunk& chunk)
    {
        assert(chunk.IsType(ChunkType::SceneGraphRoot));

        MemoryStream stream(chunk.GetData());
        
        for (auto const& child : chunk.GetChildren())
        {
            switch (child->GetType())
            {
                case ChunkType::SceneGraphBranch:
                    {
                        _branch = std::make_unique<SceneGraphBranch>(*child);
                        break;
                    }
                default:
                    break;
            }
        }
    }

    SceneGraphBranch::SceneGraphBranch(const P3DChunk& chunk)
    {
        assert(chunk.IsType(ChunkType::SceneGraphBranch));

        MemoryStream stream(chunk.GetData());
        _name = stream.ReadLPString();

        for (auto const& child : chunk.GetChildren())
        {
            switch (child->GetType())
            {
                case ChunkType::SceneGraphTransform:
                    {
                        _children.push_back(std::make_unique<SceneGraphTransform>(*child));
                        break;
                    }
                default:
                    break;
            }
        }
    }

    SceneGraphTransform::SceneGraphTransform(const P3DChunk& chunk)
    {
        assert(chunk.IsType(ChunkType::SceneGraphTransform));

        MemoryStream stream(chunk.GetData());
        _name = stream.ReadLPString();
        _numChildren = stream.Read<uint32_t>();
        _transform = stream.Read<glm::mat4>();

        for (auto const& child : chunk.GetChildren())
        {
            switch (child->GetType())
            {
                case ChunkType::SceneGraphTransform:
                    {
                        _children.push_back(std::make_unique<SceneGraphTransform>(*child));
                        break;
                    }
                case ChunkType::SceneGraphDrawable:
                    {
                        _drawables.push_back(std::make_unique<SceneGraphDrawable>(*child));
                        break;
                    }
                default:
                    break;
            }
        }
    }

    SceneGraphDrawable::SceneGraphDrawable(const P3DChunk& chunk)
    {
        assert(chunk.IsType(ChunkType::SceneGraphDrawable));

        MemoryStream stream(chunk.GetData());
        _name = stream.ReadLPString();

        for (auto const& child : chunk.GetChildren())
        {
            MemoryStream data(child->GetData());

            switch (child->GetType())
            {
                case ChunkType::SceneGraphSortOrder:
                    {
                        _sortOrder = data.Read<float>();
                        break;
                    }
                default:
                    break;
            }
        }
    }

    Shader::Shader(const P3DChunk& chunk)
    {
        assert(chunk.IsType(ChunkType::Shader));

        MemoryStream stream(chunk.GetData());
        _name = stream.ReadLPString();
        _version = stream.Read<uint32_t>();
        _pddiShaderName = stream.ReadLPString();
        _isTrans = stream.Read<uint32_t>();
        _vertexNeeds = stream.Read<uint32_t>();
        _vertexMask = stream.Read<uint32_t>();
        _numParams = stream.Read<uint32_t>();

        for (auto const& child : chunk.GetChildren())
        {
            switch (child->GetType())
            {
                case ChunkType::ShaderTextureParam:
                    {
                        _textureParams.push_back(std::make_unique<ShaderTextureParam>(*child));
                        break;
                    }
                default:
                    break;
            }
        }
    }

    ShaderTextureParam::ShaderTextureParam(const P3DChunk& chunk)
    {
        assert(chunk.IsType(ChunkType::ShaderTextureParam));

        MemoryStream stream(chunk.GetData());
        _key = stream.ReadString(4);
        _value = stream.ReadLPString();
    }

    CompositeDrawable::CompositeDrawable(const P3DChunk& chunk)
    {
        assert(chunk.IsType(ChunkType::CompositeDrawable));

        MemoryStream stream(chunk.GetData());
        _name = stream.ReadLPString();
        _skeletonName = stream.ReadLPString();

        for (auto const& child : chunk.GetChildren())
        {
            switch (child->GetType())
            {
                case ChunkType::CompositeDrawablePropList:
                    {
                        _propList = std::make_unique<CompositeDrawablePropList>(*child);
                        break;
                    }
                default:
                    break;
            }
        }
    }

    CompositeDrawablePropList::CompositeDrawablePropList(const P3DChunk& chunk)
    {
        assert(chunk.IsType(ChunkType::CompositeDrawablePropList));

        MemoryStream stream(chunk.GetData());
        _numElements = stream.Read<uint32_t>();

        for (auto const& child : chunk.GetChildren())
        {
            switch (child->GetType())
            {
                case ChunkType::CompositeDrawableProp:
                    {
                        _props.push_back(std::make_unique<CompositeDrawableProp>(*child));
                        break;
                    }
                default:
                    break;
            }
        }
    }

    CompositeDrawableProp::CompositeDrawableProp(const P3DChunk& chunk)
    {
        assert(chunk.IsType(ChunkType::CompositeDrawableProp));

        MemoryStream stream(chunk.GetData());
        _name = stream.ReadLPString();
        _isTrans = stream.Read<uint32_t>();
        _skeletonJoint = stream.Read<uint32_t>();
    }

    Intersect::Intersect(const P3DChunk& chunk)
    {
        assert(chunk.IsType(ChunkType::Intersect));

        MemoryStream stream(chunk.GetData());
        _indices.resize(stream.Read<uint32_t>());
        stream.ReadBytes(reinterpret_cast<uint8_t*>(_indices.data()), _indices.size() * sizeof(uint32_t));
        _positions.resize(stream.Read<uint32_t>());
        stream.ReadBytes(reinterpret_cast<uint8_t*>(_positions.data()), _positions.size() * sizeof(glm::vec3));
        _normals.resize(stream.Read<uint32_t>());
        stream.ReadBytes(reinterpret_cast<uint8_t*>(_normals.data()), _normals.size() * sizeof(glm::vec3));

        for (auto const& child : chunk.GetChildren())
        {
            switch (child->GetType())
            {
                case ChunkType::BoundingBox:
                    {
                        _bounds = std::make_unique<BoundingBox>(*child);
                        break;
                    }
                default:
                    break;
            }
        }
    }

    WorldSphere::WorldSphere(const P3DChunk& chunk)
    {
        assert(chunk.IsType(ChunkType::WorldSphere));

        MemoryStream stream(chunk.GetData());
        _name = stream.ReadLPString();
        _version = stream.Read<uint32_t>();
        _meshCount = stream.Read<uint32_t>();
        _billboardCount = stream.Read<uint32_t>();

        for (auto const& child : chunk.GetChildren())
        {
            switch (child->GetType())
            {
                case ChunkType::Mesh:
                    {
                        _meshes.push_back(std::make_unique<Mesh>(*child));
                        break;
                    }
                default:
                    break;
            }
        }
    }

    BillboardQuad::BillboardQuad(const P3DChunk& chunk)
    {
        assert(chunk.IsType(ChunkType::BillboardQuad));

        MemoryStream stream(chunk.GetData());
        _version = stream.Read<uint32_t>();
        _name = stream.ReadLPString();
        _mode = stream.ReadString(4);
        _translation = stream.Read<glm::vec3>();
        _color = stream.Read<uint32_t>();
        _uv0 = stream.Read<glm::vec2>();
        _uv1 = stream.Read<glm::vec2>();
        _uv2 = stream.Read<glm::vec2>();
        _uv3 = stream.Read<glm::vec2>();
        _width = stream.Read<float>();
        _height = stream.Read<float>();
        _distance = stream.Read<float>();
        _uvOffset = stream.Read<glm::vec2>();
    }

    BillboardQuadGroup::BillboardQuadGroup(const P3DChunk& chunk)
    {
        assert(chunk.IsType(ChunkType::BillboardQuadGroup));

        MemoryStream stream(chunk.GetData());
        _version = stream.Read<uint32_t>();
        _name = stream.ReadLPString();
        _shader = stream.ReadLPString();
        _zTest = stream.Read<uint32_t>();
        _zWrite = stream.Read<uint32_t>();
        _fog = stream.Read<uint32_t>();
        _quadCount = stream.Read<uint32_t>();

        for (auto const& child : chunk.GetChildren())
        {
            switch (child->GetType())
            {
                case ChunkType::BillboardQuad:
                    {
                        _quads.push_back(std::make_unique<BillboardQuad>(*child));
                        break;
                    }
                default:
                    break;
            }
        }
    }

    Texture::Texture(const P3DChunk& chunk)
    {
        assert(chunk.IsType(ChunkType::Texture));

        MemoryStream stream(chunk.GetData());
        _name = stream.ReadLPString();
        _version = stream.Read<uint32_t>();
        _width = stream.Read<uint32_t>();
        _height = stream.Read<uint32_t>();
        _bpp = stream.Read<uint32_t>();
        _alphaDepth = stream.Read<uint32_t>();
        _numMipMaps = stream.Read<uint32_t>();
        _textureType = stream.Read<uint32_t>();
        _usage = stream.Read<uint32_t>();
        _priority = stream.Read<uint32_t>();

        for (auto const& child : chunk.GetChildren())
        {
            switch (child->GetType())
            {
                case ChunkType::Image:
                    {
                        _image = std::make_unique<Image>(*child);
                        break;
                    }
                default:
                    break;
            }
        }
    }

    Image::Image(const P3DChunk& chunk)
    {
        assert(chunk.IsType(ChunkType::Image));

        MemoryStream stream(chunk.GetData());
        _name = stream.ReadLPString();
        _version = stream.Read<uint32_t>();
        _width = stream.Read<uint32_t>();
        _height = stream.Read<uint32_t>();
        _bpp = stream.Read<uint32_t>();
        _palettized = stream.Read<uint32_t>();
        _hasAlpha = stream.Read<uint32_t>();
        _format = stream.Read<uint32_t>();

        for (auto const& child : chunk.GetChildren())
        {
            MemoryStream data(child->GetData());

            switch (child->GetType())
            {
                case ChunkType::ImageData:
                    {
                        _data.resize(data.Read<uint32_t>());
                        data.ReadBytes(reinterpret_cast<uint8_t*>(_data.data()), _data.size() * sizeof(uint8_t));
                        break;
                    }
                default:
                    break;
            }
        }
    }

    TextureFont::TextureFont(const P3DChunk& chunk)
    {
        assert(chunk.IsType(ChunkType::TextureFont));

        MemoryStream stream(chunk.GetData());
        _version = stream.Read<uint32_t>();
        _name = stream.ReadLPString();
        _shader = stream.ReadLPString();
        _size = stream.Read<float>();
        _width = stream.Read<float>();
        _height = stream.Read<float>();
        _baseLine = stream.Read<float>();
        _numTextures = stream.Read<uint32_t>();

        for (auto const& child : chunk.GetChildren())
        {
            MemoryStream data(child->GetData());

            switch (child->GetType())
            {
                case ChunkType::Texture:
                    {
                        _textures.push_back(std::make_unique<Texture>(*child));
                        break;
                    }
                case ChunkType::FontGlyphs:
                    {
                        _glyphs.resize(data.Read<uint32_t>());
                        data.ReadBytes(reinterpret_cast<uint8_t*>(_glyphs.data()), _glyphs.size() * sizeof(FontGlyph));
                        break;
                    }
                default:
                    break;
            }
        }
    }

    Sprite::Sprite(const P3DChunk& chunk)
    {
        assert(chunk.IsType(ChunkType::Sprite));

        MemoryStream stream(chunk.GetData());
        _imageCount = stream.Read<uint32_t>();
        _name = stream.ReadLPString();
        _shader = stream.ReadLPString();
        _nativeWidth = stream.Read<uint32_t>();
        _nativeHeight = stream.Read<uint32_t>();
        _width = stream.Read<uint32_t>();
        _height = stream.Read<uint32_t>();
        _blitBorder = stream.Read<uint32_t>();

        for (auto const& child : chunk.GetChildren())
        {
            switch (child->GetType())
            {
                case ChunkType::Image:
                    {
                        _images.push_back(std::make_unique<Image>(*child));
                        break;
                    }
                default:
                    break;
            }
        }
    }

    FrontendScreen::FrontendScreen(const P3DChunk& chunk)
    {
        assert(chunk.IsType(ChunkType::FrontendScreen));

        MemoryStream stream(chunk.GetData());
        _name = stream.ReadLPString();
        _version = stream.Read<uint32_t>();
        _numPages = stream.Read<uint32_t>();
        _pageNames.resize(_numPages);
        for (size_t i = 0; i < _pageNames.size(); ++i)
        {
            _pageNames[i] = stream.ReadLPString();
        }
    }

    FrontendProject::FrontendProject(const P3DChunk& chunk)
    {
        assert(chunk.IsType(ChunkType::FrontendProject));

        MemoryStream stream(chunk.GetData());
        _name = stream.ReadLPString();
        _version = stream.Read<uint32_t>();
        _resX = stream.Read<uint32_t>();
        _resY = stream.Read<uint32_t>();
        _platform = stream.ReadLPString();
        _pagePath = stream.ReadLPString();
        _resourcePath = stream.ReadLPString();
        _screenPath = stream.ReadLPString();

        for (auto const& child : chunk.GetChildren())
        {
            switch (child->GetType())
            {
                case ChunkType::FrontendPage:
                    {
                        _pages.push_back(std::make_unique<FrontendPage>(*child));
                        break;
                    }
                default:
                    break;
            }
        }
    }

    FrontendPage::FrontendPage(const P3DChunk& chunk)
    {
        assert(chunk.IsType(ChunkType::FrontendPage));

        MemoryStream stream(chunk.GetData());
        _name = stream.ReadLPString();
        _version = stream.Read<uint32_t>();
        _resX = stream.Read<uint32_t>();
        _resY = stream.Read<uint32_t>();

        for (auto const& child : chunk.GetChildren())
        {
            switch (child->GetType())
            {
                case ChunkType::FrontendLayer:
                    {
                        _layers.push_back(std::make_unique<FrontendLayer>(*child));
                        break;
                    }
                default:
                    break;
            }
        }
    }

    FrontendLayer::FrontendLayer(const P3DChunk& chunk)
    {
        assert(chunk.IsType(ChunkType::FrontendLayer));

        MemoryStream stream(chunk.GetData());
        _name = stream.ReadLPString();
        _version = stream.Read<uint32_t>();
        _visible = stream.Read<uint32_t>();
        _editable = stream.Read<uint32_t>();
        _alpha = stream.Read<uint32_t>();
    }

    FrontendGroup::FrontendGroup(const P3DChunk& chunk)
    {
        assert(chunk.IsType(ChunkType::FrontendGroup));

        MemoryStream stream(chunk.GetData());
        _name = stream.ReadLPString();
        _version = stream.Read<uint32_t>();
        _alpha = stream.Read<uint32_t>();

        for (auto const& child : chunk.GetChildren())
        {
            switch (child->GetType())
            {
                case ChunkType::FrontendGroup:
                    {
                        _children.push_back(std::make_unique<FrontendGroup>(*child));
                        break;
                    }
                default:
                    break;
            }
        }
    }
}
