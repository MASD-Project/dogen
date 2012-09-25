/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_SML_DOMAIN_PRIMITIVE_HPP
#define DOGEN_SML_DOMAIN_PRIMITIVE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/sml/domain/qualified_name.hpp"

namespace dogen {
namespace sml {

class primitive_serializer;

class primitive {
public:
    primitive() = default;
    primitive(const primitive&) = default;
    ~primitive() = default;
    primitive(primitive&&) = default;
    primitive& operator=(const primitive&) = default;

private:
    friend class primitive_serializer;

public:
    /**
     * @brief Qualified name for the type.
     */
    /**@{*/
    qualified_name name() const { return name_; }
    void name(qualified_name value) { name_ = value; }
    /**@}*/

public:
    void to_stream(std::ostream& stream) const;

public:
    bool operator==(const primitive& rhs) const;

    bool operator!=(const primitive& rhs) const {
        return(!this->operator==(rhs));
    }

private:
    qualified_name name_;
};

} }

#endif
