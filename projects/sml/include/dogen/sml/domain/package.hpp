/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_SML_DOMAIN_PACKAGE_HPP
#define DOGEN_SML_DOMAIN_PACKAGE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <boost/shared_ptr.hpp>
#include "dogen/sml/domain/qualified_name.hpp"

namespace dogen {
namespace sml {

class package_serializer;

/**
 * @brief Represents a namespace.
 */
class package {
public:
    package() = default;
    package(const package&) = default;
    ~package() = default;
    package(package&&) = default;
    package& operator=(const package&) = default;

public:
    friend class package_serializer;

public:
    /**
     * @brief Initialises the structure.
     *
     * @param name Identifier for the package.
     */
    package(dogen::sml::qualified_name name) : name_(name) { }

public:
    /**
     * @brief Identifier for the package.
     */
    /**@{*/
    dogen::sml::qualified_name name() const { return name_; }
    void name(dogen::sml::qualified_name name) { name_ = name; }
    /**@}*/

public:
    void to_stream(std::ostream& stream) const;

public:
    bool operator==(const package& rhs) const;

    bool operator!=(const package& rhs) const {
        return(!this->operator==(rhs));
    }

private:
    dogen::sml::qualified_name name_;
};

} }

#endif
