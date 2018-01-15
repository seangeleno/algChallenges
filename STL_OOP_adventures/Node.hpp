#ifndef NODE_H_
#define NODE_H_

#include <cstdint>

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;
class Node{



public:
	Node();
	Node* next[2];
	Node* prev;
	vector<Node*> * paths;	
	
	virtual void display(void) const =0;
	virtual void disp_short(void) const=0;
	virtual int8_t comp(const string) const =0;
	virtual int8_t insert(const string)=0;
	virtual ~Node()=0;

	int8_t insert_path(Node*&);
};
	




class StringNode : public Node {
private:
	string data;

public:
	StringNode(void);
	StringNode( string );
	StringNode( string,const Node*& );
	StringNode( const Node*& );

	~StringNode()override;
	int8_t insert(const string) override;
	int8_t comp(const string) const override;
	void display(void) const override;
	void disp_short(void) const override;

	string retrieve(const string )const;
};

class HashNode : public Node {
private:
	string family;
	unordered_map<string, vector<uint32_t> > data;

public:
	HashNode(void);
	HashNode( string );
	HashNode( string, string, uint32_t );

	~HashNode(void) override;
	int8_t comp(const string) const override;
	void display( void ) const override;
	void disp_short(void) const override;
	int8_t insert(const string) override;

	int8_t insert( string, uint32_t);
	int8_t insert( string,  string, uint32_t);

	unordered_map< string, vector<uint32_t> > retrieve_map( void ) const;
	vector<uint32_t> retrieve( const string ) const;


	//uint8_t remove( string );

};
#endif


