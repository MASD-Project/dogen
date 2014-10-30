/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#ifndef DOGEN_CPP_TYPES_TRANSFORMER_HPP
#define DOGEN_CPP_TYPES_TRANSFORMER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <memory>
#include "dogen/sml/types/qname.hpp"
#include "dogen/sml/types/nested_qname.hpp"
#include "dogen/sml/types/model.hpp"
#include "dogen/sml/types/module.hpp"
#include "dogen/sml/types/concept.hpp"
#include "dogen/sml/types/object.hpp"
#include "dogen/sml/types/primitive.hpp"
#include "dogen/sml/types/enumeration.hpp"
#include "dogen/cpp/types/entity.hpp"
#include "dogen/cpp/types/enum_info.hpp"
#include "dogen/cpp/types/namespace_info.hpp"

namespace dogen {
namespace cpp {

class transformer {
public:
    explicit transformer(const sml::model& m);

private:
    /**
     * @brief Transforms an SML property to an enumerator info.
     */
    enumerator_info
    to_enumerator_info(const sml::enumerator& e) const;

    /**
     * @brief Transforms a SML value containing an enumeration into an
     * enumeration info.
     */
    std::shared_ptr<enum_info> to_enum_info(const sml::enumeration& e) const;

    /**
     * @brief Transforms a SML module into a namespace info.
     */
    std::shared_ptr<namespace_info>
    to_namespace_info(const sml::module& m) const;

public:
    /**
     * @brief Transform an SML enumeration into a C++ entity.
     */
    std::shared_ptr<entity> transform(const sml::enumeration& e) const;

    /**
     * @brief Transform an SML module into a C++ entity.
     */
    std::shared_ptr<entity> transform(const sml::module& m) const;

    /**
     * @brief Transform an SML concept into a C++ entity.
     */
    std::shared_ptr<entity> transform(const sml::concept& e) const;

    /**
     * @brief Transform an SML primitive into a C++ entity.
     */
    std::shared_ptr<entity> transform(const sml::primitive& e) const;

    /**
     * @brief Transform an SML object into a C++ entity.
     */
    std::shared_ptr<entity> transform(const sml::object& e) const;

private:
    const sml::model& model_;
};

} }

#endif
