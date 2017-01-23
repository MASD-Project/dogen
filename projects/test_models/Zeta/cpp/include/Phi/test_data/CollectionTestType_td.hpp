#ifndef PHI_TEST_DATA_COLLECTIONTESTTYPE_TD_HPP
#define PHI_TEST_DATA_COLLECTIONTESTTYPE_TD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "Phi/types/CollectionTestType.hpp"

namespace Phi {

class CollectionTestType_generator {
public:
    CollectionTestType_generator();

public:
    typedef Phi::CollectionTestType result_type;

public:
    static void populate(const unsigned int position, result_type& v);
    static result_type create(const unsigned int position);
    result_type operator()();

private:
    unsigned int position_;
public:
    static result_type* create_ptr(const unsigned int position);
};

}

#endif
