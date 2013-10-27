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
#include "dogen/sml/types/tag_error.hpp"
#include "dogen/sml/types/all_model_items_traversal.hpp"
#include "dogen/sml/types/tags.hpp"
#include "dogen/sml/types/tag_adaptor.hpp"
#include "dogen/sml/types/tag_router.hpp"
#include "dogen/sml/types/entity.hpp"
#include "dogen/sml/types/enumeration.hpp"
#include "dogen/sml/types/factory.hpp"
#include "dogen/sml/types/keyed_entity.hpp"
#include "dogen/sml/types/repository.hpp"
#include "dogen/sml/types/service.hpp"
#include "dogen/sml/types/value_object.hpp"
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/sml/types/tagger.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("sml.tagger"));
const std::string original_parent_not_found(
    "Failed to find original parent for type: ");

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

class tagger::context {
public:
    context(sml::model& m) : model_(m) { }

public:
    sml::model& model() { return model_; }

private:
    sml::model& model_;
};

void tagger::
from_settings(const config::cpp_settings& s, model& m) const {
    tag_router router(make_tag_router(m));

    router.route_if_key_not_found(tags::cpp::split_project,
        s.split_project() ? tags::bool_false : tags::bool_true);

    router.route_if_key_not_found(tags::cpp::header_file_extension,
        s.header_extension());

    router.route_if_key_not_found(tags::cpp::implementation_file_extension,
        s.source_extension());

    router.route_if_key_not_found(tags::cpp::enable_facet_folders,
        s.disable_facet_folders() ? tags::bool_false : tags::bool_true);

    router.route_if_key_not_found(tags::cpp::enable_unique_file_names,
        s.disable_unique_file_names() ?
        tags::bool_false : tags::bool_true);

    using config::cpp_facet_types;
    const auto& ss(tags::status_supported);
    const auto& su(tags::status_unsupported);

    if (is_facet_enabled(s.enabled_facets(), cpp_facet_types::types)) {
        router.route_if_key_not_found(tags::cpp::types::status, ss);

        router.route_if_key_not_found(
            tags::cpp::types::generate_complete_constructor,
            s.disable_complete_constructor() ?
            tags::bool_false : tags::bool_true);

        router.route_if_key_not_found(
            tags::cpp::types::includers_file::generate,
            s.disable_facet_includers() ?
            tags::bool_false : tags::bool_true);

        router.route_if_key_not_found(
            tags::cpp::types::directory_name,
            s.domain_facet_folder());
    } else
        router.route_if_key_not_found(tags::cpp::types::status, su);

    if (is_facet_enabled(s.enabled_facets(), cpp_facet_types::hash)) {
        router.route_if_key_not_found(tags::cpp::hash::standard::status, ss);

        router.route_if_key_not_found(
            tags::cpp::hash::standard::includers_file::generate,
            s.disable_facet_includers() ?
            tags::bool_false : tags::bool_true);

        router.route_if_key_not_found(
            tags::cpp::hash::standard::directory_name,
            s.hash_facet_folder());
    } else
        router.route_if_key_not_found(tags::cpp::hash::standard::status, su);

    if (is_facet_enabled(s.enabled_facets(), cpp_facet_types::io)) {
        router.route_if_key_not_found(tags::cpp::io::status, ss);

        router.route_if_key_not_found(
            tags::cpp::io::enable_integrated_io,
            s.use_integrated_io() ?
            tags::bool_true : tags::bool_false);

        router.route_if_key_not_found(
            tags::cpp::io::includers_file::generate,
            s.disable_facet_includers() ?
            tags::bool_false : tags::bool_true);

        router.route_if_key_not_found(
            tags::cpp::io::directory_name,
            s.io_facet_folder());
    } else
        router.route_if_key_not_found(tags::cpp::io::status, su);

    if (is_facet_enabled(s.enabled_facets(), cpp_facet_types::serialization)) {
        const auto& key(tags::cpp::serialization::boost::status);
        router.route_if_key_not_found(key, ss);

        router.route_if_key_not_found(
            tags::cpp::serialization::boost::enable_xml_serialization,
            s.disable_xml_serialization() ?
            tags::bool_false : tags::bool_true);

        router.route_if_key_not_found(
            tags::cpp::serialization::boost::includers_file::generate,
            s.disable_facet_includers() ?
            tags::bool_false : tags::bool_true);

        router.route_if_key_not_found(
            tags::cpp::serialization::boost::directory_name,
            s.serialization_facet_folder());
    } else
        router.route_if_key_not_found(tags::cpp::serialization::boost::status,
            su);

    if (is_facet_enabled(s.enabled_facets(), cpp_facet_types::test_data)) {
        const auto& key(tags::cpp::test_data::status);
        router.route_if_key_not_found(key, ss);

        router.route_if_key_not_found(
            tags::cpp::test_data::includers_file::generate,
            s.disable_facet_includers() ?
            tags::bool_false : tags::bool_true);

        router.route_if_key_not_found(
            tags::cpp::test_data::directory_name,
            s.test_data_facet_folder());
    } else
        router.route_if_key_not_found(tags::cpp::test_data::status, su);

    if (is_facet_enabled(s.enabled_facets(), cpp_facet_types::odb)) {
        router.route_if_key_not_found(tags::cpp::odb::status, ss);

        router.route_if_key_not_found(
            tags::cpp::odb::includers_file::generate,
            s.disable_facet_includers() ?
            tags::bool_false : tags::bool_true);

        router.route_if_key_not_found(
            tags::cpp::odb::directory_name,
            s.odb_facet_folder());
    } else
        router.route_if_key_not_found(tags::cpp::odb::status, su);
}

