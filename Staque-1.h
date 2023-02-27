#include<iostream>
using namespace std;
typedef int StaqueMember;

#ifndef STAQUE_H
#define STAQUE_H

class Staque{
private:
	class Node {
	public:
		StaqueMember data;
		Node* following;
		Node(StaqueMember value, Node* link = 0)
			:data(value), following(link)
		{}
	};
	typedef Node* NodeP;
	NodeP MyTopMost;

public:
	Staque();
	Staque(const Staque& real);
	~Staque();
	const Staque& operator=(const Staque& rightSide);
	bool UnLoad() const;
	void Show(ostream& out)const;
	void Shove(const StaqueMember& object);
	void EliminateFront(int number);
	void EliminateBack(int number);
	int EvenComponents() const;
	int OddComponents() const;
	StaqueMember TopMost() const;
};
ostream& operator<<(ostream& out, const Staque& aStaque);
#endif // !Staque
