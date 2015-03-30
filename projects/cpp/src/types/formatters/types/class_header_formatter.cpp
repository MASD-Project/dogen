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
#include <memory>
#include <sstream>
#include <boost/make_shared.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/formatters/types/indent_filter.hpp"
#include "dogen/dynamic/expansion/types/expansion_error.hpp"
#include "dogen/dynamic/schema/types/field_instance_factory.hpp"
#include "dogen/sml/types/string_converter.hpp"
#include "dogen/cpp/types/traits.hpp"
#include "dogen/cpp/types/settings/path_expander.hpp"
#include "dogen/cpp/types/formatters/traits.hpp"
#include "dogen/cpp/types/formatters/io/traits.hpp"
#include "dogen/cpp/types/formatters/types/traits.hpp"
#include "dogen/cpp/types/formatters/formatting_error.hpp"
#include "dogen/cpp/types/formatters/inclusion_constants.hpp"
#include "dogen/cpp/types/formatters/boilerplate_formatter.hpp"
#include "dogen/cpp/types/formatters/types/class_header_formatter.hpp"

namespace {

using namespace dogen::utility::log;
using namespace dogen::cpp::formatters::types;
static logger lg(logger_factory(traits::class_header_formatter_name()));

const std::string formatter_settings_not_found(
    "Could not find settings for formatter: ");
const std::string file_path_not_set(
    "File path for formatter is not set. Formatter: ");
const std::string header_guard_not_set(
    "Header guard for formatter is not set. Formatter: ");
const std::string include_directive_not_set(
    "Include directive for formatter is not set. Formatter: ");

const std::string no_fields_for_formatter(
    "Could not find any fields for formatter: ");
const std::string field_definition_not_found(
    "Could not find expected field definition: ");
const std::string qname_not_found("Could not find qualified name in model: ");

}

namespace dogen {
namespace cpp {
namespace formatters {
namespace types {

void null_deleter(const sml::model *) {}

class inclusion_expander final : public dynamic::expansion::expander_interface {
public:
    ~inclusion_expander() noexcept { }

private:
    struct formatter_properties {
        dynamic::schema::field_definition inclusion_dependency;
        std::shared_ptr<const sml::model> model;
    };

public:
    std::string name() const override;

    const std::forward_list<std::string>& dependencies() const override;

    void setup(const dynamic::expansion::expansion_context& ec) override;

