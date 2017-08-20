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
#include "dogen/yarn/types/meta_model/concept.hpp"
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

std::string dehydrator::tidy_up_string(std::string s) const {
    boost::replace_all(s, "\r", "\\r");
    boost::replace_all(s, "\n", "\\n");
    boost::replace_all(s, "\"", "\\\"");
    return s;
}

bool dehydrator::has_elements(const meta_model::intermediate_model& im) const {
    return
        !im.modules().empty() ||
        !im.concepts().empty() ||
        !im.enumerations().empty() ||
        !im.primitives().empty() ||
        !im.objects().empty() ||
        !im.exceptions().empty();
}

boost::optional<annotations::scribble_group>
dehydrator::scribble_group_for_name(const meta_model::intermediate_model& im,
    const meta_model::name& n) const {

    const auto& scribble_groups(im.scribble_groups());
    const auto i(scribble_groups.find(n.id()));
    if (i == scribble_groups.end())
        return boost::optional<annotations::scribble_group>();

    return i->second;
}

boost::optional<annotations::scribble> dehydrator::
scribble_for_name(const boost::optional<annotations::scribble_group>& sg,
    const meta_model::name& n) const {

    if (!sg)
        return boost::optional<annotations::scribble>();

    const auto i(sg->children().find(n.simple()));
    if (i == sg->children().end())
        return boost::optional<annotations::scribble>();

    return i->second;
}

void dehydrator::
dehydrate_name(const meta_model::name& n, std::ostream& s) const {
    formatters::utility_formatter uf(s);
    s << " { ";
    uf.insert_quoted("simple");
    s << " : ";
    uf.insert_quoted(n.simple());

    const auto& l(n.location());
    if (!l.internal_modules().empty()) {
        s << comma_space;
        uf.insert_quoted("internal_modules");
        s << " : ";
        uf.insert_quoted(join(l.internal_modules(), scope));
    }
    s << " } ";
}

void dehydrator::dehydrate_names(const std::list<meta_model::name>& names,
    std::ostream& s) const {
    s << " [ ";
    bool is_first(true);
    for (const auto& n : names) {
        if (!is_first)
            s << comma_space;

        dehydrate_name(n, s);
        is_first = false;
    }
    s << " ] ";
}

void dehydrator::
dehydrate_annotations(const boost::optional<annotations::scribble>& scribble,
    std::ostream& s) const {

    if (!scribble || scribble->entries().empty())
        return;

    formatters::utility_formatter uf(s);
    s << comma_space;
    uf.insert_quoted("annotation");
    s << " : {";

    bool is_first(true);
    for (const auto& entry : scribble->entries()) {
        if (!is_first)
            s << ", ";
        uf.insert_quoted(entry.first);
        s << " : ";
        uf.insert_quoted(entry.second);
        is_first = false;
    }
    s << " }";
}

void dehydrator::
dehydrate_element(const boost::optional<annotations::scribble_group>& sg,
    const meta_model::element& e,
    const std::string& meta_type, std::ostream& s) const {

    formatters::utility_formatter uf(s);
    uf.insert_quoted("name");
    s << " : ";
    dehydrate_name(e.name(), s);
    s << comma_space;

    uf.insert_quoted("meta_type");
    s << ": ";
    uf.insert_quoted(meta_type);

    if (!e.documentation().empty()) {
        s << comma_space;
        uf.insert_quoted("documentation");
        s << " : ";
        uf.insert_quoted(tidy_up_string(e.documentation()));
    }

    if (!e.stereotypes().empty()) {
        s << comma_space;
        uf.insert_quoted("stereotypes");
        s << " : [ ";
        bool is_first(true);
        for (const auto& stereotype : e.stereotypes()) {
            if (!is_first)
                s << comma_space;

            uf.insert_quoted(stereotype);

            is_first = false;
        }
        s << " ] ";
    }

    if (sg)
        dehydrate_annotations(sg->parent(), s);
}

