#pragma once

#include "bit_io.h"
#include<memory>
#include<iostream>
#include<array>
#include<vector>
#include<limits>
#include<queue>



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


// Encodes the ASCII input stream from `in` onto `out`.
void huff(std::istream& in, ipd::bostream& out);

// Decodes the 7-bit-packed input stream from `in` onto `out`.
void puff(ipd::bistream& in, std::ostream& out);



struct node {
    node(char c, size_t count) : c(c),count(count), left(nullptr), right(nullptr){ }

    char c;
    size_t count;
    std::shared_ptr<node> left;
    std::shared_ptr<node> right;
};

using link_t = std::shared_ptr<node>;


struct cmp{

    bool operator()(node a, node b){
        return a.count > b.count;
    }

};

class HuffTree{

public:
    explicit  HuffTree() : root(nullptr), size(0) { }

    explicit HuffTree(std::priority_queue<node,std::vector<node>, cmp> &pq);

    void print_bits(char);
    void print_to_file(ipd::bostream& out);

    size_t get_size(){
        return size;
    }

private:
    std::shared_ptr<node> root;
    size_t size;

};


