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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/filesystem/file.hpp"
#include "dogen.utility/types/formatters/utility_formatter.hpp"
#include "dogen.injection.org_mode/types/dehydrator.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("injection.org_mode.dehydrator"));

const std::string scope("::");
const std::string comma_space(", ");
const std::string invalid_enumerator("invalid");

}

namespace dogen::injection::org_mode {

void dehydrator::insert_documentation(std::ostream& s,  const std::string& d) {
    utility::formatters::utility_formatter uf(s);
    uf.insert_quoted("documentation");
    s << " : ";
    uf.insert_quoted(d);
}

void dehydrator::insert_tagged_values(std::ostream& s,
    const std::list<std::pair<std::string, std::string>>& tv) {

    s << ":dogen:" << std::endl;
    for (const auto& pair : tv)
        s << ":" << pair.first << ": " << pair.second << std::endl;
    s << ":end:" << std::endl << std::endl;
}

void dehydrator::insert_stereotypes(std::ostream& s,
    const std::list<std::string>& st) {

    s << "stereotypes: ";

    bool is_first(true);
    for (const auto& stereotype : st) {
        if (!is_first)
            s << ", ";
        s << stereotype;
        is_first = false;
    }
    s << std::endl;
}

void dehydrator::insert_parents(std::ostream& s,
    const std::list<std::string>& st) {

    utility::formatters::utility_formatter uf(s);
    s << "parents: ";

    bool is_first(true);
    for (const auto& stereotype : st) {
        if (!is_first)
            s << ", ";
        s << stereotype;
        is_first = false;
    }
    s << std::endl;
}

void dehydrator::insert_attribute(std::ostream& s,
    const injection::entities::attribute& a) {

    s << "** " << a.name() << std::endl;

    utility::formatters::utility_formatter uf(s);
    uf.insert_quoted("type");
    s << " : ";
    uf.insert_quoted_escaped(a.type());

    if (!a.value().empty()) {
        s << comma_space;
        uf.insert_quoted("value");
        s << " : ";
        uf.insert_quoted_escaped(a.value());
    }

    if (!a.documentation().empty()) {
        s << comma_space;
        insert_documentation(s, a.documentation());
    }

    if (!a.stereotypes().empty()) {
        s << comma_space;
        insert_stereotypes(s, a.stereotypes());
    }

    if (!a.tagged_values().empty()) {
        s << comma_space;
        insert_tagged_values(s, a.tagged_values());
    }

    s << " }" << std::endl;
}

void dehydrator::insert_element(std::ostream& s,
    const injection::entities::element& e) {

    s << "* " << e.name() << std::endl;
    utility::formatters::utility_formatter uf(s);

    if (!e.parents().empty()) {
        s << comma_space;
        insert_parents(s, e.parents());
    }

    if (!e.documentation().empty()) {
        s << e.documentation() << std::endl;
    }

    if (!e.stereotypes().empty()) {
        s << comma_space;
        insert_stereotypes(s, e.stereotypes());
    }

    if (!e.tagged_values().empty()) {
        s << comma_space;
        insert_tagged_values(s, e.tagged_values());
    }

    if (!e.fallback_element_type().empty()) {
        s << comma_space;
        uf.insert_quoted("fallback_element_type");
        s << " : ";
        uf.insert_quoted_escaped(e.fallback_element_type());
    }

    for (const auto& a : e.attributes())
        insert_attribute(s, a);
}

std::string dehydrator::dehydrate(const injection::entities::model& m) {
    std::ostringstream s;

    s << "#+title: " << m.name() << std::endl
      << "#+options: ^:nil" << std::endl;

    if (!m.tagged_values().empty())
        insert_tagged_values(s, m.tagged_values());

    s << m.documentation() << std::endl;

    if (!m.stereotypes().empty()) {
        if (!m.documentation().empty())
            s << ", ";
        insert_stereotypes(s, m.stereotypes());
    }

    for (const auto& e : m.elements())
        insert_element(s, e);

    return s.str();
}

void dehydrator::dehydrate(const injection::entities::model& m,
    const boost::filesystem::path& p) {
    const auto s(dehydrate(m));
    utility::filesystem::write_file_content(p, s);
}

}
