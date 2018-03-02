#ifndef TREE_H_
#define TREE_H_

#include <iostream>
#include <cstdint>
#include <unordered_map>
#include  <vector>
#include "Node.hpp"




#include <string>
using namespace std;
class Tree{
private:
	Node* head; // Note is Node, not HashNode or StringNode. Allows for runtime designation

	int8_t insert_path( const string, const Node*&, Node*);
	void display_one( string, Node* ) const;
	void display_all(Node*) const;
	int8_t EOU_del(Node*&);
	unordered_map<string, vector<uint32_t> > retrieve_map(const string, Node*) const;

public:
	Tree(void);
	Tree(const string);
	Tree(string, string, uint32_t);
	~Tree(void);

	int8_t insert(const string);
	int8_t insert(string, uint32_t);
	int8_t insert(string,  string, uint32_t);
	int8_t insert_path(const string, const string);
	int8_t insert_path(const string, const string, Node*);
	int8_t insert_path(const string, Node*&, Node*);
	void display_all( void ) const;
	void display_one( string ) const;

	unordered_map<string, vector<uint32_t> > retrieve_map( const string ) const;
	vector<uint32_t> retrieve( const string, const string) const;
	string retrieve(const string);

};
#endif
