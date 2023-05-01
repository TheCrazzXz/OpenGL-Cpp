#pragma once

#ifndef __MODEL_LOADER_H__
#define __MODEL_LOADER_H__

#include <glm/glm.hpp>
#include <vector>  

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../memory/sizedArray.h"

#include "../RawModel.h"
#include "../Loader.h"

#include <string>


class MeshData
{
    public:
        // mesh data
        
        SizedArray<float> vertices;
        SizedArray<float> texCoords;
        SizedArray<float> normals;

        SizedArray<unsigned int> indices;

        MeshData(SizedArray<float> vertices, SizedArray<float> texCoords, SizedArray<float> normals, SizedArray<unsigned int> indices)
            :   vertices(vertices), texCoords(texCoords), normals(normals), indices(indices)
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

        unsigned long calculateIndicesLength(aiMesh *mesh)
        {
            unsigned long indicesLength = 0;
            for(unsigned int i = 0; i < mesh->mNumFaces; i++)
            {
                aiFace face = mesh->mFaces[i];
                for(unsigned int j = 0; j < face.mNumIndices; j++)
                    indicesLength++;
            }  
            return indicesLength;
        }

        MeshData processMesh(aiMesh *mesh, const aiScene *scene)
        {
            // 3 floats for each vertices
            SizedArray<float> vertices(new float[mesh->mNumVertices * 3], sizeof(float) * mesh->mNumVertices * 3);
            SizedArray<float> texCoords(new float[mesh->mNumVertices * 2],sizeof(float) * mesh->mNumVertices * 2);
            SizedArray<float> normals(new float[mesh->mNumVertices * 3], sizeof(float) * mesh->mNumVertices * 3);

            // 1 unsigned int for each indice
            unsigned long indicesLength = calculateIndicesLength(mesh);
            SizedArray<unsigned int> indices(new unsigned int[indicesLength], sizeof(unsigned int) * indicesLength);

            // getting indices
            unsigned int currentIndiceIndex = 0;
            // process indices
            for(unsigned int i = 0; i < mesh->mNumFaces; i++)
            {
                aiFace face = mesh->mFaces[i];
                for(unsigned int j = 0; j < face.mNumIndices; j++)
                {
                    indices.data[currentIndiceIndex] = face.mIndices[j];
                    currentIndiceIndex++;
                }
            }  

            for(unsigned int i = 0; i < mesh->mNumVertices; i++)
            {
                // getting vertices
                vertices.data[i * 3] = mesh->mVertices[i].x;
                vertices.data[i * 3 + 1] = mesh->mVertices[i].y;
                vertices.data[i * 3 + 2] = mesh->mVertices[i].z;

                // getting normals
                normals.data[i * 3] = mesh->mNormals[i].x;
                normals.data[i * 3 + 1] = mesh->mNormals[i].y;
                normals.data[i * 3 + 2] = mesh->mNormals[i].z;

                // getting texture coords if they exist or else just plug in null vector
                if(mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
                {    
                    texCoords.data[i * 2] = mesh->mTextureCoords[0][i].x;
                    texCoords.data[i * 2 + 1] = mesh->mTextureCoords[0][i].y;
                }
                else
                {
                    texCoords.data[i * 2] = 0.0f;
                    texCoords.data[i * 2 + 1] = 0.0f;
                }
                
            }
            
            // returning all the data
            return MeshData(vertices, texCoords, normals, indices);
        }  
};

RawModel loadOBJToModel(const char* fileName, Loader& loader)
{
    ModelData modelData(fileName);
    return loader.loadToVAO(modelData.getMeshes()[0].vertices, modelData.getMeshes()[0].texCoords, modelData.getMeshes()[0].normals, modelData.getMeshes()[0].indices);
}

#endif