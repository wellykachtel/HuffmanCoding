#include "common.h"
#include "huffman.h"

#define DEFAULT_INFILE  "test-files/hamlet-ascii.txt"
#define DEFAULT_OUTFILE "test-files/hamlet-ascii.txt.huff"

int main(int argc, const char* argv[])
{
    const char *infile, *outfile;
    get_file_names(argc, argv, infile, outfile,
                   DEFAULT_INFILE, DEFAULT_OUTFILE);

    std::ifstream in(infile);
    assert_good(in, argv);

    ipd::bofstream out(outfile);
    assert_good(out, argv);

    huff(in, out);
}
