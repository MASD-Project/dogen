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
#include <list>
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

void dehydrator::insert_tagged_values(std::ostream& s,
    const std::list<std::pair<std::string, std::string>>& tv) {
    if (tv.empty())
        return;

    for (const auto& pair : tv)
        s << ":" << pair.first << ": " << pair.second << std::endl;
}

void dehydrator::insert_stereotypes(std::ostream& s,
    const std::list<std::string>& st) {
    if (st.empty())
        return;

    s << ":masd.injection.stereotypes: ";

    bool is_first(true);
    for (const auto& stereotype : st) {
        if (!is_first)
            s << ", ";
        s << stereotype;
        is_first = false;
    }
    s << std::endl;
}

void dehydrator::
insert_parents(std::ostream& s, const std::list<std::string>& parents) {
    if (parents.empty())
        return;

    s << ":masd.injection.parent: ";

    bool is_first(true);
    for (const auto& p : parents) {
        if (!is_first)
            s << ", ";
        s << p;
        is_first = false;
    }
    s << std::endl;
}

void dehydrator::insert_attribute(std::ostream& s,
    const unsigned int level, const entities::attribute& a) {
    const std::string stars(level, '*');
    s << stars << " " << a.name() << std::endl;

    const auto& tv(a.tagged_values());
    if (!a.type().empty() || !a.value().empty() || !a.stereotypes().empty()
        || !tv.empty()) {
        s << ":PROPERTIES:" << std::endl;
        insert_tagged_values(s, tv);
        if (!a.type().empty())
            s << ":masd.injection.type: " << a.type() << std::endl;

        if (!a.value().empty())
            s << ":masd.injection.value: " << a.value() << std::endl;

        insert_stereotypes(s, a.stereotypes());
        s << ":END:" << std::endl;

        if (!a.documentation().empty())
            s << std::endl;
    }

    if (!a.documentation().empty()) {
        if (a.name() == "content") {
            s << "#+begin_src mustache" << std::endl
              << a.documentation() << std::endl
              << "#+end_src" << std::endl;
        } else if (a.name() == "stitch_template_content") {
            s << "#+begin_src stitch" << std::endl
              << a.documentation() << std::endl
              << "#+end_src" << std::endl;
        } else if (a.name() == "short_form" || a.name() == "long_form") {
            s << "#+begin_src fundamental" << std::endl
              << a.documentation() << std::endl
              << "#+end_src" << std::endl;
        } else
            s << a.documentation() << std::endl;
    }
}

void dehydrator::insert_element(std::ostream& s,
    const unsigned int level, const entities::element& e) {

    const std::string stars(level, '*');
    s << stars << " " << e.name() << std::endl;

    const auto& tv(e.tagged_values());
    if (!e.parents().empty() || !e.stereotypes().empty() || !tv.empty()) {
        s << ":PROPERTIES:" << std::endl;
        insert_tagged_values(s, tv);
        insert_parents(s, e.parents());
        insert_stereotypes(s, e.stereotypes());
        s << ":END:" << std::endl;

        if (!e.documentation().empty())
            s << std::endl;
    }

    if (!e.documentation().empty())
        s << e.documentation() << std::endl;

    for (const auto& a : e.attributes())
        insert_attribute(s, level + 1, a);
}

void dehydrator::walk_parent_to_child(std::ostream& s, const unsigned int level,
    const std::string& id, const std::unordered_map<std::string,
    std::list<entities::element>>& parent_to_child_map) {

    const auto i(parent_to_child_map.find(id));
    if (i != parent_to_child_map.end()) {
        for (const auto& e : i->second) {
            insert_element(s, level, e);
            const auto id(e.origin_element_id());
            walk_parent_to_child(s, level + 1, id, parent_to_child_map);
        }
    }
}

std::string dehydrator::dehydrate(const injection::entities::model& m) {
    std::ostringstream s;

    s << "#+title: " << m.name() << std::endl
      << "#+options: <:nil c:nil todo:nil ^:nil d:nil date:nil author:nil"
      << std::endl;

    const auto& tv(m.tagged_values());
    if (!m.stereotypes().empty() || !tv.empty()) {
        s << ":PROPERTIES:" << std::endl;
        insert_tagged_values(s, tv);
        insert_stereotypes(s, m.stereotypes());
        s << ":END:" << std::endl;

        if (!m.documentation().empty())
            s << std::endl;
    }

    if (!m.documentation().empty())
        s << m.documentation() << std::endl;

    std::unordered_map<std::string,
                       std::list<entities::element>> parent_to_child_map;
    for (const auto& e : m.elements()) {
        auto& n(parent_to_child_map[e.origin_containing_element_id()]);
        n.push_back(e);
    }

    std::string empty;
    walk_parent_to_child(s, 1, empty, parent_to_child_map);

    return s.str();
}

void dehydrator::dehydrate(const injection::entities::model& m,
    const boost::filesystem::path& p) {
    const auto s(dehydrate(m));
    utility::filesystem::write_file_content(p, s);
}

}