    void expand(const sml::qname& qn, const dynamic::schema::scope_types& st,
        dynamic::schema::object& o) const override;

private:
    boost::optional<formatter_properties> formatter_properties_;
};

std::string inclusion_expander::name() const {
    static std::string name("cpp.types.inclusion_expander");
    return name;
}

const std::forward_list<std::string>& inclusion_expander::
dependencies() const {
    static std::forward_list<std::string>
        r { settings::path_expander::static_name() };
    return r;
}

void inclusion_expander::
setup(const dynamic::expansion::expansion_context& ec) {
    const auto fn(traits::class_header_formatter_name());
    const auto& rp(ec.repository());
    const auto i(rp.field_definitions_by_formatter_name().find(fn));
    if (i == rp.field_definitions_by_formatter_name().end()) {
        BOOST_LOG_SEV(lg, error) << no_fields_for_formatter << fn;
        BOOST_THROW_EXCEPTION(dynamic::expansion::expansion_error(
                no_fields_for_formatter + fn));
    }

    formatter_properties_ = formatter_properties();
    formatter_properties_->model =
        std::shared_ptr<const sml::model>(&ec.model(), &null_deleter);

    bool found_inclusion_dependency(false);
    for (const auto fd : i->second) {
        if (fd.name().simple() == cpp::traits::inclusion_dependency()) {
            formatter_properties_->inclusion_dependency = fd;
            found_inclusion_dependency = true;
        }
    }

    if (!found_inclusion_dependency) {
        BOOST_LOG_SEV(lg, error) << field_definition_not_found
                                 << cpp::traits::inclusion_dependency()
                                 << " for formatter: " << fn;
        BOOST_THROW_EXCEPTION(
            dynamic::expansion::expansion_error(field_definition_not_found +
                cpp::traits::inclusion_dependency()));
    }
}

void inclusion_expander::
expand(const sml::qname& qn, const dynamic::schema::scope_types& /*st*/,
    dynamic::schema::object& o) const {

    const auto& m(*formatter_properties_->model);

    // we only handle includes for objects.
    const auto i(m.objects().find(qn));
    if (i == m.objects().end())
        return;

    std::list<std::string> includes;

    // algorithm: domain headers need it for the swap function.
    includes.push_back(inclusion_constants::std::algorithm());

    // settings::selector s(formatter_properties_->settings);
    // const auto io_fn(formatters::io::traits::facet_name());
    // const bool io_enabled(s.is_formatter_enabled(io_fn));

    // const auto types_fn(formatters::types::traits::facet_name());
    // const bool use_integrated_io(s.is_facet_integrated(io_fn));

    // if (io_enabled && use_integrated_io)
    //     includes.push_back(inclusion_constants::std::iosfwd());

    // const auto& o(pair.second);
    // return r;

    dynamic::schema::field_instance_factory f;
    o.fields()[formatter_properties_->inclusion_dependency.name().qualified()] =
        f.make_text_collection(includes);
}

void class_header_formatter::validate(
    const settings::formatter_settings& fs) const {

    const auto& fn(ownership_hierarchy().formatter_name());
    if (fs.file_path().empty()) {
        BOOST_LOG_SEV(lg, error) << file_path_not_set << fn;
        BOOST_THROW_EXCEPTION(formatting_error(file_path_not_set + fn));
    }

    if (!fs.header_guard() || fs.header_guard()->empty()) {
        BOOST_LOG_SEV(lg, error) << header_guard_not_set << fn;
        BOOST_THROW_EXCEPTION(formatting_error(header_guard_not_set + fn));
    }
}

settings::formatter_settings class_header_formatter::
formatter_settings_for_formatter(const formattables::class_info& c) const {
    const auto& fs(c.settings().formatter_settings());
    const auto& fn(ownership_hierarchy().formatter_name());
    const auto i(fs.find(fn));
    if (i == fs.end()) {
        BOOST_LOG_SEV(lg, error) << formatter_settings_not_found << fn;

        BOOST_THROW_EXCEPTION(
            formatting_error(formatter_settings_not_found + fn));
    }
    return i->second;
}

boost::shared_ptr<dynamic::expansion::expander_interface>
class_header_formatter::create_expander() const {
    return boost::make_shared<inclusion_expander>();
}

dynamic::schema::ownership_hierarchy
class_header_formatter::ownership_hierarchy() const {
    static dynamic::schema::ownership_hierarchy
        r(formatters::traits::model_name(), traits::facet_name(),
            traits::class_header_formatter_name(),
            formatters::traits::header_formatter_group_name());
    return r;
}

file_types class_header_formatter::file_type() const {
    return file_types::cpp_header;
}

dogen::formatters::file
class_header_formatter::format(const formattables::class_info& c) const {
    boilerplate_formatter boilerplate_;
    BOOST_LOG_SEV(lg, debug) << "Formatting type: " << c.name();

    std::ostringstream ss;
    boost::iostreams::filtering_ostream fo;
    dogen::formatters::indent_filter::push(fo, 4);
    fo.push(ss);

    const auto fs(formatter_settings_for_formatter(c));
    validate(fs);

    const auto hg(*fs.header_guard());
    dogen::cpp::formatters::boilerplate_formatter f;
    const auto gs(c.settings().general_settings());
    if (gs)
        f.format_begin(fo, gs->annotation(), fs.inclusion_dependencies(), hg);

    // do formatting.

    if (gs)
        f.format_end(fo, gs->annotation(), hg);

    BOOST_LOG_SEV(lg, debug) << "Formatted type: " << c.name();
    dogen::formatters::file r;
    r.content(ss.str());
    r.path(fs.file_path());

    BOOST_LOG_SEV(lg, debug) << "Filename: "
                             << r.path().generic_string();
    BOOST_LOG_SEV(lg, debug) << "Content: " << r.content();
    return r;
}

} } } }
