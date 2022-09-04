#include<SFML/Graphics.hpp>
#include<windows.h>
#include<iostream>
#include<cstdio>
#include<sstream>
#include<algorithm>
#define pow2(n) (1 << (n))
using namespace std;
using namespace sf;


//AVL Tree Setup 
struct avl_node
{
	int data;
	struct avl_node* left;
	struct avl_node* right;
}*root;


class avlTree
{
public:
	int* arr;
	const int size = 7;
	int height(avl_node*);
	int diff(avl_node*);
	avl_node* rr_rotation(avl_node*);
	avl_node* ll_rotation(avl_node*);
	avl_node* lr_rotation(avl_node*);
	avl_node* rl_rotation(avl_node*);
	avl_node* balance(avl_node*);
	avl_node* insert(avl_node*, int);
	void display(avl_node*, int);
	void inorder(avl_node*);
	void preorder(avl_node*);
	void postorder(avl_node*);
	avlTree()
	{
		root = NULL;
		arr = new int[size];
		for (int i = 0; i < 7; i++)
			arr[i] = 0;
	}
	void Insertion_Array(avl_node* current, int index)
	{
		if (current == NULL || index >= size)
			return;
		arr[index] = current->data;
		Insertion_Array(current->left, (2 * index) + 1);
		Insertion_Array(current->right, (2 * index) + 2);
	}
	void Array_PreOrder(int index)
	{
		if (index >= size)
			return;
		if (arr[index] != 0)
			cout << arr[index] << "  ";
		Array_PreOrder((2 * index) + 1);
		Array_PreOrder((2 * index) + 2);
	}
	void Array_InOrder(int index)
	{
		if (index >= size)
			return;
		Array_InOrder((2 * index) + 1);
		if (arr[index] != 0)
			cout << arr[index] << "  ";
		Array_InOrder((2 * index) + 2);
	}
	//Returns the updated AVL Tree after each entry of data.
	int* ArrRet()
	{
		return arr;
	}
};


int avlTree::height(avl_node* temp)
{
	int h = 0;
	if (temp != NULL)
	{
		int l_height = height(temp->left);
		int r_height = height(temp->right);
		int max_height = max(l_height, r_height);
		h = max_height + 1;
	}
	return h;
}


int avlTree::diff(avl_node* temp)
{
	int l_height = height(temp->left);
	int r_height = height(temp->right);
	int b_factor = l_height - r_height;
	return b_factor;
}


avl_node* avlTree::rr_rotation(avl_node* parent)
{
	avl_node* temp;
	temp = parent->right;
	parent->right = temp->left;
	temp->left = parent;
	return temp;
}

avl_node* avlTree::ll_rotation(avl_node* parent)
{
	avl_node* temp;
	temp = parent->left;
	parent->left = temp->right;
	temp->right = parent;
	return temp;
}


avl_node* avlTree::lr_rotation(avl_node* parent)
{
	avl_node* temp;
	temp = parent->left;
	parent->left = rr_rotation(temp);
	return ll_rotation(parent);
}


avl_node* avlTree::rl_rotation(avl_node* parent)
{
	avl_node* temp;
	temp = parent->right;
	parent->right = ll_rotation(temp);
	return rr_rotation(parent);
}


avl_node* avlTree::balance(avl_node* temp)
{
	int bal_factor = diff(temp);
	if (bal_factor > 1)
	{
		if (diff(temp->left) > 0)
			temp = ll_rotation(temp);
		else
			temp = lr_rotation(temp);
	}
	else if (bal_factor < -1)
	{
		if (diff(temp->right) > 0)
			temp = rl_rotation(temp);
		else
			temp = rr_rotation(temp);
	}
	return temp;
}


avl_node* avlTree::insert(avl_node* root, int value)
{
	if (root == NULL)
	{
		root = new avl_node;
		root->data = value;
		root->left = NULL;
		root->right = NULL;
		return root;
	}
	else if (value < root->data)
	{
		root->left = insert(root->left, value);
		root = balance(root);
	}
	else if (value >= root->data)
	{
		root->right = insert(root->right, value);
		root = balance(root);
	}
	return root;
}

