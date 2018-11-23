#include<iostream>
#include<fstream>
#include<cmath>
using namespace std;

struct HashNode
{
public:
    std::string word;
};



class HashTable
{
public:
    int tsize;
    int count;
    int collis;
    struct HashNode *hash_arr;

    HashTable(int s)
    {
        this->tsize = s;
        this->count = 0;
        this->collis = 0;
        this->hash_arr = new HashNode[tsize];

        for(int i = 0; i < tsize; i++)
        {
            hash_arr[i].word = "NULL";
        }

    }

    int hash_val(string, int);
    HashTable hash_file_linear(string, HashTable);
    HashTable hash_file_quad(string, HashTable);
    int rehash(HashTable);
    bool isPrime(int);
    void search(string, HashTable);
    void display(HashTable);

};



int HashTable::hash_val(string key, int t)
{
    int h = 0;
    for(int i = 0; i < key.length(); i++)
    {
        h = h + key[i];
    }
    return (h % t);

}


HashTable HashTable::hash_file_linear(string fname, HashTable href)
{
    std::string word;
    ifstream dict;
    dict.open(fname);
    if(dict.fail())
    {
        cout<<"Error opening file";
    }
    while(dict >> word)
    {
        if (href.count < (href.tsize / 2))
        {
            int pos = hash_val(word, href.tsize);
            while (href.hash_arr[pos].word != "NULL")
            {
                pos = (pos + 1) % href.tsize;
                href.collis = href.collis + 1;
            }
            href.hash_arr[pos].word = word;
            href.count = href.count + 1;
        }
        else
        {
            cout <<endl;
            cout << "Collisions with table size of " << href.tsize << " : " << href.collis << endl;
            cout << "Load factor exceeds 0.5..." << endl;
            int n = href.rehash(href);
            cout << "Increasing table size from " << href.tsize << " to " << n << " ..." << endl;
            HashTable hnew(n);
            return hash_file_linear(fname, hnew);
        }
    }
    dict.close();
    return href;
}



HashTable HashTable::hash_file_quad(string fname, HashTable hp)
{
    std::string word;
    ifstream dict;
    dict.open(fname);
    if(dict.fail())
    {
        cout<<"Error opening file";
    }
    while(dict >> word)
    {
        if (hp.count < (hp.tsize / 2))
        {
            int pos = hash_val(word, hp.tsize);
            int j = 1;
            while (hp.hash_arr[pos].word != "NULL")
            {
                pos = (pos + 2*j - 1) % hp.tsize;
                hp.collis = hp.collis + 1;
                j = j + 1;
            }
            hp.hash_arr[pos].word = word;
            hp.count = hp.count + 1;
        }
        else
        {
            cout << endl;
            cout << "Collisions with table size of " << hp.tsize << " : " << hp.collis << endl;
            cout << "Load factor exceeds 0.5..." << endl;
            int n = hp.rehash(hp);
            cout << "Increasing table size from " << hp.tsize << " to " << n << " ..." << endl;
            HashTable hnew(n);
            return hash_file_quad(fname, hnew);
        }
    }
    dict.close();
    return hp;
}






int HashTable::rehash(HashTable ht)
{
    int r = 2 * (ht.tsize);
    int s = r + 1;
    bool flag = false;
    while(!flag)
    {
        if(isPrime(s))
        {
            flag = true;
        }
        s = s + 1;
    }
    return (s-1);
}





bool HashTable::isPrime(int n)
{
    for(int i = 2; i <= n/2; i++)
    {
        if(n % i == 0)
        {
            return false;
        }
    }
    return true;
}





void HashTable::search(string word, HashTable ht)
{
    for(int i = 0; i< ht.tsize; i++)
    {
        if (ht.hash_arr[i].word == word)
        {
            cout << "The word " << word << " was found" << endl;
            return;
        }
    }
    cout << "The word " << word << " was not found" << endl;
}


void HashTable::display(HashTable ht)
{
    cout << endl;
    cout << "The words in the dictionary are:" << endl;
    for(int i = 0; i < ht.tsize; i++)
    {
        if(hash_arr[i].word != "NULL")
        {
            cout << hash_arr[i].word << endl;
        }
    }

}


int main()
{
    cout << "Implementing hashing using linear probing for 100 words" << endl;
    HashTable ht(53);
    cout << "Starting table size: " << ht.tsize << endl;
    ht = ht.hash_file_linear("wordlist.txt", ht);
    cout <<  endl;
    cout << "Collisions with a table size of " << ht.tsize << " : " << ht.collis << endl;
    cout << endl;
    cout << "The number of words hashed is " << ht.count << endl;
    cout << "The final table size is " << ht.tsize << endl;
    cout << "----------------------------------------------------------" << endl;


    cout << "Implementing hashing using quadratic probing for 100 words" << endl;
    HashTable hs(53);
    cout << "Starting table size: " << hs.tsize << endl;
    hs = hs.hash_file_quad("wordlist.txt", hs);
    cout << endl;
    cout << "Collisions with a table size of " << hs.tsize << " : " << hs.collis << endl;
    cout << endl;
    cout << "The number of words hashed is " << hs.count << endl;
    cout << "The final table size is " << hs.tsize << endl;
    cout << "----------------------------------------------------------" << endl;

    cout << "Implementing hashing using quadratic probing for 115 words" << endl;
    HashTable hdemo(53);
    cout << "Starting table size: " << hdemo.tsize << endl;
    hdemo = hdemo.hash_file_quad("wordlist2.txt", hdemo);
    cout <<  endl;
    cout << "Collisions with a table size of " << hdemo.tsize << " : " << hdemo.collis << endl;
    cout << endl;
    cout << "The number of words hashed is " << hdemo.count << endl;
    cout << "The final table size is " << hdemo.tsize << endl;
    cout << "----------------------------------------------------------" << endl;
    int choice;
    string userword;

    while (1)
    {
        cout << endl;
        cout << "Please select an option" << endl;
        cout << "1. Search for a word in the hash table" << endl;
        cout << "2. Exit the menu" << endl;
        cin >> choice;

        switch(choice)
        {
            case 1:
                cout << "Enter the word to be searched: " << endl;
                cin >> userword;
                ht.search(userword, ht);
                break;

            case 2:
                exit(0);
                break;

            default:
                cout << "Wrong choice" << endl;
                break;
        }
    }
    return 0;

}