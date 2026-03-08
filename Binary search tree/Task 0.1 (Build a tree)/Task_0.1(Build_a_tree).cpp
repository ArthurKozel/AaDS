#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Element
{
    int key = 0;
    Element* left_son = NULL;
    Element* right_son = NULL;
};

class Binary_search_tree
{
private:
    Element* root = new Element;
    vector<int> PreOrderTraversal_massive;

public:
    Element* Get_root()
    {
        return root;
    }

    void Read_from_file()
    {
        ifstream fin;
        fin.open("input.txt");
        int key;
        fin >> key;
        Add_root(key);
        while(fin >> key)
        {
            Add_element_to_bst(key);
        }
        fin.close();
    }

    void Add_root(int root_key)
    {
        root->key = root_key;
    }

    void Add_element_to_bst(int key)
    {
        Element* curr = root;
        Element* last = root;
        while (curr != NULL)
        {
            if (key == curr->key)
            {
                return;
            }
            else if (key > curr->key)
            {
                last = curr;
                curr = curr->right_son;
            }
            else if (key < curr->key)
            {
                last = curr;
                curr = curr->left_son;
            }
        }
        Element* Added = new Element;
        Added->key = key;
        if (key < last->key)
        {
            last->left_son = Added;
        }
        else
        {
            last->right_son = Added;
        }
    }

    void PreOrderTraversal(Element* element)
    {
        if(element != NULL)
        {
            PreOrderTraversal_massive.push_back(element->key);
            PreOrderTraversal(element->left_son);
            PreOrderTraversal(element->right_son);
        }
    }

    void Write_to_file()
    {
        ofstream fout;
        fout.open("output.txt");
        fout << PreOrderTraversal_massive[0];
        for(int i = 1; i < PreOrderTraversal_massive.size(); i++)
        {
            fout << endl << PreOrderTraversal_massive[i];
        }
        fout.close();
    }
};

int main()
{
    Binary_search_tree tree;
    tree.Read_from_file();
    tree.PreOrderTraversal(tree.Get_root());
    tree.Write_to_file();
    return 0;
}