#ifndef PHI_IO_TESTTYPE_IO_HPP
#define PHI_IO_TESTTYPE_IO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include "Phi/types/TestType.hpp"

namespace Phi {

std::ostream&
operator<<(std::ostream& s,
     const Phi::TestType& v);

}

#endif
