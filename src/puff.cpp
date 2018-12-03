#include "common.h"
#include "bit_io.h"
#include "huffman.h"

#define DEFAULT_INFILE  "test-files/hamlet-ascii.txt.huff"
#define DEFAULT_OUTFILE "test-files/hamlet-ascii.txt.puff"

using namespace ipd;
using namespace std;

int main(int argc, const char *argv[])
{
    const char *infile, *outfile;

    get_file_names(argc, argv, infile, outfile,
                   DEFAULT_INFILE, DEFAULT_OUTFILE);

    bifstream in(infile);
    assert_good(in, argv);

    ofstream out(outfile);
    assert_good(out, argv);

    puff(in, out);
}
