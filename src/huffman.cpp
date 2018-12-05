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

    write_freq(out, f);
    tree ht = tree::from_frequency_table(f);
    ht.serialize(in,out);
}

void puff(bistream& in, ostream& out) {
    tree ht = tree::deserialize(in);

    size_t counter = 0;
    in.read_bits(counter, sizeof(size_t) * 8);

    while(counter) {
        out << ht.decode_symbol(in);
        counter--;
    }


}

void write_freq(ipd::bostream &bos, frequency_table f) {


    size_t total_frequency = 0;
    for(size_t i = 0; i < f.size(); i++){
        bos.write_bits(f[i],sizeof(size_t) * 8);
        total_frequency += f[i];
    }

    bos.write_bits(total_frequency, sizeof(size_t)*8);
}

tree tree::from_frequency_table(frequency_table & f){

    std::priority_queue<link_t ,std::vector<link_t >, cmp> pq;

    for(size_t i = 0; i <f.size();i++){
        if(f[i]!=0){
            link_t n = std::make_shared<node_>(node_((char) i,f[i]));
            pq.push(n);
        }
    }

    while(pq.size() > 1) {
        link_t x = pq.top();
        pq.pop();
        link_t y = pq.top();
        pq.pop();

        link_t new_root = std::make_shared<node_>(node_('\0', x->count + y->count));
        new_root->left = x;
        new_root->right = y;
        pq.push(new_root);
    }

    if(!pq.size()){
        throw std::logic_error("File is empty");
    }

    link_t final_root = pq.top();
    return tree(final_root);

}

void tree::serialize(istream & in, ipd::bostream & out) const {

    if(!in){
        in.clear();
        in.seekg(0,ios_base::beg);
    }

    std::map<char,std::vector<bool>> code_table;
    code_table = traverse_tree(code_table);

    ipd::bistream_adaptor bis(in);
    char c;


    while(bis.read_bits(c,8)){
        std::vector<bool> x = code_table.at(c);

        for(size_t i = 0; i < x.size(); ++i) {
            out.write(x[i]);
        }
    }
}


std::map<char, std::vector<bool>> tree::traverse_tree (std::map<char, std::vector<bool>> m) const {
   std::vector<bool> v;
   traverse_inside(root_, m, v);

   /*
   auto iter = m.begin();
   for(iter; iter != m.end(); ++iter) {
       std::cout << iter->first << ":";
       std::vector<bool> q = iter->second;
       for(int i = 0; i < q.size(); ++i) {
           std::cout<< q.at(i);
       }
   }
   */
   return m;
}

void tree::traverse_inside(tree::link_t const node, std::map<char, std::vector<bool>>& m, std::vector<bool> v) {


    if(node->left != nullptr) {
        v.push_back(false);
        traverse_inside(node->left, m, v);
        v.pop_back();
    }
    if(node->right != nullptr) {
        v.push_back(true);
        traverse_inside(node->right, m, v);
        v.pop_back();
    }

    if(node->left == nullptr and node->right == nullptr){
        m.insert({node->c, v});
    }

}

tree::tree(tree::link_t root) {
    root_ = root;
}

tree tree::deserialize(ipd::bistream & in) {
    frequency_table f;
    for (int i = 0; i < 256; ++i) {
        size_t count;
        in.read_bits(count, sizeof(size_t) * 8);
        f[i] = count;
    }

    return tree::from_frequency_table(f);
}

char tree::decode_symbol(ipd::bistream & in) const {
    bool value;
    link_t travel = root_;
    int i_enter1 = 0;
    int i_enter2 = 0;


    while (travel->left != nullptr and travel->right != nullptr) {
        in.read_bits(value, 1);
        if(value == true){
            travel = travel->right;
        }
        else if (value == false){
            travel = travel->left;
        }
    }

    return travel->c;

}


