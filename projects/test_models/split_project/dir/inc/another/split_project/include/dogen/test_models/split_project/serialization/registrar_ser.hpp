#ifndef DOGEN_TEST_MODELS_SPLIT_PROJECT_SERIALIZATION_REGISTRAR_SER_HPP
#define DOGEN_TEST_MODELS_SPLIT_PROJECT_SERIALIZATION_REGISTRAR_SER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

namespace dogen {
namespace test_models {
namespace split_project {

template<typename Archive>
void register_types(Archive& ar);

} } }

#endif
