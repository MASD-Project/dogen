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
#include "dogen/dynamic/types/workflow.hpp"
#include "dogen/cpp/types/settings/workflow.hpp"
#include "dogen/cpp/types/formatters/workflow.hpp"
#include "dogen/cpp/types/formattables/workflow.hpp"
#include "dogen/cpp/types/workflow.hpp"

namespace {

const std::string id("cpp.workflow");

using namespace dogen::utility::log;
static logger lg(logger_factory(id));

}

namespace dogen {
namespace cpp {

workflow::~workflow() noexcept { }

std::shared_ptr<formatters::registrar> workflow::registrar_;

cpp::formatters::registrar& workflow::registrar() {
    if (!registrar_)
        registrar_ = std::make_shared<cpp::formatters::registrar>();

    return *registrar_;
}

settings::settings workflow::
create_settings_activty(const std::forward_list<dynamic::field_definition>& fds,
    const sml::model& m) const {
    settings::workflow w;
    return w.execute(fds, m);
}

std::forward_list<std::shared_ptr<formattables::formattable> >
workflow::create_formattables_activty(const settings::selector& s,
    const formatters::container& c, const sml::model& m) const {
    formattables::workflow w;
    return w.execute(s, c, m);
}

std::forward_list<dogen::formatters::file>
workflow::format_activty(const settings::selector& s,
    const formatters::container& c,
    const std::forward_list<std::shared_ptr<formattables::formattable> >&
    f) const {
    formatters::workflow w;
    return w.execute(s, c, f);
}

std::string workflow::id() const {
    return ::id;
}

std::vector<boost::filesystem::path> workflow::managed_directories() const {
    std::vector<boost::filesystem::path> r;
    return r;
}

void workflow::validate() const {
    BOOST_LOG_SEV(lg, debug) << "Validating c++ backend workflow.";

    registrar().validate();
    const auto& c(registrar().formatter_container());
    BOOST_LOG_SEV(lg, debug) << "Found "
                             << std::distance(
                                 c.class_formatters().begin(),
                                 c.class_formatters().end())
                             << " registered class formatter(s): ";

    BOOST_LOG_SEV(lg, debug) << "Listing all class formatters.";
    for (const auto& f : c.class_formatters())
        BOOST_LOG_SEV(lg, debug) << "Name: '" << f->formatter_name() << "'";

    BOOST_LOG_SEV(lg, debug) << "Finished validating c++ backend workflow.";
}

std::forward_list<dogen::formatters::file>
workflow::generate(const sml::model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Started C++ backend.";

    validate();
    const auto& fds(dynamic::workflow::registrar().field_definitions());
    const auto s(create_settings_activty(fds, m));
    const auto& c(registrar().formatter_container());
    const auto f(create_formattables_activty(s, c, m));
    const auto r(format_activty(s, c, f));

    BOOST_LOG_SEV(lg, debug) << "Finished C++ backend.";
    return r;
}

} }
