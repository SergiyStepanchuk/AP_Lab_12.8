#include <iostream>
#include <iomanip>
using namespace std;

struct Abonent {
	Abonent* next = nullptr;
	Abonent* parent = nullptr;

	string lastname;
	string number;
	float borg = 0;
};

void push_abonent(Abonent*& start, Abonent*& end, Abonent* ab) {
	if (start == nullptr) {
		end = start = ab;
		ab->next = nullptr;
		ab->parent = nullptr;
	}
	else {
		end->next = ab;
		ab->parent = end;
		ab->next = nullptr;
		end = ab;
	}
}

Abonent* remove_abonent(Abonent*& start, Abonent*& end, Abonent* ab) {
	if (ab == end)
		end = ab->parent;
	else ab->next->parent = ab->parent;

	if (ab == start)
		start = ab->next;
	else ab->parent->next = ab->next;
	return ab;
}

void abonent_factory(Abonent* &start, Abonent*& end) {
	char ch;
	cout << "Adding abonents: " << endl;
	Abonent* ab;
	do
	{
		ab = new Abonent();
		cout << "Input lastname of abonent: "; cin >> ab->lastname;
		cout << "Input number of abonent: "; cin >> ab->number;
		cout << "Input borg of abonent: "; cin >> ab->borg;
		push_abonent(start, end, ab);
		cout << "continue(y/n): "; cin >> ch;
	} while (ch == 'Y' || ch == 'y');
}

void draw_abonents(Abonent* start) {
	cout << "==========================================" << endl;
	cout << "| Lastname       | Number         | Borg |" << endl;
	cout << "------------------------------------------" << endl;
	while (start) {
		cout << "| " << setw(15) << start->lastname
			<< "| " << setw(15) << start->number 
			<< "| " << setw(5) << start->borg
			<< "|" << endl;
		start = start->next;
	}
	cout << "==========================================" << endl;
}

void get_delete_borznyki(const float &start_borg, Abonent*& start, Abonent *&end, Abonent*& borz_s, Abonent*& end_s) {
	Abonent* pos = start, *tmp;
	while (pos) {
		if (pos->borg >= start_borg) {
			tmp = pos;
			pos = pos->next;
			push_abonent(borz_s, end_s, remove_abonent(start, end, tmp));
		}else pos = pos->next;
	}
}

void delete_list(Abonent*& list, Abonent*& end) {
	if (list->next)
		delete_list(list->next, end);
	else end = nullptr;
	delete list;
	list = nullptr;
}

void main() {
	cout << fixed;
	cout.precision(1);
	Abonent* start = nullptr, * end = start, *borz[2] = {nullptr, nullptr};
	float s_borg;
	abonent_factory(start, end);
	cout << "All abonents: " << endl;
	draw_abonents(start);
	cout << "Input start borg: "; cin >> s_borg;
	get_delete_borznyki(1, start, end, borz[0], borz[1]);
	cout << "Without borg: " << endl;
	draw_abonents(start);
	cout << "With borg: " << endl;
	draw_abonents(borz[0]);
	delete_list(start, end);
	delete_list(borz[0], borz[1]);
}