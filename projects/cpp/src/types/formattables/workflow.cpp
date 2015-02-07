/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include "dogen/utility/log/logger.hpp"
#include "dogen/cpp/types/formattables/file_properties_factory.hpp"
#include "dogen/cpp/types/formattables/file_name_factory.hpp"
#include "dogen/cpp/types/formattables/workflow.hpp"

namespace {

const std::string id("cpp.formattables.workflow");

using namespace dogen::utility::log;
static logger lg(logger_factory(id));

}

namespace dogen {
namespace cpp {
namespace formattables {

std::unordered_map<
    sml::qname,
    std::unordered_map<std::string, boost::filesystem::path> >
workflow::obtain_file_names_activity(const settings::selector& s,
    const formatters::container& c,
    const sml::model& m) const {
    formattables::file_name_factory f;
    return f.make(s, c, m);
}

std::unordered_map<
    sml::qname,
    std::unordered_map<std::string, formattables::file_properties> >
workflow::obtain_file_properties_activity(
    const settings::selector& s,
    const formatters::container& c, const sml::model& m,
    const std::unordered_map<sml::qname,
    std::unordered_map<std::string, boost::filesystem::path> >&
    file_names) const {
    formattables::file_properties_factory f;
    return f.make(s, c, file_names, m);
}

std::forward_list<std::shared_ptr<formattables::formattable> >
workflow::execute(const settings::selector& s, const formatters::container& c,
    const sml::model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Started creating formattables.";
    const auto fn(obtain_file_names_activity(s, c, m));
    const auto fp(obtain_file_properties_activity(s, c, m, fn));

    std::forward_list<std::shared_ptr<formattables::formattable>> r;
    r.splice_after(r.before_begin(),
        to_formattables_activity(fp, m, m.modules()));
    r.splice_after(r.before_begin(),
        to_formattables_activity(fp, m, m.concepts()));
    r.splice_after(r.before_begin(),
        to_formattables_activity(fp, m, m.primitives()));
    r.splice_after(r.before_begin(),
        to_formattables_activity(fp, m, m.enumerations()));
    r.splice_after(r.before_begin(),
        to_formattables_activity(fp, m, m.objects()));

    BOOST_LOG_SEV(lg, debug) << "Finished creating formattables.";
    return r;
}

} } }
