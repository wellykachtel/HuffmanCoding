#pragma once

#include "bit_io.h"
#include<memory>
#include<iostream>
#include<array>
#include<vector>
#include<limits>
#include<queue>
#include<map>

class frequency_table{

public:
    frequency_table()
    {
        counts_.fill(0);
    }

    size_t operator[](char c) const
    {
        return counts_[c2i_(c)];
    }

    size_t&operator[](char c){
        return counts_[c2i_(c)];
    }

    size_t size(){
        return nsymbols;
    }
private:
    static size_t const nsymbols =
            size_t(std::numeric_limits<unsigned char>::max()) + 1;

    std::array<size_t, nsymbols> counts_{};

    static size_t c2i_(char c)
    {
        return (size_t)(unsigned char) c;
    }
};

class tree
{
public:
    // Builds a Huffman tree from a frequency table.
    static tree from_frequency_table(frequency_table &);

    // Reads a Huffman tree from a file.
    static tree deserialize(ipd::bistream&);

     //Encodes text using Huffmantree and writes to a file.
     void serialize(std::istream&, ipd::bostream&) const;

    std::map<char,std::vector<bool>> traverse_tree(std::map<char,std::vector<bool>>) const;

     // Decodes one symbol (char) from the given bit in stream.
     char decode_symbol(ipd::bistream&) const;

    // Writes a Huffman tree to an output stream in a format suitable for
    // debugging.
    void format(std::ostream&) const;

    // Compares two Huffman trees for equality. Ignores frequencies and just
    // compares structure and leaf symbols.
    // bool operator==(const tree&) const;

private:
    struct node_;
    using link_t = std::shared_ptr<node_>;

    std::shared_ptr<node_> root_;

    // private constructor:
    explicit tree(link_t root);
    int height(link_t) const;

    struct cmp;

    static void traverse_inside(link_t const, std::map<char,std::vector<bool>> &, std::vector<bool>);

};

struct tree::node_{
    node_(char c, size_t count) : c(c),count(count), left(nullptr), right(nullptr){ }

    char c;
    size_t count;
    std::shared_ptr<node_> left;
    std::shared_ptr<node_> right;
};

struct tree::cmp{

    bool operator()(link_t a, link_t b){
        return a->count > b->count;
    }

};

tree::tree(tree::link_t root) {
    root_ = root;
}


// Encodes the ASCII input stream from `in` onto `out`.
void huff(std::istream& in, ipd::bostream& out);


// Decodes the 7-bit-packed input stream from `in` onto `out`.
void puff(ipd::bistream& in, std::ostream& out);

void printvec(std::vector<bool> &v);


void write_freq(ipd::bostream & bos, frequency_table f){

    for(size_t i = 0; i < f.size(); i++){
        bos.write_bits(f[i],sizeof(size_t) * 8);
    }
}

