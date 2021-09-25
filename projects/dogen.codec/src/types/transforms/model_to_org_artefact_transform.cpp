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
#include "dogen.utility/types/formatters/utility_formatter.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.org/types/entities/affiliated_keyword.hpp"
#include "dogen.org/types/entities/block_type.hpp"
#include "dogen.org/types/entities/drawer_content.hpp"
#include "dogen.org/types/entities/drawer_type.hpp"
#include "dogen.org/types/entities/parameter.hpp"
#include "dogen.org/io/entities/document_io.hpp"
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
const std::string element_tag("element");
const std::string attribute_tag("attribute");
const std::string module_tag("module");
const std::string module_element_type("masd::module");
const std::string custom_id("custom_id");

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
using org::entities::block_type;

void model_to_org_artefact_transform::add_kvp(const std::string& key,
    const std::string& value, key_value_pairs& kvps) {

    std::pair<std::string, std::string> pair;
    pair.first = key;
    if (kvps.max_key < pair.first.size())
        kvps.max_key = pair.first.size();

    pair.second = value;
    if (kvps.max_key < pair.second.size())
        kvps.max_key = pair.second.size();

    kvps.contents.push_back(pair);
}

void model_to_org_artefact_transform::
add_kvp(const std::list<identification::entities::stereotype>& sts,
    key_value_pairs& kvps) {

    BOOST_LOG_SEV(lg, debug) << "Adding stereotypes to property drawer.";
    if (sts.empty()) {
        BOOST_LOG_SEV(lg, debug) << "No stereotypes found.";
        return;
    }

    std::ostringstream os;
    bool is_first(true);
    for (const auto& st : sts) {
        if (!is_first)
            os << ", ";
        os << st.value();
        is_first = false;
    }

    add_kvp("masd.codec.stereotypes", os.str(), kvps);

    BOOST_LOG_SEV(lg, debug) << "Finished adding stereotypes to drawer.";
}

void model_to_org_artefact_transform::
add_kvp(const std::list<std::string>& parents, key_value_pairs& kvps) {
    BOOST_LOG_SEV(lg, debug) << "Adding parents to property drawer.";

    if (parents.empty()) {
        BOOST_LOG_SEV(lg, debug) << "No parents found.";
        return;
    }

    std::ostringstream os;
    bool is_first(true);
    for (const auto& p : parents) {
        if (!is_first)
            os << ", ";
        os << p;
        is_first = false;
    }

    add_kvp("masd.codec.parent", os.str(), kvps);

    BOOST_LOG_SEV(lg, debug) << "Finished adding parents to drawer.";
}

void model_to_org_artefact_transform::add_kvp(const entities::element& e,
    key_value_pairs& kvps) {
    BOOST_LOG_SEV(lg, debug) << "Adding element properties to property drawer.";

    /*
     * Don't bother outputting any of these flags if they are false.
     */
    if (e.can_be_primitive_underlier()) {
        BOOST_LOG_SEV(lg, debug) << "Added " << primitive_underlier;
        add_kvp(primitive_underlier, "true", kvps);
    }

    if (e.in_global_module()) {
        BOOST_LOG_SEV(lg, debug) << "Added " << global_module;
        add_kvp(global_module, "true", kvps);
    }

    if (e.can_be_enumeration_underlier()) {
        BOOST_LOG_SEV(lg, debug) << "Added " << enumeration_underlier;
        add_kvp(enumeration_underlier, "true", kvps);
    }

    if (e.is_default_enumeration_type()) {
        BOOST_LOG_SEV(lg, debug) << "Added " << default_enumeration_type;
        add_kvp(default_enumeration_type, "true", kvps);
    }

    if (e.is_associative_container()) {
        BOOST_LOG_SEV(lg, debug) << "Added " << associative_container;
        add_kvp(associative_container, "true", kvps);
    }

    if (e.is_floating_point()) {
        BOOST_LOG_SEV(lg, debug) << "Added " << floating_point;
        add_kvp(floating_point, "true", kvps);
    }

    BOOST_LOG_SEV(lg, debug) << "Finished adding element properties to drawer.";

}

void model_to_org_artefact_transform::
add_kvp(const std::list<identification::entities::tagged_value>& tvs,
    key_value_pairs& kvps) {
    BOOST_LOG_SEV(lg, debug) << "Adding tagged values to property drawer.";

    if (tvs.empty()) {
        BOOST_LOG_SEV(lg, debug) << "No tagged values to add.";
        return;
    }

    for (const auto& tv : tvs)
        add_kvp(tv.tag(), tv.value(), kvps);

    BOOST_LOG_SEV(lg, debug) << "Added tagged values to property drawer.";
}

