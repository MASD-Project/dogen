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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/formatters/utility_formatter.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.codec/io/entities/model_io.hpp"
#include "dogen.codec/io/entities/artefact_io.hpp"
#include "dogen.codec/types/transforms/model_to_org_artefact_transform.hpp"

namespace {

const std::string
transform_id("codec.transforms.model_to_org_artefact_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string scope("::");
const std::string comma_space(", ");
const std::string element_tag(":masd_element:");
const std::string attribute_tag(":masd_attribute:");

const std::string invalid_enumerator("invalid");

}

namespace dogen::codec::transforms {

std::string model_to_org_artefact_transform::
make_headline(const unsigned int level,
    const std::string& title, const std::string& tag) {
    const std::string stars(level, '*');

    std::ostringstream os;
    os << stars << " " << title;
    const auto tag_space_count(77 - tag.size() - title.size() - 1
        - stars.size());
    const std::string tag_spaces(tag_space_count > 0 ?
        tag_space_count : 1, ' ');
    os << tag_spaces << tag << std::endl;
    return os.str();
}

void model_to_org_artefact_transform::insert_tagged_values(std::ostream& s,
    const std::list<identification::entities::tagged_value>& tvs) {
    if (tvs.empty())
        return;

    for (const auto& tv : tvs)
        s << ":" << tv.tag() << ": " << tv.value() << std::endl;
}

void model_to_org_artefact_transform::insert_stereotypes(std::ostream& s,
    const std::list<identification::entities::stereotype>& sts) {
    if (sts.empty())
        return;

    s << ":masd.codec.stereotypes: ";

    bool is_first(true);
    for (const auto& st : sts) {
        if (!is_first)
            s << ", ";
        s << st.value();
        is_first = false;
    }
    s << std::endl;
}

void model_to_org_artefact_transform::
insert_parents(std::ostream& s, const std::list<std::string>& parents) {
    if (parents.empty())
        return;

    s << ":masd.codec.parent: ";

    bool is_first(true);
    for (const auto& p : parents) {
        if (!is_first)
            s << ", ";
        s << p;
        is_first = false;
    }
    s << std::endl;
}

void model_to_org_artefact_transform::insert_attribute(std::ostream& s,
    const unsigned int level, const entities::attribute& a) {
    s << make_headline(level, a.name().simple(), attribute_tag);

    const auto& tvs(a.tagged_values());
    if (!a.type().empty() || !a.value().empty() || !a.stereotypes().empty()
        || !tvs.empty()) {
        s << ":PROPERTIES:" << std::endl;
        insert_tagged_values(s, tvs);
        if (!a.type().empty())
            s << ":masd.codec.type: " << a.type() << std::endl;

        if (!a.value().empty())
            s << ":masd.codec.value: " << a.value() << std::endl;

        insert_stereotypes(s, a.stereotypes());
        s << ":END:" << std::endl;

        if (!a.documentation().empty())
            s << std::endl;
    }

    if (!a.documentation().empty()) {
        const auto sn(a.name().simple());
        if (sn == "content") {
            s << "#+begin_src mustache" << std::endl
              << a.documentation() << std::endl
              << "#+end_src" << std::endl;
        } else if (sn == "stitch_template_content") {
            s << "#+begin_src fundamental" << std::endl
              << a.documentation() << std::endl
              << "#+end_src" << std::endl;
        } else if (sn == "short_form" || sn == "long_form") {
            s << "#+begin_src fundamental" << std::endl
              << a.documentation() << std::endl
              << "#+end_src" << std::endl;
        } else
            s << a.documentation() << std::endl;
    }
}

void model_to_org_artefact_transform::insert_element_attributes(std::ostream& s,
    const entities::element& e) {
    /*
     * Don't bother outputting any of these flags if they are false.
     */
    if (e.can_be_enumeration_underlier())
        s << ":masd.codec.can_be_primitive_underlier: true" << std::endl;

    if (e.in_global_module())
        s << ":masd.codec.in_global_module: true" << std::endl;

    if (e.can_be_enumeration_underlier())
        s << ":masd.codec.can_be_enumeration_underlier: true" << std::endl;

    if (e.is_default_enumeration_type())
        s << ":masd.codec.is_default_enumeration_type: true" << std::endl;

    if (e.is_associative_container())
        s << ":masd.codec.is_associative_container: true" << std::endl;

    if (e.is_floating_point())
        s << ":masd.codec.is_floating_point: true" << std::endl;
}

void model_to_org_artefact_transform::insert_element(std::ostream& s,
    const unsigned int level, const entities::element& e) {
    s << make_headline(level, e.name().simple(), element_tag);

    const auto& tv(e.tagged_values());
    if (!e.parents().empty() || !e.stereotypes().empty() || !tv.empty()) {
        s << ":PROPERTIES:" << std::endl;
        insert_tagged_values(s, tv);
        insert_parents(s, e.parents());
        insert_stereotypes(s, e.stereotypes());
        insert_element_attributes(s, e);
        s << ":END:" << std::endl;

        if (!e.documentation().empty())
            s << std::endl;
    }

    if (!e.documentation().empty())
        s << e.documentation() << std::endl;

    for (const auto& a : e.attributes())
        insert_attribute(s, level + 1, a);
}

void model_to_org_artefact_transform::
walk_parent_to_child(std::ostream& s, const unsigned int level,
    const std::string& id, const std::unordered_map<std::string,
    std::list<entities::element>>& parent_to_child_map) {

    const auto i(parent_to_child_map.find(id));
    if (i != parent_to_child_map.end()) {
        for (const auto& e : i->second) {
            insert_element(s, level, e);
            const auto id(e.provenance().codec_id().value());
            walk_parent_to_child(s, level + 1, id, parent_to_child_map);
        }
    }
}

std::string
model_to_org_artefact_transform::to_string(const codec::entities::model& m) {
    std::ostringstream s;

    s << "#+title: " << m.name().simple() << std::endl
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
        auto& n(parent_to_child_map[e.containing_element_id().value()]);
        n.push_back(e);
    }

    std::string empty;
    walk_parent_to_child(s, 1, empty, parent_to_child_map);

    return s.str();
}


entities::artefact model_to_org_artefact_transform::
apply(const transforms::context& ctx, const boost::filesystem::path& p,
    const entities::model& m) {
    tracing::scoped_transform_tracer stp(lg, "org artefact to model",
        transform_id, m.name().qualified(), *ctx.tracer(), m);

    entities::artefact r;
    r.path(p);
    r.content(to_string(m));
    r.codec_name("org");

    stp.end_transform(r);
    return r;

}

}
