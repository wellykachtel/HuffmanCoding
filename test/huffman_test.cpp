#include <UnitTest++/UnitTest++.h>

// Add your Huffman tests here!
#include "huffman.h"
#include <UnitTest++/UnitTest++.h>

#include <sstream>

using namespace std;
using namespace ipd;

string round_trip(string const& msg)
{
    istringstream is(msg);
    bostringstream boss;
    huff(is, boss);

    bistringstream biss(boss.data());
    ostringstream os;
    puff(biss, os);

    return os.str();
}

TEST(Round_trip_empty_string) {
    CHECK_THROW(round_trip(""), std::logic_error);
}

TEST(Round_trip_A) {
    CHECK_EQUAL(round_trip("A"), "A");
}

TEST(Round_trip_hello) {
    CHECK_EQUAL(round_trip("hello"), "hello");
}

TEST(Round_trip_Hello_world) {
    CHECK_EQUAL(round_trip("Hello, world!"), "Hello, world!");
}
