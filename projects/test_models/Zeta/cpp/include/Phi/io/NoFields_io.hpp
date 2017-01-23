#ifndef PHI_IO_NOFIELDS_IO_HPP
#define PHI_IO_NOFIELDS_IO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include "Phi/types/NoFields.hpp"

namespace Phi {

std::ostream&
operator<<(std::ostream& s,
     const Phi::NoFields& v);

}

#endif
