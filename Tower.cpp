using namespace std;

#include <iostream>
#include <stack>
#include <cstdlib>

void move(stack<int> &src, stack<int> &dst)
{
	try
	{
		if (src.empty())
			throw ("There is no disk at the source to move.");
		if (dst.empty() || src.top() < dst.top())
		{
			dst.push(src.top());
			src.pop();
		}
		else
			throw ("The move is illegal.");
	}
	catch (const char *e)
	{
		cerr << e << endl;
	}
}

void print_floor(int floor_size, int tower_height)
{
	for (int i = 0; i < tower_height - floor_size; i++) cout << ' ';
	for (int i = 0; i < floor_size * 2 - 1; i++) cout << "■";
	for (int i = 0; i < tower_height - floor_size; i++) cout << ' ';
}

void print_towers(stack<int> tower1, stack<int> tower2, stack<int> tower3, int tower_height)
{
	int i = 0;
	while (i < tower_height)
	{
		if (i < tower_height - tower1.size())
			for (int i = 0; i < tower_height * 2 - 1; i++) cout << ' ';
		else
		{
			print_floor(tower1.top(), tower_height);
			tower1.pop();
		}
		for (int i = 0; i < tower_height / 2 + 1; i++) cout << ' ';
		if (i < tower_height - tower2.size())
			for (int i = 0; i < tower_height * 2 - 1; i++) cout << ' ';
		else
		{
			print_floor(tower2.top(), tower_height);
			tower2.pop();
		}
		for (int i = 0; i < tower_height / 2 + 1; i++) cout << ' ';
		if (i < tower_height - tower3.size())
			for (int i = 0; i < tower_height * 2 - 1; i++) cout << ' ';
		else
		{
			print_floor(tower3.top(), tower_height);
			tower3.pop();
		}
		cout << endl;
		i++;
	}
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		cout << "Usage: ./a.out <number>" << endl; 
	}

	int tower_height = atoi(argv[1]);
	
	stack<int> tower1;
	stack<int> tower2;
	stack<int> tower3;
	
	// tower1 initialization
	int i = tower_height;
	while (i > 0)
	{
		tower1.push(i);
		i--;
	}

	cout << i << endl;
	print_towers(tower1, tower2, tower3, tower_height);
	while (i < (1 << tower_height) - 1)
	{
		if (tower_height % 2 == 0)
		{
			if (i % 2 == 0)
			{
				if (i % 3 == 0)
					move(tower1, tower2);
				if (i % 3 == 2)
					move(tower2, tower3);
				if (i % 3 == 1)
					move(tower3, tower1);
			}
			if (i % 2 == 1)
			{
				if (i % 3 == 1)
				{
					if (!tower1.empty() && (tower3.empty() || tower1.top() < tower3.top()))
						move(tower1, tower3);
					else
						move(tower3, tower1);
				}
				if (i % 3 == 0)
				{
					if (!tower2.empty() && (tower1.empty() || tower2.top() < tower1.top()))
						move(tower2, tower1);
					else
						move(tower1, tower2);
				}
				if (i % 3 == 2)
				{
					if (!tower3.empty() && (tower2.empty() || tower3.top() < tower2.top()))
						move(tower3, tower2);
					else
						move(tower2, tower3);
				}
			}
		}
		if (tower_height % 2 == 1)
		{
			if (i % 2 == 0)
			{
				if (i % 3 == 0)
					move(tower1, tower3);
				if (i % 3 == 2)
					move(tower3, tower2);
				if (i % 3 == 1)
					move(tower2, tower1);
			}
			if (i % 2 == 1)
			{
				if (i % 3 == 1)
				{
					if (!tower1.empty() && (tower2.empty() || tower1.top() < tower2.top()))
						move(tower1, tower2);
					else
						move(tower2, tower1);
				}
				if (i % 3 == 0)
				{
					if (!tower3.empty() && (tower1.empty() || tower3.top() < tower1.top()))
						move(tower3, tower1);
					else
						move(tower1, tower3);
				}
				if (i % 3 == 2)
				{
					if (!tower2.empty() && (tower3.empty() || tower2.top() < tower3.top()))
						move(tower2, tower3);
					else
						move(tower3, tower2);
				}
			}
		}
		i++;
		cout << i << endl;
		print_towers(tower1, tower2, tower3, tower_height);
	}
}
