#ifndef STACK_C
#define STACK_C

template <class T>
class Node
{
private:
	T mData;
	Node<T>* mpParent;
	Node<T>* mpChild;

public:

	Node(T data, Node<T>* parent)
	{
		mData = data;
		mpChild = nullptr;
		mpParent = parent;
	}

	~Node()
	{
		mpParent = nullptr;
		mpChild = nullptr;
	}

	const T& getData() { return mData; }
	Node<T>* getParent() { return mpParent; }
	Node<T>* getChild() { return mpChild; }

	void setChild(Node<T>* child) { mpChild = child; }
	void setParent(Node<T>* parent) { mpParent = parent; }
	void setData(T data) { mData = data; }
};

template <class T>
class Stack
{
private:
	Node<T>* mpFirst;
	Node<T>* mpLast;

	unsigned int mNumNodes;

public:
	Stack()
	{
		mpFirst = nullptr;
		mpLast = nullptr;

		mNumNodes = 0;
	}

	~Stack()
	{
		Node<T>* currNode = mpLast;
		for (unsigned int i = 0; i < mNumNodes; i++)
		{
			if (currNode->getParent() == nullptr)
				break;

			currNode = currNode->getParent();
			delete currNode->getChild();
		}

		delete currNode;
		currNode = nullptr;
	}

	unsigned int size() const { return mNumNodes; }

	bool

	void push(T data)
	{
		Node<T>* node = new Node<T>(data, mpLast);

		if (mpLast != nullptr)
		{
			mpLast->setChild(node);
			node->setParent(mpLast);
		}
		else
			mpFirst = node;

		mpLast = node;
		mNumNodes++;
	}

	T pop()
	{
		T data = mpLast->getData();
		Node<T>* next = mpLast->getParent();
		delete mpLast;

		if (next != nullptr)
		{
			next->setChild(nullptr);
			mpLast = next;
		}

		mNumNodes--;

		if (mNumNodes == 0)
			mpFirst = mpLast = nullptr; 

		return data;
	}

	const T& findAtIndex(unsigned int index)
	{
		Node<T>* currNode = mpFirst;

		for (unsigned int i = 0; i < index; i++)
			currNode = currNode->getChild();

		return currNode->getData();
	}

	int find(const T& data)
	{
		Node<T>* currNode = mpFirst;
		for (int i = 0; i < mNumNodes; i++)
		{
			if (currNode->getData() == data)
				return i;

			currNode = currNode->getChild();
		}

		return -1;
	}

};

#endif