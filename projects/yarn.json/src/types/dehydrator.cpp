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
#include "dogen/yarn.json/types/dehydrator.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.json.dehydrator"));

const std::string scope("::");
const std::string comma_space(", ");

}

namespace dogen {
namespace yarn {
namespace json {

bool dehydrator::has_elements(const intermediate_model& im) const {
    return
        !im.objects().empty() ||
        !im.primitives().empty() ||
        !im.enumerations().empty() ||
        !im.modules().empty();
}
void dehydrator::
insert_objects(const intermediate_model& im, std::ostream& s) const {
    using boost::algorithm::join;
    formatters::utility_formatter uf(s);
    bool is_first_object(true);
    for (const auto& pair : im.objects()) {
        if (!is_first_object)
            s << comma_space;

        const auto& o(pair.second);
        s << " { ";
        uf.insert_quoted("name");
        s << " : { ";
        uf.insert_quoted("simple_name");
        s << " : ";
        uf.insert_quoted(o.name().simple());

        const auto& l(o.name().location());
        if (!l.internal_modules().empty()) {
            s << comma_space;
            uf.insert_quoted("internal_modules");
            s << " : ";
            uf.insert_quoted(join(l.internal_modules(), scope));
        }
        s << " }, ";

        uf.insert_quoted("meta_type");
        s << ": ";
        uf.insert_quoted("object");

        if (!o.local_attributes().empty()) {
            s << comma_space;
            uf.insert_quoted("attributes");
            s << ": [";

            bool is_first_attribute(true);
            for(const auto& a : o.local_attributes()) {
                if (!is_first_attribute)
                    s << ",";

                s << " { ";
                uf.insert_quoted("simple_name");
                s << " : ";
                uf.insert_quoted(a.name().simple());

                s << comma_space;

                uf.insert_quoted("type");
                s << " : ";
                uf.insert_quoted(a.unparsed_type());

                s << " }";
                is_first_attribute = false;
            }
            s << " ]";
        }
        s << " }";
        is_first_object = false;
    }
}


std::string dehydrator::dehydrate(const intermediate_model& im) const {
    std::ostringstream s;
    formatters::utility_formatter uf(s);
    using boost::algorithm::join;

    const auto& l(im.name().location());
    s << "{ ";
    uf.insert_quoted("model_name");
    s << " : ";
    uf.insert_quoted(join(l.model_modules(), scope));
    s << comma_space;

    uf.insert_quoted("external_modules");
    s << " : ";
    uf.insert_quoted(join(l.external_modules(), scope));
    s << comma_space;

    bool has_annotations(false);
    const auto& scribble_groups(im.indices().scribble_groups());
    const auto i(scribble_groups.find(im.name().id()));
    if (i != scribble_groups.end()) {
        bool is_first(true);
        const auto scribble(i->second.parent());
        has_annotations = !scribble.entries().empty();
        if (has_annotations) {
            uf.insert_quoted("annotation");
            s << " : {";

            for (const auto& entry : scribble.entries()) {
                if (!is_first)
                    s << ", ";
                uf.insert_quoted(entry.first);
                s << " : ";
                uf.insert_quoted(entry.second);
                is_first = false;
            }
            s << " }";
        }
    }

    if (has_elements(im)) {
        if (has_annotations)
            s << comma_space;

        uf.insert_quoted("elements");
        s << ": [";
        insert_objects(im, s);
        s << " ]";
    }

    s << " }";

    return s.str();
}

void dehydrator::dehydrate(const intermediate_model& im,
    const boost::filesystem::path& p) const {

    const auto s(dehydrate(im));
    utility::filesystem::write_file_content(p, s);
}

} } }
