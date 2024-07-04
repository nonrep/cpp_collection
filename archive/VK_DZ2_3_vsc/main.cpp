#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <string>

template<class T>
class isLessDefault {
public:
	bool operator()( const T& left, const T& right ) { return left < right; }
};

template<class T, class isLess = isLessDefault<T>>
class BTree {
public:
	BTree( size_t _t ) : root( nullptr ), t( _t ) {}
	~BTree() { delete root; }

	void Insert( const T& key );
	void PrintLayers( void (*visit)( const T& key ), void (*endl)() ) const;

private:
	struct Node {
		bool IsLeaf;
		std::vector<T> Keys;
		std::vector<Node*> Children;

		Node( bool isLeaf ) : IsLeaf( isLeaf ) {}
		~Node() { for( Node* child : Children ) { delete child; } }
	};
	Node* root;
	size_t t;

	bool isNodeFull( Node* node ) { return node->Keys.size() == 2 * t - 1; }
	void splitChild( Node* node, int pos );
	void insertNonFull( Node* node, const T& key );
};

template<class T, class isLess>
void BTree<T, isLess>::Insert(const T& key)
{
    if (!root) {
        root = new Node(true);
    }

    if (isNodeFull(root)) {
        Node* newRoot = new Node(false);
        newRoot->Children.push_back(root);
        root = newRoot;
        splitChild(root, 0);
    }

    insertNonFull(root, key);
}

template<class T, class isLess>
void BTree<T, isLess>::insertNonFull( Node* node, const T& key )
{
	int pos = node->Keys.size() - 1;
    if ( node->IsLeaf ) {
        node->Keys.resize( node->Keys.size() + 1 );
        while ( pos >= 0 && isLess()( key, node->Keys[pos] ) ) {
            node->Keys[pos + 1] = node->Keys[pos];
            pos--;
        }
        node->Keys[pos + 1] = key;
    } else {
        while ( pos >= 0 && isLess()( key, node->Keys[pos] ) ) {
            pos--;
        }
            
        if ( isNodeFull( node->Children[pos + 1] ) ) {
            splitChild( node, pos + 1 );
            if ( key > node->Keys[pos + 1] )
                pos++;
        }
        insertNonFull( node->Children[pos + 1], key );
    }
}

template<class T, class isLess>
void BTree<T, isLess>::splitChild( Node* node, int pos )
{
	Node* y = node->Children[pos];
	Node* z = new Node( y->IsLeaf );

	z->Keys.resize( t - 1 );
	y->Keys.resize( t - 1 );

	if( !y->IsLeaf ) {
		z->Children.resize( t );
		y->Children.resize( t );
	}

	for( int i = 0; i < t - 1; ++i ) {
		z->Keys[i] = y->Keys[t + i];
	}

	if( !y->IsLeaf ) {
		for( int i = 0; i < t; ++i ) {
			z->Children[i] = y->Children[t + i];
		}
	}

	node->Keys.insert( node->Keys.begin() + pos, y->Keys[t - 1] );
	node->Children.insert( node->Children.begin() + pos + 1, z );
}

template<class T, class isLess>
void BTree<T, isLess>::PrintLayers( void (*visit)( const T& key ), void (*endl)() ) const {
	if ( !root ) return;

    std::queue<Node*> q;
    q.push( root );
    while ( !q.empty() ) {
        int nodesInCurrentLevel = q.size();
        while ( nodesInCurrentLevel > 0 ) {
            Node* current = q.front();
            q.pop();
            nodesInCurrentLevel--;

            for ( const T& key : current->Keys ) {
                visit( key );
            }

            for ( Node* child : current->Children ) {
                if ( child ) {
                    q.push( child );
                }
            }

            if ( nodesInCurrentLevel == 0 ) {
                endl();
                nodesInCurrentLevel = q.size();
            }
        }
    }
}

int main()
{
	int t;
	std::cin >> t;
	std::cin.ignore();
	BTree<int> tree( t );

	std::string str;
    std::getline( std::cin, str );
    std::istringstream ss( str );
    int key;
    while ( ss >> key ) {
        tree.Insert( key) ;
    }
    
	tree.PrintLayers( []( const int& key ) { std::cout << key << ' '; }, []() { std::cout << std::endl; } );

	return 0;
}