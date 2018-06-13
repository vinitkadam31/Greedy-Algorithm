
#include <iostream>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>
#include<list>
#include<algorithm>
#include <iterator>


using namespace std;

struct Node
{
	char chr;
	int value;
	int label;
	Node* left;
	Node* right;
	Node(char chr, int value)
	{
        	this->chr = chr;
        	left = right = NULL;
        	this->value = value;
        	//this->freq = freq;
    	}
};

vector<Node *> Huff;

/*Node* createNode(int data)
{
  Node* Nnode;
  Nnode = new Node(data);
  //Nnode->value = data;
  Nnode->left = NULL;
  Nnode->right = NULL;
  return Nnode;
}*/

/*Node* makeNode(int data)
{
  Node* Nnode;
  //Nnode = new node();
  Nnode->value = data;
  Nnode->left = NULL;
  Nnode->right = NULL;
  return Nnode;
}*/

void sort(int arr[], int n)
{
   int temp;
   for (int i = 0; i < n-1; i++)
       for (int j = 0; j < n-i-1; j++)
           if (arr[j] > arr[j+1])
           {
           		temp = arr[j];
           		arr[j] = arr[j+1];
           		arr[j+1] = temp;
           }
}

void sSort()
{
    Node* temp;
    for (int i=1; i < Huff.size(); i++)
    {
        for (int j = 0; j < Huff.size() - i; j++)
             if (Huff[j]->value > Huff[j + 1]->value)
            {
                temp = Huff[j];
                Huff[j] = Huff[j + 1];
                Huff[j + 1] = temp;
            }
    }
}

void addNewStruct(Node arr[],Node *str,int n)
{
	arr[n].chr = str->chr;
	arr[n].value = str->value;
	arr[n].label = str->label;
	arr[n].left = str->left;
	arr[n].right = str->right;
}

void removeFirstElement()
{
	for (int i = 0; i < Huff.size()-1; i++)
	{
		Huff[i] = Huff[i+1];
	}
	Huff.pop_back();
}

void printCodes(Node *root, string str)
{

    if (root == NULL)
        return;

    if (root->chr != '$')
        cout << root->chr << ": " << str << "\n";

    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
}

void PreTraversal(Node *node)
{
    if(node != NULL)
    {
	cout<<"\nNODE:"<<node->chr<<"-"<<node->value;
	PreTraversal(node->left);
        PreTraversal(node->right);
    }
}

vector<string> split(const string &s, char delim) {
    stringstream ss(s);
    string item;
    vector<string> tokens;
    while (getline(ss, item, delim)) {
        tokens.push_back(item);
    }
    return tokens;
}

string removeLeadingSpace(string text)
{
    size_t emptySpaceIndex = text.find_first_not_of(" \t");
    text.erase(0, emptySpaceIndex);
    return text;
}

int main(int argc, char* argv[]){

	ifstream in(argv[1]);//argv[1]
    	vector<string> input;
    	if(!in) {
        	cout << "Cannot open input file.\n";
        	return 1;
    	}

    	char str[255];

    	while(in)
    	{
        	in.getline(str, 255);  // delim defaults to '\n'
        	if(in)
        	{
         		input.push_back(str);
         		//cout<<str<<endl;
        	}
    	}
    	in.close();
//cout<<endl;
	vector<string> c = split(input[0],',');
	vector<string> f = split(input[1],',');

	char ch[20];
	int freq[20];

	for(int i=0;i<(int)c.size();i++)
    	{
    	    string temp = removeLeadingSpace(c[i].c_str());
    	    //cout<<temp<<endl;;
        	ch[i] = temp[0];
    	}
    	//cout<<endl;
	for(int i=0;i<(int)f.size();i++)
    	{
        	freq[i] = atoi(f[i].c_str());//atoi(removeLeadingSpace(f[i].c_str()));
        	//cout<<freq[i]<<endl;
    	}
//cout<<endl;
//	char ch[20] = {'a','b','c','d','e','f'};
//	int freq[20] = {45,13,12,16,9,5};
	//int pQueue[20] = {45,13,12,16,9,5};
	int MAX_FREQ = 0;
	int MAX_SIZE = 0;
	//Node min1,min2;
	//node Huff[20];


	for(int i=0;i<(int)f.size();i++)
	{
	    if(freq[i] == 0)
		{
			MAX_SIZE = i;
			break;
		}
		MAX_FREQ += freq[i];
		//Huff[i].chr = ch[i];
		//Huff[i].value = freq[i];
		Node* temp1 = new Node(ch[i], freq[i]);
		//temp1->chr = ch[i];
		//cout<<ch[i]<<"-"<<freq[i];
		Huff.push_back(temp1);

	}
//cout<<endl;
	//cout<<Huff[0]->chr<<Huff[0]->value<<MAX_SIZE<<endl;
	sSort();
	int n=0;
	int minSum = 0;
	struct Node *min1, *min2;
	while(Huff.size()!=1){

		if(Huff[0]->value == MAX_FREQ)
			break;
		min1 = Huff[0];
		removeFirstElement();
		MAX_SIZE--;
		min2 = Huff[0];
		removeFirstElement();
		MAX_SIZE--;
		minSum = min1->value + min2->value;
		//Node *root = createNode(minSum);
		//addNewStruct(Huff,root,MAX_SIZE);
		Node *root = new Node('$', minSum);
		root->left = min1;
		root->right = min2;
		Huff.push_back(root);
		MAX_SIZE++;
		//cout<<Huff[0].value<<Huff[MAX_SIZE-1].value;
		//root->left = &min1;
		//root->right = &min2;
		/*if(Huff[0]->value == MAX_FREQ)
        {
            cout<<endl;
        }*/
		//cout<<root->right->value<<endl;
		sSort();
		n++;
	}

	//bubbleSort();
    	printCodes(Huff[0], "");
    	//PreTraversal(Huff[0]);
	//cout<<Huff[20]->chr<<endl;

	return 0;
}