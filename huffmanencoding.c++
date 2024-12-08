#include <iostream>
#include <queue>
#include <unordered_map>
#include <string>
using namespace std;


struct HuffmanNode {
    char ch;
    int freq;
    HuffmanNode *left, *right;

    HuffmanNode(char c, int f) {
        ch = c;
        freq = f;
        left = right = nullptr;
    }
};


struct Compare {
    bool operator()(HuffmanNode* left, HuffmanNode* right) {
        return left->freq > right->freq;
    }
};


HuffmanNode* buildHuffmanTree(const string& text) {
    unordered_map<char, int> freqMap;
    for (char ch : text) {
        freqMap[ch]++;
    }

    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> minHeap;

    
    for (auto& pair : freqMap) {
        minHeap.push(new HuffmanNode(pair.first, pair.second));
    }

    while (minHeap.size() > 1) {
       
        HuffmanNode* left = minHeap.top(); minHeap.pop();
        HuffmanNode* right = minHeap.top(); minHeap.pop();

       
        int sum = left->freq + right->freq;
        HuffmanNode* node = new HuffmanNode('\0', sum);
        node->left = left;
        node->right = right;

        
        minHeap.push(node);
    }

    
    return minHeap.top();
}


void generateCodes(HuffmanNode* root, string code, unordered_map<char, string>& huffmanCodes) {
    if (!root) return;

   
    if (root->ch != '\0') {
        huffmanCodes[root->ch] = code;
    }

    generateCodes(root->left, code + "0", huffmanCodes);
    generateCodes(root->right, code + "1", huffmanCodes);
}


string encode(const string& text, unordered_map<char, string>& huffmanCodes) {
    string encodedText;
    for (char ch : text) {
        encodedText += huffmanCodes[ch];
    }
    return encodedText;
}


string decode(HuffmanNode* root, const string& encodedText) {
    string decodedText;
    HuffmanNode* current = root;

    for (char bit : encodedText) {
        if (bit == '0') {
            current = current->left;
        } else {
            current = current->right;
        }

        
        if (current->left == nullptr && current->right == nullptr) {
            decodedText += current->ch;
            current = root;
        }
    }

    return decodedText;
}


int main() {
    string text;
    cout << "Enter the text to encode: ";
    getline(cin, text);

   
    HuffmanNode* root = buildHuffmanTree(text);

    
    unordered_map<char, string> huffmanCodes;
    generateCodes(root, "", huffmanCodes);

   
    cout << "\nHuffman Codes:\n";
    for (auto& pair : huffmanCodes) {
        cout << pair.first << ": " << pair.second << "\n";
    }

    
    string encodedText = encode(text, huffmanCodes);
    cout << "\nEncoded Text: " << encodedText << "\n";

 
    string decodedText = decode(root, encodedText);
    cout << "Decoded Text: " << decodedText << "\n";

    return 0;
}