void avlTree::display(avl_node* ptr, int level)
{
	int i;
	if (ptr != NULL)
	{
		display(ptr->right, level + 1);
		printf("\n");
		if (ptr == root)
			cout << "Root -> ";
		for (i = 0; i < level && ptr != root; i++)
			cout << "        ";
		cout << ptr->data;
		display(ptr->left, level + 1);
	}
}


void avlTree::inorder(avl_node* tree)
{
	if (tree == NULL)
		return;
	inorder(tree->left);
	cout << tree->data << "  ";
	inorder(tree->right);
}

void avlTree::preorder(avl_node* tree)
{
	if (tree == NULL)
		return;
	cout << tree->data << "  ";
	preorder(tree->left);
	preorder(tree->right);

}


void avlTree::postorder(avl_node* tree)
{
	if (tree == NULL)
		return;
	postorder(tree->left);
	postorder(tree->right);
	cout << tree->data << "  ";
}


//Hash Tree Setup
class Hash
{
public:
	int* Arr;
	Hash()
	{
		Arr = new int[10];
		for (int i = 0; i < 10; i++)
		{
			Arr[i] = -1;
		}
	}

	//Setting Linear Tree 
	void Linear(int Data)
	{
		bool condi = true;
		int h = Data % 10;
		for (int i = 0; i < 10; i++)
		{
			if (Arr[(h + i) % 10] == -1)
			{
				Arr[(h + i) % 10] = Data;
				condi = false;
			}
		}
		if (condi)
		{
			cout << "Its already Full" << endl;
		}
	}

	//Setting Quadratic Tree
	void Quadratic(int Data)
	{
		bool condi = true;
		int h = Data % 10;
		for (int i = 0; i < 100; i++)
		{
			if (Arr[(h + (i * i)) % 10] == -1)
			{
				Arr[(h + (i * i)) % 10] = Data;
				condi = false;
			}
		}
		if (condi)
		{
			cout << "Its already Full or unable to be stored" << endl;
		}
	}

	int* RetArr()
	{
		for (int i = 0; i < 10; i++)
			cout << Arr[i] << "->";
		cout << endl;
		return Arr;
	}
};


//Binary Search Tree Setup
class BST
{
	int* arr;
	const int size = 7;
public:
	BST()
	{
		arr = new int[size];
		for (int i = 0; i < size; i++)
			arr[i] = 0;
	}
	void Insert(int v, int index)
	{
		if (index >= size)
			return;
		else if (arr[index] != 0)
		{
			if (v <= arr[index])
				Insert(v, (2 * index) + 1);
			else if (v > arr[index])
				Insert(v, (2 * index) + 2);
		}
		else
			arr[index] = v;
	}
	int Search(int v, int index)
	{
		if (index >= size)
			return -1;
		else if (v != arr[index])
		{
			if (v < arr[index])
				Search(v, (2 * index) + 1);
			else if (v > arr[index])
				Search(v, (2 * index) + 2);
		}
		else if (v = arr[index])
			return index;
	}
	void Delete(int v)
	{
		int index = Search(v, 0);
		if (index != -1)
		{
			arr[index] = 0;
			int i;
			if (arr[(2 * index) + 1] != 0)//this if condition's body is for left-sub Tree maximum value
			{
				i = (index * 2) + 1;
				while (i < size && arr[i] != 0)
					i = (2 * i) + 2;
				i = (i / 2) - 1;
			}
			else if (arr[(2 * index) + 2] != 0)//This is for Right-sub Tree Minimum value
			{
				i = (index * 2) + 2;
				while (i < size && arr[i] != 0)
					i = (2 * i) + 1;
				i = (i / 2);
			}
			swap(arr[i], arr[index]);
			InsertAgain(i);
		}
		else
			cout << "The number is not present in tree!!!!........." << endl;
	}
	void InsertAgain(int i)
	{
		if (i >= size)
			return;
		else if (arr[i] != 0)
		{
			Insert(arr[i], 0);
			arr[i] = 0;
		}
		InsertAgain((2 * i) + 1);
		InsertAgain((2 * i) + 2);
	}
	int* Display()
	{
		for (int i = 0; i < size; i++)
			cout << arr[i] << "->";
		cout << endl;
		return arr;
	}
};


