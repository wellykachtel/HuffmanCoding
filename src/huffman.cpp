#include "huffman.h"

using namespace std;
using namespace ipd;

void huff(istream& in, bostream& out)
{
    frequency_table f;

    char c;
    ipd::bistream_adaptor bis(in);

    while(bis.read_bits(c,8)){
        f[c]++;
    }

    std::priority_queue<node,std::vector<node>, cmp> pq;

    for(size_t i = 0; i <f.size();i++){
        if(f[i]!=0){
            pq.push({(char)i,f[i]});
        }
    }

    HuffTree h(pq);

    h.print_to_file(out);
}

void puff(bistream& in, ostream& out)
{
    char c;

    while (in.read_bits(c, 7)) {
        out << c;
    }
}


HuffTree::HuffTree(std::priority_queue<node, std::vector<node>, cmp> &pq) {


    if(root == nullptr) {
        node x = pq.top();
        link_t first = std::make_shared<node>(x);
        pq.pop();

        node new_root('\0',x.count);
        new_root.left = first;
        new_root.right = nullptr;
        root = std::make_shared<node>(new_root);
        size = 1;
    }

    while(!pq.empty()) {
        node z = pq.top();
        link_t new_child = std::make_shared<node>(z);
        pq.pop();

        node new_root('\0', root->count + z.count);
        new_root.left = new_child;
        new_root.right = root;
        root = std::make_shared<node>(new_root);
        ++size;
    }
    cout<<"\nSize of tree - no of characters in tree"<<size;
    cout<<"\nFrequency total"<<root->count<<endl;


}

void HuffTree::print_bits(char input){

    link_t traverse = root;

    while(traverse->left->c != input){
        cout<<"1";
        traverse = traverse->right;
    }
    cout<<"0"<<endl;

}


void HuffTree::print_to_file(bostream& out) {
    link_t traverse = root;


    out.write_bits(size,32);

    while(traverse != nullptr) {
        std::cout << traverse->left->c;
        out.write_bits(traverse->left->c, 8);
        traverse = traverse->right;
    }
}