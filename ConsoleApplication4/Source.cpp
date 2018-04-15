#include <iostream>
#include <fstream>
using namespace std;

struct date {
	char first_name[20];
	char surname[20];
	int age;
};

struct List {
	date person;
	List *next;
};


int isEqual(char *s1, char *s2) {
	int len = strlen(s1);
	for (int i(0); i < len; i++) {
		if (isalpha(s1[i]) && isalpha(s2[i])) {
			if (tolower(s1[i]) < tolower(s2[i])) return -1;
			else if (tolower(s1[i]) > tolower(s2[i])) return 1;
		}
		else {
			if (s1[i] < s2[i]) return -1;
			else if (s1[i] > s2[i]) return 1;
		}
	}
	if (strlen(s1) == strlen(s2)) return 0; 
	else if (strlen(s1) < strlen(s2)) return -1;
	else return 1;
};

// �������� ������
void showList(List *b) {
	while (b) {
		cout << "Surname: " << b->person.surname << endl;
		cout << "Name: " << b->person.first_name << endl;
		cout << "Age: " << b->person.age << endl << endl;
		b = b->next;
	}
	cout << "_______________________\n\n";
}

// �������� ���� ������
void showPerson(date o) {
	cout << "Surname: " << o.surname << endl;
	cout << "Name: " << o.first_name << endl;
	cout << "Age: " << o.age << endl << endl;
}

// ����� �� �����
void find_name(List *b, char *s) {
	while (b) {
		if (isEqual(s, b->person.surname) == 0) {
			showPerson(b->person);
			return;
		}
		b = b->next;
	}
	cout << "Name wasn\'t found.\n\n";
}

// ����� �� ��������
void find_age(List *b, int a) {
	while (b) {
		if (b->person.age == a) {
			showPerson(b->person);
		}
		b = b->next;
	}
}

// ����� �� ������ ����� �������
void find_first_letter(List *b, char l) {
	while (b) {
		if (tolower(b->person.surname[0]) == tolower(l)) {
			showPerson(b->person);
		}
		b = b->next;
	}
}


void insert(List **b, date o) {
	if (*b == NULL) { 
		*b = new List;
		(*b)->person = o;
		(*b)->next = NULL;
		return;
	}

	
	if (isEqual(o.surname, (*b)->person.surname) == -1) {
		List *temp = new List;
		temp->person = o;
		temp->next = *b;
		*b = temp;
		return;
	}

	
	if ((*b)->next == NULL && isEqual(o.surname, (*b)->person.surname) == 1) {
		List *temp = new List;
		temp->next = NULL;
		temp->person = o;
		(*b)->next = temp;
		return;
	}

	

	List *temp = new List;
	temp = *b;
	while (temp) {
		
		if (temp->next == NULL && isEqual(o.surname, temp->person.surname) == 1) {
			List *t = new List;
			t->next = NULL;
			t->person = o;
			temp->next = t;
			return;
		}
		
		if (temp->next != NULL && isEqual(o.surname, temp->person.surname) == 1 && isEqual(o.surname, temp->next->person.surname) == -1) {
			List *t = new List;
			t->person = o;
			t->next = temp->next;
			temp->next = t;
			return;
		}
		temp = temp->next;
	}
}

// ������� ���� ������ �� �������
void del(List **b, char *s) {
	// ���� � ������ ��� �������
	if (*b == NULL) return;

	// ���� � ������ ������ ���� ������
	if ((*b)->next == NULL) {
		*b = NULL;
		return;
	}

	// ���� � ������ ��� ������ � ��������� ������
	if (isEqual(s, (*b)->person.surname) == 0) {
		List *temp = new List;
		temp = *b;
		*b = (*b)->next;
		delete temp;
		return;
	}

	// ���� � ������ ��� ������ � ��������� ������
	if (isEqual(s, (*b)->next->person.surname) == 0 && (*b)->next->next == NULL) {
		List *temp = new List;
		temp = (*b)->next;
		(*b)->next = NULL;
		delete temp;
		return;
	}

	// ���� � ������ ����� ���� �������
	List *t = *b;
	List *t2 = t->next;
	while (t2) {
		// � ��������� ���������
		if (isEqual(s, t2->person.surname) == 0 && t2->next == NULL) {
			t->next = NULL;
			delete t2;
			return;
		}
		else
			// � ��������� �� ��������
			if (isEqual(s, t2->person.surname) == 0 && t2->next != NULL) {
				List *temp = new List;
				temp = t2;
				t->next = t2->next;
				delete temp;
				return;
			}
		t = t2;
		t2 = t2->next;
	}
}

// ������ ����� ������ �� ������ !!! �� ��������
void change(List **b1, char *s1, char *s2) {
	List *b = new List;
	b = *b1;

	while (b) {
		if (isEqual(b->person.surname, s1) == 0) {
			date t;
			strcpy(t.surname, s2);
			strcpy(t.first_name, b->person.first_name);
			t.age = b->person.age;

			del(&b, s1);
			insert(&b, t);
			cout << "������ �������.\n";
			return;
		}
		b = b->next;
	}
}

// ������� ���� ������
void Free(List **b) {
	if (*b == NULL) return;

	// ���� ������ ����
	if ((*b)->next == NULL) {
		*b = NULL;
		return;
	}

	// ���� ������� ���
	if ((*b)->next->next == NULL) {
		delete (*b)->next;
		*b = NULL;
		return;
	}

	// ���� ������� ������, ��� ���

	while (*b) {
		List *temp = new List;
		temp = *b;
		*b = (*b)->next;
		delete temp;
	}
}

