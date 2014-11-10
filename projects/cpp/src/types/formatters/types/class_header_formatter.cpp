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
#include <sstream>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/formatters/types/indent_filter.hpp"
#include "dogen/cpp/types/identifier_name_builder.hpp"
#include "dogen/cpp/types/formatters/types/traits.hpp"
#include "dogen/cpp/types/formatters/formatting_error.hpp"
#include "dogen/cpp/types/formatters/boilerplate_formatter.hpp"
#include "dogen/cpp/types/formatters/types/class_header_formatter.hpp"

namespace {

const std::string formatter_id("cpp.formatters.types.class_header_formatter");
const std::string relative_path_for_formatter_not_found(
    "Relative path for formatter not found. Formatter: ");

using namespace dogen::utility::log;
static logger lg(logger_factory(formatter_id));

// FIXME
const dogen::cpp::includes empty_includes = dogen::cpp::includes();

}

namespace dogen {
namespace cpp {
namespace formatters {
namespace types {

class includes_builder : public includes_builder_interface {
public:
    explicit includes_builder(
        const std::unordered_map<path_spec_key, boost::filesystem::path>&
        relative_paths);

public:
    std::string id() const override { return ::formatter_id; }
    unsigned int required_passes() const override { return 1; }
    bool consume_last() const override { return false; }
    void consume(const sml::model& /*model*/, const unsigned int /*pass*/,
        const sml::concept& /*target*/) const override { }
    void consume(const sml::model& /*model*/, const unsigned int /*pass*/,
        const sml::module& /*target*/) const override { }
    void consume(const sml::model& /*model*/, const unsigned int /*pass*/,
        const sml::enumeration& /*target*/) const override { }
    virtual void consume(const sml::model& /*model*/,
        const unsigned int /*pass*/,
        const sml::primitive& /*target*/) const override { }
    void consume(const sml::model& model, const unsigned int pass,
        const sml::object& target) const override;

public:
    std::string formatter_id() const override { return ::formatter_id; }
    std::unordered_map<path_spec_key, includes>
    includes_for_path_spec_key() const override;

private:
    /*const std::unordered_map<path_spec_key, boost::filesystem::path>&
      relative_paths_;*/
};

includes_builder::includes_builder(
    const std::unordered_map<path_spec_key, boost::filesystem::path>&
    /*relative_paths*/) /*: relative_paths_(relative_paths)*/ { }

void includes_builder::consume(const sml::model& /*model*/,
    const unsigned int /*pass*/, const sml::object& /*target*/) const {
}

std::unordered_map<path_spec_key, includes> includes_builder::
includes_for_path_spec_key() const {
    std::unordered_map<path_spec_key, includes> r;
    return r;
}

boost::filesystem::path class_header_formatter::
get_relative_path(const class_info& c) const {
    const auto i(c.relative_path_for_formatter().find(::formatter_id));
    if (i == c.relative_path_for_formatter().end()) {
        return boost::filesystem::path();
        /*
          FIXME
        BOOST_LOG_SEV(lg, error) << relative_path_for_formatter_not_found
                                 << ::formatter_id;

        BOOST_THROW_EXCEPTION(formatting_error(
                relative_path_for_formatter_not_found +
                ::formatter_id));
        */
    }
    return i->second;
}

std::string class_header_formatter::facet_id() const {
    return traits::facet_id;
}

std::string class_header_formatter::formatter_id() const {
    return ::formatter_id;
}

dogen::formatters::file class_header_formatter::
format(const class_info& c, const settings_bundle& sb) const {
    boilerplate_formatter boilerplate_;
    BOOST_LOG_SEV(lg, debug) << "Formatting type: " << c.name();

    std::ostringstream s;
    boost::iostreams::filtering_ostream fo;
    dogen::formatters::indent_filter::push(fo, 4);
    fo.push(s);

    const auto rp(get_relative_path(c));
    dogen::cpp::formatters::boilerplate_formatter f;
    const auto a(sb.general_settings().annotation());
    f.format_begin(fo, a, empty_includes, rp);
    f.format_end(fo, a, rp);

    BOOST_LOG_SEV(lg, debug) << "Formatted type: " << c.name();
    dogen::formatters::file r;
    r.content(s.str());
    r.relative_path(rp);

    BOOST_LOG_SEV(lg, debug) << "filename: "
                             << r.relative_path().generic_string();
    BOOST_LOG_SEV(lg, debug) << "content: " << r.content();
    return r;
}

boost::filesystem::path class_header_formatter::
make_file_name(const settings_bundle& sb, const sml::qname& qn) const {
    identifier_name_builder b;
    return b.header_file_name(sb, qn);
}

std::shared_ptr<includes_builder_interface>
class_header_formatter::make_includes_builder(
    const std::unordered_map<path_spec_key, boost::filesystem::path>&
    relative_paths) const {
    return std::make_shared<includes_builder>(relative_paths);
}

} } } }
