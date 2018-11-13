#include "data.h"

Vertex::Vertex(){
	x = 0;
	y = 0;
	z = 0;
}
Vertex::Vertex(double x, double y, double z){
	this->x = x;
	this->y = y;
	this->z = z;
}
//construtor de copia
Vertex::Vertex(const Vertex& v){
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
}
bool Vertex::operator==(const Vertex & rhs) const{
	return x==rhs.x && y==rhs.y && z==rhs.z;
}
string Vertex::to_str(){
	ostringstream strs;
	strs << x << " " << y << " " << z;
	string str = strs.str();
	return str;
}


// Face
Face::Face(){}
Face::Face(const Face& f){
	vector<Vertex> vert = f.getVertexes();
	for (int i=0; i<vert.size(); i++)
	{
		addVertex(vert[i]);
	}
	vn = f.getNormal();
}
void Face::addVertex(Vertex v){
	vertexes.push_back(Vertex(v));
}
void Face::changeNormal(Vertex normal){
	vn = Vertex(normal);
}
vector<Vertex> Face::getVertexes() const{
	return vertexes;
}
Vertex Face::getNormal() const{
	return vn;
}
string Face::to_str(){
	ostringstream strs;
	for (int i=0; i<vertexes.size(); i++)
	{
		strs << "( " << vertexes[i].to_str() << " ) ";
	}
	strs << "- ( " << vn.to_str() << " )";
	return strs.str();
}


// Mesh
Mesh::Mesh(){
	name = "object";
}
void Mesh::setName(string n){
	name = n;
}
void Mesh::addFace(Face f){
	faces.push_back(Face(f));
}
string Mesh::getName(){
	return name;
}
vector<Face> Mesh::getFaces(){
	return faces;
}
string Mesh::to_str(){
	ostringstream strs;
	strs << "[ " << name << " ]" << endl;
	for (int i=0; i<faces.size(); i++){
		strs << faces[i].to_str() << endl;
	}
	return strs.str();
}


//ObjMesh
ObjMesh::ObjMesh(){}
void ObjMesh::addVertex(Vertex v){
	vertexes.push_back(Vertex(v));
}
void ObjMesh::addNormal(Vertex n){
	normals.push_back(Vertex(n));
}
vector<Vertex> ObjMesh::getVertexes(){
	return vertexes;
}
vector<Vertex> ObjMesh::getNormals(){
	return normals;
}
string ObjMesh::to_str(){
	ostringstream strs;
	vector<Vertex>::iterator it;
	vector<Face>::iterator f;
	vector<Face> fa = getFaces();

	// mesh_name
	strs << "o " << getName() << endl;
	// vertexes list - "v x y z"
	for (it = vertexes.begin(); it < vertexes.end(); it++){
		strs << "v " << (*it).to_str() << endl;
	}
	// normals list - "vn x y z"
	for (it = normals.begin(); it < normals.end(); it++){
		strs << "vn " << (*it).to_str() << endl;
	}
	strs << "s off" << endl;
	// faces list - "f v_1//vn_1 [...] v_n//vn_n"
	for (f=fa.begin(); f <fa.end(); f++){
		strs << "f ";
		vector<Vertex> vs = (*f).getVertexes();
		vector<Vertex>::iterator v;

		it = find(normals.begin(), normals.end(), (*f).getNormal());
		int vn_num = (it - normals.begin()) + 1;

		for (v = vs.begin(); v < vs.end(); v++){
			it = find(vertexes.begin(), vertexes.end(), *v);
			int v_num = (it - vertexes.begin())+1;
			strs << v_num << "//" << vn_num << " ";
		}
		strs << endl;
	}

	return strs.str();
}
