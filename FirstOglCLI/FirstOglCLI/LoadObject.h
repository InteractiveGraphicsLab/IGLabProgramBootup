#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "OglForCLI.h"

struct Vertex {
    float x, y, z, r, g, b;
};

struct Nomal {
    float x, y, z;
};

struct Triangle {
    int v1, v2, v3;
};

struct Object {
    std::vector<Vertex> vertices;
    std::vector<Nomal> nomals;
    std::vector<Triangle> triangles;
};

class LoadObject {

private:
    Object obj;

public:
    Object GetObject()
    {
        return obj;
    }

    bool loadObj(const char* path) {
        std::ifstream file(path);
        if (!file.is_open()) {
            std::cerr << "Could not open file " << path << std::endl;
            return false;
        }

        std::vector<Vertex> vertices;
        std::vector<Nomal> nomals;
        std::vector<Triangle> triangles;

        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string type;
            iss >> type;
            if (type == "v") {
                float x, y, z, r, g, b;
                iss >> x >> y >> z >> r >> g >> b;
                vertices.push_back({ x, y, z, r, g, b });
            }
            if (type == "vn") {
                float x, y, z;
                iss >> x >> y >> z;
                nomals.push_back({ x, y, z });
            }
            else if (type == "f") {
                std::string v1, v2, v3;
                iss >> v1 >> v2 >> v3;
                // Parse vertex indices
                int v1Index = std::stoi(v1.substr(0, v1.find('/'))) - 1;
                int v2Index = std::stoi(v2.substr(0, v2.find('/'))) - 1;
                int v3Index = std::stoi(v3.substr(0, v3.find('/'))) - 1;
                triangles.push_back({ v1Index, v2Index, v3Index });
            }
        }

        obj.vertices = vertices;
        obj.nomals = nomals;
        obj.triangles = triangles;

        return true;
    }
};
