#include <iostream>
#include <queue>
#include <map>
#include <vector>
#include <string>
#include <Windows.h>

using namespace std;

struct Node {
    string symbol;
    int frequency;
    Node* left;
    Node* right;

    Node(const string& s, int f) : symbol(s), frequency(f), left(nullptr), right(nullptr) {}
};
struct Compare {
    bool operator()(Node* left, Node* right) {
        if (left->frequency == right->frequency) {
            return left->symbol.compare(right->symbol) == 1;
        }
        return left->frequency > right->frequency;
    }
};

void buildCodes(Node* root, const string& code, map<string, string>& huffmanCodes) {
    if (!root) return;
    if (root->left == nullptr && root->right == nullptr) {
        huffmanCodes[root->symbol] = code;
    }
    buildCodes(root->left, code + "0", huffmanCodes);
    buildCodes(root->right, code + "1", huffmanCodes);
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    string input;
    getline(cin, input);

    map<string, int> frequency;

    for (int i = 0; i < input.length(); i++) {
        frequency[string(1, input[i])]++;
    }

    cout << "Частота символов:" << endl;
    for (const auto& pair : frequency) {
        cout << pair.first << ": " << pair.second << '\n';
    }
    cout << '\n';

    priority_queue<Node*, vector<Node*>, Compare> pq;


    for (const auto& pair : frequency) {
        pq.push(new Node(pair.first, pair.second));
    }

    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        Node* parent = new Node(left->symbol, left->frequency + right->frequency);
        parent->left = left;
        parent->right = right;

        pq.push(parent);
    }

    Node* root = pq.top();
    map<string, string> huffmanCodes;
    buildCodes(root, "", huffmanCodes);

    cout << "Коды Хаффмана:" << endl;
    for (const auto& pair : huffmanCodes) {
        cout << pair.first << ": " << pair.second << endl;
    }


    string encodedString;
    for (char c : input) {
        encodedString += huffmanCodes[string(1, c)];
    }

    cout << "\nЗакодированная строка: " << encodedString << endl;


    string decodedString;
    Node* current = root;
    for (char bit : encodedString) {
        current = (bit == '0') ? current->left : current->right;
        if (current->left == nullptr && current->right == nullptr) {
            decodedString += current->symbol;
            current = root;
        }
    }

    cout << "Декодированная строка: " << decodedString << endl;

    return 0;
}
