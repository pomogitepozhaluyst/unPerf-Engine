#pragma once




class Model {

public:
    string pathModel;
    vector<Mesh> mesh;
    Model(const char* path, string texture1 = "")
    {
        pathModel = path;

        loadModel(path);
        //cout << texture << endl;

       // objMat = Mat4().E();
    }
private:
    // model data
    string directory;

    void loadModel(string path)
    {
        Assimp::Importer import;
        const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
            return;
        }
        directory = path.substr(0, path.find_last_of('/'));

        processNode(scene->mRootNode, scene);
    }

    void processNode(aiNode* node, const aiScene* scene)
    {
        // process all the node's meshes (if any)
        for (unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            aiMesh* meshAi = scene->mMeshes[node->mMeshes[i]];
            mesh.push_back(processMesh(meshAi, scene));
        }
        // then do the same for each of its children
        for (unsigned int i = 0; i < node->mNumChildren; i++)
        {
            processNode(node->mChildren[i], scene);
        }
    }
    string loadTexture(aiMaterial* mat, aiTextureType type, string typeName) {
        aiString  texture;
        for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
        {
            mat->GetTexture(type, i, &texture);
        }
        return texture.C_Str();
    }
    Mesh processMesh(aiMesh* mesh, const aiScene* scene)
    {
        vector<Vertex> verts;
        vector<unsigned> indices;
        //cout << texture.c_str() << endl;




        for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            // process vertex positions, normals and texture coordinates

            Vec3 ver;
            Vec3 verNorm;
            Vec2 verTex;

            ver.x = mesh->mVertices[i].x;
            ver.y = mesh->mVertices[i].y;
            ver.z = mesh->mVertices[i].z;
            if (mesh->mNormals) {
                verNorm.x = mesh->mNormals[i].x;
                verNorm.y = mesh->mNormals[i].y;
                verNorm.z = mesh->mNormals[i].z;
            }

            if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
            {
                verTex.x = mesh->mTextureCoords[0][i].x;
                verTex.y = mesh->mTextureCoords[0][i].y;
            }
            else
                verTex = Vec2(0.0f, 0.0f);

            verts.push_back(Vertex(ver, verTex, verNorm));

        }
        // process indices
        for (int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            for (int j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }


        if (mesh->mMaterialIndex >= 0)
        {
            string directory = pathModel;
            while(directory[directory.size()-1] != '\\' && directory[directory.size() - 1] != '/') {
                directory.pop_back();
            }
            aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

                cout << directory + loadTexture(material,
                    aiTextureType_DIFFUSE, "texture_diffuse") << endl;

                return Mesh(verts, indices, directory + loadTexture(material,
                    aiTextureType_DIFFUSE, "texture_diffuse"), "");
            
        }

        return Mesh(verts, indices);
    }


};