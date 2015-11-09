#pragma once

#include <map>
#include <list>
#include <string>

#include <CGAL/Simple_cartesian.h>
#include <CGAL/Surface_mesh.h>

typedef CGAL::Simple_cartesian<double>     	Kernel;
typedef Kernel::Point_3						Point_3;
typedef Kernel::Vector_3					Vector_3;
typedef CGAL::Surface_mesh<Point_3>        	Mesh;
typedef Mesh::Vertex_index 					vertex_descriptor;
typedef Mesh::Face_index 					face_descriptor;


enum Axis {X, Y, Z};

class Node {

public:
	Node(Node* _parent, bool _visible);
	~Node();

	void load(std::string path);
	void setShape(Mesh _shape) {shape = _shape;}
	void setVisible(bool _visible);
	void setParent(Node* _parent) {parent = _parent;}
	void addChild(Node* _child); 

	bool isVisible() {return visible;}

	Mesh getSubGeometry();
	void extrude(Kernel::RT height);
	void split(Axis axis, std::vector<Node*>& actions, std::vector<double> weights);

private:
	Node* parent;
	std::list<Node*> children;

	Mesh shape;
	std::map<std::string, double> attributes;
	bool visible;
	bool anonymous;
};

class ShapeTree {

public:
	ShapeTree();
	~ShapeTree() {}

	void initFromFile(std::string path) {root.load(path);}

	Node* getRoot() {return &root;}

	void outputGeometry();
	void displayGeometry();

private:
	Node root;

};

