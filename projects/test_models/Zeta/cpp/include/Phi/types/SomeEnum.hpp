#ifndef PHI_TYPES_SOMEENUM_HPP
#define PHI_TYPES_SOMEENUM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

namespace Phi {

/**
 * @brief Represents an enum
 */
enum class SomeEnum : unsigned int {
    invalid = 0 ///< Represents an uninitialised enum
};

}

#endif
