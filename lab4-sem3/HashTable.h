#pragma once
#include <functional>
#include <vector>

template <typename TKey, typename TValue>
class HashTable
{
protected:
    typedef std::hash<Key> Hash;
	struct Node
	{
		Key key;
		T item;
		Node* next;
	};

	class List
	{
		Node* first = nullptr;
		Node* last = nullptr;
		friend List;
	public:
		List() = default;
		List(const List& list)
		{
			Node* currentNode = list.first;
			while (currentNode)
			{
				Node insertingNode{ currentNode->key,currentNode->item,nullptr };
				this->PushBack(insertingNode);
				currentNode = currentNode->next;
			}
		}

		Node* GetLast() { return last; }
		Node* GetFirst() { return first; }

		void PushBack(Node node)
		{
			Node* insertingNode = new Node(node);
			if (!first)
			{
				first = insertingNode;
			}
			if (!last)
			{
				last = insertingNode;
			}
			else
			{
				last->next = insertingNode;
				last = insertingNode;
			}
		}
		void Pop(Key key)
		{
			Node* currentNode = first,*previousNode = nullptr;
			while (currentNode->key != key)
			{
				previousNode = currentNode;
				currentNode = currentNode->next;
			}

			if (previousNode)
			{
				previousNode->next = currentNode->next;
			}
			if (currentNode == first)
			{
				first = currentNode->next;
			}
			if (currentNode == last)
			{
				last = previousNode;
			}
			delete currentNode;
		}

		T& Get(Key key)
		{
			Node* currentNode = first;
			while (currentNode->key != key)
				currentNode = currentNode->next;
			return currentNode->item;
		}

		bool TryGet(Key key)
		{
			Node* currentNode = first;
			while (currentNode)
			{
				if (currentNode->key == key) return true;
				currentNode = currentNode->next;
			}
			return false;
		}

		~List()
		{
			if (first == nullptr)return;

			Node* currentNode = first, * nextNode = currentNode->next;
			while (currentNode)
			{
				delete currentNode;
				currentNode = nextNode;
				if (currentNode) nextNode = currentNode->next;
			}
		}
	};

	size_t capacity;
	size_t length;
	const size_t expansionCoeff = 2;
	const size_t extraCapacityCoeff = 2;
	shared_ptr<Sequence<shared_ptr<SmartPtrLinkedList>>> container;

    
	void IncreaseCapacity() {
		capacity *= expansionCoeff;
	}
	void DecreaseCapacity() {
		capacity /= expansionCoeff;
	}
    shared_ptr<Sequence<shared_ptr<SmartPtrLinkedList<Pair<TKey, TValue>>>>> emptySequence(size_t size) {
        auto emptySeq = shared_ptr<Sequence<shared_ptr<SmartPtrLinkedList>>>(new ArraySequence<shared_ptr<SmartPtrLinkedList<Pair<TKey, TValue>>>>());
        for(int i = 0; i < size; ++i) {
            emptySeq->Append(new SmartPtrLinkedList<Pair<TKey, TValue>>());
        }
    }
	void Rearrangement() {
		auto tempContainer = container;
		container = emptySequence(capacity);
        auto e = tempContainer->GetEnumerator();
		while(e->next()) {
			auto eList = (**e)->GetEnumerator();
			while (eList->next()) {
				TKey key = (**eList).GetKey();
				TValue item = (**eList).GetValue();
				size_t index = Hash{}(key) % capacity;
				Node node{ key,item,nullptr };
				container[index].PushBack(node);
				currentNode = currentNode->next;
			}
		}
	}
public:
	HashTable() = delete;
	HashTable(std::size_t capacity) : capacity(capacity), length(0) 
	{
		container.resize(capacity);
	}

	std::size_t Count() { return length; }
	std::size_t GetCapacity() { return capacity; }

	void Add(Key key, T item)
	{
		std::size_t index = Hash{}(key) % capacity;
		Node node{ key,item,nullptr };
		container[index].PushBack(node);
		length++;
		if (length == capacity)
		{
			IncreaseCapacity();
			Rearrangement();
		}
	}

	T& Get(Key key)
	{
		std::size_t index = Hash{}(key) % capacity;
		return container[index].Get(key);
	}

	void Remove(Key key)
	{
		std::size_t index = Hash{}(key) % capacity;
		container[index].Pop(key);
		length--;
		if (length < capacity/extraCapacityCoeff)
		{
			DecreaseCapacity();
			Rearrangement();
		}
	}

	bool ContainsKey(Key key)
	{
		std::size_t index = Hash{}(key) % capacity;
		return container[index].TryGet(key);
	}
};