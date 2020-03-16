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
#include "dogen.logical/types/meta_model/orm/odb_options.hpp"
#include "dogen.logical/types/meta_model/structural/object.hpp"
#include "dogen.logical/types/meta_model/structural/primitive.hpp"
#include "dogen.logical/types/meta_model/element_visitor.hpp"
#include "dogen.generation.cpp/types/formattables/adapter.hpp"
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

using dogen::logical::meta_model::element_visitor;

class updator : public element_visitor {
public:
    explicit updator(const locator& l);

private:
    logical::meta_model::orm::odb_options
    make_options(const logical::meta_model::name& n);

public:
    using element_visitor::visit;
    void visit(logical::meta_model::structural::object& o);
    void visit(logical::meta_model::structural::primitive& p);

private:
    const locator locator_;
};

updator::updator(const locator& l) : locator_(l) {}

logical::meta_model::orm::odb_options
updator::make_options(const logical::meta_model::name& n) {
    logical::meta_model::orm::odb_options r;
    const auto odb_arch(formatters::odb::traits::class_header_archetype());
    const auto odb_rp(locator_.make_inclusion_path_for_cpp_header(n, odb_arch));

    std::ostringstream os;
    os << "'#include \"" << odb_rp.generic_string() << "\"'";
    r.epilogue(os.str());
    os.str("");

    const auto types_arch(formatters::types::traits::class_header_archetype());
    const auto ip(locator_.make_inclusion_path_for_cpp_header(n, types_arch));
    const auto types_rp(ip.parent_path());

    os << "'%(.*).hpp%" << types_rp.generic_string() << "/$1.hpp%'";
    r.include_regexes().push_back(os.str());

    os.str("");
    os << "'%(^[a-zA-Z0-9_]+)-odb(.*)%"
       << odb_rp.parent_path().generic_string() << "/$1-odb$2%'";
    r.include_regexes().push_back(os.str());

    os.str("");
    os << "'%" << types_rp.generic_string() << "/(.*)-odb(.*)%"
       << odb_rp.parent_path().generic_string() << "/$1-odb$2%'";
    r.include_regexes().push_back(os.str());
    r.header_guard_prefix(header_guard_factory::make(odb_rp.parent_path()));
    return r;
}

void updator::visit(logical::meta_model::structural::object& o) {
    if (o.orm_properties())
        o.orm_properties()->odb_options(make_options(o.name()));
}

void updator::visit(logical::meta_model::structural::primitive& p) {
    if (p.orm_properties())
        p.orm_properties()->odb_options(make_options(p.name()));
}

void odb_expander::expand(const locator& l, model& m) const {

    BOOST_LOG_SEV(lg, debug) << "Started expanding odb properties.";

    for (auto& pair : m.formattables()) {
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
        auto& e(*formattable.element());
        if (e.origin_type() != logical::meta_model::origin_types::target)
            continue;

        updator g(l);
        e.accept(g);
    }

    BOOST_LOG_SEV(lg, debug) << "Finished expanding odb properties. ";
}

}
