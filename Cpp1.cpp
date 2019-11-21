#include <iostream>
#include <conio.h>

using namespace std;

struct node
{
	int puzzle[9];
	int empty;
	int prev;
	int h;
	node *parent;
	node *next;
};
int sc(int, int);
int f(void);
void ans(void);
int test(void);
int h2(void);
int th(void);
void rnode(void);
node *parent = new node;
node *first = new node;
node *last = new node;
node *answer = new node;
int countstep = 0;
int start[9];
int empty;
int a[9];
int g;
int step[40];
int sp = -1;
int goal[2][9] = {	{0, 1, 2, 3, 4, 5, 6, 7, 8},
					{1, 2, 3, 8, 0, 4, 7, 6, 5}
				 };
int main()
{
	int count = 0, i, j;
	for (i=0; i<9; i++)
	{
		cout << "Enter the number(" << (i+1) << ")= ";
		cin >> parent->puzzle[i];
		if (parent->puzzle[i] == 0)
			parent->empty = i;
	}
	parent->next = NULL;
	parent->parent = NULL;
	parent->prev = -1;
	for (i=0; i<9; i++)
		if (parent->puzzle[i] > 0)
			for (j=i+1; j<9; j++)
				if (parent->puzzle[j]>0 && parent->puzzle[j]<parent->puzzle[i])
					count++;
	g = count%2;
	for (i=0; i<9; i++)
		start[i] = a[i] = parent->puzzle[i];

	if (h2() == 1)
		parent->h = th();
	else
		parent->h = 0;
	empty = parent->empty;
	if (test() == 1)
		return 0;
	f();
	cout << endl << "----------------------" << endl;;
	cout << endl << "COUNT STEP = " << countstep << "\n\n";
	ans();
	for (i=sp; i>=0; i--)
	{
		start[empty] = start[step[i]];
		start[step[i]] = 0;
		empty = step[i];
		for (j=0; j<9; j++)
		{
			cout << start[j] << " ";
			if (j%3 == 2)
				cout << endl;
		}
		cout << "\nTo Step " << i <<endl;
		cout << "Press any key to next step..." << endl;
		getch();
		cout << endl;
	}
	cout << "FINISH" << endl;
	getch();
	return 0;
}
int f()
{
	int s, i, f = 0;
	while (1)
	{
		countstep++;
		s = sc(parent->empty, parent->prev);
		for (i=0; i<9; i++)
			first->puzzle[i] = parent->puzzle[i];
		first->puzzle[parent->empty] = first->puzzle[s%10];
		first->puzzle[s%10] = 0;
		first->empty = s%10;
		first->parent = parent;
		first->next = NULL;
		first->prev = parent->empty;
		for (i=0; i<9; i++)
			a[i] = first->puzzle[i];

		if (h2() == 1)
			first->h = th();
		else
			first->h = 0;
		if (test() == 1)
		{
			answer = first;
			return 0;
		}
		if (first->h == 1)
			f = 1;
		last = first;
		s /= 10;
		while(1)
		{
			if (s <= 0)
			{
				if (parent->next == NULL)
					break;
				else
				{
					parent = parent->next;
					s = sc(parent->empty, parent->prev);
				}
			}
			node *p = new node;
			for (i=0; i<9; i++)
				p->puzzle[i] = parent->puzzle[i];
			p->puzzle[parent->empty] = p->puzzle[s%10];
			p->puzzle[s%10] = 0;
			p->empty = s%10;
			p->parent = parent;
			p->next = NULL;
			p->prev = parent->empty;
			for (i=0; i<9; i++)
				a[i] = p->puzzle[i];
			if (h2() == 1)
				p->h = th();
			else
				p->h = 0;
			if (test() == 1)
			{
				answer = p;
				return 0;
			}
			if (p->h == 1)
				f = 1;
			last->next = p;
			last = p;
			s /= 10;
		}
		if (f == 1)
		{
			rnode();
			f = 0;
		}
		parent = first;
		first = new node;
	}
}
int th()
{
	if (g == 0)
	{
		for (int i=1; i<9; i++)
			if (a[i] != i && a[i]!=0)
				if (a[a[i]]==i)
					return 0;
	}
	else
	{
		for (int i=0; i<9; i++)
			if (a[i] != 0)
				switch(i)
				{
					case 0:
						if ((a[0]==2 && a[1]==1) || (a[0]==8 && a[3]==1))
							return 0;
						break;
					case 1:
						if (a[1]==3 && a[2]==2)
							return 0;
						break;
					case 2:
						if (a[2]==4 && a[5]==3)
							return 0;
						break;
					case 3:
						if (a[3]==7 && a[8]==4)
							return 0;
						break;
					case 5:
						if (a[5]==5 && a[8]==4)
							return 0;
						break;
					case 6:
						if (a[6]==6 && a[7]==7)
							return 0;
						break;
					case 7:
						if (a[7]==5 && a[8]==6)
							return 0;
						break;
				}
	}
	return 1;
}
int h2()
{
	if (g == 0)
	{
		if (a[0]!=0 && a[0]!=1 && a[0]!=3)
			return 0;
		if (a[1]!=0 && a[1]!=1 && a[1]!=2 && a[1]!=4)
			return 0;
		if (a[2]!=0 && a[2]!=1 && a[2]!=2 && a[2]!=5)
			return 0;
		if (a[3]!=0 && a[3]!=3 && a[3]!=4 && a[3]!=6)
			return 0;
		if (a[4]!=0 && a[4]!=1 && a[4]!=3 && a[4]!=4 && a[4]!=5 && a[4]!=7)
			return 0;
		if (a[5]!=0 && a[5]!=2 && a[5]!=4 && a[5]!=5 && a[5]!=8)
			return 0;
		if (a[6]!=0 && a[6]!=3 && a[6]!=6 && a[6]!=7)
			return 0;
		if (a[7]!=0 && a[7]!=4 && a[7]!=6 && a[7]!=7 && a[7]!=8)
			return 0;
		if (a[8]!=0 && a[8]!=5 && a[8]!=7 && a[8]!=8)
			return 0;
	}
	else
	{
		if (a[0]!=0 && a[0]!=1 && a[0]!=2 && a[0]!=8)
			return 0;
		if (a[1]!=0 && a[1]!=1 && a[1]!=2 && a[1]!=3)
			return 0;
		if (a[2]!=0 && a[2]!=2 && a[2]!=3 && a[2]!=4)
			return 0;
		if (a[3]!=0 && a[3]!=1 && a[3]!=7 && a[3]!=8)
			return 0;
		if (a[4]!=0 && a[4]!=2 && a[4]!=4 && a[4]!=6 && a[4]!=8)
			return 0;
		if (a[5]!=0 && a[5]!=3 && a[5]!=4 && a[5]!=5)
			return 0;
		if (a[6]!=0 && a[6]!=6 && a[6]!=7 && a[6]!=8)
			return 0;
		if (a[7]!=0 && a[7]!=5 && a[7]!=6 && a[7]!=7)
			return 0;
		if (a[8]!=0 && a[8]!=4 && a[8]!=5 && a[8]!=6)
			return 0;
	}
	return 1;
}
void rnode()
{
	node *p = new node;
	node *t = new node;
	while (first->h == 0)
	{
		if (first->next == NULL)
			return;
		first = first->next;
	}
	t = first;
	if (t->next == NULL)
		return;
	p = t->next;
	while (1)
	{
		if (p->h == 0)
		{
			if (p->next != NULL)
			{
				p = p->next;
				t->next = p;
				continue;
			}
			else
			{
				t->next = NULL;
				break;
			}
		}
		if (p->next == NULL)
			break;
		p = p->next;
		t = t->next;
	}
}
void ans()
{
	while (1)
	{
		step[++sp] = answer->empty;
		if (answer->parent == NULL)
			break;
		answer = answer->parent;
	}
}
int sc(int empty, int prev)
{
	int s = 0;
	if (empty < 6)
		if (prev != empty+3)
			s = s * 10 + (empty+3);
	if (empty%3 != 2)
		if (prev != empty+1)
			s = s * 10 + (empty+1);
	if (empty%3 != 0)
		if (prev != empty-1)
			s = s * 10 + (empty-1);
	if (empty > 2)
		if (prev != empty-3)
			s = s * 10 + (empty-3);
	return s;
}
int test()
{
	for (int i=0; i<9; i++)
		if (a[i] != goal[g][i])
			return 0;
	return 1;
}