int main()
{
	Hash HASHVar;
	avlTree AVLVar;
	BST BSTVar;
	bool BCondi = false, ACondi = false, HCondi = false, Dis = false, Spress = true, Lin = false, Quad = false, Q = false, E = false;
	int Data = 0;
	string DataS;
	string DataSArr[7];
	string HashSArr[10];
	int Counter = 0;
	sf::RenderWindow window(VideoMode(1000, 500), "Visualization");
	Color color(Color::Black);
	sf::Event event;
	Font font;
	//Checking if arial font style is stored locally.
	if (!font.loadFromFile("arial.ttf")) {
		cout << "Font loading failed:" << endl;
	}
	Text text[3];
	Text Picked;
	Text IncDec;
	Text Del;
	Text DataMunip;
	Text DisOutput[7];
	Text HashDis[10];
	Text Lin_Quad;
	Text LQPick;


	//Setting font text size, color, font style(arial.ttf)
	for (int i = 0; i < 3; i++)
	{
		text[i].setFont(font);
		text[i].setFillColor(Color::Blue);
		text[i].setCharacterSize(20);
	}
	for (int i = 0; i < 7; i++)
	{
		DisOutput[i].setFont(font);
		DisOutput[i].setFillColor(Color::Magenta);
		DisOutput[i].setCharacterSize(20);
	}
	for (int i = 0; i < 10; i++)
	{
		HashDis[i].setFont(font);
		HashDis[i].setFillColor(Color::Magenta);
		HashDis[i].setCharacterSize(20);
	}
	Picked.setFont(font);
	Picked.setFillColor(Color::Green);
	Picked.setCharacterSize(25);
	Picked.setStyle(Text::Bold | Text::Underlined);

	IncDec.setFont(font);
	IncDec.setFillColor(Color::Green);
	IncDec.setCharacterSize(25);
	IncDec.setStyle(Text::Bold);

	Del.setFont(font);
	Del.setFillColor(Color::Green);
	Del.setCharacterSize(25);
	Del.setStyle(Text::Bold);

	DataMunip.setFont(font);
	DataMunip.setFillColor(Color::Cyan);
	DataMunip.setCharacterSize(30);
	DataMunip.setStyle(Text::Bold);

	Lin_Quad.setFont(font);
	Lin_Quad.setFillColor(Color::Green);
	Lin_Quad.setCharacterSize(25);
	Lin_Quad.setStyle(Text::Bold);

	LQPick.setFont(font);
	LQPick.setFillColor(Color::Green);
	LQPick.setCharacterSize(25);
	LQPick.setStyle(Text::Bold);


	//Setting Position for text and Tree nodes
	text[0].setPosition(30, 10);
	text[1].setPosition(30, 30);
	text[2].setPosition(30, 50);
	DisOutput[0].setPosition(700, 100);
	DisOutput[1].setPosition(600, 250);
	DisOutput[2].setPosition(800, 250);
	DisOutput[3].setPosition(550, 400);
	DisOutput[4].setPosition(650, 400);
	DisOutput[5].setPosition(750, 400);
	DisOutput[6].setPosition(850, 400);
	Picked.setPosition(30, 70);
	IncDec.setPosition(30, 100);
	Del.setPosition(30, 150);
	DataMunip.setPosition(30, 400);
	HashDis[0].setPosition(700, 30);
	HashDis[1].setPosition(700, 60);
	HashDis[2].setPosition(700, 90);
	HashDis[3].setPosition(700, 120);
	HashDis[4].setPosition(700, 150);
	HashDis[5].setPosition(700, 180);
	HashDis[6].setPosition(700, 210);
	HashDis[7].setPosition(700, 240);
	HashDis[8].setPosition(700, 270);
	HashDis[9].setPosition(700, 300);
	Lin_Quad.setPosition(30, 200);
	LQPick.setPosition(30, 250);
	while (window.isOpen())
	{
		text[0].setString("1)Binary Search Tree");
		window.draw(text[0]);
		text[1].setString("2)AVL Tree");
		window.draw(text[1]);
		text[2].setString("3)Heap Tree");
		window.draw(text[2]);
		Del.setString("To stop delete press S");

		if (Keyboard::isKeyPressed(Keyboard::Num1) || BCondi)
		{
			Picked.setString("You picked BST");
			BCondi = true;
		}
		if (Keyboard::isKeyPressed(Keyboard::Num2) || ACondi)
		{
			Picked.setString("You picked AVL");
			ACondi = true;
		}
		if (Keyboard::isKeyPressed(Keyboard::Num3) || HCondi)
		{
			Picked.setString("You picked Heap");
			Lin_Quad.setString("Q for Linear | E for Quadratic");
			HCondi = true;
		}

		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			Data++;
		}

		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			Data--;
		}

		if (Keyboard::isKeyPressed(Keyboard::Enter))
		{
			stringstream ss;
			int* Display = nullptr;
			if (BCondi)
			{
				if (Spress)
					BSTVar.Insert(Data, 0);
				else if (!Spress)
					BSTVar.Delete(Data);
				Display = BSTVar.Display();
			}
			if (ACondi)
			{
				if (Counter < 7)
					AVLVar.insert(root, Data);
				Display = AVLVar.ArrRet();
			}
			if (BCondi || ACondi)
			{
				for (int i = 0; i < 7; i++)
				{
					if (Display[i] != 0)
					{
						ss << Display[i];
						ss >> DataSArr[i];
					}
					else
					{
						DataSArr[i] = "0";
					}
				}
			}
			if (HCondi && (Lin || Quad))
			{
				if (Lin)
				{
					HASHVar.Linear(Data);
				}
				if (Quad)
				{
					HASHVar.Quadratic(Data);
				}
				Display = HASHVar.RetArr();
				for (int i = 0; i < 10; i++)
				{
					if (Display[i] != -1)
					{
						ss << Display[i];
						ss >> HashSArr[i];
					}
					else
					{
						HashSArr[i] = "0";
					}
				}
			}
			Data = 0;
			Dis = true;
			Counter++;
		}

		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			Spress = true;
		}

		if (Keyboard::isKeyPressed(Keyboard::S))
		{
			Spress = false;
		}

		if (Keyboard::isKeyPressed(Keyboard::Q))
		{
			Q = true;
			E = false;
			Lin = true;
			Quad = false;
		}

		if (Keyboard::isKeyPressed(Keyboard::E))
		{
			E = true;
			Q = false;
			Lin = false;
			Quad = true;
		}

		if (Q)
		{
			LQPick.setString("Linear Probing");
			window.draw(LQPick);
		}
		if (E)
		{
			LQPick.setString("Quadratic Probing");
			window.draw(LQPick);
		}

		if (!Spress)
		{
			window.draw(Del);
		}

		if (Dis && (BCondi || ACondi))
		{
			for (int i = 0; i < 7; i++)
			{
				DisOutput[i].setString(DataSArr[i]);
				window.draw(DisOutput[i]);
			}
		}

		if (Dis && HCondi)
		{
			for (int i = 0; i < 10; i++)
			{
				HashDis[i].setString(HashSArr[i]);
				window.draw(HashDis[i]);
			}
		}

		if (BCondi || ACondi || HCondi)
		{
			IncDec.setString("Left to Dec | Right to Inc");
			stringstream ss;
			ss << Data;
			ss >> DataS;
			DataMunip.setString(DataS);
			window.draw(Picked);
			window.draw(IncDec);
			window.draw(DataMunip);
		}
		if (HCondi)
		{
			window.draw(Lin_Quad);
		}

		Window();
		window.display();
		window.clear(color);
		Sleep(100);

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			{
				window.close();
			}
		}

	}
}