org::entities::drawer model_to_org_artefact_transform::
to_property_drawer(const key_value_pairs& kvps) {
    org::entities::drawer r;
    r.type(org::entities::drawer_type::property_drawer);
    for (const auto& pair : kvps.contents) {
        org::entities::drawer_content dc;
        dc.key(pair.first);
        dc.value(pair.second);
        r.contents().push_back(dc);
    }
    return r;
}

org::entities::tag
model_to_org_artefact_transform::to_tag(const entities::element& e) {
    if (e.fallback_element_type() == module_element_type)
        return org::entities::tag(module_tag);
    else
        return org::entities::tag(element_tag);
}

std::string model_to_org_artefact_transform::identifier_to_headline_title(
    const std::string& identifier) {
    const auto r(boost::replace_all_copy(identifier, "_", " "));
    return r;
}

org::entities::headline model_to_org_artefact_transform::
to_headline(const unsigned int level, const entities::attribute& attr) {
    BOOST_LOG_SEV(lg, debug) << "Creating headline for attribute: "
                             << attr.name().simple();

    org::entities::headline r;
    r.level(level);
    r.title(identifier_to_headline_title(attr.name().simple()));
    r.tags().push_back(org::entities::tag(attribute_tag));

    key_value_pairs kvps;
    add_kvp(attr.tagged_values(), kvps);
    if (!attr.type().empty()) {
        BOOST_LOG_SEV(lg, debug) << "Adding type.";
        add_kvp("masd.codec.type", attr.type(), kvps);
    }

    if (!attr.value().empty()) {
        BOOST_LOG_SEV(lg, debug) << "Adding value.";
        add_kvp("masd.codec.value", attr.value(), kvps);
    }

    /*
     * Only add the drawer if we have some content.
     */
    const auto d(to_property_drawer(kvps));
    if (!d.contents().empty()) {
        BOOST_LOG_SEV(lg, debug) << "Adding drawer.";
        r.drawers().push_back(d);
    } else
        BOOST_LOG_SEV(lg, debug) << "Ignoring empty drawer.";

    if (attr.comment().documentation().empty()) {
        BOOST_LOG_SEV(lg, debug) << "Attribute has no documentation.";
    } else {
        BOOST_LOG_SEV(lg, debug) << "Processing attribute documentation.";
        org::entities::block tb;
        const auto sn(attr.name().simple());
        const auto& doc(attr.comment().documentation());
        const auto gbt(block_type::greater_block);
        if (sn == "content") {
            BOOST_LOG_SEV(lg, debug) << "Found mustache template.";
            const auto b(to_block(doc, gbt, "mustache"));
            r.section().blocks().push_back(b);
        } else if (sn == "stitch_template_content") {
            BOOST_LOG_SEV(lg, debug) << "Found stitch template.";
            const auto b(to_block(doc, gbt, "fundamental"));
            r.section().blocks().push_back(b);
        } else if (sn == "short_form" || sn == "long_form") {
            BOOST_LOG_SEV(lg, debug) << "Found licence.";
            const auto b(to_block(doc, gbt, "fundamental"));
            r.section().blocks().push_back(b);
        } else {
            const auto b(to_block(doc, block_type::text_block));
            r.section().blocks().push_back(b);
        }
    }

    BOOST_LOG_SEV(lg, debug) << "Finished generating headline for attribute.";
    return r;
}

org::entities::headline model_to_org_artefact_transform::
to_headline(const unsigned int level, const entities::element& e) {
    BOOST_LOG_SEV(lg, debug) << "Creating headline for element: "
                             << e.name().simple();

    org::entities::headline r;
    r.level(level);
    r.title(identifier_to_headline_title(e.name().simple()));
    r.tags().push_back(to_tag(e));

    /*
     * Create a property drawer for the element.
     */
    BOOST_LOG_SEV(lg, debug) << "Creating drawer for element.";

    /*
     * If we have a unique ID in the element, propagate it into org.
     */
    key_value_pairs kvps;
    const auto id(e.provenance().codec_id().value());
    if (!id.empty()) {
        BOOST_LOG_SEV(lg, debug) << "Added ID: " << id;
        add_kvp(custom_id, id, kvps);
    }

    /*
     * Add all other properties to drawer.
     */
    add_kvp(e.tagged_values(), kvps);
    add_kvp(e.parents(), kvps);
    add_kvp(e.stereotypes(), kvps);
    add_kvp(e, kvps);

    const auto d(to_property_drawer(kvps));
    if (!d.contents().empty()) {
        BOOST_LOG_SEV(lg, debug) << "Drawer has contents.";
        r.drawers().push_back(d);
    } else
        BOOST_LOG_SEV(lg, debug) << "Drawer is empty, ignoring it.";

    /*
     * Add documentation to element.
     */
    if (!e.comment().documentation().empty()) {
        BOOST_LOG_SEV(lg, debug) << "Element has documentation.";
        const auto& doc(e.comment().documentation());
        const auto tb(to_block(doc, block_type::text_block));
        r.section().blocks().push_back(tb);
    }

    /*
     * Add all attributes as headlines.
     */
    BOOST_LOG_SEV(lg, debug) << "Processing attributes for element.";
    for (const auto& attr : e.attributes())
        r.headlines().push_back(to_headline(level + 1, attr));

    BOOST_LOG_SEV(lg, debug) << "Total attributes added: "
                             << r.headlines().size();
    BOOST_LOG_SEV(lg, debug) << "Finished creating headline for element.";
    return r;
}

