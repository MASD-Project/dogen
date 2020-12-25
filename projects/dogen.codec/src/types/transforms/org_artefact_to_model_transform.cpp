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
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include <sstream>
#include "dogen.org/types/entities/drawer_type.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.org/io/entities/drawer_type_io.hpp"
#include "dogen.org/types/transforms/string_to_document_transform.hpp"
#include "dogen.codec/io/entities/model_io.hpp"
#include "dogen.codec/io/entities/artefact_io.hpp"
#include "dogen.codec/types/transforms/transformation_error.hpp"
#include "dogen.codec/types/transforms/org_artefact_to_model_transform.hpp"

namespace {

const std::string
transform_id("codec.transforms.org_artefact_to_model_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string element_tag("masd_element");
const std::string attribute_tag("masd_attribute");
const std::string object_element_type("masd::object");
const std::string module_element_type("masd::module");

const std::string unexpected_number_of_drawers(
    "Unexpected number of drawers: ");
const std::string unexpected_drawer_type("Unexpected drawer type: ");
const std::string invalid_property("Property is missing key or value.");
const std::string invalid_tags("Invalid tags for headline: ");
const std::string unexpected_attribute(
    "Did not expect headline with attribute tag:");
const std::string unexpected_children(
    "Attribute headlines cannot have children: ");
const std::string unexpected_element("Cannot mix elements with attributes: ");

}

namespace dogen::codec::transforms {

using identification::entities::tagged_value;
using org::entities::drawer_type;

org_artefact_to_model_transform::headline_type org_artefact_to_model_transform::
get_headline_type(const org::entities::headline& h) {
    /*
     * If the headline has no tags, we can safely ignore it.
     */
    if (h.tags().empty())
        return headline_type::ignore;

    /*
     * Loop through all the tags, and locate those we're interested
     * in.
     */
    bool found(false);
    auto r(headline_type::ignore);
    for (const auto& tag : h.tags()) {
        if (tag.value() == element_tag)
            r = headline_type::element;
        else if (tag.value() == attribute_tag)
            r = headline_type::attribute;

        /*
         * We expect to have one or zero type related tags. If they appear
         * more than once, throw.
         */
        if (found) {
            BOOST_LOG_SEV(lg, error) << invalid_tags << h.title();
            BOOST_THROW_EXCEPTION(
                transformation_error(invalid_tags + h.title()));
        }
        found = true;
    }
    return r;
}

std::string org_artefact_to_model_transform::
section_to_text(const org::entities::section& s) {
    BOOST_LOG_SEV(lg, debug) << "Processing section.";

    std::ostringstream os;
    for (const auto& b : s.blocks())
        os << b.contents();

    BOOST_LOG_SEV(lg, debug) << "Finished processing section.";
    return os.str();
}

std::list<tagged_value> org_artefact_to_model_transform::
make_tagged_values(const std::list<org::entities::drawer>& drawers) {
    /*
     * Org models are expected to have exactly one property
     * drawer. Ensure that's the case and read its contents.
     */
    const auto sz(drawers.size());
    if (sz != 1) {
        BOOST_LOG_SEV(lg, error) << unexpected_number_of_drawers << sz;
        BOOST_THROW_EXCEPTION(
            transformation_error(unexpected_number_of_drawers +
                boost::lexical_cast<std::string>(sz)));
    }

    const auto& drawer(drawers.front());
    if (drawer.type() != drawer_type::property_drawer) {
        BOOST_LOG_SEV(lg, error) << unexpected_drawer_type << drawer.type();
        BOOST_THROW_EXCEPTION(
            transformation_error(unexpected_drawer_type +
                boost::lexical_cast<std::string>(drawer.type())));
    }

    std::list<tagged_value> r;
    for (const auto& dc : drawer.contents()) {
        /*
         * Properties are expected to have both key and value.
         */
        if (dc.key().empty() || dc.value().empty()) {
            BOOST_LOG_SEV(lg, error) << invalid_property << "Key: '"
                                     << dc.key() << "' Value: '"
                                     << dc.value() << "'";
            BOOST_THROW_EXCEPTION(
                transformation_error(invalid_property));
        }

        tagged_value tv;
        tv.tag(dc.key());
        tv.value(dc.value());
        r.push_back(tv);
    }
    return r;
}

entities::attribute org_artefact_to_model_transform::
make_attribute(const org::entities::headline& h) {
    /*
     * The headline must not have children.
     */
    if(!h.headlines().empty()) {
        BOOST_LOG_SEV(lg, error) << unexpected_children << h.title();
        BOOST_THROW_EXCEPTION(
            transformation_error(unexpected_children + h.title()));
    }

    entities::attribute r;
    r.name().simple(h.title());
    r.name().qualified(h.title()); // FIXME
    r.comment().original_content(section_to_text(h.section()));
    r.documentation(r.comment().original_content());

    /*
     * Attributes may not have drawers.
     */
    if (!h.drawers().empty())
        r.tagged_values(make_tagged_values(h.drawers()));

    return r;
}

std::list<entities::element> org_artefact_to_model_transform::
make_elements(const std::list<org::entities::headline>& headlines,
    entities::element& current) {
    /*
     * Process all top-level headlines.
     */
    bool found_element(false);
    bool found_attribute(false);
    std::list<entities::element> r;
    for (const auto& h : headlines) {
        BOOST_LOG_SEV(lg, debug) << "Processing headline: '"
                                 << h.title() << "'";

        /*
         * If the headline is not one of ours, we can ignore it. This
         * allows having non-Dogen content in a org document. However,
         * note that if the user decided to use tags in sub-headlines
         * these are ignored as well.
         */
        const auto ht(get_headline_type(h));
        if (ht == headline_type::ignore) {
            BOOST_LOG_SEV(lg, debug) << "Ignoring headline: " << h.title();
            continue;
        }

        /*
         * If we found an attribute, all other headlines processed
         * thus far must also be attributes.
         */
        if (ht == headline_type::attribute) {
            found_attribute = true;
            if (found_element) {
                BOOST_LOG_SEV(lg, error) << unexpected_attribute << h.title();
                BOOST_THROW_EXCEPTION(
                    transformation_error(unexpected_attribute + h.title()));
            }

            current.attributes().push_back(make_attribute(h));
            continue;
        }

        /*
         * If the headline type is element, we don't expect to have
         * already seen attributes.
         */
        if (ht == headline_type::element) {
            found_element = true;
            if (found_attribute) {
                BOOST_LOG_SEV(lg, error) << unexpected_element << h.title();
                BOOST_THROW_EXCEPTION(
                    transformation_error(unexpected_element + h.title()));
            }

            /*
             * Since we contain elements, we must be a module.
             */
            current.fallback_element_type(module_element_type);

            entities::element child;
            child.fallback_element_type(object_element_type);
            child.comment().original_content(section_to_text(h.section()));
            child.documentation(child.comment().original_content());
            child.name().simple(h.title());
            child.name().qualified(current.name().qualified() + "::" +
                child.name().simple());

            /*
             * Elements may not have drawers.
             */
            if (!h.drawers().empty())
                child.tagged_values(make_tagged_values(h.drawers()));

            r.splice(r.end(), make_elements(h.headlines(), child));
        }
    }

    r.push_back(current);
    return r;
}

entities::model org_artefact_to_model_transform::
apply(const transforms::context& ctx, const entities::artefact& a) {
    const auto fn(a.path().filename().stem().generic_string());
    const auto t(ctx.tracer());
    tracing::scoped_transform_tracer stp(lg, "org artefact to model",
        transform_id, fn, *t, a);

    BOOST_LOG_SEV(lg, debug) << "Processing org-mode document.";
    using org::transforms::string_to_document_transform;
    const auto doc(string_to_document_transform::apply(t, a.content()));

    BOOST_LOG_SEV(lg, debug) << "Processed org-mode document.";
    entities::model r;
    r.name().simple(fn);
    r.tagged_values(make_tagged_values(doc.drawers()));
    r.comment().original_content(section_to_text(doc.section()));
    r.documentation(r.comment().original_content());

    /*
     * Process all top-level headlines.
     */
    for (const auto& h : doc.headlines()) {
        BOOST_LOG_SEV(lg, debug) << "Processing headline: '"
                                 << h.title() << "'";

        /*
         * If the headline is not one of ours, we can ignore it. This
         * allows having non-Dogen content in a org document. However,
         * note that if the user decided to use tags in sub-headlines
         * these are ignored as well.
         */
        const auto ht(get_headline_type(h));
        if (ht == headline_type::ignore) {
            BOOST_LOG_SEV(lg, debug) << "Ignoring headline.";
            continue;
        }

        /*
         * We are only expecting "element" as our children, so if it's
         * not throw.
         */
        if (ht == headline_type::attribute) {
            BOOST_LOG_SEV(lg, error) << unexpected_attribute << h.title();
            BOOST_THROW_EXCEPTION(
                transformation_error(unexpected_attribute + h.title()));
        }

        /*
         * Process the current element.
         */
        entities::element current;
        current.name().simple(h.title());
        current.name().qualified(current.name().simple());
        current.fallback_element_type(object_element_type);
        current.comment().original_content(section_to_text(h.section()));
        current.documentation(current.comment().original_content());

        /*
         * Elements may not have drawers.
         */
        if (!h.drawers().empty())
            current.tagged_values(make_tagged_values(h.drawers()));

        r.elements().splice(r.elements().end(),
            make_elements(h.headlines(), current));
    }

    stp.end_transform(r);
    return r;
}

}
