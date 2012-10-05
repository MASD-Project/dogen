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
 * You should have received a copy of the GNU General PublicLicense
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#ifndef DOGEN_SML_TEST_DATA_QUALIFIED_NAME_SEQUENCE_HPP
#define DOGEN_SML_TEST_DATA_QUALIFIED_NAME_SEQUENCE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/utility/test_data/generator.hpp"
#include "dogen/utility/test_data/sequence.hpp"
#include "dogen/sml/domain/qualified_name.hpp"

namespace dogen {
namespace sml {
namespace test_data {

namespace detail {

/**
 * @brief Generates an open ended sequence of versions.
 *
 * @see sequence.
 */
class qualified_name_generator {
public:
    typedef dogen::sml::qualified_name value_type;

public:
    value_type next_term(const unsigned int position) {
        dogen::sml::qualified_name name;

        name.model_name("model_0");
        name.meta_type(dogen::sml::meta_types::pod);

        std::list<std::string> package_path;
        std::list<std::string> external_package_path;
        external_package_path.push_back("external_package_path_0");
        name.external_package_path(external_package_path);

        if (position == 0) {
            name.type_name("name_0");
            package_path.push_back("package_0");
        } else if (position == 1) {
            name.type_name("name_1");
            package_path.push_back("package_1");
        } else {
            name.type_name("name_2");
            package_path.push_back("package_2");
        }

        name.package_path(package_path);
        return name;
    }

    unsigned int length() const { return(3); }
};

}

typedef utility::test_data::sequence<
    detail::qualified_name_generator> qualified_name_sequence;

} } }


#endif
