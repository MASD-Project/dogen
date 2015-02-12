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
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/sml/io/object_types_io.hpp"
#include "dogen/sml/types/string_converter.hpp"
#include "dogen/sml/types/all_model_items_traversal.hpp"
#include "dogen/cpp/types/formattables/name_builder.hpp"
#include "dogen/cpp/io/formatters/formatter_types_io.hpp"
#include "dogen/cpp/io/formattables/file_properties_io.hpp"
#include "dogen/cpp/types/formattables/building_error.hpp"
#include "dogen/cpp/types/formattables/file_properties_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("cpp.formattables.file_properties_factory"));

const std::string duplicate_formatter_name("Duplicate formatter name: ");
const std::string duplicate_qname("Duplicate qname: ");
const std::string unsupported_object_type("Object type is not supported: ");

}

namespace dogen {
namespace cpp {
namespace formattables {

/**
 * @brief Generates all file properties.
 */
class generator {
public:
    generator(const settings::selector& s,
        const provider_selector_interface& ps) : selector_(s),
                                                 provider_selector_(ps) { }

private:
    /**
     * @brief Generates all of the file names for the formatters and
     * qualified name.
     */
    std::pair<sml::qname, std::unordered_map<std::string, file_properties> >
    generate(const std::forward_list<
            std::shared_ptr<formattables::provider_interface> >& providers,
        const sml::qname& qn) const;

public:
    void operator()(const dogen::sml::object& o);
    void operator()(const dogen::sml::enumeration& e);
    void operator()(const dogen::sml::primitive& p);
    void operator()(const dogen::sml::module& m);
    void operator()(const dogen::sml::concept& c);

public:
    const std::unordered_map<sml::qname,
                             std::unordered_map<std::string, file_properties>
                             >& result() const;

private:
    const settings::selector& selector_;
    const provider_selector_interface& provider_selector_;
    std::unordered_map<sml::qname,
                       std::unordered_map<std::string, file_properties>
                       > result_;
};

std::pair<sml::qname,
          std::unordered_map<std::string, file_properties>
          >
generator::generate(const std::forward_list<
        std::shared_ptr<formattables::provider_interface> >& providers,
    const sml::qname& qn) const {

    std::pair<sml::qname, std::unordered_map<std::string, file_properties>> r;

    r.first = qn;
    auto& props(r.second);
    for (const auto p : providers) {
        const auto fp(p->provide_file_properties(selector_, qn));
        const auto i(props.insert(std::make_pair(p->formatter_name(), fp)));

        if (!i.second) {
            BOOST_LOG_SEV(lg, error) << duplicate_formatter_name
                                     << p->formatter_name();
            BOOST_THROW_EXCEPTION(
                building_error(duplicate_formatter_name + p->formatter_name()));
        }
    }
    return r;
}

void generator::operator()(const dogen::sml::object& o) {
    const auto qn(o.name());
    const auto ot(o.object_type());
    const auto& p(provider_selector_.select_providers_for_object(ot));

    // FIXME: p can be empty for now
    if (!p.empty()) {
        const auto pair(result_.insert(generate(p, qn)));
        const bool inserted(pair.second);
        if (!inserted) {
            const auto n(sml::string_converter::convert(o.name()));
            BOOST_LOG_SEV(lg, error) << duplicate_qname << n;
            BOOST_THROW_EXCEPTION(building_error(duplicate_qname + n));
        }
    }
}

void generator::operator()(const dogen::sml::enumeration& /*e*/) { }

void generator::operator()(const dogen::sml::primitive& /*p*/) { }

void generator::operator()(const dogen::sml::module& /*m*/) { }

void generator::operator()(const dogen::sml::concept& /*c*/) { }

const std::unordered_map<sml::qname,
                         std::unordered_map<std::string, file_properties>
                         >& generator::result() const {
    return result_;
}

std::unordered_map<
    sml::qname,
    std::unordered_map<std::string, file_properties>
    >
file_properties_factory::make(const settings::selector& s,
    const provider_selector_interface& ps, const sml::model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Building all file properties.";

    generator g(s, ps);
    sml::all_model_items_traversal(m, g);

    BOOST_LOG_SEV(lg, debug) << "Finished building file properties.";
    BOOST_LOG_SEV(lg, debug) << "File properties: " << g.result();
    return g.result();
}

} } }
