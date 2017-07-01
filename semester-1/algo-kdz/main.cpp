#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>


using std::string;
using std::map;
using std::vector;
using std::priority_queue;
using std::ifstream;
using std::ofstream;

// Operations counter
unsigned long int count = 0;
// Number of chars in file
unsigned long int num = 0;

/**
 * Tree node struct
 */
struct Node
{
    char value = '\0';
    int frequency = 0;
    Node *left = nullptr;
    Node *right = nullptr;
};

/**
 * Utility comparator struct
 * (descending order)
 */
struct CountCompare
{
    bool operator()(Node *a, Node *b) const
    {
        return a->frequency > b->frequency;
    }
};

/**
 * Temporary code for letter
 */
vector<int> temp_code;

/**
 * Builds frequency table for compression algorithms.
 * If compressed == true, ifstream should be opened in binary mode.
 * @param path - path to the .txt file
 * @return map &lt;char, int&gt;
 */
map<char, unsigned> BuildFrequencyTable(ifstream &fin, bool compressed)
{
    map<char, unsigned> frequency_table;
    char temp_char;
    unsigned table_size;
    unsigned temp_freq;

    if (compressed)
    {
        // Read number of chars
        count++;
        fin.read((char *) &num, sizeof(num));
        // Read frequecny table size
        count++;
        fin.read((char *) &table_size, sizeof(table_size));
        for (int i = 0; i < table_size; ++i)
        {
            count++;
            fin.read(&temp_char, sizeof(temp_char));
            count++;
            fin.read((char *) &temp_freq, sizeof(temp_freq));
            count++;
            frequency_table[temp_char] = temp_freq;
        }
    }
    else
    {
        // Reading .txt file without
        // skipping whitespaces
        while (fin >> std::noskipws >> temp_char)
        {
            count++;
            frequency_table[temp_char]++;
            count++;
            num++;
        }
    }


    count++;
    return frequency_table;
};

/**
 * Builds Huffman tree based on frequency table
 * @param table - frequency table
 * @return Node*
 */
Node *BuildHuffmanTree(map<char, unsigned> frequency_table)
{
    // Priority queue of Nodes
    priority_queue<Node *, vector<Node *>, CountCompare> nodes;

    // Fill priority queue
    // std::pair<char, int> in fact
    for (auto i : frequency_table)
    {
        count++;
        Node *temp_node = new Node;
        count++;
        temp_node->value = i.first;
        count++;
        temp_node->frequency = i.second;
        count++;
        nodes.push(temp_node);
    }

    // Build a new tree by taking
    // two first elements as left and right child
    while (nodes.size() > 1)
    {
        count++;
        Node *left = nodes.top();
        count++;
        nodes.pop();
        count++;
        Node *right = nodes.top();
        count++;
        nodes.pop();

        count++;
        Node *temp_node = new Node;
        count++;
        temp_node->frequency = left->frequency + right->frequency;
        count++;
        temp_node->left = left;
        count++;
        temp_node->right = right;

        count++;
        nodes.push(temp_node);
    }

    // Return root of the final tree
    count++;
    return nodes.top();
}

/**
 * Retrieves char codes table from the tree
 * @param node - root node of huffman tree
 * @param codes - map, which contains char and its code
 */
void GetCharCodes(Node *root, map<char, vector<int> > &codes)
{
    // Check left child
    if (root->left != nullptr)
    {
        count++;
        temp_code.push_back(0);
        count++;
        GetCharCodes(root->left, codes);
    }
    // Check right child
    if (root->right != nullptr)
    {
        count++;
        temp_code.push_back(1);
        count++;
        GetCharCodes(root->right, codes);
    }
    // Write code if letter is not null
    if (root->value != '\0')
    {
        count++;
        codes[root->value] = temp_code;
    }

    // Remove the last digit from code
    // because of moving to the previous node
    count++;
    temp_code.pop_back();
}

/**
 * Creates compressed .haff file
 * @param fin - input stream (.txt)
 * @param fout - output stream (.haff | .shan)
 * @param frequency_table - table of char frequences
 * @param codes - binary char codes
 */
