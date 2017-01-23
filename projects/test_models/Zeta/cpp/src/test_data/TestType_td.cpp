#include "Zeta/test_data/String_td.hpp"
#include "Phi/test_data/TestType_td.hpp"

namespace {

Zeta::String
create_Zeta_String(const unsigned int position) {
    return Zeta::String_generator::create(position);
}

}

namespace Phi {

TestType_generator::TestType_generator() : position_(0) { }

void TestType_generator::
populate(const unsigned int position, result_type& v) {
    v.Version(create_Zeta_String(position + 0));
    v.AField(create_Zeta_String(position + 1));
}

TestType_generator::result_type
TestType_generator::create(const unsigned int position) {
    TestType r;
    TestType_generator::populate(position, r);
    return r;
}

TestType_generator::result_type*
TestType_generator::create_ptr(const unsigned int position) {
    TestType* p = new TestType();
    TestType_generator::populate(position, *p);
    return p;
}

TestType_generator::result_type
TestType_generator::operator()() {
    return create(position_++);
}

}
