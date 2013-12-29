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
#include "dogen/sml/types/meta_data_error.hpp"
#include "dogen/sml/types/all_model_items_traversal.hpp"
#include "dogen/sml/types/tags.hpp"
#include "dogen/sml/types/enumeration.hpp"
#include "dogen/sml/types/object.hpp"
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/sml/types/meta_data_tagger.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("sml.meta_data_tagger"));
const std::string empty;
const std::string original_parent_not_found(
    "Failed to find original parent for type: ");
const std::string too_many_original_parents(
    "Type has too many original parents, expected one: ");

const std::string cpp_header_extension(".hpp");
const std::string cpp_implementation_extension(".cpp");
const std::string cpp_includer_file_name("all");

const std::string empty_postfix;
const std::string types_postfix;
const std::string forward_decls_postfix("_fwd");
const std::string io_postfix("_io");
const std::string hash_postfix("_hash");
const std::string serialization_postfix("_ser");
const std::string test_data_postfix("_td");
const std::string odb_postfix("_pragmas");

const std::string source_directory("src");
const std::string include_directory("include");
const std::string types_directory("types");
const std::string io_directory("io");
const std::string hash_directory("hash");
const std::string serialization_directory("serialization");
const std::string test_data_directory("test_data");
const std::string odb_directory("odb");

const std::string scope_operator("::");

const bool is_header_file(true);

}

