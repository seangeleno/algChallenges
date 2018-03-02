#ifndef NODE_H_
#define NODE_H_

#include <cstdint>  //This library allows for more specific primitive data sizes
//For embedded systems where definitions might be variable, this explicit primitive
//size is useful in order to avoid unexpected bugs at runtime

#include <iostream>
#include <string>  //c++ string class import
#include <unordered_map> // a hashtable template. Uses std:: namespace and has its own namespace.
//namespaces allow for informative variable names to be reused in context. an iterator can be called an iterator
//for both vector and unordered_map this way, so long as they are prefixed with their namespace 


#include <vector> //dynamic array
using namespace std;
class Node{



public:
	Node();
	Node* next[2]; //if all derived classes will use the members, define them in the abstract class
	Node* prev;
	vector<Node*> * paths;	
	//virtual says we will implement these functions per class. if not, the compiler will throw errors
	virtual void display(void) const =0; //these are pure virtual functions. the =0 at the end
	virtual void disp_short(void) const=0; //says we will override them in the derived implementations
	virtual int8_t comp(const string) const =0; //Note the virtual keyword prefixing the prototypes
	virtual int8_t insert(const string)=0;
	virtual ~Node()=0; //The classes will likely have specific destructors, so lets make sure we define them

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
	int8_t insert(const string) override;  //note the overrides and how I grouped them together
	int8_t comp(const string) const override; //allows for a one to one check on whether they were implemented 
	void display(void) const override; //visually
	void disp_short(void) const override;

	string retrieve(const string )const;
};

class HashNode : public Node {
private:
	string family;
	//notice the chevrons.  This says that the data structure will take
	//both data types as arguments in implementation.  This data ambiguity
	//allows templates to be extremely useful. However, c++ has made them so robust
	//that their defintions often are many lines long, and gdbing through them can be tough
	//Their utility and uniformity in expected members is really helpful though.
	
	unordered_map<string, vector<uint32_t> > data; //notice the uint32_t in vector. this means unsigned integer of 32 bits
	
	
	//notice also how it is nested.  That is very common. the space between the last two cheverons is necessary because
	//the compiler will otherwise read it as bit shifting.

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

	unordered_map< string, vector<uint32_t> > retrieve_map( void ) const; //const following prototype says
	//that the method will allow no changes to class members
	
	vector<uint32_t> retrieve( const string ) const;


	//uint8_t remove( string );

};
#endif


