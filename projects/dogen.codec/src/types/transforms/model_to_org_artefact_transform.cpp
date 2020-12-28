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
#include "dogen.org/types/entities/affiliated_keyword.hpp"
#include "dogen.org/types/entities/block_type.hpp"
#include "dogen.org/types/entities/drawer_content.hpp"
#include "dogen.org/types/entities/drawer_type.hpp"
#include "dogen.org/types/entities/parameter.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/formatters/utility_formatter.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.org/types/transforms/document_to_string_transform.hpp"
#include "dogen.codec/io/entities/model_io.hpp"
#include "dogen.codec/io/entities/artefact_io.hpp"
#include "dogen.codec/types/transforms/transformation_error.hpp"
#include "dogen.codec/types/transforms/model_to_org_artefact_transform.hpp"

namespace {

const std::string
transform_id("codec.transforms.model_to_org_artefact_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string empty;
const std::string scope("::");
const std::string comma_space(", ");
const std::string element_tag(":masd_element:");
const std::string attribute_tag(":masd_attribute:");
const std::string module_tag(":masd_module:");
const std::string element_tag_new("masd_element");
const std::string attribute_tag_new("masd_attribute");
const std::string module_tag_new("masd_module");
const std::string module_element_type("masd::module");

const std::string primitive_underlier("masd.codec.can_be_primitive_underlier");
const std::string global_module("masd.codec.in_global_module");
const std::string enumeration_underlier(
    "masd.codec.can_be_enumeration_underlier");
const std::string default_enumeration_type(
    "masd.codec.is_default_enumeration_type");
const std::string associative_container("masd.codec.is_associative_container");
const std::string floating_point("masd.codec.is_floating_point");

const std::string invalid_enumerator("invalid");
const std::string child_not_found("Cannot locate child with ID: ");

}

namespace dogen::codec::transforms {

using identification::entities::tagged_value;
using identification::entities::stereotype;

std::string model_to_org_artefact_transform::
make_headline(const unsigned int level, const std::string& title,
    const std::string& tag) {
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
    const std::string& spaces, const std::list<tagged_value>& tvs) {
    if (tvs.empty())
        return;

    for (const auto& tv : tvs)
        s << spaces << ":" << tv.tag() << ": " << tv.value() << std::endl;
}

void model_to_org_artefact_transform::insert_stereotypes(std::ostream& s,
    const std::string& spaces, const std::list<stereotype>& sts) {
    if (sts.empty())
        return;

    s << spaces << ":masd.codec.stereotypes: ";
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
insert_parents(std::ostream& s, const std::string& spaces,
    const std::list<std::string>& parents) {
    if (parents.empty())
        return;

    s << spaces << ":masd.codec.parent: ";
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
    const std::string spaces(level + 1, ' ');

    if (!a.type().empty() || !a.value().empty() || !a.stereotypes().empty()
        || !tvs.empty()) {
        s << spaces << ":PROPERTIES:" << std::endl;
        insert_tagged_values(s, spaces, tvs);
        if (!a.type().empty())
            s << spaces << ":masd.codec.type: " << a.type() << std::endl;

        if (!a.value().empty())
            s << spaces << ":masd.codec.value: " << a.value() << std::endl;

        insert_stereotypes(s, spaces, a.stereotypes());
        s << spaces << ":END:" << std::endl;

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
    const std::string& spaces, const entities::element& e) {
    /*
     * Don't bother outputting any of these flags if they are false.
     */
    if (e.can_be_primitive_underlier()) {
        s << spaces << ":masd.codec.can_be_primitive_underlier: true"
          << std::endl;
    }

    if (e.in_global_module()) {
        s << spaces << ":masd.codec.in_global_module: true"
          << std::endl;
    }

    if (e.can_be_enumeration_underlier()) {
        s << spaces << ":masd.codec.can_be_enumeration_underlier: true"
          << std::endl;
    }

    if (e.is_default_enumeration_type()) {
        s << spaces << ":masd.codec.is_default_enumeration_type: true"
          << std::endl;
    }

    if (e.is_associative_container()) {
        s << spaces << ":masd.codec.is_associative_container: true"
          << std::endl;
    }

    if (e.is_floating_point()) {
        s << spaces << ":masd.codec.is_floating_point: true"
          << std::endl;
    }
}

void model_to_org_artefact_transform::insert_element(std::ostream& s,
    const unsigned int level, const entities::element& e) {
    const auto tag(e.fallback_element_type() == module_element_type ?
        module_tag : element_tag);
    s << make_headline(level, e.name().simple(), tag);

    const auto& tv(e.tagged_values());
    const std::string spaces(level + 1, ' ');

    if (!e.parents().empty() || !e.stereotypes().empty() || !tv.empty()) {
        s << spaces << ":PROPERTIES:" << std::endl;
        insert_tagged_values(s, spaces, tv);
        insert_parents(s, spaces, e.parents());
        insert_stereotypes(s, spaces, e.stereotypes());
        insert_element_attributes(s, spaces, e);
        s << spaces << ":END:" << std::endl;
    }

    if (!e.documentation().empty())
        s << std::endl;

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
        insert_tagged_values(s, empty, tv);
        insert_stereotypes(s, empty, m.stereotypes());
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

/*
 * New methods
*/
org::entities::drawer_content to_drawer_content(
    const std::string& key, const std::string& value) {
    org::entities::drawer_content r;
    r.key(key);
    r.value(value);
    return r;
}

void model_to_org_artefact_transform::add_to_property_drawer(
    const std::list<identification::entities::stereotype>& sts,
    org::entities::drawer& d) {

    if (sts.empty())
        return;

    org::entities::drawer_content dc;
    dc.key("masd.codec.stereotypes");

    std::ostringstream os;
    bool is_first(true);
    for (const auto& st : sts) {
        if (!is_first)
            os << ", ";
        os << st.value();
        is_first = false;
    }
    dc.value(os.str());
    d.contents().push_back(dc);
}

void model_to_org_artefact_transform::add_to_property_drawer(
    const std::list<std::string>& parents, org::entities::drawer& d) {

    if (parents.empty())
        return;

    org::entities::drawer_content dc;
    dc.key("masd.codec.parent");

    std::ostringstream os;
    bool is_first(true);
    for (const auto& p : parents) {
        if (!is_first)
            os << ", ";
        os << p;
        is_first = false;
    }
    dc.value(os.str());
    d.contents().push_back(dc);
}

void model_to_org_artefact_transform::add_to_property_drawer(
    const entities::element& e, org::entities::drawer& d) {
    /*
     * Don't bother outputting any of these flags if they are false.
     */
    if (e.can_be_primitive_underlier()) {
        const auto dc(to_drawer_content(primitive_underlier, "true"));
        d.contents().push_back(dc);
    }

    if (e.in_global_module()) {
        const auto dc(to_drawer_content(global_module, "true"));
        d.contents().push_back(dc);
    }

    if (e.can_be_enumeration_underlier()) {
        const auto dc(to_drawer_content(enumeration_underlier, "true"));
        d.contents().push_back(dc);
    }

    if (e.is_default_enumeration_type()) {
        const auto dc(to_drawer_content(default_enumeration_type, "true"));
        d.contents().push_back(dc);
    }

    if (e.is_associative_container()) {
        const auto dc(to_drawer_content(associative_container, "true"));
        d.contents().push_back(dc);
    }

    if (e.is_floating_point()) {
        const auto dc(to_drawer_content(associative_container, "true"));
        d.contents().push_back(dc);
    }
}

void model_to_org_artefact_transform::add_to_property_drawer(
    const std::list<identification::entities::tagged_value>& tvs,
    org::entities::drawer& d) {
    for (const auto& tv : tvs) {
        const auto dc(to_drawer_content(tv.tag(), tv.value()));
        d.contents().push_back(dc);
    }
}

org::entities::tag
model_to_org_artefact_transform::to_tag(const entities::element& e) {
    if (e.fallback_element_type() == module_element_type)
        return org::entities::tag(module_tag_new);
    else
        return org::entities::tag(element_tag_new);
}

org::entities::headline
model_to_org_artefact_transform::to_headline(const unsigned int level,
    const entities::attribute& attr) {

    org::entities::headline r;
    r.level(level);
    r.title(attr.name().simple());
    r.tags().push_back(org::entities::tag(attribute_tag_new));

    org::entities::drawer d;
    d.type(org::entities::drawer_type::property_drawer);

    add_to_property_drawer(attr.tagged_values(), d);

    if (!attr.type().empty()) {
        const auto dc(to_drawer_content("masd.codec.type", attr.type()));
        d.contents().push_back(dc);
    }

    if (!attr.value().empty()) {
        const auto dc(to_drawer_content("masd.codec.value", attr.value()));
        d.contents().push_back(dc);

    }

    if (!d.contents().empty())
        r.drawers().push_back(d);

    if (!attr.documentation().empty()) {
        org::entities::block tb;
        const auto sn(attr.name().simple());
        if (sn == "content") {
            tb.type(org::entities::block_type::greater_block);
            org::entities::parameter p("mustache");
            tb.parameters().push_back(p);
        } else if (sn == "stitch_template_content") {
            tb.type(org::entities::block_type::greater_block);
            org::entities::parameter p("fundamental");
            tb.parameters().push_back(p);
        } else if (sn == "short_form" || sn == "long_form") {
            tb.type(org::entities::block_type::greater_block);
            org::entities::parameter p("fundamental");
            tb.parameters().push_back(p);
        } else
            tb.type(org::entities::block_type::text_block);

        tb.contents(attr.documentation());
        r.section().blocks().push_back(tb);
    }
    return r;
}

org::entities::headline
model_to_org_artefact_transform::to_headline(const unsigned int level,
    const entities::element& e) {

    org::entities::headline r;
    r.level(level);
    r.title(e.name().simple());
    r.tags().push_back(to_tag(e));

    org::entities::drawer d;
    d.type(org::entities::drawer_type::property_drawer);

    add_to_property_drawer(e.tagged_values(), d);
    add_to_property_drawer(e.parents(), d);
    add_to_property_drawer(e.stereotypes(), d);
    add_to_property_drawer(e, d);

    if (!d.contents().empty())
        r.drawers().push_back(d);

    if (!e.documentation().empty()) {
        org::entities::block tb;
        tb.type(org::entities::block_type::text_block);
        tb.contents(e.documentation());
        r.section().blocks().push_back(tb);
    }

    for (const auto& a : e.attributes())
        r.headlines().push_back(to_headline(level + 1, a));

    return r;
}

std::list<org::entities::headline> model_to_org_artefact_transform::
walk_parent_to_child(const unsigned int level,
    const std::string& id, const std::unordered_map<std::string,
    std::list<entities::element>>& parent_to_child_map) {

    std::list<org::entities::headline> r;
    /*
     * Child must exist in parent to child map.
     */
    const auto i(parent_to_child_map.find(id));
    if (i == parent_to_child_map.end()) {
        BOOST_LOG_SEV(lg, error) << child_not_found << id;
        BOOST_THROW_EXCEPTION(transformation_error(child_not_found + id));
    }

    /*
     * Loop through all the elements at this level and recurse to
     * their children.
     */
    for (const auto& e : i->second) {
        to_headline(level, e);
        const auto id(e.provenance().codec_id().value());
        walk_parent_to_child(level + 1, id, parent_to_child_map);
    }

    return r;
}

org::entities::document
model_to_org_artefact_transform::to_document(const codec::entities::model& m) {
    org::entities::document r;

    org::entities::affiliated_keyword title;
    title.key("title");
    title.value(m.name().simple());
    r.affiliated_keywords().push_back(title);

    org::entities::affiliated_keyword options;
    options.key("options");
    options.value("<:nil c:nil todo:nil ^:nil d:nil date:nil author:nil");
    r.affiliated_keywords().push_back(options);

    const auto& tvs(m.tagged_values());
    if (!tvs.empty()) {
        org::entities::drawer d;
        d.type(org::entities::drawer_type::property_drawer);
        add_to_property_drawer(tvs, d);
        r.drawers().push_back(d);
    }

    if (!m.documentation().empty()) {
        org::entities::block tb;
        tb.type(org::entities::block_type::text_block);
        tb.contents(m.documentation());
        r.section().blocks().push_back(tb);
    }

    std::unordered_map<std::string,
                       std::list<entities::element>> parent_to_child_map;
    for (const auto& e : m.elements()) {
        auto& n(parent_to_child_map[e.containing_element_id().value()]);
        n.push_back(e);
    }

    std::string empty;
    r.headlines(walk_parent_to_child(1, empty, parent_to_child_map));

    return r;
}

entities::artefact model_to_org_artefact_transform::
apply_new(const transforms::context& ctx, const boost::filesystem::path& p,
    const entities::model& m) {
    tracing::scoped_transform_tracer stp(lg, "org artefact to model",
        transform_id, m.name().qualified(), *ctx.tracer(), m);

    /*
     * Convert the codec model into an org-mode document.
     */
    const auto doc(to_document(m));

    /*
     * Convert the org document into a string.
     */
    using org::transforms::document_to_string_transform;
    const auto s(document_to_string_transform::apply(ctx.tracer(), doc));

    /*
     * Finally, construct the artefact with the contents.
     */
    entities::artefact r;
    r.path(p);
    r.content(s);
    r.codec_name("org");

    stp.end_transform(r);
    return r;
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
