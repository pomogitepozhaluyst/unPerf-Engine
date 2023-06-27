#pragma once


class Model: public Object {

public:
    Model(const char* path, const char* texture1)
    {
        texture = texture1;

        loadModel(path);
        //cout << texture << endl;

       // objMat = Mat4().E();
    }
    string texture;
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

    Mesh processMesh(aiMesh* mesh, const aiScene* scene)
    {
        vector<Vertex> verts;
        vector<unsigned> indices;
        cout << texture.c_str() << endl;




        for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            // process vertex positions, normals and texture coordinates

            Vec3 ver;
            Vec3 verNorm;
            Vec2 verTex;

            ver.x = mesh->mVertices[i].x;
            ver.y = mesh->mVertices[i].y;
            ver.z = mesh->mVertices[i].z;

            verNorm.x = mesh->mNormals[i].x;
            verNorm.y = mesh->mNormals[i].y;
            verNorm.z = mesh->mNormals[i].z;


            if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
            {
                verTex.x = mesh->mTextureCoords[0][i].x;
                verTex.y = mesh->mTextureCoords[0][i].y;
            }
            else
                verTex=Vec2(0.0f, 0.0f);

            verts.push_back(Vertex(ver, verTex, verNorm));

        }
        // process indices
        for (int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            for (int j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }

        cout << indices.size() << " == " << verts.size();
        return Mesh(verts, indices, texture, "");
    }


};