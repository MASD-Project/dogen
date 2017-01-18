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
#include <boost/throw_exception.hpp>
#include <boost/algorithm/string.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/unordered_set_io.hpp"
#include "dogen/annotations/types/entry_selector.hpp"
#include "dogen/annotations/types/type_repository_selector.hpp"
#include "dogen/yarn/types/traits.hpp"
#include "dogen/yarn/types/name_tree_parser.hpp"
#include "dogen/yarn/types/name_builder.hpp"
#include "dogen/yarn/types/expansion_error.hpp"
#include "dogen/yarn/types/parsing_expander.hpp"

typedef boost::error_info<struct owner, std::string>
errmsg_parsing_owner;

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("yarn.parsing_expander"));

const std::string empty_type("Attribute type is empty: ");
const std::string parent_name_conflict(
    "Parent name is defined in both meta-data and structure of model: ");

}

namespace dogen {
namespace yarn {

parsing_expander::type_group parsing_expander::make_type_group(
    const annotations::type_repository& atrp) const {
    type_group r;
    const annotations::type_repository_selector s(atrp);
    r.parent = s.select_type_by_name(traits::generalization::parent());
    return r;
}

std::string parsing_expander::
make_parent(const type_group& tg, const annotations::annotation& o) const {
    const annotations::entry_selector s(o);
    if (s.has_entry(tg.parent))
        return s.get_text_content(tg.parent);

    return std::string();
}

std::unordered_set<std::string>
parsing_expander::obtain_top_level_modules(const intermediate_model& m) const {
    std::unordered_set<std::string> r;
    BOOST_LOG_SEV(lg, debug) << "Obtaining top-level modules for: "
                             << m.name().id();

    for (const auto& pair : m.modules()) {
        const auto& module(pair.second);

        if (!module.contained_by()) {
            BOOST_LOG_SEV(lg, debug) << "Module is not a top-level module: "
                                     << pair.first;
            continue;
        }

        const auto& cm(*module.contained_by());
        if (cm != m.name()) {
            BOOST_LOG_SEV(lg, debug) << "Module is not a top-level module: "
                                     << pair.first
                                     << " containing module: "
                                     << cm.id()
                                     << " model name: " << m.name().id();
        }
        r.insert(module.name().simple());
    }

    BOOST_LOG_SEV(lg, debug) << "Top-level model names for "
                             << m.name().id() << " : "
                             << r;
    return r;
}

void parsing_expander::
parse_attributes(const location& model_location,
    const std::unordered_set<std::string>& top_level_modules,
    const languages language, std::list<attribute>& attrs) const {

    const name_tree_parser ntp(top_level_modules, model_location, language);
    for (auto& attr : attrs) {
        const auto ut(boost::algorithm::trim_copy(attr.unparsed_type()));

        /*
         * Attribute must always supply the unparsed type.
         */
        if (ut.empty()) {
            const auto sn(attr.name().simple());
            BOOST_LOG_SEV(lg, error) << empty_type << sn;
            BOOST_THROW_EXCEPTION(expansion_error(empty_type + sn));
        }

        auto nt(ntp.parse(ut));
        attr.parsed_type(nt);
    }
}

void parsing_expander::
parse_parent(const type_group& tg, const location& model_location,
    const std::unordered_set<std::string>& top_level_modules, object& o) const {

    /*
     * Obtain the parent name from the meta-data. If there is no
     * parent name there is nothing to do.
     */
    const auto parent(make_parent(tg, o.annotation()));
    if (parent.empty())
        return;

    /*
     * If we've already have a parent name, this means there are now
     * two conflicting sources of parenting information so bomb out.
     */
    if (!o.parents().empty()) {
        const auto& id(o.name().id());
        BOOST_LOG_SEV(lg, error) << parent_name_conflict << id;
        BOOST_THROW_EXCEPTION(expansion_error(parent_name_conflict + id));
    }

    /*
     * Convert the string obtained via meta-data into a yarn name and
     * set it as our parent name.
     */
    const auto& tpm(top_level_modules);
    const auto pn(name_builder::build(model_location, tpm, parent));
    o.parents().push_back(pn);
}

void parsing_expander::
expand(const annotations::type_repository& atrp, intermediate_model& m) const {
    const auto tg(make_type_group(atrp));
    const auto tlmn(obtain_top_level_modules(m));
    const auto ml(m.name().location());
    const auto l(m.input_language());

    for (auto& pair : m.objects()) {
        auto& o(pair.second);
        const auto id(o.name().id());

        try {
            parse_attributes(ml, tlmn, l, o.local_attributes());
            parse_parent(tg, ml, tlmn, o);
        } catch (boost::exception& e) {
            e << errmsg_parsing_owner(id);
            throw;
        }
    }

    for (auto& pair : m.concepts()) {
        auto& c(pair.second);
        const auto id(c.name().id());

        try {
            parse_attributes(ml, tlmn, l, c.local_attributes());
        } catch (boost::exception& e) {
            e << errmsg_parsing_owner(id);
            throw;
        }
    }
}

} }
