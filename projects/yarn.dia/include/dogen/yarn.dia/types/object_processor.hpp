/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
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
#ifndef DOGEN_YARN_DIA_TYPES_OBJECT_PROCESSOR_HPP
#define DOGEN_YARN_DIA_TYPES_OBJECT_PROCESSOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include "dogen/dia/types/attribute_fwd.hpp"
#include "dogen/dia/types/object_fwd.hpp"
#include "dogen/dia/types/attribute_fwd.hpp"
#include "dogen/dia/types/composite_fwd.hpp"
#include "dogen/yarn.dia/types/dia_object_types.hpp"
#include "dogen/yarn.dia/types/processed_object_fwd.hpp"
#include "dogen/yarn.dia/types/comment_processor.hpp"

namespace dogen {
namespace yarn {
namespace dia {

/**
 * @brief Processes dia objects into an intermediate format.
 */
class object_processor {
public:
    object_processor(const object_processor&) = delete;
    object_processor(object_processor&&) = default;

public:
    object_processor();

private:
    /**
     * @brief Parses the dia attribute as a string, returning its value.
     */
    std::string parse_string_attribute(const dogen::dia::attribute& a) const;

    /**
     * @brief Makes a processed comment from the input attribute.
     *
     * @pre Attribute must be of type string.
     */
    processed_comment create_processed_comment(
      const dogen::dia::attribute& a) const;

    /**
     * @brief Given a string with a dia object type, returns the
     * appropriate enum.
     */
    dia_object_types parse_object_type(const std::string& ot) const;

public:
    /**
     * @brief Process the object.
     */
    processed_object process(const dogen::dia::object& o);

private:
    const comment_processor comment_processor_;
};

} } }

#endif
