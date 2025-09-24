#include "CircularLinkedList.h"
#include "ExceptionInterface.h"

template<class t_Type>
class CircularLinkedList
{
public:
	CircularLinkedList();

	~CircularLinkedList();

	void Clear() const;

	void Resize(size_t p_NewSize);

	bool ReadFile(const char* p_FileName);

	void PushFront(const t_Type& p_NewElement);

	void PopFront();

	t_Type& Front();

	t_Type& operator [](size_t p_Index);

public:

private:
	t_Type* m_HeadPtr;

};