#ifndef DOGEN_TEST_MODELS_LAM_MODEL_IO_BUILTINS_IO_HPP
#define DOGEN_TEST_MODELS_LAM_MODEL_IO_BUILTINS_IO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include "dogen/test_models/lam_model/types/builtins.hpp"

namespace dogen {
namespace test_models {
namespace lam_model {

std::ostream&
operator<<(std::ostream& s,
     const dogen::test_models::lam_model::builtins& v);

} } }

#endif