void CreateCompressedFile(ifstream &fin, ofstream &fout,
        map<char, unsigned> frequency_table, map<char, vector<int> > codes)
{
    unsigned table_size = (unsigned) frequency_table.size();
    unsigned offset = 0;
    unsigned temp_freq;
    char temp_char;
    char temp_byte;

    // Write number of chars
    count++;
    fout.write((char *) &num, sizeof(num));
    // Write frequency table size
    count++;
    fout.write((char *) &table_size, sizeof(table_size));
    // Write char and its frequency
    for (auto i : frequency_table)
    {
        // Write char
        count++;
        temp_char = i.first;
        count++;
        fout.write(&temp_char, sizeof(temp_char));
        // Write frequency
        count++;
        temp_freq = i.second;
        count++;
        fout.write((char *) &temp_freq, sizeof(temp_freq));
    }

    // Write compressed text
    count++;
    offset = 0;
    count++;
    temp_byte = 0;

    while (fin >> std::noskipws >> temp_char)
    {
        for (int i : codes[temp_char])
        {
            count++;
            temp_byte = temp_byte | (i << (7 - offset));
            count++;
            offset++;
            if (offset == 8)
            {
                count++;
                fout.write(&temp_byte, sizeof(temp_byte));
                count++;
                offset = 0;
                count++;
                temp_byte = 0;
            }
        }
    }

    // Flush the rest
    count++;
    fout.write(&temp_byte, sizeof(temp_byte));
}

/**
 * Decode compressed text (binary -> text)
 * @param fin - input stream (.haff | .shan)
 * @param fout - output stream (.txt)
 */
void TranslateCharCodes(ifstream &fin, ofstream &fout, Node *root)
{
    unsigned offset = 0;
    char temp_byte;
    Node *temp_node = root;
    bool digit;
    unsigned long int i = 0;

    // Read first byte
    count++;
    fin.read(&temp_byte, sizeof(temp_byte));
    while (i < num)
    {
        // If digit appears in binary code
        count++;
        digit = temp_byte & (1 << (7 - offset));

        if (digit)
        {
            count++;
            temp_node = temp_node->right;
        }
        else
        {
            count++;
            temp_node = temp_node->left;
        }

        if (temp_node->value != '\0')
        {
            count++;
            fout << temp_node->value;
            count++;
            temp_node = root;
            count++;
            i++;
        }

        count++;
        offset++;
        if (offset == 8)
        {
            count++;
            offset = 0;
            count++;
            fin.read(&temp_byte, sizeof(temp_byte));
        }
    }
}

/**
 * Shannon-Fano divide function
 * @param root - pointer to the root of a tree
 * @param nodes - temporary container for nodes
 * @param sum - total sum of frequences
 */
void Divide(Node *&root, vector<Node *> nodes, int sum)
{
    if (nodes.size() == 1)
    {
        count++;
        root = nodes[0];
        count++;
        return;
    }

    if (root == nullptr)
    {
        count++;
        root = new Node;
    }

    int sum_left = 0, sum_right = 0;
    vector<Node *> part_left, part_right;

    for (int i = 0; i < nodes.size(); ++i)
    {
        if (sum_left < sum / 2)
        {
            count++;
            part_left.push_back(nodes[i]);
            count++;
            sum_left += nodes[i]->frequency;
        }
        else
        {
            count++;
            part_right.push_back(nodes[i]);
            count++;
            sum_right += nodes[i]->frequency;
        }
    }

    count++;
    Divide(root->left, part_left, sum_left);
    count++;
    Divide(root->right, part_right, sum_right);
}

/**
 * Builds Shannon-Fano tree based on frequency table
 * @param table - frequency table
 * @return Node*
 */
Node *BuildSFTree(map<char, unsigned> frequency_table)
{
    vector<Node *> nodes;
    int sum = 0;

    for (auto i : frequency_table)
    {
        count++;
        Node *temp_node = new Node;
        count++;
        temp_node->value = i.first;
        count++;
        temp_node->frequency = i.second;
        count++;
        sum += temp_node->frequency;
        count++;
        nodes.push_back(temp_node);
    }

    CountCompare c;
    count++;
    std::sort(nodes.begin(), nodes.end(), c);
    count++;
    Node *tree = new Node;
    count++;
    Divide(tree, nodes, sum);
    count++;
    return tree;
}

/**
 * Deallocates memory for tree
 * @param root - root of a tree
 */
void DeleteTree(Node *root)
{
    if (root != nullptr)
    {
        count++;
        DeleteTree(root->left);
        count++;
        DeleteTree(root->right);
        count++;
        delete root;
        count++;
        root = nullptr;
    }
}