org::entities::block model_to_org_artefact_transform::
to_block(const std::string& content, const block_type bt,
    const std::string& parameter) {

    org::entities::block r;
    r.type(bt);

    std::ostringstream os;
    os << content << std::endl;
    r.contents(os.str());

    if (!parameter.empty()) {
        org::entities::parameter p(parameter);
        r.parameters().push_back(p);
    }

    return r;
}

org::entities::block
model_to_org_artefact_transform::to_block(const std::string& content,
    const block_type bt) {
    return to_block(content, bt, empty);
}

std::list<org::entities::headline> model_to_org_artefact_transform::
walk_parent_to_child(const unsigned int level, const std::string& id,
    const std::unordered_map<std::string, std::list<entities::element>>&
    parent_to_child_map) {
    BOOST_LOG_SEV(lg, debug) << "Processing ID: '" << id << "'";

    std::list<org::entities::headline> r;
    const auto i(parent_to_child_map.find(id));
    if (i != parent_to_child_map.end()) {
        /*
         * Loop through all the elements at this level and recurse to
         * their children.
         */
        BOOST_LOG_SEV(lg, debug) << "Found ID in map.";
        const auto& map(parent_to_child_map);
        for (const auto& e : i->second) {
            BOOST_LOG_SEV(lg, debug) << "Processing element: "
                                     << e.name().qualified();

            auto h(to_headline(level, e));
            const auto id(e.provenance().codec_id().value());
            h.headlines().splice(h.headlines().end(),
                walk_parent_to_child(level + 1, id, map));
            r.push_back(h);
        }
    }

    BOOST_LOG_SEV(lg, debug) << "Finished processing ID. Headlines: "
                             << r.size();
    return r;
}

org::entities::document model_to_org_artefact_transform::
to_document(const codec::entities::model& m) {
    org::entities::document r;

    BOOST_LOG_SEV(lg, debug) << "Converting model to org document: "
                             << m.name().simple();

    /*
     * Inject all of the affiliated keywords into the document.
     */
    org::entities::affiliated_keyword title;
    title.key("title");
    title.value(m.name().simple());
    r.affiliated_keywords().push_back(title);

    org::entities::affiliated_keyword options;
    options.key("options");
    options.value("<:nil c:nil todo:nil ^:nil d:nil date:nil author:nil");
    r.affiliated_keywords().push_back(options);

    org::entities::affiliated_keyword tags;
    tags.key("tags");
    tags.value("{ element(e) attribute(a) module(m) }");
    r.affiliated_keywords().push_back(tags);

    /*
     * Handle tagged values and documentation.
     */
    const auto& tvs(m.tagged_values());
    if (!tvs.empty()) {
        BOOST_LOG_SEV(lg, debug) << "Model has tagged values.";

        key_value_pairs kvps;
        add_kvp(tvs, kvps);
        const auto d(to_property_drawer(kvps));
        r.drawers().push_back(d);
    }

    if (!m.comment().documentation().empty()) {
        BOOST_LOG_SEV(lg, debug) << "Model has documentation.";
        const auto& doc(m.comment().documentation());
        const auto tb(to_block(doc, block_type::text_block));
        r.section().blocks().push_back(tb);
    }

    /*
     * Construct a map with the ID of the parent pointing to a list of
     * its children.
     */
    std::unordered_map<std::string,
                       std::list<entities::element>> parent_to_child_map;
    for (const auto& e : m.elements()) {
        auto& n(parent_to_child_map[e.containing_element_id().value()]);
        n.push_back(e);
    }

    /*
     * Process all elements into headlines, recursively.
     */
    std::string empty;
    r.headlines(walk_parent_to_child(1, empty, parent_to_child_map));
    BOOST_LOG_SEV(lg, debug) << "Converted model to org document. Result: "
                             << r;
    return r;
}

entities::artefact model_to_org_artefact_transform::
apply(const transforms::context& ctx, const boost::filesystem::path& p,
    const entities::model& m) {
    tracing::scoped_transform_tracer stp(lg, "model to org artefact",
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

}
