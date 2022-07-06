#pragma once
#include <glm/glm.hpp>
#include "Mesh.h"

struct aiNode;
struct aiMesh;
struct aiScene;

namespace LMX
{
	class SceneNode
	{
	public:
		glm::vec3 Translation { 0.f }, Rotation { 0.f }, Scale { 1.f }; // relative to parent
		glm::mat4 TransformMatrix{ 1.f };
		std::string Name;
		std::vector<Ref<Mesh>> Meshes;
		std::vector<Ref<SceneNode>> Children;
		SceneNode(const std::string& path)
		{
			loadModel(path);
		}
		void Init();
		SceneNode() = default;
		virtual void Draw(Ref<Shader> shader, const glm::mat4& offset = glm::mat4{1.f}) const;
		virtual glm::mat4 UpdateTransform();
		
		
		virtual void AddModel( const std::string& path );
		virtual void AddChild( Ref<SceneNode> child );
		
		virtual void RemoveChild( Ref<SceneNode> child );
		virtual void RemoveChild( const std::string& name );
		virtual void RemoveChild( size_t index );
		
		virtual void RemoveNode( const std::string& name );
		virtual void RemoveNode( Ref<SceneNode> node);
		
		virtual std::vector<Ref<SceneNode>>::iterator FindNode( const std::string& name );
		virtual std::vector<Ref<SceneNode>>::iterator FindNode( Ref<SceneNode> node );
		inline virtual std::vector<Ref<SceneNode>>::iterator FindChild( const std::string& name );
		inline virtual std::vector<Ref<SceneNode>>::iterator FindChild( Ref<SceneNode> child );

		virtual std::vector<Ref<SceneNode>>::iterator FindNode(const std::string& name) const{ return FindNode(name); }
		virtual std::vector<Ref<SceneNode>>::iterator FindNode(Ref<SceneNode> node) const{ return FindNode(node); }
		virtual std::vector<Ref<SceneNode>>::iterator FindChild(const std::string& name) const{ return FindChild(name); }
		virtual std::vector<Ref<SceneNode>>::iterator FindChild(Ref<SceneNode> child) const{ return FindChild(child); }
		
		
		virtual Ref<SceneNode> operator[] (size_t index) { return Children[index];}
		virtual Ref<SceneNode> operator[] (const std::string& name)	{ return *FindChild(name); }
		virtual Ref<SceneNode> operator[] (Ref<SceneNode> node)		{ return *FindChild(node); }
		
		virtual Ref<SceneNode> operator[] (size_t index) const { return Children[index]; }
		virtual Ref<SceneNode> operator[] (Ref<SceneNode> node) const { return *FindChild(node); }
		virtual Ref<SceneNode> operator[] (const std::string& name) const { return *FindChild(name); }

		virtual size_t size() const { return Children.size(); }
	private:
		std::mutex m_AddChildMutex, m_RemoveChildMutex;

		std::string m_Path;
		void loadModel(const std::string& path);
		void processNode(aiNode* node, const aiScene* scene);
		Ref<Mesh> processMesh(aiMesh* mesh, const aiScene* scene);
	};
}