#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

class Vertex{
	public:
		double x, y, z;
		Vertex();
		Vertex(double x, double y, double z);
    Vertex(const Vertex& v);//construtor de copia
		bool operator==(const Vertex& rhs) const;
		string to_str();
};

class Face{
	private:
		vector<Vertex> vertexes;
		Vertex vn;
	public:
		Face();
		Face(const Face& f);
		void addVertex(Vertex v);
		void changeNormal(Vertex normal);
		vector<Vertex> getVertexes() const;
		Vertex getNormal() const;
		string to_str();
};

class Mesh{
	private:
		string name;
		vector<Face> faces;
	public:
		Mesh();
		void setName(string n);
		void addFace(Face f);
		string getName();
		vector<Face> getFaces();
		string to_str();
};

class ObjMesh : public Mesh{
	private:
		vector<Vertex> vertexes;
		vector<Vertex> normals;
	public:
		ObjMesh();
		void addVertex(Vertex v);
		void addNormal(Vertex n);
		vector<Vertex> getVertexes();
		vector<Vertex> getNormals();
		string to_str();
};
