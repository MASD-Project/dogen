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
#include <boost/algorithm/string.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/filesystem/file.hpp"
#include "dogen/formatters/types/utility_formatter.hpp"
#include "dogen/yarn/types/meta_model/primitive.hpp"
#include "dogen/yarn/types/meta_model/exception.hpp"
#include "dogen/yarn/types/meta_model/enumeration.hpp"
#include "dogen/yarn/types/meta_model/attribute.hpp"
#include "dogen/yarn/types/meta_model/module.hpp"
#include "dogen/yarn/types/meta_model/element.hpp"
#include "dogen/yarn/types/meta_model/object.hpp"
#include "dogen/yarn/types/meta_model/object_template.hpp"
#include "dogen/yarn.json/types/dehydrator.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.json.dehydrator"));

const std::string scope("::");
const std::string comma_space(", ");
const std::string invalid_enumerator("invalid");

}

using boost::algorithm::join;

namespace dogen {
namespace yarn {
namespace json {

std::string dehydrator::tidy_up_string(std::string s) {
    boost::replace_all(s, "\r", "\\r");
    boost::replace_all(s, "\n", "\\n");
    boost::replace_all(s, "\"", "\\\"");
    return s;
}

void dehydrator::insert_documentation(std::ostream& s,  const std::string& d) {
    formatters::utility_formatter uf(s);
    uf.insert_quoted("documentation");
    s << " : ";
    uf.insert_quoted(tidy_up_string(d));
}

void dehydrator::insert_tagged_values(std::ostream& s,
    const std::list<std::pair<std::string, std::string>>& tv) {

    formatters::utility_formatter uf(s);
    uf.insert_quoted("tagged_values");
    s << " : { ";

    bool is_first(true);
    for (const auto& pair : tv) {
        if (!is_first)
            s << ", ";

        uf.insert_quoted(pair.first);
        s << " : ";
        uf.insert_quoted_escaped(pair.second);
        is_first = false;
    }
    s << " }";
}

void dehydrator::insert_stereotypes(std::ostream& s,
    const std::list<std::string>& st) {

    formatters::utility_formatter uf(s);
    uf.insert_quoted("stereotypes");
    s << " : [";

    bool is_first(true);
    for (const auto& stereotype : st) {
        if (!is_first)
            s << ", ";
        uf.insert_quoted(stereotype);
        is_first = false;
    }
    s << " ]";
}

void dehydrator::insert_parents(std::ostream& s,
    const std::list<std::string>& st) {

    formatters::utility_formatter uf(s);
    uf.insert_quoted("parents");
    s << " : [";

    bool is_first(true);
    for (const auto& stereotype : st) {
        if (!is_first)
            s << ", ";
        uf.insert_quoted(stereotype);
        is_first = false;
    }
    s << " ]";
}

void dehydrator::insert_attribute(std::ostream& s,
    const meta_model::exoattribute& ea) {

    s << "{ ";

    formatters::utility_formatter uf(s);
    uf.insert_quoted("name");
    s << " : ";
    uf.insert_quoted_escaped(ea.name());
    s << comma_space;
    uf.insert_quoted("type");
    s << " : ";
    uf.insert_quoted_escaped(ea.type());

    if (!ea.documentation().empty()) {
        s << comma_space;
        insert_documentation(s, ea.documentation());
    }

    if (!ea.stereotypes().empty()) {
        s << comma_space;
        insert_stereotypes(s, ea.stereotypes());
    }

    if (!ea.tagged_values().empty()) {
        s << comma_space;
        insert_tagged_values(s, ea.tagged_values());
    }

    s << " }";
}

void dehydrator::insert_element(std::ostream& s,
    const meta_model::exoelement& ee) {

    s << "{ ";

    formatters::utility_formatter uf(s);
    uf.insert_quoted("name");
    s << " : ";
    uf.insert_quoted_escaped(ee.name());

    if (!ee.parents().empty()) {
        s << comma_space;
        insert_parents(s, ee.parents());
    }

    if (!ee.documentation().empty()) {
        s << comma_space;
        insert_documentation(s, ee.documentation());
    }

    if (!ee.stereotypes().empty()) {
        s << comma_space;
        insert_stereotypes(s, ee.stereotypes());
    }

    if (!ee.tagged_values().empty()) {
        s << comma_space;
        insert_tagged_values(s, ee.tagged_values());
    }

    if (!ee.fallback_element_type().empty()) {
        s << comma_space;
        uf.insert_quoted("fallback_element_type");
        s << " : ";
        uf.insert_quoted_escaped(ee.fallback_element_type());
    }

    if (!ee.attributes().empty()) {
        s << comma_space;
        uf.insert_quoted("attributes");
        s << " : [ ";
        bool is_first(true);
        for (const auto& a : ee.attributes()) {
            if (!is_first)
                s << comma_space;
            insert_attribute(s, a);
            is_first = false;
        }
        s << " ] ";
    }

    s << " }";
}

std::string dehydrator::dehydrate(const meta_model::exomodel& em) {
    std::ostringstream s;

    s << "{ ";
    if (!em.documentation().empty())
        insert_documentation(s, em.documentation());

    if (!em.stereotypes().empty()) {
        if (!em.documentation().empty())
            s << ", ";
        insert_stereotypes(s, em.stereotypes());
    }

    if (!em.tagged_values().empty()) {
        if (!em.documentation().empty() || !em.stereotypes().empty())
            s << comma_space;
        insert_tagged_values(s, em.tagged_values());
    }

    if (!em.documentation().empty() || !em.stereotypes().empty() ||
        !em.tagged_values().empty()) {
        s << comma_space;
    }

    formatters::utility_formatter uf(s);
    uf.insert_quoted("elements");
    s << " : [ ";
    bool is_first(true);
    for (const auto& ee : em.elements()) {
        if (!is_first)
            s << comma_space;
        insert_element(s, ee);
        is_first = false;
    }
    s << " ]";
    s << " }";

    return s.str();
}

void dehydrator::dehydrate(const meta_model::exomodel& em,
    const boost::filesystem::path& p) {
    const auto s(dehydrate(em));
    utility::filesystem::write_file_content(p, s);
}

} } }
