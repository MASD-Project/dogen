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
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/sml/types/string_converter.hpp"
#include "dogen/sml/types/all_model_items_traversal.hpp"
#include "dogen/cpp/io/settings/local_settings_io.hpp"
#include "dogen/cpp/types/settings/type_settings_factory.hpp"
#include "dogen/cpp/types/settings/facet_settings_factory.hpp"
#include "dogen/cpp/types/settings/formatter_settings_factory.hpp"
#include "dogen/cpp/types/settings/local_settings_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("cpp.settings.workflow"));

}

namespace dogen {
namespace cpp {
namespace settings {

/**
 * @brief Generates all local settings.
 */
class generator {
public:
    generator(const dogen::formatters::general_settings_factory&
        general_settings_factory, const std::unordered_map<
            std::string,
            std::forward_list<dynamic::schema::field_definition> >&
        field_definitions_by_formatter_name);

private:
    /**
     * @brief Generates the local settings for the identity.
     */
    void generate(const sml::qname& qn, const dynamic::schema::object& o);

public:
    void operator()(const dogen::sml::type& t);
    void operator()(const dogen::sml::module& m);
    void operator()(const dogen::sml::concept& c);

public:
    const std::unordered_map<std::string, local_settings>& result() const;

private:
    const dogen::formatters::general_settings_factory&
    general_settings_factory_;
    const std::unordered_map<
        std::string, std::forward_list<dynamic::schema::field_definition>
        >& field_definitions_by_formatter_name_;
    std::unordered_map<std::string, local_settings> result_;
};

generator::generator(const dogen::formatters::general_settings_factory&
    general_settings_factory, const std::unordered_map<
        std::string, std::forward_list<dynamic::schema::field_definition> >&
    field_definitions_by_formatter_name)
    : general_settings_factory_(general_settings_factory),
      field_definitions_by_formatter_name_(
          field_definitions_by_formatter_name) {
}

void generator::
generate(const sml::qname& qn, const dynamic::schema::object& o) {
    std::pair<std::string, local_settings> pair;
    pair.first = sml::string_converter::convert(qn);

    auto& ls(pair.second);
    bool found_any_settings(false);
    ls.general_settings(general_settings_factory_.make_only_if_overriden(o));
    found_any_settings |= (bool)ls.general_settings();

    formatter_settings_factory fmt;
    ls.formatter_settings(
        fmt.make_local_settings(field_definitions_by_formatter_name_, o));
    found_any_settings |= !ls.formatter_settings().empty();

    facet_settings_factory fct;
    ls.facet_settings(
        fct.make_local_settings(field_definitions_by_formatter_name_, o));
    found_any_settings |= !ls.facet_settings().empty();

    type_settings_factory tsf;
    ls.type_settings(tsf.make(o));
    found_any_settings |= (bool)ls.type_settings();

    if (found_any_settings)
        result_.insert(pair);
}

void generator::operator()(const dogen::sml::type& t) {
    generate(t.name(), t.extensions());
}

void generator::operator()(const dogen::sml::module& m) {
    generate(m.name(), m.extensions());
}

void generator::operator()(const dogen::sml::concept& c) {
    generate(c.name(), c.extensions());
}

const std::unordered_map<std::string, local_settings>&
generator::result() const {
    return result_;
}

std::unordered_map<std::string, local_settings>
local_settings_factory::make(const dogen::formatters::general_settings_factory&
    general_settings_factory, const dynamic::schema::indexer& idx,
    const sml::model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Building all local settings.";

    const auto& fds(idx.field_definitions_by_formatter_name());
    generator g(general_settings_factory, fds);
    sml::all_model_items_traversal(m, g);

    BOOST_LOG_SEV(lg, debug) << "Finished building local settings.";
    BOOST_LOG_SEV(lg, debug) << "Local settings: " << g.result();
    return g.result();
}

} } }