bool tagger::is_facet_enabled(
    const std::set<config::cpp_facet_types>& enabled_facets,
    const config::cpp_facet_types facet) const {
    const auto i(enabled_facets.find(facet));
    return i != enabled_facets.end();
}

std::string tagger::cpp_qualified_name(const sml::qname& qn) const {
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

std::string tagger::filename_for_qname(
    const tag_adaptor& adaptor, const bool is_header, const qname& qn,
    const std::string& facet_directory, const std::string& facet_postfix,
    const std::string& additional_postfix) const {

    boost::filesystem::path r;
    if (adaptor.is_true(tags::cpp::split_project)) {
        for(auto n : qn.external_module_path())
            r /= n;
    }

    if (adaptor.is_true(tags::cpp::split_project))
        r /= qn.model_name();
    else if (is_header) {
        for(auto n : qn.external_module_path())
            r /= n;
        r /= qn.model_name();
    }

    if (adaptor.is_true(tags::cpp::enable_facet_folders))
        r /= facet_directory;

    for(auto n : qn.module_path())
        r /= n;

    std::ostringstream stream;
    stream << qn.simple_name() << additional_postfix;

    if (adaptor.is_true(tags::cpp::enable_unique_file_names))
        stream << facet_postfix;

    if (is_header)
        stream << adaptor.get(tags::cpp::header_file_extension);
    else
        stream << adaptor.get(tags::cpp::implementation_file_extension);

    r /= stream.str();

    return r.generic_string();
}

void tagger::copy_model_tags(tag_router& router) const {
    auto adaptor(make_tag_adaptor(context_->model()));

    router.route_if_key_not_found(tags::copyright_holder,
        adaptor.get(tags::copyright_holder));

    router.route_if_key_not_found(tags::generate_preamble,
        adaptor.get(tags::generate_preamble));

    router.route_if_key_not_found(dogen::sml::tags::licence_name,
        adaptor.get(dogen::sml::tags::licence_name));

    router.route_if_key_not_found(dogen::sml::tags::modeline_group_name,
        adaptor.get(dogen::sml::tags::modeline_group_name));

    router.route_if_key_not_found(dogen::sml::tags::code_generation_marker,
        adaptor.get(dogen::sml::tags::code_generation_marker));

    router.route_if_key_not_found(tags::cpp::header_file_extension,
        adaptor.get(tags::cpp::header_file_extension));

        router.route_if_key_not_found(tags::cpp::implementation_file_extension,
            adaptor.get(tags::cpp::implementation_file_extension));

        router.route_if_key_not_found(tags::cpp::enable_facet_folders,
            adaptor.get(tags::cpp::enable_facet_folders));

        router.route_if_key_not_found(tags::cpp::enable_unique_file_names,
            adaptor.get(tags::cpp::enable_unique_file_names));

        router.route_if_key_not_found(tags::cpp::forward_declaration_postfix,
            adaptor.get(tags::cpp::forward_declaration_postfix));

        router.route_if_key_not_found(tags::cpp::types::status,
            adaptor.get(tags::cpp::types::status));

        router.route_if_key_not_found(tags::cpp::hash::standard::status,
            adaptor.get(tags::cpp::hash::standard::status));

        router.route_if_key_not_found(tags::cpp::serialization::boost::status,
            adaptor.get(tags::cpp::serialization::boost::status));

        router.route_if_key_not_found(tags::cpp::io::status,
            adaptor.get(tags::cpp::io::status));

        router.route_if_key_not_found(tags::cpp::test_data::status,
            adaptor.get(tags::cpp::test_data::status));

        router.route_if_key_not_found(tags::cpp::odb::status,
            adaptor.get(tags::cpp::odb::status));
    }

void tagger::visit(sml::primitive& p) const {
    tag_router router(make_tag_router(p));
    router.route_if_key_not_found(tags::cpp::types::is_simple_type,
        tags::bool_true);
}

void tagger::visit(sml::enumeration& e) const {
    tag_router router(make_tag_router(e));
    router.route_if_key_not_found(tags::cpp::types::is_simple_type,
        tags::bool_true);
}

void tagger::visit(sml::service& s) const {
    tag(s);
}

void tagger::visit(sml::factory& f) const {
    tag(f);
}

void tagger::visit(sml::repository& r) const {
    tag(r);
}

void tagger::visit(sml::value_object& vo) const {
    tag(vo);
}

void tagger::visit(sml::keyed_entity& ke) const {
    tag(ke);
}

void tagger::visit(sml::entity& e) const {
    tag(e);
}

void tagger::operator()(type& t) const {
    tag_router router(make_tag_router(t));
    copy_model_tags(router);

    auto adaptor(make_tag_adaptor(t));
    router.route_if_key_not_found(tags::cpp::types::qualified_name,
        cpp_qualified_name(t.name()));

    if (adaptor.is_supported(tags::cpp::types::status)) {
        router.route_if_key_not_found(
            tags::cpp::types::header_file::generate, tags::bool_true);

        const auto header_fn(filename_for_qname(adaptor, is_header_file,
                t.name(), adaptor.get(tags::cpp::types::directory_name),
                adaptor.get(tags::cpp::types::postfix),
                empty_postfix));

        router.route_if_key_not_found(
            tags::cpp::types::header_file::file_name, header_fn);

        router.route_if_key_not_found(
            tags::cpp::types::header_file::is_system, tags::bool_false);

        const auto impl_fn(filename_for_qname(adaptor, !is_header_file,
                t.name(), adaptor.get(tags::cpp::types::directory_name),
                adaptor.get(tags::cpp::types::postfix),
                empty_postfix));

        router.route_if_key_not_found(
            tags::cpp::types::implementation_file::file_name, impl_fn);

        router.route_if_key_not_found(
            tags::cpp::types::implementation_file::is_system, tags::bool_false);

        const auto fwd_fn(filename_for_qname(adaptor, is_header_file,
                t.name(), adaptor.get(tags::cpp::types::directory_name),
                adaptor.get(tags::cpp::types::postfix),
                empty_postfix));

        router.route_if_key_not_found(
            tags::cpp::types::forward_declarations_file::file_name, fwd_fn);

        router.route_if_key_not_found(
            tags::cpp::types::forward_declarations_file::is_system,
            tags::bool_false);
    }

    if (adaptor.is_supported(tags::cpp::hash::standard::status)) {
        router.route_if_key_not_found(
            tags::cpp::hash::standard::header_file::generate, tags::bool_true);

        const auto header_fn(filename_for_qname(adaptor, is_header_file,
                t.name(),
                adaptor.get(tags::cpp::hash::standard::directory_name),
                adaptor.get(tags::cpp::hash::standard::postfix),
                empty_postfix));

        router.route_if_key_not_found(
            tags::cpp::hash::standard::header_file::file_name, header_fn);

        router.route_if_key_not_found(
            tags::cpp::hash::standard::header_file::is_system,
            tags::bool_false);

        const auto impl_fn(filename_for_qname(adaptor, !is_header_file,
                t.name(),
                adaptor.get(tags::cpp::hash::standard::directory_name),
                adaptor.get(tags::cpp::hash::standard::postfix),
                empty_postfix));

        router.route_if_key_not_found(
            tags::cpp::hash::standard::implementation_file::file_name, impl_fn);

        router.route_if_key_not_found(
            tags::cpp::hash::standard::implementation_file::is_system,
            tags::bool_false);
    }

    if (adaptor.is_supported(tags::cpp::serialization::boost::status)) {
        router.route_if_key_not_found(
            tags::cpp::serialization::boost::header_file::generate,
            tags::bool_true);

        const auto header_fn(filename_for_qname(adaptor, is_header_file,
                t.name(),
                adaptor.get(tags::cpp::serialization::boost::directory_name),
                adaptor.get(tags::cpp::serialization::boost::postfix),
                empty_postfix));

        router.route_if_key_not_found(
            tags::cpp::serialization::boost::header_file::file_name, header_fn);

        router.route_if_key_not_found(
            tags::cpp::serialization::boost::header_file::is_system,
            tags::bool_false);

        const auto impl_fn(filename_for_qname(adaptor, !is_header_file,
                t.name(),
                adaptor.get(tags::cpp::serialization::boost::directory_name),
                adaptor.get(tags::cpp::serialization::boost::postfix),
                empty_postfix));

        router.route_if_key_not_found(
            tags::cpp::serialization::boost::implementation_file::file_name,
            impl_fn);

        router.route_if_key_not_found(
            tags::cpp::serialization::boost::implementation_file::is_system,
            tags::bool_false);
    }

    if (adaptor.is_supported(tags::cpp::io::status)) {
        router.route_if_key_not_found(
            tags::cpp::io::header_file::generate, tags::bool_true);

        const auto header_fn(filename_for_qname(adaptor, is_header_file,
                t.name(), adaptor.get(tags::cpp::io::directory_name),
                adaptor.get(tags::cpp::io::postfix),
                empty_postfix));

        router.route_if_key_not_found(tags::cpp::io::header_file::file_name,
            header_fn);

        router.route_if_key_not_found(tags::cpp::io::header_file::is_system,
            tags::bool_false);

        const auto impl_fn(filename_for_qname(adaptor, !is_header_file,
                t.name(), adaptor.get(tags::cpp::io::directory_name),
                adaptor.get(tags::cpp::io::postfix),
                empty_postfix));

        router.route_if_key_not_found(
            tags::cpp::io::implementation_file::file_name,
            impl_fn);

        router.route_if_key_not_found(
            tags::cpp::io::implementation_file::is_system,
            tags::bool_false);
    }

    if (adaptor.is_supported(tags::cpp::test_data::status)) {
        router.route_if_key_not_found(
            tags::cpp::test_data::header_file::generate, tags::bool_true);

        const auto header_fn(filename_for_qname(adaptor, is_header_file,
                t.name(), adaptor.get(tags::cpp::test_data::directory_name),
                adaptor.get(tags::cpp::test_data::postfix),
                empty_postfix));

        router.route_if_key_not_found(
            tags::cpp::test_data::header_file::file_name,
            header_fn);

        router.route_if_key_not_found(
            tags::cpp::test_data::header_file::is_system,
            tags::bool_false);

        const auto impl_fn(filename_for_qname(adaptor, !is_header_file,
                t.name(), adaptor.get(tags::cpp::test_data::directory_name),
                adaptor.get(tags::cpp::test_data::postfix),
                empty_postfix));

        router.route_if_key_not_found(
            tags::cpp::test_data::implementation_file::file_name,
            impl_fn);

        router.route_if_key_not_found(
            tags::cpp::test_data::implementation_file::is_system,
            tags::bool_false);
    }

    if (adaptor.is_supported(tags::cpp::odb::status)) {
        router.route_if_key_not_found(
            tags::cpp::odb::header_file::generate, tags::bool_true);

        const auto header_fn(filename_for_qname(adaptor, is_header_file,
                t.name(), adaptor.get(tags::cpp::odb::directory_name),
                adaptor.get(tags::cpp::odb::postfix),
                empty_postfix));

        router.route_if_key_not_found(
            tags::cpp::odb::header_file::file_name,
            header_fn);

        router.route_if_key_not_found(
            tags::cpp::odb::header_file::is_system,
            tags::bool_false);
    }

    t.accept(*this);
}

void tagger::operator()(module& m) const {
    tag_router router(make_tag_router(m));
    copy_model_tags(router);

    // only generate a types file for models when there is
    // documentation for the model.
    if (!m.documentation().empty()) {
        router.route_if_key_not_found(
            tags::cpp::types::header_file::generate, tags::bool_true);

        // must massage the model name in order to generate the
        // correct file name for the model.
        qname qn(m.name());
        qn.simple_name(m.name().model_name());

        auto adaptor(make_tag_adaptor(m));
        const auto fn(filename_for_qname(adaptor, is_header_file, qn,
                adaptor.get(tags::cpp::types::directory_name),
                adaptor.get(tags::cpp::types::postfix),
                empty_postfix));

        router.route_if_key_not_found(
            tags::cpp::types::header_file::file_name, fn);

        router.route_if_key_not_found(
            tags::cpp::types::header_file::is_system, tags::bool_false);
    }
}

void tagger::operator()(concept& /*c*/) const {
    // nothing to do for concepts
}

void tagger::tag(abstract_object& o) const {
    tag_router router(make_tag_router(o));
    router.route_if_key_not_found(tags::cpp::types::is_simple_type,
        tags::bool_false);

    if (o.original_parent_name()) {
        const auto opn(*o.original_parent_name());
        router.route_if_key_not_found(tags::original_parent_name,
            opn.simple_name());

        const auto i(context_->model().objects().find(opn));
        if (i == context_->model().objects().end()) {
            BOOST_LOG_SEV(lg, error) << original_parent_not_found << opn;
            BOOST_THROW_EXCEPTION(tag_error(original_parent_not_found +
                    opn.simple_name()));
        }

        router.route_if_key_not_found(tags::is_original_parent_visitable,
            i->second->is_visitable() ? tags::bool_true : tags::bool_false);

        router.route_if_key_not_found(tags::cpp::types::generate_accept,
            i->second->is_visitable() ? tags::bool_true : tags::bool_false);

        router.route_if_key_not_found(
            tags::cpp::types::qualified_original_parent_name,
            cpp_qualified_name(opn));
    }

    router.route_if_key_not_found(tags::cpp::types::generate_accept,
        o.is_visitable() ? tags::bool_true : tags::bool_false);

    if (!o.is_parent())
        router.route_if_key_not_found(tags::is_final, tags::bool_true);

    router.route_if_key_not_found(
        tags::cpp::types::generate_defaulted_functions, tags::bool_true);

    router.route_if_key_not_found(
        tags::cpp::types::generate_explicit_default_constructor,
        tags::bool_false);

    router.route_if_key_not_found(
        tags::cpp::types::generate_explicit_move_constructor, tags::bool_false);

    router.route_if_key_not_found(
        tags::cpp::types::generate_explicit_assignment_operator,
        tags::bool_false);

    router.route_if_key_not_found(
        tags::cpp::types::generate_complete_constructor,
        tags::bool_true);

    router.route_if_key_not_found(tags::cpp::types::generate_equality,
        tags::bool_true);

    router.route_if_key_not_found(tags::cpp::types::generate_friends,
        tags::bool_true);

    router.route_if_key_not_found(tags::cpp::types::generate_to_stream,
        tags::bool_true);

    router.route_if_key_not_found(tags::cpp::types::generate_swap,
        tags::bool_true);
}

void tagger::tag(model& m) const {
    context_ = std::unique_ptr<context>(new context(m));

    tag_router router(make_tag_router(m));
    router.route_if_key_not_found(tags::generate_preamble, tags::bool_true);

    router.route_if_key_not_found(tags::cpp::header_file_extension,
        cpp_header_extension);

    router.route_if_key_not_found(tags::cpp::implementation_file_extension,
        cpp_implementation_extension);

    router.route_if_key_not_found(tags::cpp::enable_facet_folders,
        tags::bool_true);

    router.route_if_key_not_found(tags::cpp::enable_unique_file_names,
        tags::bool_true);

    router.route_if_key_not_found(tags::cpp::forward_declaration_postfix,
        forward_decls_postfix);

    const auto& ss(tags::status_supported);
    router.route_if_key_not_found(tags::cpp::types::status, ss);
    router.route_if_key_not_found(tags::cpp::hash::standard::status, ss);
    router.route_if_key_not_found(tags::cpp::serialization::boost::status, ss);
    router.route_if_key_not_found(tags::cpp::io::status, ss);
    router.route_if_key_not_found(tags::cpp::test_data::status, ss);
    router.route_if_key_not_found(tags::cpp::odb::status, ss);

    auto adaptor(make_tag_adaptor(m));
    if (adaptor.is_supported(tags::cpp::types::status)) {
        router.route_if_key_not_found(tags::cpp::types::directory_name,
            types_directory);

        router.route_if_key_not_found(tags::cpp::types::postfix,
            types_postfix);

        // only generate a types file for models when there is
        // documentation for the model.
        if (!m.documentation().empty()) {
            router.route_if_key_not_found(
                tags::cpp::types::header_file::generate, tags::bool_true);

            // must massage the model name in order to generate the
            // correct file name for the model.
            qname qn(m.name());
            qn.simple_name(m.name().model_name());
            const auto fn(filename_for_qname(adaptor, is_header_file, qn,
                    adaptor.get(tags::cpp::types::directory_name),
                    adaptor.get(tags::cpp::types::postfix),
                    empty_postfix));

            router.route_if_key_not_found(
                tags::cpp::types::header_file::file_name, fn);

            router.route_if_key_not_found(
                tags::cpp::types::header_file::is_system, tags::bool_false);
        }

        qname qn;
        qn.simple_name(cpp_includer_file_name);
        qn.model_name(m.name().model_name());
        qn.external_module_path(m.name().external_module_path());
        const auto includers_fn(filename_for_qname(adaptor, is_header_file,
                qn, adaptor.get(tags::cpp::types::directory_name),
                adaptor.get(tags::cpp::types::postfix),
                empty_postfix));

        router.route_if_key_not_found(
            tags::cpp::types::includers_file::file_name, includers_fn);

        router.route_if_key_not_found(
            tags::cpp::types::includers_file::is_system, tags::bool_false);
    }

    if (adaptor.is_supported(tags::cpp::hash::standard::status)) {
        router.route_if_key_not_found(tags::cpp::hash::standard::directory_name,
            hash_directory);

        router.route_if_key_not_found(tags::cpp::hash::standard::postfix,
            hash_postfix);

        qname qn;
        qn.simple_name(cpp_includer_file_name);
        qn.model_name(m.name().model_name());
        qn.external_module_path(m.name().external_module_path());
        const auto includers_fn(filename_for_qname(adaptor, is_header_file,
                qn, adaptor.get(tags::cpp::hash::standard::directory_name),
                adaptor.get(tags::cpp::hash::standard::postfix),
                empty_postfix));

        router.route_if_key_not_found(
            tags::cpp::hash::standard::includers_file::file_name, includers_fn);

        router.route_if_key_not_found(
            tags::cpp::hash::standard::includers_file::is_system,
            tags::bool_false);
    }

    if (adaptor.is_supported(tags::cpp::serialization::boost::status)) {
        router.route_if_key_not_found(
            tags::cpp::serialization::boost::directory_name,
            hash_directory);

        router.route_if_key_not_found(tags::cpp::serialization::boost::postfix,
            hash_postfix);

        qname qn;
        qn.simple_name(cpp_includer_file_name);
        qn.model_name(m.name().model_name());
        qn.external_module_path(m.name().external_module_path());
        const auto includers_fn(filename_for_qname(adaptor, is_header_file, qn,
                adaptor.get(tags::cpp::serialization::boost::directory_name),
                adaptor.get(tags::cpp::serialization::boost::postfix),
                empty_postfix));

        router.route_if_key_not_found(
            tags::cpp::serialization::boost::includers_file::file_name,
            includers_fn);

        router.route_if_key_not_found(
            tags::cpp::serialization::boost::includers_file::is_system,
            tags::bool_false);
    }

    if (adaptor.is_supported(tags::cpp::io::status)) {
        router.route_if_key_not_found(tags::cpp::io::directory_name,
            serialization_directory);

        router.route_if_key_not_found(tags::cpp::io::postfix,
            serialization_postfix);

        qname qn;
        qn.simple_name(cpp_includer_file_name);
        qn.model_name(m.name().model_name());
        qn.external_module_path(m.name().external_module_path());
        const auto includers_fn(filename_for_qname(adaptor, is_header_file,
                qn, adaptor.get(tags::cpp::io::directory_name),
                adaptor.get(tags::cpp::io::postfix),
                empty_postfix));

        router.route_if_key_not_found(tags::cpp::io::includers_file::file_name,
            includers_fn);

        router.route_if_key_not_found(tags::cpp::io::includers_file::is_system,
            tags::bool_false);
    }

    if (adaptor.is_supported(tags::cpp::test_data::status)) {
        router.route_if_key_not_found(tags::cpp::test_data::directory_name,
            test_data_directory);

        router.route_if_key_not_found(tags::cpp::test_data::postfix,
            test_data_postfix);

        qname qn;
        qn.simple_name(cpp_includer_file_name);
        qn.model_name(m.name().model_name());
        qn.external_module_path(m.name().external_module_path());
        const auto includers_fn(filename_for_qname(adaptor, is_header_file,
                qn, adaptor.get(tags::cpp::test_data::directory_name),
                adaptor.get(tags::cpp::test_data::postfix),
                empty_postfix));

        router.route_if_key_not_found(
            tags::cpp::test_data::includers_file::file_name,
            includers_fn);

        router.route_if_key_not_found(
            tags::cpp::test_data::includers_file::is_system,
            tags::bool_false);
    }

    if (adaptor.is_supported(tags::cpp::odb::status)) {
        router.route_if_key_not_found(tags::cpp::odb::directory_name,
            odb_directory);

        router.route_if_key_not_found(tags::cpp::odb::postfix, odb_postfix);

        qname qn;
        qn.simple_name(cpp_includer_file_name);
        qn.model_name(m.name().model_name());
        qn.external_module_path(m.name().external_module_path());
        const auto includers_fn(filename_for_qname(adaptor, is_header_file,
                qn, adaptor.get(tags::cpp::odb::directory_name),
                adaptor.get(tags::cpp::odb::postfix),
                empty_postfix));

        router.route_if_key_not_found(tags::cpp::odb::includers_file::file_name,
            includers_fn);

        router.route_if_key_not_found(tags::cpp::odb::includers_file::is_system,
            tags::bool_false);
    }

    all_model_items_traversal(m, *this);
    context_ = std::unique_ptr<context>();
}

void tagger::tag(const config::cpp_settings& s, model& m) const {
    from_settings(s, m);
    tag(m);
}

} }
