#include "UnitTest++/UnitTest++.h"
#include "bit_io.h"

#include <memory>

using namespace ipd;

using bistream_ptr = std::unique_ptr<bistream>;
using bostringstream_ptr = std::unique_ptr<bostringstream>;

using bytes_t = std::vector<uint8_t>;

static bistream_ptr make_bistringstream(std::vector<uint8_t> bytes) {
    return bistream_ptr(new bistringstream(bytes));
}

TEST(BISTREAM1) {
    auto b = make_bistringstream({0});
    bool bit;

    b->read(bit);
    CHECK_EQUAL(false, bit);
}

TEST(BISTREAM2) {
    auto b = make_bistringstream({255});
    bool bit;

    b->read(bit);
    CHECK_EQUAL(true, bit);
}

TEST(BISTREAM3) {
    auto b = make_bistringstream({128});
    bool bit;

    b->read(bit);
    CHECK_EQUAL(true, bit);
}

TEST(BISTREAM4) {
    auto b = make_bistringstream({1 << 6 | 1 << 5});
    bool bit;

    b->read(bit);
    CHECK_EQUAL(false, bit);
    b->read(bit);
    CHECK_EQUAL(true, bit);
    b->read(bit);
    CHECK_EQUAL(true, bit);
}


TEST(BISTREAM5) {
    auto b = make_bistringstream({255, 1 << 6 | 1 << 5});
    bool bit;

    for (int i = 0; i < 8; i++) {
        b->read(bit);
    }

    b->read(bit);
    CHECK_EQUAL(false, bit);
    b->read(bit);
    CHECK_EQUAL(true, bit);
    b->read(bit);
    CHECK_EQUAL(true, bit);
}


TEST(BISTREAM6) {
    auto b = make_bistringstream({255, 255});
    bool bit;

    for (int i = 0; i < 16; i++) {
        b->read(bit);
        CHECK_EQUAL(true, bit);
    }
    CHECK_EQUAL(b->eof(), true);
}


TEST(BOSTREAM1) {
    bostringstream_ptr b(new bostringstream);
    bostream& br = *b;
    CHECK_EQUAL(0, b->bits_written());
    br.write(false);
    CHECK_EQUAL(1, b->bits_written());
    CHECK_EQUAL(0, b->data()[0]);
}

TEST(BOSTREAM2) {
    bostringstream_ptr b(new bostringstream);
    bostream& br = *b;
    br.write(true);
    CHECK_EQUAL(128, b->data()[0]);
}

TEST(BOSTREAM3) {
    bostringstream_ptr b(new bostringstream);
    bostream& br = *b;
    br.write_bits('a', 8);
    CHECK_EQUAL(8, b->bits_written());
    CHECK_EQUAL('a', b->data()[0]);
}
