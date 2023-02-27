#include<iostream>
#include "Staque-1.h"
using namespace std;
Staque::Staque()
	:MyTopMost(0)
{};
Staque::Staque(const Staque& real) {
	MyTopMost = 0;
	if (!real.UnLoad()) {
		MyTopMost = new Staque::Node(real.TopMost());
		Staque::NodeP FinalPointer = MyTopMost,
			BeginningPointer = real.MyTopMost->following;
		while (BeginningPointer != 0) {
			FinalPointer->following = new Staque::Node(BeginningPointer->data);
			FinalPointer = FinalPointer->following;
			BeginningPointer = BeginningPointer->following;
		}
	}
}
Staque::~Staque() {
	Staque::NodeP OngoingPointter = MyTopMost, followingPointer;
	while (OngoingPointter != 0) {
		followingPointer = OngoingPointter->following;
		delete OngoingPointter;
		OngoingPointter = followingPointer;
	}
}
const Staque &Staque::operator=(const Staque& rightSide) {
	if (this != &rightSide) {
		this->~Staque();
		if (rightSide.UnLoad())
			MyTopMost = 0;
		else {
			MyTopMost = new Staque::Node(rightSide.TopMost());
			Staque::NodeP FinalPointer = MyTopMost,
				rhsPointer = rightSide.MyTopMost->following;
			while (rhsPointer != 0)
			{
				FinalPointer->following = new Staque::Node(rhsPointer->data);
				FinalPointer = FinalPointer->following;
				rhsPointer = rhsPointer->following;
			}
		}
	}
	return *this;
}
bool Staque::UnLoad() const {
	return (MyTopMost == 0);
}
StaqueMember Staque::TopMost() const {
	if (!UnLoad())
		return (MyTopMost->data);
	else {
		cerr << "\t\tStaque is UnLoad - it is a 'waste'" << endl;
		StaqueMember *waste = new StaqueMember;
		return *waste;
		delete waste;
	}
}
ostream& operator<<(ostream& out, const Staque& aStaque) {
	aStaque.Show(out);
	return out;
}
void Staque::Show(ostream& out) const {
	Staque::NodeP i;
	if (!UnLoad()) {
		for (i = MyTopMost; i != 0; i = i->following)
			out << i->data << " ";
		out << endl;
	}
	else {
		cerr << "\t*** Staque is UnLoad ***" << endl;
	}
}
void Staque::Shove(const StaqueMember& object) {
	if (object % 2 == 0) {
		MyTopMost = new Staque::Node(object, MyTopMost);
	}
	else {
		Staque::NodeP temp = MyTopMost;
		while (temp->following != 0)
		{
			temp = temp->following;
		}
		Staque::Node* lastElement = new Staque::Node(object, 0);
		temp->following = lastElement;
	}
}
int Staque::EvenComponents()const {
	Staque::NodeP pointer = MyTopMost;
	int answer = 0;
	while (pointer != 0)
	{
		if (pointer->data % 2 == 0)
			answer++;
		pointer = pointer->following;
	}
	delete pointer;
	return answer;
}
int Staque::OddComponents()const {
	Staque::NodeP pointer = MyTopMost;
	int answer = 0;
	while (pointer != 0)
	{
		if (pointer->data % 2 != 0)
			answer++;
		pointer = pointer->following;
	}
	delete pointer;
	return answer;
}
void Staque::EliminateFront(int number) {
	int count = 0;
	if (number <= 0) {
		cerr << "\t*** It is not valid operation ***" << endl;
		return;
	}
	if (EvenComponents() < number) {
		cout << "There is only " << EvenComponents() << " even components to delete instead of " << number << endl;
			number = EvenComponents();
	}
	while (!UnLoad() && number != count) {
		Staque::NodeP pointer = MyTopMost;
		MyTopMost = MyTopMost->following;
		delete pointer;
		count++;
	}
}
void::Staque::EliminateBack(int number) {
	int count = 0;
	if (number <= 0) {
		cerr << "\t*** It is not valid operation ***" << endl;
		return;
	}
	if (OddComponents() < number) {
		cout << "There is only " << OddComponents() << " odd components to delete instead of " << number << endl;
			number = OddComponents();
	}
	int total = OddComponents() + EvenComponents();
	if (total == number) number--;
	while (!UnLoad() && number != count) {
		Staque::NodeP pointer = MyTopMost;
		while ((pointer->following)->following != 0)
			pointer = pointer->following;
		delete (pointer->following->following);
		pointer->following = 0;
		count++;
	}
	if (total == ++number) {
		MyTopMost = 0;
	}
}
