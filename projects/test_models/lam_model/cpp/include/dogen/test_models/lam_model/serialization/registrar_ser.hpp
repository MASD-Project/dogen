#ifndef DOGEN_TEST_MODELS_LAM_MODEL_SERIALIZATION_REGISTRAR_SER_HPP
#define DOGEN_TEST_MODELS_LAM_MODEL_SERIALIZATION_REGISTRAR_SER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

namespace dogen {
namespace test_models {
namespace lam_model {

template<typename Archive>
void register_types(Archive& ar);

} } }

#endif