// ������ �� ����� !!! �� ��������
void read_from_file(ifstream &f, List **b) {
	date temp;
	char str[3];

	while (f) {
		// ��������� �������
		f.getline(temp.surname, 20, ' ');
		// ��������� ���
		f.getline(temp.first_name, 20, ' ');
		// ��������� �������
		f >> temp.age;
		f.getline(str, 3, '\n');// �������� ���� �������� ������
		insert(b, temp); // ��������� � ��������� ��������� ������
	} // ������ ����� ��������� � ���������
}

// ������ � ����
void write_in_file(ofstream &f, List *b) {
	date temp;
	while (b) {
		strcpy(temp.surname, b->person.surname);
		strcpy(temp.first_name, b->person.first_name);
		temp.age = b->person.age;

		for (int i(0); i < strlen(b->person.surname); i++)
			f.put(b->person.surname[i]);
		f.put(' ');
		for (int i(0); i < strlen(b->person.first_name); i++)
			f.put(b->person.first_name[i]);
		f.put(' ');
		f << b->person.age;
		if (b->next != NULL)f.put('\n');

		b = b->next;
	}
}

// ���������� ������ � ����, �������� �������������
void save_in_file(char *s, List *k) {
	ofstream f(s, ios::binary | ios::out);

	write_in_file(f, k);
	cout << "File was seved.\n\n";
}

// �������� ��� ����������, ��� (����� ��������) ������ ������������
bool isvalid(char ch) {
	if ((ch < '1' || ch > '6') && ch != 'q') return false;
	else return true;
}

// �������� ���������
void showmenu() {
	cout << "1 - �������� ������.\n";
	cout << "2 - �������� ������.\n";
	cout << "3 - ������� ������.\n";
	cout << "4 - ����� ����������.\n";
	cout << "5 - ����� ���� �����������.\n";
	cout << "6 - ��������� ����������� � ����.\n";
	cout << "������� 'q' ��� ������.\n";
}

// ��������� ��������
void action(List **k, char ch) {
	List *b = new List;
	b = *k;
	switch (ch) {
	case '1':
		cout << "�������� ������:\n";
		date temp;
		cout << "������� �������: ";
		cin >> temp.surname;
		cout << "������� ���: ";
		cin >> temp.first_name;
		cout << "������� �������: ";
		cin >> temp.age;
		insert(k, temp);
		cout << "*********������ ����������.*********\n\n";
		break;
	case '2':

		char name1[20], name2[20];
		cout << "������� �������, ������� ������ ��������: ";
		cin >> name1;
		find_name(*k, name1);
		cout << "������� ����� �������: ";
		cin >> name2;

		while (b) {
			if (isEqual(b->person.surname, name1) == 0) {
				date t;
				strcpy(t.surname, name2);
				strcpy(t.first_name, b->person.first_name);
				t.age = b->person.age;

				del(k, name1);
				insert(k, t);
				cout << "������ �������.\n";
				return;
			}
			b = b->next;
		}

		break;
	case '3':
		char name[20];
		cout << "������� �������, ��� �� ������� ������: ";
		cin >> name;
		del(k, name);
		break;
	case '4':
		char c;
		cout << "����� �����������:\n";
		cout << "1 - ����� �� �������.\n";
		cout << "2 - ����� �� ��������.\n";
		cout << "3 - ����� �� ������ ����� � �������.\n";
		cin >> c;
		switch (c) {
		case '1':
			cout << "������� �������: ";
			char n[20];
			cin >> n;
			find_name(*k, n);
			break;
		case '2':
			int a;
			cout << "������� �������: ";
			cin >> a;
			find_age(*k, a);
			break;
		case '3':
			char c;
			cout << "������� ������ ����� �������: ";
			cin >> c;
			find_first_letter(*k, c);
			break;
		default:
			cout << "�� �� ������� �����.\n\n";
		}

		break;
	case '5':
		cout << "_____________________________\n\n";
		cout << "����� ���� �����������:\n\n";
		cout << "_____________________________\n\n";
		showList(*k);
		break;
	case '6':
		cout << "���������� ��������� � ����:\n";
		cout << "������� ��� ����� (��������, names.txt): ";
		char n[50];
		cin >> n;
		save_in_file(n, *k);
		break;

	};
};

int main() {
	setlocale(0, "");

	

	// ���������� �����
	// �� �������� ����� ��������� ������
	ifstream f("text2.txt", ios::binary | ios::in);
	// � ������� ����� ������ ������������ ��������������, ����� ���������� ���������
	ofstream f2("text2.txt", ios::binary | ios::out);
	if (!f) {
		cout << "File can\'t be opened.\n";
		cin.get();
		return -1;
	}
	if (!f2) {
		cout << "File can\'t be opened.\n";
		cin.get();
		return -1;
	}

	// �������� ������ ������
	List *kartoteka = new List;
	kartoteka = NULL;

	// ��������� ��� ���������� � ���������
	read_from_file(f, &kartoteka);

	char ch;
	// ����, ��� ������ ���������� (�.�. ��� ������ ����)
	for (;;) {
		do {
			showmenu();
			cin >> ch;
		} while (!isvalid(ch));

		if (ch == 'q') break;
		action(&kartoteka, ch);
	}

	// ���������� � ����
	write_in_file(f2, kartoteka);

	// ������� ��� ������ �� ������
	Free(&kartoteka);

	// ��������� �����
	f2.close();
	f.close();
	cin.get();
	return 0;
}