void dehydrator::dehydrate_attributes(
    const boost::optional<annotations::scribble_group>& sg,
    const std::list<meta_model::attribute>& attrs, std::ostream& s) const {

    formatters::utility_formatter uf(s);
    uf.insert_quoted("attributes");
    s << ": [";

    bool is_first(true);
    for(const auto& a : attrs) {
        if (!is_first)
            s << comma_space;

        s << " { ";
        uf.insert_quoted("name");
        s << " : { ";
        uf.insert_quoted("simple");
        s << " : ";
        uf.insert_quoted(a.name().simple());
        s << " } " << comma_space;

        uf.insert_quoted("unparsed_type");
        s << " : ";
        uf.insert_quoted(a.unparsed_type());

        if (!a.documentation().empty()) {
            s << comma_space;
            uf.insert_quoted("documentation");
            s << " : ";
            uf.insert_quoted(tidy_up_string(a.documentation()));
        }

        const auto scribble(scribble_for_name(sg, a.name()));
        dehydrate_annotations(scribble, s);

        s << " }";
        is_first = false;
    }
    s << " ]";
}

void dehydrator::dehydrate_objects(const bool requires_leading_comma,
    const meta_model::intermediate_model& im, std::ostream& s) const {

    using boost::algorithm::join;
    formatters::utility_formatter uf(s);

    const auto objects(to_map(im.objects()));
    bool output_comma(requires_leading_comma);
    for (const auto& pair : objects) {
        if (output_comma)
            s << comma_space;

        const auto& o(*pair.second);
        const auto sg(scribble_group_for_name(im, o.name()));

        s << " { ";
        dehydrate_element(sg, o, "object", s);
        if (!o.parents().empty()) {
            s << comma_space;
            uf.insert_quoted("parents");
            s << " : ";
            dehydrate_names(o.parents(), s);
        }

        if (!o.local_attributes().empty()) {
            s << comma_space;
            dehydrate_attributes(sg, o.local_attributes(), s);
        }
        s << " }";
        output_comma = true;
    }
}

void dehydrator::dehydrate_concepts(const bool requires_leading_comma,
    const meta_model::intermediate_model& im, std::ostream& s) const {

    using boost::algorithm::join;
    formatters::utility_formatter uf(s);
    bool output_comma(requires_leading_comma);

    const auto concepts(to_map(im.concepts()));
    for (const auto& pair : concepts) {
        if (output_comma)
            s << comma_space;

        const auto& c(*pair.second);
        const auto sg(scribble_group_for_name(im, c.name()));

        s << " { ";
        dehydrate_element(sg, c, "concept", s);

        if (!c.refines().empty()) {
            s << comma_space;
            uf.insert_quoted("refines");
            s << " : ";
            dehydrate_names(c.refines(), s);
        }

        if (!c.local_attributes().empty()) {
            s << comma_space;
            dehydrate_attributes(sg, c.local_attributes(), s);
        }
        s << " }";
        output_comma = true;
    }
}

void dehydrator::dehydrate_modules(const bool requires_leading_comma,
    const meta_model::intermediate_model& im, std::ostream& s) const {
    /*
     * Remove the root module.
     */
    auto modules(to_map(im.modules()));
    const auto i(modules.find(im.name().id()));
    if (i != modules.end())
        modules.erase(i);

    using boost::algorithm::join;
    formatters::utility_formatter uf(s);
    bool output_comma(requires_leading_comma);
    for (const auto& pair : modules) {
        if (output_comma)
            s << comma_space;

        const auto& m(*pair.second);
        const auto sg(scribble_group_for_name(im, m.name()));

        s << " { ";
        dehydrate_element(sg, m, "module", s);
        s << " }";

        output_comma = true;
    }
}

