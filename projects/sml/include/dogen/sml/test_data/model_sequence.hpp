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
#include "dogen/sml/test_data/enumeration_sequence.hpp"

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
    typedef dogen::sml::model result_type;

public:
    result_type next_term(const unsigned int position) {
        dogen::sml::model result;
        std::unordered_map<qualified_name, package> packages;
        std::unordered_map<qualified_name, pod> pods;
        std::unordered_map<qualified_name, primitive> primitives;
        std::unordered_map<qualified_name, enumeration> enumerations;

        std::list<std::string> external_package_path;
        external_package_path.push_back("external_package_path_0");
        result.external_package_path(external_package_path);

        qualified_name_sequence qsec;
        package_sequence pkg_seq;
        pod_sequence pod_seq;
        primitive_sequence prim_seq;
        enumeration_sequence enum_seq;

        if (position == 0) {
            result.name("model_0");
            result.schema_name("model_schema_0");

            const auto pkg(pkg_seq());
            packages[pkg.name()] = pkg;

            const auto pod(pod_seq());
            pods[pod.name()] = pod;

            const auto prim(prim_seq());
            primitives[prim.name()] = prim;

            const auto en(enum_seq());
            enumerations[en.name()] = en;
        } else if (position == 1){
            result.name("model_1");
            result.schema_name("model_schema_1");

            pkg_seq();
            const auto pkg(pkg_seq());
            packages[pkg.name()] = pkg;

            pod_seq();
            const auto pod(pod_seq());
            pods[pod.name()] = pod;

            prim_seq();
            const auto prim(prim_seq());
            primitives[prim.name()] = prim;

            enum_seq();
            const auto en(enum_seq());
            enumerations[en.name()] = en;
        }
        else {
            result.name("model_2");
            result.schema_name("model_schema_2");
            pkg_seq();
            pkg_seq();
            const auto pkg(pkg_seq());
            packages[pkg.name()] = pkg;

            pod_seq();
            pod_seq();
            const auto pod(pod_seq());
            pods[pod.name()] = pod;

            prim_seq();
            prim_seq();
            const auto prim(prim_seq());
            primitives[prim.name()] = prim;

            enum_seq();
            enum_seq();
            const auto en(enum_seq());
            enumerations[en.name()] = en;

        }
        result.packages(packages);
        result.pods(pods);
        result.primitives(primitives);
        result.is_system(false);

        qualified_name m1;
        m1.model_name("m1");
        result.dependencies(std::unordered_set<qualified_name>{ m1 });
        return result;
    }

    unsigned int length() const { return(3); }
};

}

typedef utility::test_data::sequence<detail::model_generator> model_sequence;

} } }


#endif
