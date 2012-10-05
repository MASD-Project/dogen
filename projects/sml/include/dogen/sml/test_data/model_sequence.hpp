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
#ifndef DOGEN_SML_TEST_DATA_MODEL_SEQUENCE_HPP
#define DOGEN_SML_TEST_DATA_MODEL_SEQUENCE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/utility/test_data/generator.hpp"
#include "dogen/utility/test_data/sequence.hpp"
#include "dogen/sml/domain/model.hpp"
#include "dogen/sml/test_data/qualified_name_sequence.hpp"
#include "dogen/sml/test_data/package_sequence.hpp"
#include "dogen/sml/test_data/pod_sequence.hpp"
#include "dogen/sml/test_data/primitive_sequence.hpp"

namespace dogen {
namespace sml {
namespace test_data {

namespace detail {

/**
 * @brief Generates an open ended sequence of versions.
 *
 * @see sequence.
 */
class model_generator {
public:
    typedef dogen::sml::model value_type;

public:
    value_type next_term(const unsigned int position) {
        dogen::sml::model result;
        std::unordered_map<qualified_name, package> packages;
        std::unordered_map<qualified_name, pod> pods;
        std::unordered_map<qualified_name, primitive> primitives;

        std::list<std::string> external_package_path;
        external_package_path.push_back("external_package_path_0");
        result.external_package_path(external_package_path);

        qualified_name_sequence qsec;
        package_sequence pkg_seq;
        pod_sequence pod_seq;
        primitive_sequence prim_seq;

        if (position == 0) {
            result.name("model_0");
            result.schema_name("model_schema_0");
            const dogen::sml::qualified_name qname(qsec());
            packages[qname] = pkg_seq();
            pods[qname] = pod_seq();
            primitives[qname] = prim_seq();
        } else if (position == 1){
            result.name("model_1");
            result.schema_name("model_schema_1");
            qsec();
            const dogen::sml::qualified_name qname(qsec());
            pkg_seq();
            packages[qname] = pkg_seq();
            pod_seq();
            pods[qname] = pod_seq();
            prim_seq();
            primitives[qname] = prim_seq();
        }
        else {
            result.name("model_2");
            result.schema_name("model_schema_2");
            const dogen::sml::qualified_name qname(qsec());
            pkg_seq();
            pkg_seq();
            packages[qname] = pkg_seq();
            pod_seq();
            pod_seq();
            pods[qname] = pod_seq();
            prim_seq();
            prim_seq();
            primitives[qname] = prim_seq();
        }
        result.packages(packages);
        result.pods(pods);
        result.primitives(primitives);
        return result;
    }

    unsigned int length() const { return(3); }
};

}

typedef utility::test_data::sequence<detail::model_generator> model_sequence;

} } }


#endif
