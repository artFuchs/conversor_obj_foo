#include <iostream>
#include <fstream>
#include <string>
//#include <unistd.h>
//#include <ctime>
#include "data.h"
using namespace std;

//#define SLEEP_TIME 1

/*
	Este programa tem como objetivo fazer a conversão de um arquivo .obj para .foo
	Uso: conversor arquivo_entrada arquivo_saida
*/

Face load_face(stringstream&, vector<Vertex>, vector<Vertex>);
Mesh load_obj(ifstream&);
Mesh load_foo(ifstream&);

int main(int argc, char **argv){
	ifstream inFile;
	ofstream outFile;

	if (argc==3){
		inFile.open(argv[1]);
		if (!inFile){
			cout << "Unable to open file";
		  exit(1); // terminate with error
		}

		//clock_t begin = clock();

		Mesh m;
		m = load_obj(inFile);
		inFile.close();

		//clock_t end = clock();
		//cout << "leu arquivo: " << double(end - begin)/CLOCKS_PER_SEC << endl;


		outFile.open(argv[2]);
		outFile << m.to_str() << endl;
		outFile.close();

		//end = clock();
		//cout << "escreveu arquivo: " << double(end - begin)/CLOCKS_PER_SEC + SLEEP_TIME << endl;
	}
	else{
		cout << "Help:" << endl;
		cout << "This program makes the conversion of a .obj file to a .foo file" << endl;
		cout << "Usage : " << endl;
		cout << "conversor in_file out_file" << endl;
	}

	return 0;
}

Face load_face(stringstream& stream, vector<Vertex> vertexes, vector<Vertex> normals)
{
	Face f;
	string o;
	while (stream >> o){
		size_t pos = 0;
		string delimiter = "//";
		string token;
		int v_number, n_number;
		if (o.find(delimiter) == string::npos){
			delimiter = "/";
			if (o.find(delimiter) == string::npos){	// error
			}
			else{ // vertex in format v/vt/vn
					pos = o.find(delimiter);
					token = o.substr(0, pos);
					v_number = stoi(token);
					o.erase(0, pos+delimiter.length()); //erase "v/"
					pos = o.find(delimiter);
					o.erase(0, pos+delimiter.length()); // erase "vt/"
					n_number = stoi(o);
			}
		}
		else { // vertex in format v//vn
			pos = o.find(delimiter);
			token = o.substr(0, pos);
			v_number = stoi(token);
			o.erase(0, pos+delimiter.length()); //erase "v//"
			n_number = stoi(o);
		}
		f.addVertex(vertexes[v_number-1]);
		f.changeNormal(normals[n_number-1]);
	}
	return f;
}

Mesh load_obj(ifstream& inFile)
{
	Mesh m;
	vector<Vertex> vertexes;
	vector<Vertex> normals;
	string line;
	while (getline(inFile, line))
	{
		stringstream stream;
		string o;
		stream << line;
		stream >> o;

		if (o.compare("o") == 0)
		{
			stream >> o;
			m.setName(o);
		}
		else if (o.compare("v") == 0)
		{
			double x,y,z;
			stream >> x >> y >> z;
			vertexes.push_back(Vertex(x,y,z));
		}
		else if (o.compare("vn") == 0)
		{
			double x,y,z;
			stream >> x >> y >> z;
			normals.push_back(Vertex(x,y,z));
		}
		else if (o.compare("f") == 0)
		{
			Face f = load_face(stream, vertexes, normals);
			m.addFace(f);
		}
		//clean stream
		stream.str("");
	}
	inFile.close();
	return m;
}