/**
 * Generic compress function
 * @param input - path to the .txt file
 * @param output - path to the .haff or .shan file
 * @param BuildTree - pointer to build tree function
 * (BuildSFTree or BuildHuffmanTree)
 */
void Compress(string input, string output, Node *(*BuildTree)(map<char, unsigned> frequency_table))
{
    ifstream fin(input);
    ofstream fout(output, std::ios::binary | std::ios::out);

    count++;
    num = 0;
    count++;
    map<char, unsigned> frequency_table = BuildFrequencyTable(fin, false);
    count++;
    Node *tree = BuildTree(frequency_table);

    map<char, vector<int> > codes;
    count++;
    temp_code.clear();
    count++;
    GetCharCodes(tree, codes);
    // Reset input stream
    count++;
    fin.clear();
    count++;
    fin.seekg(0);
    count++;
    CreateCompressedFile(fin, fout, frequency_table, codes);
    count++;
    DeleteTree(tree);

    // Print codes
//    for (auto i: codes)
//    {
//        std::cout << i.first << "---";
//        for (auto j: i.second)
//            std::cout << j;
//        std::cout << std::endl;
//    }
//    std::cout << std::endl;
}

/**
 * Generic decompress function
 * @param input - path to the .haff or .shan file
 * @param output - path to the .txt file
 * @param BuildTree - pointer to build tree function
 * (BuildSFTree or BuildHuffmanTree)
 */
void Decompress(string input, string output, Node *(*BuildTree)(map<char, unsigned> frequency_table))
{
    ifstream fin(input, std::ios::binary | std::ios::in);
    ofstream fout(output);

    count++;
    num = 0;
    count++;
    map<char, unsigned> frequency_table = BuildFrequencyTable(fin, true);
    count++;
    Node *tree = BuildTree(frequency_table);
    count++;
    TranslateCharCodes(fin, fout, tree);
    count++;
    DeleteTree(tree);
}

/**
 * Huffman compress function
 * @param input - path to the .txt file
 * @param output - path to the .haff file
 */
void HuffmanCompress(string input, string output)
{
    count = 0;
    count++;
    Compress(input, output, BuildHuffmanTree);
}

/**
 * Huffman decompress function
 * @param input - path to .haff file
 * @param output - path to .txt file
 */
void HuffmanDecompress(string input, string output)
{
    count = 0;
    count++;
    Decompress(input, output, BuildHuffmanTree);
}

/**
 * Shannon-Fano compress function
 * @param input - path to the .txt file
 * @param output - path to the .haff file
 */
void ShannonFanoCompress(string input, string output)
{
    count = 0;
    count++;
    Compress(input, output, BuildSFTree);
}

/**
 * Shannon-Fano decompress function
 * @param input - path to .haff file
 * @param output - path to .txt file
 */
void ShannonFanoDecompress(string input, string output)
{
    count = 0;
    count++;
    Decompress(input, output, BuildSFTree);
}

int main(int argc, char *argv[])
{
    if (argc < 5)
    {
        std::cout << "Usage: " << argv[0] << " [ALGO] [OPTION] [INPUT_FILE] [OUTPUT_FILE]" << std::endl;
        std::cout << "Algo:" << std::endl;
        std::cout << "  haff\tHuffman" << std::endl;
        std::cout << "  shan\tShannon-Fano" << std::endl;
        std::cout << "Options:" << std::endl;
        std::cout << "  -c\tCompress" << std::endl;
        std::cout << "  -d\tDecompress" << std::endl;
    }
    else
    {
        // Huffman
        if (!std::strcmp(argv[1], "haff") && !std::strcmp(argv[2], "-c"))
            HuffmanCompress(argv[3], argv[4]);
        if (!std::strcmp(argv[1], "haff") && !std::strcmp(argv[2], "-d"))
            HuffmanDecompress(argv[3], argv[4]);
        // Shannon-Fano
        if (!std::strcmp(argv[1], "shan") && !std::strcmp(argv[2], "-c"))
            ShannonFanoCompress(argv[3], argv[4]);
        if (!std::strcmp(argv[1], "shan") && !std::strcmp(argv[2], "-d"))
            ShannonFanoDecompress(argv[3], argv[4]);

        std::cout << "Total operations: " << count << std::endl;
    }

    return 0;
}