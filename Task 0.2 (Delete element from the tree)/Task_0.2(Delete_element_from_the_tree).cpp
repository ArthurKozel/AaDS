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

    int Read_from_file()
    {
        ifstream fin;
        fin.open("input.txt");
        int key, deleted_key;
        fin >> deleted_key;
        fin >> key;
        Add_root(key);
        while (fin >> key)
        {
            Add_element_to_bst(key);
        }
        fin.close();
        return deleted_key;
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

    Element* Find_deleted_element(int deleted_key)
    {
        Element* curr = root;
        while(curr != NULL && curr->key != deleted_key)
        {
            if(deleted_key > curr->key)
            {
                curr = curr->right_son;
            }
            else if(deleted_key < curr->key)
            {
                curr = curr->left_son;
            }
        }
        return curr;
    }

    void Delete_key(Element* deleted_element)
    {
        if(deleted_element->left_son == NULL && deleted_element->right_son == NULL)
        {
            Element* curr = root;
            while(curr->left_son != deleted_element && curr->right_son != deleted_element)
            {
                if(deleted_element->key > curr->key)
                {
                    curr = curr->right_son;
                }
                else if (deleted_element->key < curr->key)
                {
                    curr = curr->left_son;
                }
            }
            if(curr->left_son == deleted_element)
            {
                curr->left_son = NULL;
            }
            else
            {
                curr->right_son = NULL;
            }
            delete deleted_element;
        }

        else if(deleted_element->left_son != NULL && deleted_element->right_son != NULL)
        {
            Element* curr = deleted_element->right_son;
            Element* previous = deleted_element;
            while (curr->left_son != NULL) 
            {
                previous = curr;
                curr = curr->left_son;
            }
            deleted_element->key = curr->key;
            if (previous == deleted_element) 
            {
                deleted_element->right_son = curr->right_son;
            }
            else
            {
                previous->left_son = curr->right_son;
            }
            delete curr;
        }

        else
        {
            if(deleted_element == root)
            {
                if(deleted_element->right_son != NULL)
                {
                    root = deleted_element->right_son;
                }
                else
                {
                    root = deleted_element->left_son;
                }
            }
            else
            {
                Element* curr = root;
                while (curr->left_son != deleted_element && curr->right_son != deleted_element)
                {
                    if (deleted_element->key > curr->key)
                    {
                        curr = curr->right_son;
                    }
                    else if (deleted_element->key < curr->key)
                    {
                        curr = curr->left_son;
                    }
                }
                if(deleted_element->left_son != NULL)
                {
                    if(curr->left_son == deleted_element)
                    {
                        curr->left_son = deleted_element->left_son;
                    }
                    else
                    {
                        curr->right_son = deleted_element->left_son;
                    }
                }
                else
                {
                    if (curr->left_son == deleted_element)
                    {
                        curr->left_son = deleted_element->right_son;
                    }
                    else
                    {
                        curr->right_son = deleted_element->right_son;
                    }
                }
                delete deleted_element;
            }
        }

    }

    void PreOrderTraversal(Element* element)
    {
        if (element != NULL)
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
        for (int i = 1; i < PreOrderTraversal_massive.size(); i++)
        {
            fout << '\n' << PreOrderTraversal_massive[i];
        }
        fout.close();
    }
};

int main()
{
    Binary_search_tree tree;
    int deleted_key = tree.Read_from_file();
    Element* deleted_element = tree.Find_deleted_element(deleted_key);
    if(deleted_element != NULL)
    {
        tree.Delete_key(deleted_element);
    }
    tree.PreOrderTraversal(tree.Get_root());
    tree.Write_to_file();
    return 0;
}