namespace dogen {
namespace sml {

class meta_data_tagger::context {
public:
    context(sml::model& m) : model_(m) { }

public:
    sml::model& model() { return model_; }

private:
    sml::model& model_;
};

void meta_data_tagger::
from_settings(const config::cpp_settings& s, model& m) const {
    meta_data_writer writer(m.meta_data());

    writer.add_if_key_not_found(tags::cpp::split_project,
        s.split_project() ? tags::bool_false : tags::bool_true);

    writer.add_if_key_not_found(tags::cpp::header_file_extension,
        s.header_extension());

    writer.add_if_key_not_found(tags::cpp::implementation_file_extension,
        s.source_extension());

    writer.add_if_key_not_found(tags::cpp::enable_facet_folders,
        s.disable_facet_folders() ? tags::bool_false : tags::bool_true);

    writer.add_if_key_not_found(tags::cpp::enable_unique_file_names,
        s.disable_unique_file_names() ?
        tags::bool_false : tags::bool_true);

    using config::cpp_facet_types;
    if (is_facet_enabled(s.enabled_facets(), cpp_facet_types::types)) {
        writer.add_if_key_not_found(tags::cpp::types::enabled, tags::bool_true);

        writer.add_if_key_not_found(
            tags::cpp::types::generate_complete_constructor,
            s.disable_complete_constructor() ?
            tags::bool_false : tags::bool_true);

        writer.add_if_key_not_found(
            tags::cpp::types::includers_file::generate,
            s.disable_facet_includers() ?
            tags::bool_false : tags::bool_true);

        writer.add_if_key_not_found(
            tags::cpp::types::directory_name,
            s.domain_facet_folder());
    } else {
        writer.add_if_key_not_found(tags::cpp::types::enabled,
            tags::bool_false);
    }

    if (is_facet_enabled(s.enabled_facets(), cpp_facet_types::hash)) {
        writer.add_if_key_not_found(tags::cpp::hash::standard::enabled,
            tags::bool_true);

        writer.add_if_key_not_found(
            tags::cpp::hash::standard::includers_file::generate,
            s.disable_facet_includers() ?
            tags::bool_false : tags::bool_true);

        writer.add_if_key_not_found(
            tags::cpp::hash::standard::directory_name,
            s.hash_facet_folder());
    } else {
        writer.add_if_key_not_found(tags::cpp::hash::standard::enabled,
            tags::bool_false);
    }

    if (is_facet_enabled(s.enabled_facets(), cpp_facet_types::io)) {
        writer.add_if_key_not_found(tags::cpp::io::enabled, tags::bool_true);

        writer.add_if_key_not_found(
            tags::cpp::io::enable_integrated_io,
            s.use_integrated_io() ?
            tags::bool_true : tags::bool_false);

        writer.add_if_key_not_found(
            tags::cpp::io::includers_file::generate,
            s.disable_facet_includers() ?
            tags::bool_false : tags::bool_true);

        writer.add_if_key_not_found(
            tags::cpp::io::directory_name,
            s.io_facet_folder());
    } else {
        writer.add_if_key_not_found(tags::cpp::io::enabled,
            tags::bool_false);
    }

    if (is_facet_enabled(s.enabled_facets(), cpp_facet_types::serialization)) {
        writer.add_if_key_not_found(tags::cpp::serialization::boost::enabled,
            tags::bool_true);

        writer.add_if_key_not_found(
            tags::cpp::serialization::boost::enable_xml_serialization,
            s.disable_xml_serialization() ?
            tags::bool_false : tags::bool_true);

        writer.add_if_key_not_found(
            tags::cpp::serialization::boost::includers_file::generate,
            s.disable_facet_includers() ?
            tags::bool_false : tags::bool_true);

        writer.add_if_key_not_found(
            tags::cpp::serialization::boost::directory_name,
            s.serialization_facet_folder());
    } else {
        writer.add_if_key_not_found(tags::cpp::serialization::boost::enabled,
            tags::bool_false);
    }

    if (is_facet_enabled(s.enabled_facets(), cpp_facet_types::test_data)) {
        writer.add_if_key_not_found(tags::cpp::test_data::enabled,
            tags::bool_true);

        writer.add_if_key_not_found(
            tags::cpp::test_data::includers_file::generate,
            s.disable_facet_includers() ?
            tags::bool_false : tags::bool_true);

        writer.add_if_key_not_found(
            tags::cpp::test_data::directory_name,
            s.test_data_facet_folder());
    } else {
        writer.add_if_key_not_found(tags::cpp::test_data::enabled,
            tags::bool_false);
    }

    if (is_facet_enabled(s.enabled_facets(), cpp_facet_types::odb)) {
        writer.add_if_key_not_found(tags::cpp::odb::enabled, tags::bool_true);

        writer.add_if_key_not_found(
            tags::cpp::odb::includers_file::generate,
            s.disable_facet_includers() ?
            tags::bool_false : tags::bool_true);

        writer.add_if_key_not_found(
            tags::cpp::odb::directory_name,
            s.odb_facet_folder());
    } else {
        writer.add_if_key_not_found(tags::cpp::odb::enabled, tags::bool_false);
    }
}

bool meta_data_tagger::is_facet_enabled(
    const std::set<config::cpp_facet_types>& enabled_facets,
    const config::cpp_facet_types facet) const {
    const auto i(enabled_facets.find(facet));
    return i != enabled_facets.end();
}

std::string meta_data_tagger::cpp_qualified_name(const sml::qname& qn) const {
    std::ostringstream s;

    if (!qn.model_name().empty())
        s << qn.model_name() << scope_operator;

    bool is_first(false);
    for (const auto& p : qn.module_path()) {
        if (is_first)
            s << scope_operator;
        s << p;
    }

    s << qn.simple_name();
    return s.str();
}

std::string meta_data_tagger::filename_for_qname(
    const meta_data_reader& reader, const bool is_header, const qname& qn,
    const std::string& facet_directory, const std::string& facet_postfix,
    const std::string& additional_postfix) const {

    boost::filesystem::path r;
    if (reader.is_true(tags::cpp::split_project)) {
        for(auto n : qn.external_module_path())
            r /= n;
    }

    if (reader.is_true(tags::cpp::split_project))
        r /= qn.model_name();
    else if (is_header) {
        for(auto n : qn.external_module_path())
            r /= n;
        r /= qn.model_name();
    }

    if (reader.is_true(tags::cpp::enable_facet_folders))
        r /= facet_directory;

    for(auto n : qn.module_path())
        r /= n;

    std::ostringstream stream;
    stream << qn.simple_name() << additional_postfix;

    if (reader.is_true(tags::cpp::enable_unique_file_names))
        stream << facet_postfix;

    if (is_header)
        stream << reader.get(tags::cpp::header_file_extension);
    else
        stream << reader.get(tags::cpp::implementation_file_extension);

    r /= stream.str();

    return r.generic_string();
}

void meta_data_tagger::copy_model_tags(meta_data_writer& writer) const {
    meta_data_reader reader(context_->model().meta_data());

    writer.add_if_key_not_found(tags::copyright_holder,
        reader.get(tags::copyright_holder));

    writer.add_if_key_not_found(tags::generate_preamble,
        reader.get(tags::generate_preamble));

    if (reader.has_key(dogen::sml::tags::licence_name)) {
        writer.add_if_key_not_found(dogen::sml::tags::licence_name,
            reader.get(dogen::sml::tags::licence_name));
    }

    if (reader.has_key(dogen::sml::tags::modeline_group_name)) {
        writer.add_if_key_not_found(dogen::sml::tags::modeline_group_name,
            reader.get(dogen::sml::tags::modeline_group_name));
    }

    if (reader.has_key(dogen::sml::tags::code_generation_marker::message)) {
        writer.add_if_key_not_found(
            dogen::sml::tags::code_generation_marker::message,
            reader.get(dogen::sml::tags::code_generation_marker::message));
    }

    writer.add_if_key_not_found(
        dogen::sml::tags::code_generation_marker::add_warning,
        reader.get(dogen::sml::tags::code_generation_marker::add_warning));

    writer.add_if_key_not_found(
        dogen::sml::tags::code_generation_marker::add_date_time,
        reader.get(dogen::sml::tags::code_generation_marker::add_date_time));

    writer.add_if_key_not_found(tags::cpp::header_file_extension,
        reader.get(tags::cpp::header_file_extension));

    writer.add_if_key_not_found(tags::cpp::implementation_file_extension,
        reader.get(tags::cpp::implementation_file_extension));

    writer.add_if_key_not_found(tags::cpp::enable_facet_folders,
        reader.get(tags::cpp::enable_facet_folders));

    writer.add_if_key_not_found(tags::cpp::enable_unique_file_names,
        reader.get(tags::cpp::enable_unique_file_names));

    writer.add_if_key_not_found(tags::cpp::forward_declaration_postfix,
        reader.get(tags::cpp::forward_declaration_postfix));

    writer.add_if_key_not_found(tags::cpp::types::enabled,
        reader.get(tags::cpp::types::enabled));

    writer.add_if_key_not_found(tags::cpp::hash::standard::enabled,
        reader.get(tags::cpp::hash::standard::enabled));

    writer.add_if_key_not_found(tags::cpp::serialization::boost::enabled,
        reader.get(tags::cpp::serialization::boost::enabled));

    writer.add_if_key_not_found(tags::cpp::io::enabled,
        reader.get(tags::cpp::io::enabled));

    writer.add_if_key_not_found(tags::cpp::test_data::enabled,
        reader.get(tags::cpp::test_data::enabled));

    writer.add_if_key_not_found(tags::cpp::odb::enabled,
        reader.get(tags::cpp::odb::enabled));
}

void meta_data_tagger::visit(sml::primitive& p) const {
    meta_data_writer writer(p.meta_data());
    writer.add_if_key_not_found(tags::cpp::types::is_simple_type,
        tags::bool_true);
}

void meta_data_tagger::visit(sml::enumeration& e) const {
    meta_data_writer writer(e.meta_data());
    writer.add_if_key_not_found(tags::cpp::types::is_simple_type,
        tags::bool_true);
}

void meta_data_tagger::visit(sml::object& o) const {
    tag(o);
}

void meta_data_tagger::operator()(type& t) const {
    meta_data_writer writer(t.meta_data());
    copy_model_tags(writer);

    meta_data_reader reader(t.meta_data());
    writer.add_if_key_not_found(tags::cpp::types::qualified_name,
        cpp_qualified_name(t.name()));

    using gt = generation_types;
    if (reader.is_true(tags::cpp::types::enabled)) {
        const auto header_fn(filename_for_qname(reader, is_header_file,
                t.name(), reader.get(tags::cpp::types::directory_name),
                reader.get(tags::cpp::types::postfix),
                empty_postfix));

        writer.add_if_key_not_found(
            tags::cpp::types::header_file::file_name, header_fn);

        writer.add_if_key_not_found(
            tags::cpp::types::header_file::is_system, tags::bool_false);

        if (t.generation_type() == gt::full_generation) {
            writer.add_if_key_not_found(
                tags::cpp::types::header_file::generate, tags::bool_true);
            writer.add_if_key_not_found(
                tags::cpp::types::header_file::overwrite, tags::bool_true);
        } else if (t.generation_type() == gt::partial_generation) {
            writer.add_if_key_not_found(
                tags::cpp::types::header_file::generate, tags::bool_true);
            writer.add_if_key_not_found(
                tags::cpp::types::header_file::overwrite, tags::bool_false);
        } else if (t.generation_type() == gt::no_generation) {
            writer.add_if_key_not_found(
                tags::cpp::types::header_file::generate, tags::bool_false);
            writer.add_if_key_not_found(
                tags::cpp::types::header_file::overwrite, tags::bool_false);
        }

        const auto impl_fn(filename_for_qname(reader, !is_header_file,
                t.name(), reader.get(tags::cpp::types::directory_name),
                reader.get(tags::cpp::types::postfix),
                empty_postfix));

        writer.add_if_key_not_found(
            tags::cpp::types::implementation_file::file_name, impl_fn);

        writer.add_if_key_not_found(
            tags::cpp::types::implementation_file::is_system, tags::bool_false);

        if (t.generation_type() == gt::full_generation) {
            writer.add_if_key_not_found(
                tags::cpp::types::implementation_file::generate,
                tags::bool_true);
            writer.add_if_key_not_found(
                tags::cpp::types::implementation_file::overwrite,
                tags::bool_true);
        } else if (t.generation_type() == gt::partial_generation) {
            writer.add_if_key_not_found(
                tags::cpp::types::implementation_file::generate,
                tags::bool_true);
            writer.add_if_key_not_found(
                tags::cpp::types::implementation_file::overwrite,
                tags::bool_false);
        } else if (t.generation_type() == gt::no_generation) {
            writer.add_if_key_not_found(
                tags::cpp::types::implementation_file::generate,
                tags::bool_false);
            writer.add_if_key_not_found(
                tags::cpp::types::implementation_file::overwrite,
                tags::bool_false);
        }

        const auto fwd_fn(filename_for_qname(reader, is_header_file,
                t.name(), reader.get(tags::cpp::types::directory_name),
                reader.get(tags::cpp::types::postfix),
                empty_postfix));

        writer.add_if_key_not_found(
            tags::cpp::types::forward_declarations_file::file_name, fwd_fn);

        writer.add_if_key_not_found(
            tags::cpp::types::forward_declarations_file::is_system,
            tags::bool_false);

        if (t.generation_type() == gt::full_generation) {
            writer.add_if_key_not_found(
                tags::cpp::types::forward_declarations_file::generate,
                tags::bool_true);
            writer.add_if_key_not_found(
                tags::cpp::types::forward_declarations_file::overwrite,
                tags::bool_true);
        } else if (t.generation_type() == gt::partial_generation) {
            writer.add_if_key_not_found(
                tags::cpp::types::forward_declarations_file::generate,
                tags::bool_true);
            writer.add_if_key_not_found(
                tags::cpp::types::forward_declarations_file::overwrite,
                tags::bool_true);
        } else if (t.generation_type() == gt::no_generation) {
            writer.add_if_key_not_found(
                tags::cpp::types::forward_declarations_file::generate,
                tags::bool_false);
            writer.add_if_key_not_found(
                tags::cpp::types::forward_declarations_file::overwrite,
                tags::bool_false);
        }
    }

    if (reader.is_true(tags::cpp::hash::standard::enabled)) {
        const auto header_fn(filename_for_qname(reader, is_header_file,
                t.name(),
                reader.get(tags::cpp::hash::standard::directory_name),
                reader.get(tags::cpp::hash::standard::postfix),
                empty_postfix));

        writer.add_if_key_not_found(
            tags::cpp::hash::standard::header_file::file_name, header_fn);

        writer.add_if_key_not_found(
            tags::cpp::hash::standard::header_file::is_system,
            tags::bool_false);

                if (t.generation_type() == gt::full_generation) {
            writer.add_if_key_not_found(
                tags::cpp::hash::standard::header_file::generate,
                tags::bool_true);
            writer.add_if_key_not_found(
                tags::cpp::hash::standard::header_file::overwrite,
                tags::bool_true);
        } else if (t.generation_type() == gt::partial_generation) {
            writer.add_if_key_not_found(
                tags::cpp::hash::standard::header_file::generate,
                tags::bool_true);
            writer.add_if_key_not_found(
                tags::cpp::hash::standard::header_file::overwrite,
                tags::bool_false);
        } else if (t.generation_type() == gt::no_generation) {
            writer.add_if_key_not_found(
                tags::cpp::hash::standard::header_file::generate,
                tags::bool_false);
            writer.add_if_key_not_found(
                tags::cpp::hash::standard::header_file::overwrite,
                tags::bool_false);
        }

        const auto impl_fn(filename_for_qname(reader, !is_header_file,
                t.name(),
                reader.get(tags::cpp::hash::standard::directory_name),
                reader.get(tags::cpp::hash::standard::postfix),
                empty_postfix));

        writer.add_if_key_not_found(
            tags::cpp::hash::standard::implementation_file::file_name, impl_fn);

        writer.add_if_key_not_found(
            tags::cpp::hash::standard::implementation_file::is_system,
            tags::bool_false);

        if (t.generation_type() == gt::full_generation) {
            writer.add_if_key_not_found(
                tags::cpp::hash::standard::implementation_file::generate,
                tags::bool_true);
            writer.add_if_key_not_found(
                tags::cpp::hash::standard::implementation_file::overwrite,
                tags::bool_true);
        } else if (t.generation_type() == gt::partial_generation) {
            writer.add_if_key_not_found(
                tags::cpp::hash::standard::implementation_file::generate,
                tags::bool_true);
            writer.add_if_key_not_found(
                tags::cpp::hash::standard::implementation_file::overwrite,
                tags::bool_false);
        } else if (t.generation_type() == gt::no_generation) {
            writer.add_if_key_not_found(
                tags::cpp::hash::standard::implementation_file::generate,
                tags::bool_false);
            writer.add_if_key_not_found(
                tags::cpp::hash::standard::implementation_file::overwrite,
                tags::bool_false);
        }
    }

    if (reader.is_true(tags::cpp::serialization::boost::enabled)) {
        const auto header_fn(filename_for_qname(reader, is_header_file,
                t.name(),
                reader.get(tags::cpp::serialization::boost::directory_name),
                reader.get(tags::cpp::serialization::boost::postfix),
                empty_postfix));

        writer.add_if_key_not_found(
            tags::cpp::serialization::boost::header_file::file_name, header_fn);

        writer.add_if_key_not_found(
            tags::cpp::serialization::boost::header_file::is_system,
            tags::bool_false);

        if (t.generation_type() == gt::full_generation) {
            writer.add_if_key_not_found(
                tags::cpp::serialization::boost::header_file::generate,
                tags::bool_true);
            writer.add_if_key_not_found(
                tags::cpp::serialization::boost::header_file::overwrite,
                tags::bool_true);
        } else if (t.generation_type() == gt::partial_generation) {
            writer.add_if_key_not_found(
                tags::cpp::serialization::boost::header_file::generate,
                tags::bool_true);
            writer.add_if_key_not_found(
                tags::cpp::serialization::boost::header_file::overwrite,
                tags::bool_false);
        } else if (t.generation_type() == gt::no_generation) {
            writer.add_if_key_not_found(
                tags::cpp::serialization::boost::header_file::generate,
                tags::bool_false);
            writer.add_if_key_not_found(
                tags::cpp::serialization::boost::header_file::overwrite,
                tags::bool_false);
        }

        const auto impl_fn(filename_for_qname(reader, !is_header_file,
                t.name(),
                reader.get(tags::cpp::serialization::boost::directory_name),
                reader.get(tags::cpp::serialization::boost::postfix),
                empty_postfix));

        writer.add_if_key_not_found(
            tags::cpp::serialization::boost::implementation_file::file_name,
            impl_fn);

        writer.add_if_key_not_found(
            tags::cpp::serialization::boost::implementation_file::is_system,
            tags::bool_false);

        if (t.generation_type() == gt::full_generation) {
            writer.add_if_key_not_found(
                tags::cpp::serialization::boost::implementation_file::generate,
                tags::bool_true);
            writer.add_if_key_not_found(
                tags::cpp::serialization::boost::implementation_file::overwrite,
                tags::bool_true);
        } else if (t.generation_type() == gt::partial_generation) {
            writer.add_if_key_not_found(
                tags::cpp::serialization::boost::implementation_file::generate,
                tags::bool_true);
            writer.add_if_key_not_found(
                tags::cpp::serialization::boost::implementation_file::overwrite,
                tags::bool_false);
        } else if (t.generation_type() == gt::no_generation) {
            writer.add_if_key_not_found(
                tags::cpp::serialization::boost::implementation_file::generate,
                tags::bool_false);
            writer.add_if_key_not_found(
                tags::cpp::serialization::boost::implementation_file::overwrite,
                tags::bool_false);
        }
    }

    if (reader.is_true(tags::cpp::io::enabled)) {
        const auto header_fn(filename_for_qname(reader, is_header_file,
                t.name(), reader.get(tags::cpp::io::directory_name),
                reader.get(tags::cpp::io::postfix),
                empty_postfix));

        writer.add_if_key_not_found(tags::cpp::io::header_file::file_name,
            header_fn);

        writer.add_if_key_not_found(tags::cpp::io::header_file::is_system,
            tags::bool_false);

        if (t.generation_type() == gt::full_generation) {
            writer.add_if_key_not_found(
                tags::cpp::io::header_file::generate,
                tags::bool_true);
            writer.add_if_key_not_found(
                tags::cpp::io::header_file::overwrite,
                tags::bool_true);
        } else if (t.generation_type() == gt::partial_generation) {
            writer.add_if_key_not_found(
                tags::cpp::io::header_file::generate,
                tags::bool_true);
            writer.add_if_key_not_found(
                tags::cpp::io::header_file::overwrite,
                tags::bool_false);
        } else if (t.generation_type() == gt::no_generation) {
            writer.add_if_key_not_found(
                tags::cpp::io::header_file::generate,
                tags::bool_false);
            writer.add_if_key_not_found(
                tags::cpp::io::header_file::overwrite,
                tags::bool_false);
        }

        const auto impl_fn(filename_for_qname(reader, !is_header_file,
                t.name(), reader.get(tags::cpp::io::directory_name),
                reader.get(tags::cpp::io::postfix),
                empty_postfix));

        writer.add_if_key_not_found(
            tags::cpp::io::implementation_file::file_name,
            impl_fn);

        writer.add_if_key_not_found(
            tags::cpp::io::implementation_file::is_system,
            tags::bool_false);

        if (t.generation_type() == gt::full_generation) {
            writer.add_if_key_not_found(
                tags::cpp::io::implementation_file::generate,
                tags::bool_true);
            writer.add_if_key_not_found(
                tags::cpp::io::implementation_file::overwrite,
                tags::bool_true);
        } else if (t.generation_type() == gt::partial_generation) {
            writer.add_if_key_not_found(
                tags::cpp::io::implementation_file::generate,
                tags::bool_true);
            writer.add_if_key_not_found(
                tags::cpp::io::implementation_file::overwrite,
                tags::bool_false);
        } else if (t.generation_type() == gt::no_generation) {
            writer.add_if_key_not_found(
                tags::cpp::io::implementation_file::generate,
                tags::bool_false);
            writer.add_if_key_not_found(
                tags::cpp::io::implementation_file::overwrite,
                tags::bool_false);
        }
    }

    if (reader.is_true(tags::cpp::test_data::enabled)) {
        const auto header_fn(filename_for_qname(reader, is_header_file,
                t.name(), reader.get(tags::cpp::test_data::directory_name),
                reader.get(tags::cpp::test_data::postfix),
                empty_postfix));

        writer.add_if_key_not_found(
            tags::cpp::test_data::header_file::file_name,
            header_fn);

        writer.add_if_key_not_found(
            tags::cpp::test_data::header_file::is_system,
            tags::bool_false);

        if (t.generation_type() == gt::full_generation) {
            writer.add_if_key_not_found(
                tags::cpp::test_data::header_file::generate,
                tags::bool_true);
            writer.add_if_key_not_found(
                tags::cpp::test_data::header_file::overwrite,
                tags::bool_true);
        } else if (t.generation_type() == gt::partial_generation) {
            writer.add_if_key_not_found(
                tags::cpp::test_data::header_file::generate,
                tags::bool_true);
            writer.add_if_key_not_found(
                tags::cpp::test_data::header_file::overwrite,
                tags::bool_false);
        } else if (t.generation_type() == gt::no_generation) {
            writer.add_if_key_not_found(
                tags::cpp::test_data::header_file::generate,
                tags::bool_false);
            writer.add_if_key_not_found(
                tags::cpp::test_data::header_file::overwrite,
                tags::bool_false);
        }

        const auto impl_fn(filename_for_qname(reader, !is_header_file,
                t.name(), reader.get(tags::cpp::test_data::directory_name),
                reader.get(tags::cpp::test_data::postfix),
                empty_postfix));

        writer.add_if_key_not_found(
            tags::cpp::test_data::implementation_file::file_name,
            impl_fn);

        writer.add_if_key_not_found(
            tags::cpp::test_data::implementation_file::is_system,
            tags::bool_false);

        if (t.generation_type() == gt::full_generation) {
            writer.add_if_key_not_found(
                tags::cpp::test_data::implementation_file::generate,
                tags::bool_true);
            writer.add_if_key_not_found(
                tags::cpp::test_data::implementation_file::overwrite,
                tags::bool_true);
        } else if (t.generation_type() == gt::partial_generation) {
            writer.add_if_key_not_found(
                tags::cpp::test_data::implementation_file::generate,
                tags::bool_true);
            writer.add_if_key_not_found(
                tags::cpp::test_data::implementation_file::overwrite,
                tags::bool_false);
        } else if (t.generation_type() == gt::no_generation) {
            writer.add_if_key_not_found(
                tags::cpp::test_data::implementation_file::generate,
                tags::bool_false);
            writer.add_if_key_not_found(
                tags::cpp::test_data::implementation_file::overwrite,
                tags::bool_false);
        }
    }

    if (reader.is_true(tags::cpp::odb::enabled)) {
        const auto header_fn(filename_for_qname(reader, is_header_file,
                t.name(), reader.get(tags::cpp::odb::directory_name),
                reader.get(tags::cpp::odb::postfix),
                empty_postfix));

        writer.add_if_key_not_found(
            tags::cpp::odb::header_file::file_name,
            header_fn);

        writer.add_if_key_not_found(
            tags::cpp::odb::header_file::is_system,
            tags::bool_false);

        if (t.generation_type() == gt::full_generation) {
            writer.add_if_key_not_found(
                tags::cpp::odb::header_file::generate,
                tags::bool_true);
            writer.add_if_key_not_found(
                tags::cpp::odb::header_file::overwrite,
                tags::bool_true);
        } else if (t.generation_type() == gt::partial_generation) {
            writer.add_if_key_not_found(
                tags::cpp::odb::header_file::generate,
                tags::bool_true);
            writer.add_if_key_not_found(
                tags::cpp::odb::header_file::overwrite,
                tags::bool_false);
        } else if (t.generation_type() == gt::no_generation) {
            writer.add_if_key_not_found(
                tags::cpp::odb::header_file::generate,
                tags::bool_false);
            writer.add_if_key_not_found(
                tags::cpp::odb::header_file::overwrite,
                tags::bool_false);
        }
    }

    t.accept(*this);
}

void meta_data_tagger::operator()(module& m) const {
    meta_data_writer writer(m.meta_data());
    copy_model_tags(writer);

    // only generate a types file for models when there is
    // documentation for the model.
    if (m.documentation().empty()) {
        writer.add_if_key_not_found(
            tags::cpp::types::header_file::generate, tags::bool_false);
        return;
    }

    writer.add_if_key_not_found(
        tags::cpp::types::header_file::generate, tags::bool_true);

    // must massage the model name in order to generate the
    // correct file name for the model.
    qname qn(m.name());
    qn.simple_name(m.name().model_name());

    meta_data_reader reader(m.meta_data());
    const auto fn(filename_for_qname(reader, is_header_file, qn,
            reader.get(tags::cpp::types::directory_name),
            reader.get(tags::cpp::types::postfix),
            empty_postfix));

    writer.add_if_key_not_found(
        tags::cpp::types::header_file::file_name, fn);

    writer.add_if_key_not_found(
        tags::cpp::types::header_file::is_system, tags::bool_false);
}

void meta_data_tagger::operator()(concept& /*c*/) const {
    // nothing to do for concepts
}

void meta_data_tagger::tag(object& o) const {
    meta_data_writer writer(o.meta_data());
    writer.add_if_key_not_found(tags::cpp::types::is_simple_type,
        tags::bool_false);

    const auto i(o.relationships().find(relationship_types::original_parents));
    if (i != o.relationships().end() && !i->second.empty()) {
        if (i->second.size() > 1) {
            const auto sn(o.name().simple_name());
            BOOST_LOG_SEV(lg, error) << too_many_original_parents << sn;
            BOOST_THROW_EXCEPTION(meta_data_error(too_many_original_parents +
                    sn));
        }

        const auto& opn(i->second.front());
        writer.add_if_key_not_found(tags::original_parent_name,
            opn.simple_name());

        const auto i(context_->model().objects().find(opn));
        if (i == context_->model().objects().end()) {
            BOOST_LOG_SEV(lg, error) << original_parent_not_found << opn;
            BOOST_THROW_EXCEPTION(meta_data_error(original_parent_not_found +
                    opn.simple_name()));
        }

        writer.add_if_key_not_found(tags::is_original_parent_visitable,
            i->second.is_visitable() ? tags::bool_true : tags::bool_false);

        writer.add_if_key_not_found(tags::cpp::types::generate_accept,
            i->second.is_visitable() ? tags::bool_true : tags::bool_false);

        writer.add_if_key_not_found(
            tags::cpp::types::qualified_original_parent_name,
            cpp_qualified_name(opn));
    }

    writer.add_if_key_not_found(tags::cpp::types::generate_accept,
        o.is_visitable() ? tags::bool_true : tags::bool_false);

    if (!o.is_parent())
        writer.add_if_key_not_found(tags::is_final, tags::bool_true);

    writer.add_if_key_not_found(
        tags::cpp::types::generate_defaulted_functions, tags::bool_true);

    writer.add_if_key_not_found(
        tags::cpp::types::generate_explicit_default_constructor,
        tags::bool_false);

    writer.add_if_key_not_found(
        tags::cpp::types::generate_explicit_move_constructor, tags::bool_false);

    writer.add_if_key_not_found(
        tags::cpp::types::generate_explicit_assignment_operator,
        tags::bool_false);

    writer.add_if_key_not_found(
        tags::cpp::types::generate_complete_constructor,
        tags::bool_true);

    writer.add_if_key_not_found(tags::cpp::types::generate_equality,
        tags::bool_true);

    writer.add_if_key_not_found(tags::cpp::types::generate_friends,
        tags::bool_true);

    writer.add_if_key_not_found(tags::cpp::types::generate_to_stream,
        tags::bool_true);

    writer.add_if_key_not_found(tags::cpp::types::generate_swap,
        tags::bool_true);
}

void meta_data_tagger::tag(model& m) const {
    context_ = std::unique_ptr<context>(new context(m));

    meta_data_writer writer(m.meta_data());

    writer.add_if_key_not_found(tags::cpp::source_directory, source_directory);
    writer.add_if_key_not_found(tags::cpp::include_directory,
        include_directory);

    writer.add_if_key_not_found(
        dogen::sml::tags::code_generation_marker::message, empty);

    writer.add_if_key_not_found(
        dogen::sml::tags::code_generation_marker::add_warning,
        tags::bool_false);

    writer.add_if_key_not_found(
        dogen::sml::tags::code_generation_marker::add_date_time,
        tags::bool_false);

    writer.add_if_key_not_found(tags::generate_preamble, tags::bool_true);

    writer.add_if_key_not_found(tags::cpp::header_file_extension,
        cpp_header_extension);

    writer.add_if_key_not_found(tags::cpp::implementation_file_extension,
        cpp_implementation_extension);

    writer.add_if_key_not_found(tags::cpp::enable_facet_folders,
        tags::bool_true);

    writer.add_if_key_not_found(tags::cpp::enable_unique_file_names,
        tags::bool_true);

    writer.add_if_key_not_found(tags::cpp::forward_declaration_postfix,
        forward_decls_postfix);

    writer.add_if_key_not_found(tags::cpp::types::enabled, tags::bool_true);
    writer.add_if_key_not_found(tags::cpp::hash::standard::enabled,
        tags::bool_true);
    writer.add_if_key_not_found(tags::cpp::serialization::boost::enabled,
        tags::bool_true);
    writer.add_if_key_not_found(tags::cpp::io::enabled, tags::bool_true);
    writer.add_if_key_not_found(tags::cpp::test_data::enabled, tags::bool_true);
    writer.add_if_key_not_found(tags::cpp::odb::enabled, tags::bool_true);

    meta_data_reader reader(m.meta_data());
    if (reader.is_true(tags::cpp::types::enabled)) {
        writer.add_if_key_not_found(tags::cpp::types::directory_name,
            types_directory);

        writer.add_if_key_not_found(tags::cpp::types::postfix,
            types_postfix);

        // only generate a types file for models when there is
        // documentation for the model.
        if (!m.documentation().empty()) {
            writer.add_if_key_not_found(
                tags::cpp::types::header_file::generate, tags::bool_true);

            writer.add_if_key_not_found(
                tags::cpp::types::header_file::overwrite, tags::bool_true);

            // must massage the model name in order to generate the
            // correct file name for the model.
            qname qn(m.name());
            qn.simple_name(m.name().model_name());
            const auto fn(filename_for_qname(reader, is_header_file, qn,
                    reader.get(tags::cpp::types::directory_name),
                    reader.get(tags::cpp::types::postfix),
                    empty_postfix));

            writer.add_if_key_not_found(
                tags::cpp::types::header_file::file_name, fn);

            writer.add_if_key_not_found(
                tags::cpp::types::header_file::is_system, tags::bool_false);
        }

        qname qn;
        qn.simple_name(cpp_includer_file_name);
        qn.model_name(m.name().model_name());
        qn.external_module_path(m.name().external_module_path());
        const auto includers_fn(filename_for_qname(reader, is_header_file,
                qn, reader.get(tags::cpp::types::directory_name),
                reader.get(tags::cpp::types::postfix),
                empty_postfix));

        writer.add_if_key_not_found(
            tags::cpp::types::includers_file::file_name, includers_fn);

        writer.add_if_key_not_found(
            tags::cpp::types::includers_file::is_system, tags::bool_false);
    }

    if (reader.is_true(tags::cpp::hash::standard::enabled)) {
        writer.add_if_key_not_found(tags::cpp::hash::standard::directory_name,
            hash_directory);

        writer.add_if_key_not_found(tags::cpp::hash::standard::postfix,
            hash_postfix);

        qname qn;
        qn.simple_name(cpp_includer_file_name);
        qn.model_name(m.name().model_name());
        qn.external_module_path(m.name().external_module_path());
        const auto includers_fn(filename_for_qname(reader, is_header_file,
                qn, reader.get(tags::cpp::hash::standard::directory_name),
                reader.get(tags::cpp::hash::standard::postfix),
                empty_postfix));

        writer.add_if_key_not_found(
            tags::cpp::hash::standard::includers_file::file_name, includers_fn);

        writer.add_if_key_not_found(
            tags::cpp::hash::standard::includers_file::is_system,
            tags::bool_false);
    }

    if (reader.is_true(tags::cpp::serialization::boost::enabled)) {
        writer.add_if_key_not_found(
            tags::cpp::serialization::boost::directory_name,
            hash_directory);

        writer.add_if_key_not_found(tags::cpp::serialization::boost::postfix,
            hash_postfix);

        qname qn;
        qn.simple_name(cpp_includer_file_name);
        qn.model_name(m.name().model_name());
        qn.external_module_path(m.name().external_module_path());
        const auto includers_fn(filename_for_qname(reader, is_header_file, qn,
                reader.get(tags::cpp::serialization::boost::directory_name),
                reader.get(tags::cpp::serialization::boost::postfix),
                empty_postfix));

        writer.add_if_key_not_found(
            tags::cpp::serialization::boost::includers_file::file_name,
            includers_fn);

        writer.add_if_key_not_found(
            tags::cpp::serialization::boost::includers_file::is_system,
            tags::bool_false);
    }

    if (reader.is_true(tags::cpp::io::enabled)) {
        writer.add_if_key_not_found(tags::cpp::io::directory_name,
            serialization_directory);

        writer.add_if_key_not_found(tags::cpp::io::postfix,
            serialization_postfix);

        qname qn;
        qn.simple_name(cpp_includer_file_name);
        qn.model_name(m.name().model_name());
        qn.external_module_path(m.name().external_module_path());
        const auto includers_fn(filename_for_qname(reader, is_header_file,
                qn, reader.get(tags::cpp::io::directory_name),
                reader.get(tags::cpp::io::postfix),
                empty_postfix));

        writer.add_if_key_not_found(tags::cpp::io::includers_file::file_name,
            includers_fn);

        writer.add_if_key_not_found(tags::cpp::io::includers_file::is_system,
            tags::bool_false);
    }

    if (reader.is_true(tags::cpp::test_data::enabled)) {
        writer.add_if_key_not_found(tags::cpp::test_data::directory_name,
            test_data_directory);

        writer.add_if_key_not_found(tags::cpp::test_data::postfix,
            test_data_postfix);

        qname qn;
        qn.simple_name(cpp_includer_file_name);
        qn.model_name(m.name().model_name());
        qn.external_module_path(m.name().external_module_path());
        const auto includers_fn(filename_for_qname(reader, is_header_file,
                qn, reader.get(tags::cpp::test_data::directory_name),
                reader.get(tags::cpp::test_data::postfix),
                empty_postfix));

        writer.add_if_key_not_found(
            tags::cpp::test_data::includers_file::file_name,
            includers_fn);

        writer.add_if_key_not_found(
            tags::cpp::test_data::includers_file::is_system,
            tags::bool_false);
    }

    if (reader.is_true(tags::cpp::odb::enabled)) {
        writer.add_if_key_not_found(tags::cpp::odb::directory_name,
            odb_directory);

        writer.add_if_key_not_found(tags::cpp::odb::postfix, odb_postfix);

        qname qn;
        qn.simple_name(cpp_includer_file_name);
        qn.model_name(m.name().model_name());
        qn.external_module_path(m.name().external_module_path());
        const auto includers_fn(filename_for_qname(reader, is_header_file,
                qn, reader.get(tags::cpp::odb::directory_name),
                reader.get(tags::cpp::odb::postfix),
                empty_postfix));

        writer.add_if_key_not_found(tags::cpp::odb::includers_file::file_name,
            includers_fn);

        writer.add_if_key_not_found(tags::cpp::odb::includers_file::is_system,
            tags::bool_false);
    }

    all_model_items_traversal(m, *this);
    context_ = std::unique_ptr<context>();
}

void meta_data_tagger::tag(const config::cpp_settings& s, model& m) const {
    from_settings(s, m);
    tag(m);
}

} }
