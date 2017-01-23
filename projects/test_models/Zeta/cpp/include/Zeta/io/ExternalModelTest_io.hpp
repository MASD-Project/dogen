#ifndef ZETA_IO_EXTERNALMODELTEST_IO_HPP
#define ZETA_IO_EXTERNALMODELTEST_IO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include "Zeta/types/ExternalModelTest.hpp"

namespace Zeta {

std::ostream&
operator<<(std::ostream& s,
     const Zeta::ExternalModelTest& v);

}

#endif
