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
#include <sstream>
#include <boost/algorithm/string.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/io/unordered_map_io.hpp"
#include "dogen.variability/types/helpers/feature_selector.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"
#include "dogen.generation.cpp/types/formattables/adapter.hpp"
#include "dogen.generation.cpp/types/fabric/common_odb_options.hpp"
#include "dogen.generation.cpp/types/fabric/object_odb_options.hpp"
#include "dogen.generation.cpp/types/element_visitor.hpp"
#include "dogen.generation.cpp/types/fabric/odb_options_factory.hpp"
#include "dogen.generation.cpp/types/formattables/header_guard_factory.hpp"
#include "dogen.generation.cpp/types/formatters/odb/traits.hpp"
#include "dogen.generation.cpp/types/formatters/types/traits.hpp"
#include "dogen.generation.cpp/types/formattables/odb_expander.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("generation.cpp.formattables.odb_expander"));

const std::string empty_column_attribute("column(\"\")");
const std::string id_pragma("id");
const std::string no_id_pragma("no_id");

const std::string null_pragma("null");
const std::string not_null_pragma("not_null");
const std::string value_pragma("value");

}

namespace dogen::generation::cpp::formattables {

class updator : public element_visitor {
public:
    updator(model& fm, const locator& l);

public:
    using element_visitor::visit;
    void visit(fabric::common_odb_options& coo);
    void visit(fabric::object_odb_options& ooo);

private:
    const model& model_;
    const locator locator_;
};

updator::updator(model& fm, const locator& l)
    : model_(fm), locator_(l) {}

void updator::visit(fabric::common_odb_options& coo) {
    coo.databases(model_.odb_databases());
    coo.sql_name_case(model_.odb_sql_name_case());
}

void updator::visit(fabric::object_odb_options& ooo) {
    const auto odb_arch(formatters::odb::traits::class_header_archetype());
    const auto odb_rp(locator_.make_inclusion_path_for_cpp_header(ooo.name(),
            odb_arch));

    std::ostringstream os;
    os << "'#include \"" << odb_rp.generic_string() << "\"'";
    ooo.epilogue(os.str());
    os.str("");

    const auto types_arch(formatters::types::traits::class_header_archetype());
    const auto types_rp(locator_.make_inclusion_path_for_cpp_header(ooo.name(),
            types_arch).parent_path());

    os << "'%(.*).hpp%" << types_rp.generic_string() << "/$1.hpp%'";
    ooo.include_regexes().push_back(os.str());

    os.str("");
    os << "'%(^[a-zA-Z0-9_]+)-odb(.*)%"
       << odb_rp.parent_path().generic_string() << "/$1-odb$2%'";
    ooo.include_regexes().push_back(os.str());

    os.str("");
    os << "'%" << types_rp.generic_string() << "/(.*)-odb(.*)%"
       << odb_rp.parent_path().generic_string() << "/$1-odb$2%'";
    ooo.include_regexes().push_back(os.str());
    ooo.header_guard_prefix(header_guard_factory::make(odb_rp.parent_path()));
}

void odb_expander::expand(const locator& l, model& fm) const {

    BOOST_LOG_SEV(lg, debug) << "Started expanding odb properties.";

    for (auto& pair : fm.formattables()) {
        const auto id(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Procesing element: " << id;

        auto& formattable(pair.second);
        /*
         * We only need to generate the aspect properties for
         * elements of the target model. However, we can't perform
         * this after reduction because the aspect propertiess must
         * be build prior to reduction or else we will not get aspects
         * for referenced models.
         */
        auto segment(formattable.master_segment());
        if (segment->origin_type() != assets::meta_model::origin_types::target)
            continue;

        for (const auto& ptr : formattable.all_segments()) {
            auto& e(*ptr);
            updator g(fm, l);
            e.accept(g);
        }
    }

    BOOST_LOG_SEV(lg, debug) << "Finished expanding odb properties. ";
}

}
