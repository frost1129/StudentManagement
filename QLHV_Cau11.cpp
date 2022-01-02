#include <iostream>
#include <string>
#include <stdlib.h>
#include <conio.h>

using namespace std;

const int NUM_CHARS = 27; //26 chu cai + dau cach " " 


// KHAI BAO TRIE NODE
struct trieNode {
    trieNode *child[NUM_CHARS];
    bool isFullName;
};

trieNode *createTrie() {
    trieNode *newTrie = new trieNode;
    newTrie->isFullName = false;

    for (int i = 0; i < NUM_CHARS; i++) {
        newTrie->child[i] = NULL;
    }
    return newTrie;
}

void insertTrieName(trieNode *root, string fullname) {
    trieNode *pTrie = root;
    int length = fullname.length();

    for (int i = 0; i < length; i++) {

        // doi ky tu chua hoa ve chu thuong
        fullname[i] = tolower(fullname[i]);

        // index so chi vi tri cua a-z va dau cach
        int index;
        if ((int)fullname[i] != 32)
            index = fullname[i] - 'a';
        else    
            index = 26;


        if (pTrie->child[index] == NULL) 
            pTrie->child[index] = createTrie();
        
        pTrie = pTrie->child[index];
    }

    // xet co them 1 fullname vao thanh cong hay khong
    pTrie->isFullName = true;
    return;
}

bool isLastName(trieNode *root) {
    for (int i = 0; i < NUM_CHARS; i++) 
        if (root->child[i] != NULL)
            return false;
    
    return true;
}

void printAttemp(trieNode *root, string prefix) {
    if (root->isFullName) {
        cout << prefix << endl;
    }

    for (int i = 0; i < NUM_CHARS; i++) {
        if (root->child[i] != NULL) {
            // 0-25: a-z; 26: space " "
            char next;
            if (i != 26)
                next = (char)('a' + i);
            else 
                next = (char)32;
            
            prefix.push_back(next);
            printAttemp(root->child[i], prefix);
            prefix.pop_back();
        }
    }
}

void printSuggestions(trieNode *root, string query) {
    trieNode *pTrie = root;
    int length = query.length();
    
    for (int i = 0; i < length; i++) {
        int index;
        if ((int)query[i] != 32)
            index = query[i] - 'a';
        else    
            index = 26;

        // khong co chuoi nao trong trie thoa du lieu dau vao
        if (pTrie->child[index] == NULL)
            return;

        pTrie = pTrie->child[index];
    }

    bool isLast = isLastName(pTrie);

    // tao thanh ten hoan chinh va la ten cuoi cung trong nhanh trie
    if (pTrie->isFullName == true && isLast) {
        cout << query << endl;
        return;
    }

    // tiep tuc duyet cac node sau
    if (!isLast) {
        string prefix = query; 
        printAttemp(pTrie, prefix);
        return;
    }
}

void searchSuggestFunc(trieNode *root) {
    string tmp;
    char catchChar;
    
    do {
        system("cls");
        cout << "--------------- Search Suggestion Function ---------------\n\n";


        cout << "Nhap ten ban muon tim kiem (enter de thoat khoi trinh goi y): " << tmp;
        cout << endl << endl;
        if(tmp != "") {
            cout << "Y cua ban la: \n";
            printSuggestions(root, tmp);
        }
        cout << endl;
        
        catchChar = getch();
        
        // xoa ky tu khi del
        if (catchChar != 8)
            tmp.push_back(tolower(catchChar));
        else
            tmp.resize(tmp.size() - 1);
    } while (catchChar != 13);
    cout << endl;
}

 

int main() {
    trieNode *root = createTrie();

    insertTrieName(root, "nguyen van an");
    insertTrieName(root, "vu nguyen mai linh");
    insertTrieName(root, "nguyen van anh");
    insertTrieName(root, "nguyen thi thuy my");
    insertTrieName(root, "nguyen thanh hai");
    insertTrieName(root, "ngo pham thanh hieu");
    insertTrieName(root, "nguyen thi thanh");
    insertTrieName(root, "vo pham thanh hoang");
    insertTrieName(root, "Van Quoc Ty");



    searchSuggestFunc(root);

    delete(root);
    system("pause");
    return 0;
}