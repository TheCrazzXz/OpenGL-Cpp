#pragma once

#ifndef __MODEL_LOADER_H__
#define __MODEL_LOADER_H__

#include <glm/glm.hpp>
#include <vector>  

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../memory/sizedArray.h"

#include <string>

struct Vertex 
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};


class MeshData
{
    public:
        // mesh data
        std::vector<Vertex>       vertices;
        std::vector<unsigned int> indices;

        MeshData(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
            :   vertices(vertices), indices(indices)
        {}
};  

class ModelData
{
    public:
        ModelData(const char *path)
        {
            loadModel(path);
        }
        std::vector<MeshData>& getMeshes()
        {
            return meshes;
        }
    private:
        // model data
        std::vector<MeshData> meshes;
        std::string directory;



        void loadModel(std::string path)
        {
            Assimp::Importer import;
            const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);    
            
            if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
            {
                std::cerr << "Error with ASSIMP : " << import.GetErrorString() << std::endl;
                return;
            }
            directory = path.substr(0, path.find_last_of('/'));

            processNode(scene->mRootNode, scene);
        }
        void processNode(aiNode *node, const aiScene *scene)
        {
            // process all the node's meshes (if any)
            for(unsigned int i = 0; i < node->mNumMeshes; i++)
            {
                aiMesh *mesh = scene->mMeshes[node->mMeshes[i]]; 
                meshes.push_back(processMesh(mesh, scene));         
            }
            // then do the same for each of its children
            for(unsigned int i = 0; i < node->mNumChildren; i++)
            {
                processNode(node->mChildren[i], scene);
            }
        }  
        MeshData processMesh(aiMesh *mesh, const aiScene *scene)
        {
            std::vector<Vertex> vertices;
            std::vector<unsigned int> indices;

            for(unsigned int i = 0; i < mesh->mNumVertices; i++)
            {
                Vertex vertex;
                // process vertex positions, normals and texture coordinates
                
                glm::vec3 vector; 

                vector.x = mesh->mVertices[i].x;
                vector.y = mesh->mVertices[i].y;
                vector.z = mesh->mVertices[i].z; 
                vertex.Position = vector;

                vector.x = mesh->mNormals[i].x;
                vector.y = mesh->mNormals[i].y;
                vector.z = mesh->mNormals[i].z;
                vertex.Normal = vector;  

                if(mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
                {
                    glm::vec2 vec;
                    vec.x = mesh->mTextureCoords[0][i].x; 
                    vec.y = mesh->mTextureCoords[0][i].y;
                    vertex.TexCoords = vec;
                }
                else
                {
                    vertex.TexCoords = glm::vec2(0.0f, 0.0f);  
                }
                    

                vertices.push_back(vertex);
            }
            // process indices
            for(unsigned int i = 0; i < mesh->mNumFaces; i++)
            {
                aiFace face = mesh->mFaces[i];
                for(unsigned int j = 0; j < face.mNumIndices; j++)
                    indices.push_back(face.mIndices[j]);
            }  

            return MeshData(vertices, indices);
        }  
};

void loadModelToData(ModelData modelData, SizedArray<float>& vertices, SizedArray<float>& TexCoords, SizedArray<unsigned int>& indices)
{


    for(unsigned long i = 0 ; i < (unsigned long)modelData.getMeshes().size() ; i++)
    {
        unsigned long verticesLength = (unsigned long) modelData.getMeshes()[i].vertices.size();
        unsigned long textureCoordsLength = (unsigned long) modelData.getMeshes()[i].vertices.size();

        unsigned long indicesLength = (unsigned long) modelData.getMeshes()[i].indices.size();

        std::cout << sizeof(float) << std::endl;

        unsigned long verticesSize = verticesLength * 3;
        unsigned long textureCoordsSize = textureCoordsLength * 2;

        unsigned long indicesSize = indicesLength;

        vertices.data = new float[verticesSize]; 
        vertices.size = verticesSize * sizeof(float);

        TexCoords.data = new float[textureCoordsSize];
        TexCoords.size = textureCoordsSize * sizeof(float); 

        indices.data = new unsigned int[indicesSize]; 
        indices.size = indicesSize * sizeof(unsigned int);

        std::cout << "Vertices size :" << std::to_string(verticesLength) << std::endl;
        std::cout << "TexCoords size :" << std::to_string(TexCoords.size) << std::endl;
        std::cout << "Indices size :" << std::to_string(indices.size) << std::endl;



        MeshData& currentMesh = modelData.getMeshes()[i];

        for(unsigned long j = 0 ; j < verticesLength; j += 3)
        {
            glm::vec3 position = currentMesh.vertices[j/3].Position;
            

            //std::cout << "Writing position" << std::endl;

            vertices.data[j] = position.x;
            vertices.data[j+1] = position.y;
            vertices.data[j+2] = position.z;            

        }
        for(unsigned long j = 0 ; j < verticesLength; j += 2)
        {
            glm::vec2* texCoords = &currentMesh.vertices[j/2].TexCoords;

            TexCoords.data[j] = texCoords->x;
            TexCoords.data[j+1] = texCoords->y;
        }
        for(unsigned long j = 0 ; j < indicesLength ; j++)
        {
            unsigned int* indice = &currentMesh.indices[j];
            indices.data[j] = *indice;
        }
    }
}

#endif