void dehydrator::dehydrate_enumerations(const bool requires_leading_comma,
    const meta_model::intermediate_model& im, std::ostream& s) const {
    using boost::algorithm::join;
    formatters::utility_formatter uf(s);
    bool output_comma(requires_leading_comma);
    const auto enumerations(to_map(im.enumerations()));
    for (const auto& pair : enumerations) {
        if (output_comma)
            s << comma_space;

        const auto& e(*pair.second);
        const auto sg(scribble_group_for_name(im, e.name()));

        s << " { ";
        dehydrate_element(sg, e, "enumeration", s);
        s << comma_space;

        /*
         * Remove invalid from enumerators.
         */
        std::vector<meta_model::enumerator> enumerators;
        enumerators.reserve(e.enumerators().size());
        for (const auto& en : e.enumerators()) {
            const auto n(boost::algorithm::to_lower_copy(en.name().simple()));
            if (n != invalid_enumerator)
                enumerators.push_back(en);
        }

        uf.insert_quoted("enumerators");
        s << ": [";

        bool is_first(true);
        for(const auto& en : enumerators) {
            if (!is_first)
                s << comma_space;

            s << " { ";
            uf.insert_quoted("name");
            s << " : { ";
            uf.insert_quoted("simple");
            s << " : ";
            uf.insert_quoted(en.name().simple());
            s << " }";

            if (!en.documentation().empty()) {
                s << comma_space;
                uf.insert_quoted("documentation");
                s << " : ";
                uf.insert_quoted(tidy_up_string(en.documentation()));
            }

            const auto scribble(scribble_for_name(sg, en.name()));
            dehydrate_annotations(scribble, s);

            s << " }";
            is_first = false;
        }
        s << " ]";

        s << " }";
        output_comma = true;
    }
}

void dehydrator::dehydrate_primitives(const bool requires_leading_comma,
    const meta_model::intermediate_model& im, std::ostream& s) const {
    using boost::algorithm::join;
    formatters::utility_formatter uf(s);

    bool output_comma(requires_leading_comma);
    const auto primitives(to_map(im.primitives()));
    for (const auto& pair : primitives) {
        if (output_comma)
            s << comma_space;

        const auto& p(*pair.second);
        const auto sg(scribble_group_for_name(im, p.name()));

        s << " { ";
        dehydrate_element(sg, p, "primitive", s);
        s << " }";
        output_comma = true;
    }
}

void dehydrator::
dehydrate_exceptions(const bool requires_leading_comma,
    const meta_model::intermediate_model& im, std::ostream& s) const {
    using boost::algorithm::join;
    formatters::utility_formatter uf(s);

    bool output_comma(requires_leading_comma);
    const auto exceptions(to_map(im.exceptions()));
    for (const auto& pair : exceptions) {
        if (output_comma)
            s << comma_space;

        const auto& p(*pair.second);
        const auto sg(scribble_group_for_name(im, p.name()));

        s << " { ";
        dehydrate_element(sg, p, "exception", s);
        s << " }";
        output_comma = true;
    }
}

std::string
dehydrator::dehydrate(const meta_model::intermediate_model& im) const {
    std::ostringstream s;
    formatters::utility_formatter uf(s);
    using boost::algorithm::join;

    s << "{ ";

    const auto i(im.modules().find(im.name().id()));
    if (i != im.modules().end()) {
        const auto& root_module(*i->second);
        if (!root_module.documentation().empty()) {
            s << comma_space;
            uf.insert_quoted("documentation");
            s << " : ";
            uf.insert_quoted(tidy_up_string(root_module.documentation()));
        }
    }

    const auto sg(scribble_group_for_name(im, im.name()));
    if (sg)
        dehydrate_annotations(sg->parent(), s);

    if (has_elements(im)) {
        s << comma_space;
        uf.insert_quoted("elements");
        s << ": [";

        bool requires_leading_comma(false);

        dehydrate_objects(requires_leading_comma, im, s);
        requires_leading_comma |= !im.objects().empty();

        dehydrate_concepts(requires_leading_comma, im, s);
        requires_leading_comma |= !im.concepts().empty();

        dehydrate_modules(requires_leading_comma, im, s);
        requires_leading_comma |= im.modules().size() > 1/*root module*/;

        dehydrate_enumerations(requires_leading_comma, im, s);
        requires_leading_comma |= !im.enumerations().empty();

        dehydrate_primitives(requires_leading_comma, im, s);
        requires_leading_comma |= !im.primitives().empty();

        dehydrate_exceptions(requires_leading_comma, im, s);

        s << " ]";
    }

    s << " }";

    return s.str();
}

void dehydrator::dehydrate(const meta_model::intermediate_model& im,
    const boost::filesystem::path& p) const {

    const auto s(dehydrate(im));
    utility::filesystem::write_file_content(p, s);
}

} } }
