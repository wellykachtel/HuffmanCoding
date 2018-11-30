#include "common.h"
#include "bit_io.h"
#include "huffman.h"



#define DEFAULT_INFILE  "test-files/hamlet-ascii.txt"
#define DEFAULT_OUTFILE "test-files/hamlet-ascii.txt.huff"

int main(int argc, const char* argv[])
{
    const char *infile, *outfile;
    frequency_table f;

    get_file_names(argc, argv, infile, outfile,
                   DEFAULT_INFILE, DEFAULT_OUTFILE);

    std::ifstream in(infile);
    assert_good(in, argv);

    ipd::bofstream out(outfile);
    assert_good(out, argv);

    huff(in, out);

    //frequency_table f;

    /*char c = 'F';
    std::bitset<8> y(c);
    std::cout<<y;
     */

    /*char c;
    ipd::bistream_adaptor bis(in);

    while(bis.read_bits(c,8)){
        f[c]++;
    }*/

/*
    f['x']=1;
    f['f']=1;
    f['u']=1;
    f['v']=6;
    f['a']=5;
    f['z']=11
            ;
    std::priority_queue<node,std::vector<node>, cmp> pq;

    for(size_t i = 0; i <f.size();i++){
        if(f[i]!=0){
            pq.push({(char)i,f[i]});
        }
    }

    HuffTree h(pq);

    h.print_bits('x');
    h.print_bits('f');
    h.print_bits('u');
    h.print_bits('v');
    h.print_bits('a');
    h.print_bits('z');
*/
}
