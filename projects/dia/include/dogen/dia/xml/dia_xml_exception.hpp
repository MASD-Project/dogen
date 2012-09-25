/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_DIA_XML_EXCEPTION_HPP
#define DOGEN_DIA_XML_EXCEPTION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/utility/exception/utility_exception.hpp"

namespace dogen {
namespace dia {
namespace xml {

/**
 * @brief Exception thrown when there is a failure in serialisation or
 * deserialisation of dia domain types.
 */
class exception : public utility::exception::exception {
public:
    exception(std::string message) : utility::exception::exception(message) { }
    exception() { }

    virtual ~exception() throw() {}
};

} } }

#endif
