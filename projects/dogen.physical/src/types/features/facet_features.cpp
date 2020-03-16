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
#include "dogen.physical/types/features/facet_features.hpp"
#include "dogen.variability/types/helpers/value_factory.hpp"
#include "dogen.variability/types/helpers/feature_selector.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"

namespace dogen::physical::features {

namespace {

dogen::variability::entities::feature_template
make_directory() {
    using namespace dogen::variability::entities;
    feature_template r;
    r.name().simple("directory");
    r.description(R"(Directory in which to place this facet.

)");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    r.instantiation_domain_name("masd.facet");
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "" }));
    r.default_value_overrides().push_back(
        default_value_override("cpp.types",
            f.make(vt, std::list<std::string>{ "types" })));
    r.default_value_overrides().push_back(
        default_value_override("cpp.hash",
            f.make(vt, std::list<std::string>{ "hash" })));
    r.default_value_overrides().push_back(
        default_value_override("cpp.tests",
            f.make(vt, std::list<std::string>{ "generated_tests" })));
    r.default_value_overrides().push_back(
        default_value_override("cpp.io",
            f.make(vt, std::list<std::string>{ "io" })));
    r.default_value_overrides().push_back(
        default_value_override("cpp.lexical_cast",
            f.make(vt, std::list<std::string>{ "lexical_cast" })));
    r.default_value_overrides().push_back(
        default_value_override("cpp.templates",
            f.make(vt, std::list<std::string>{ "templates" })));
    r.default_value_overrides().push_back(
        default_value_override("cpp.odb",
            f.make(vt, std::list<std::string>{ "odb" })));
    r.default_value_overrides().push_back(
        default_value_override("cpp.test_data",
            f.make(vt, std::list<std::string>{ "test_data" })));
    r.default_value_overrides().push_back(
        default_value_override("cpp.serialization",
            f.make(vt, std::list<std::string>{ "serialization" })));
    r.default_value_overrides().push_back(
        default_value_override("csharp.types",
            f.make(vt, std::list<std::string>{ "Types" })));
    r.default_value_overrides().push_back(
        default_value_override("csharp.io",
            f.make(vt, std::list<std::string>{ "Dumpers" })));
    r.default_value_overrides().push_back(
        default_value_override("csharp.test_data",
            f.make(vt, std::list<std::string>{ "SequenceGenerators" })));
    return r;
}

dogen::variability::entities::feature_template
make_postfix() {
    using namespace dogen::variability::entities;
    feature_template r;
    r.name().simple("postfix");
    r.description(R"(Postfix to use for all files that belong to this facet.

)");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    r.instantiation_domain_name("masd.facet");
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "" }));
    r.default_value_overrides().push_back(
        default_value_override("cpp.tests",
            f.make(vt, std::list<std::string>{ "tests" })));
    r.default_value_overrides().push_back(
        default_value_override("cpp.hash",
            f.make(vt, std::list<std::string>{ "hash" })));
    r.default_value_overrides().push_back(
        default_value_override("cpp.lexical_cast",
            f.make(vt, std::list<std::string>{ "lc" })));
    r.default_value_overrides().push_back(
        default_value_override("cpp.io",
            f.make(vt, std::list<std::string>{ "io" })));
    r.default_value_overrides().push_back(
        default_value_override("cpp.odb",
            f.make(vt, std::list<std::string>{ "pragmas" })));
    r.default_value_overrides().push_back(
        default_value_override("cpp.test_data",
            f.make(vt, std::list<std::string>{ "td" })));
    r.default_value_overrides().push_back(
        default_value_override("cpp.serialization",
            f.make(vt, std::list<std::string>{ "ser" })));
    r.default_value_overrides().push_back(
        default_value_override("csharp.io",
            f.make(vt, std::list<std::string>{ "Dumper" })));
    r.default_value_overrides().push_back(
        default_value_override("csharp.test_data",
            f.make(vt, std::list<std::string>{ "SequenceGenerator" })));
    return r;
}

}

facet_features::feature_group
facet_features::make_feature_group(const dogen::variability::entities::feature_model& fm) {
    feature_group r;
    const dogen::variability::helpers::feature_selector s(fm);

    r.directory = s.get_by_name("directory");
    r.postfix = s.get_by_name("postfix");

    return r;
}

facet_features::static_configuration facet_features::make_static_configuration(
    const feature_group& fg,
    const dogen::variability::entities::configuration& cfg) {

    static_configuration r;
    const dogen::variability::helpers::configuration_selector s(cfg);
    r.directory = s.get_text_content_or_default(fg.directory);
    r.postfix = s.get_text_content_or_default(fg.postfix);
    return r;
}

std::list<dogen::variability::entities::feature_template>
facet_features::make_templates() {
    using namespace dogen::variability::entities;
    std::list<dogen::variability::entities::feature_template> r;
    r.push_back(make_directory());
    r.push_back(make_postfix());
    return r;
}

}
