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
#include "dogen/sml/types/object.hpp"
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/cpp/io/content_descriptor_io.hpp"
#include "dogen/sml_to_cpp/types/workflow_failure.hpp"
#include "dogen/cpp/io/class_types_io.hpp"
#include "dogen/sml_to_cpp/io/context_io.hpp"
#include "dogen/sml_to_cpp/types/extractor.hpp"
#include "dogen/sml_to_cpp/types/workflow.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("cpp.workflow"));

const std::string includer_name("all");
const std::string registrar_name("registrar");
const std::string cmakelists_file_name("CMakeLists.txt");
const std::string odb_options_file_name("options.odb");
const std::string domain_facet_must_be_enabled("Domain facet must be enabled");
const std::string missing_object("Could not find object: ");
const std::string integrated_io_incompatible_with_io_facet(
    "Integrated IO cannot be used with the IO facet");
const std::string missing_relationship(
    "Could not find relationship for qname: ");
const std::string unsupported_class_type("Class type is unsupported: ");

}

namespace dogen {
namespace sml_to_cpp {

workflow::
workflow(const sml::model& model, const config::formatting_settings& s) :
    model_(model), settings_(s),
    locator_(model.name().model_name(), settings_.cpp()),
    includer_(model_, locator_, settings_.cpp()),
    file_info_factory_(locator_),
    transformer_(model_, context_),
    descriptor_factory_(settings_.cpp().enabled_facets()),
    extractor_() {

    validate_settings();
}

void workflow::validate_settings() const {
    if (settings_.cpp().use_integrated_io()) {
        const auto f(settings_.cpp().enabled_facets());
        const bool has_io_facet(f.find(config::cpp_facet_types::io) != f.end());
        if (has_io_facet) {
            BOOST_LOG_SEV(lg, error)
                << integrated_io_incompatible_with_io_facet;
            BOOST_THROW_EXCEPTION(workflow_failure(
                    integrated_io_incompatible_with_io_facet));
        }
    }

    const auto f(settings_.cpp().enabled_facets());
    if (f.find(config::cpp_facet_types::types) == f.end()) {
        BOOST_LOG_SEV(lg, error) << domain_facet_must_be_enabled;
        BOOST_THROW_EXCEPTION(workflow_failure(domain_facet_must_be_enabled));
    }
}

void workflow::register_header(const cpp::file_info& fi) const {
    const auto header(cpp::file_types::header);
    const auto cd(fi.descriptor());
    if (cd.file_type() == header)
        includer_.register_header(cd.facet_type(), fi.relative_path());
}

void workflow::transform_object(const sml::object& ao) {
    if (ao.generation_type() == sml::generation_types::no_generation)
        return;

    const auto lambda([&](const std::list<sml::qname>& oqn) {
            if (oqn.empty())
                return;

            for (const auto& qn : oqn) {
                const auto i(context_.classes().find(qn));
                if (i != context_.classes().end())
                    return;

                const auto j(model_.objects().find(qn));
                if (j == model_.objects().end()) {
                    BOOST_LOG_SEV(lg, error) << missing_object << qn;
                    BOOST_THROW_EXCEPTION(workflow_failure(missing_object +
                            boost::lexical_cast<std::string>(qn)));
                }

                const auto& ao(j->second);
                using sml::generation_types;
                if (ao.generation_type() == generation_types::no_generation)
                    return;

                transform_object(ao);
            }
        });

    using sml::relationship_types;
    auto i(ao.relationships().find(relationship_types::parents));
    if (i != ao.relationships().end())
        lambda(i->second);

    i = ao.relationships().find(relationship_types::original_parents);
    if (i != ao.relationships().end())
        lambda(i->second);

    transformer_.from_type(ao);
    const auto rel(extractor_.extract_dependency_graph(ao));
    context_.relationships().insert(std::make_pair(ao.name(), rel));
}

void workflow::transform_module(const sml::module& m) {
    if (m.documentation().empty())
        return;

    transformer_.to_namespace_info(m);
}

void workflow::transform_registrar() {
    const auto f(settings_.cpp().enabled_facets());
    if (f.find(config::cpp_facet_types::serialization) == f.end())
        return;

    transformer_.model_to_registrar_info();
}

void workflow::transform_enumeration(const sml::enumeration& e) {
    if (e.generation_type() == sml::generation_types::no_generation)
        return;

    transformer_.from_type(e);
}

void workflow::transformation_sub_workflow() {
    BOOST_LOG_SEV(lg, debug) << "Started transformation sub-workflow.";

    for (const auto& pair : model_.objects())
        transform_object(pair.second);

    for (const auto& pair : model_.modules())
        transform_module(pair.second);

    for (const auto& pair : model_.enumerations())
        transform_enumeration(pair.second);

    transform_registrar();

    BOOST_LOG_SEV(lg, debug) << "Finished transformation sub-workflow";
    BOOST_LOG_SEV(lg, debug) << "context: " << context_;
}

std::list<cpp::file_info>
workflow::generate_file_infos_for_classes_activity() const {
    std::list<cpp::file_info> r;
    for (const auto& pair : context_.classes()) {
        const auto& qn(pair.first);
        const auto i(context_.relationships().find(qn));
        if (i == context_.relationships().end()) {
            BOOST_LOG_SEV(lg, error) << missing_relationship << qn;
            BOOST_THROW_EXCEPTION(workflow_failure(missing_relationship +
                    boost::lexical_cast<std::string>(qn)));
        }

        const auto& rel(i->second);
        const auto& ci(pair.second);
        using cpp::content_types;
        using cpp::class_types;

        content_types ct;
        // FIXME: big hack
        switch(ci->class_type()) {
        case class_types::user_defined:
            ct = content_types::value_object;
            break;
        case class_types::unversioned_key:
            ct = content_types::unversioned_key;
            break;
        case class_types::versioned_key:
            ct = content_types::versioned_key;
            break;
        case class_types::service:
            ct = content_types::user_defined_service;
            break;
        default:
            BOOST_LOG_SEV(lg, error) << unsupported_class_type
                                     << ci->class_type();
            BOOST_THROW_EXCEPTION(workflow_failure(unsupported_class_type +
                    boost::lexical_cast<std::string>(ci->class_type())));
        };

        for (const auto& cd : descriptor_factory_.create(qn, ct)) {
            const auto inc(includer_.includes_for_object(cd, rel));
            auto fi(file_info_factory_.create(ci, cd, inc));

            // we want to make sure we do not actually generate code
            // for partial generation, so override the output of the
            // factory. however, as we still want to create forward
            // declarations, ignore those.
            using sml::generation_types;
            using cpp::aspect_types;
            if (cd.aspect_type() != aspect_types::forward_decls &&
                ci->generation_type() == generation_types::partial_generation) {
                fi.descriptor().aspect_type(aspect_types::null_aspect);
            }
            r.push_back(fi);

            const auto at(fi.descriptor().aspect_type());
            if (at == aspect_types::main || at == aspect_types::null_aspect)
                register_header(fi);
        }
    }
    BOOST_LOG_SEV(lg, debug) << "Finished generate classes activity";
    return r;
}

std::list<cpp::file_info>
workflow::generate_file_infos_for_namespaces_activity() const {
    std::list<cpp::file_info> r;
    for (const auto& pair : context_.namespaces()) {
        const auto qn(pair.first);
        const auto ni(pair.second);

        const auto ct(cpp::content_types::namespace_doc);
        for (const auto& cd : descriptor_factory_.create(qn, ct)) {
            const auto fi(file_info_factory_.create(ni, cd));
            r.push_back(fi);

            if (cd.aspect_type() != cpp::aspect_types::forward_decls)
                register_header(fi);
        }
    }

    BOOST_LOG_SEV(lg, debug) << "Finished generate namespaces activity.";
    return r;
}

std::list<cpp::file_info> workflow::generate_registrars_activity() const {
    std::list<cpp::file_info> r;
    for (const auto& pair : context_.registrars()) {
        const auto qn(pair.first);
        const auto ri(pair.second);

        for (const auto& cd : descriptor_factory_.create_registrar(qn)) {
            const auto inc(includer_.includes_for_registrar(cd));
            const auto fi(file_info_factory_.create_registrar(ri, cd, inc));
            r.push_back(fi);

            if (cd.aspect_type() != cpp::aspect_types::forward_decls)
                register_header(fi);
        }
    }
    return r;
}

std::list<cpp::file_info> workflow::generate_includers_activity() const {
    sml::qname qn;
    qn.simple_name(includer_name);
    qn.external_module_path(model_.name().external_module_path());
    qn.model_name(model_.name().model_name());

    std::list<cpp::file_info> r;
    for (const auto& cd : descriptor_factory_.create_includer(qn)) {
        const auto inc(includer_.includes_for_includer_files(cd));
        r.push_back(file_info_factory_.create_includer(cd, inc));
    }
    return r;
}

std::list<cpp::file_info> workflow::generate_visitors_activity() const {
    std::list<cpp::file_info> r;
    for (const auto& pair : context_.visitors()) {
        const auto& qn(pair.first);
        const auto i(context_.relationships().find(qn));
        if (i == context_.relationships().end()) {
            BOOST_LOG_SEV(lg, error) << missing_relationship << qn;
            BOOST_THROW_EXCEPTION(workflow_failure(missing_relationship +
                    boost::lexical_cast<std::string>(qn)));
        }

        const auto& rel(i->second);
        const auto vi(pair.second);
        for (const auto& cd : descriptor_factory_.create_visitor(qn)) {
            const auto inc(includer_.includes_for_visitor(cd, rel));
            const auto fi(file_info_factory_.create_visitor(vi, cd, inc));
            r.push_back(fi);

            if (cd.aspect_type() != cpp::aspect_types::forward_decls)
                register_header(fi);
        }
    }
    return r;
}

std::list<cpp::file_info> workflow::generate_enums_activity() const {
    std::list<cpp::file_info> r;
    for (const auto& pair : context_.enumerations()) {
        const auto& qn(pair.first);
        const auto& ei(pair.second);

        const auto ct(cpp::content_types::enumeration);
        for (const auto& cd : descriptor_factory_.create(qn, ct)) {
            const auto inc(includer_.includes_for_enumeration(cd));
            const auto fi(file_info_factory_.create(ei, cd, inc));
            r.push_back(fi);

            if (cd.aspect_type() != cpp::aspect_types::forward_decls)
                register_header(fi);
        }
    }
    return r;
}

std::list<cpp::file_info> workflow::generate_exceptions_activity() const {
    std::list<cpp::file_info> r;
    for (const auto& pair : context_.exceptions()) {
        const auto& qn(pair.first);
        const auto& ei(pair.second);

        const auto ct(cpp::content_types::exception);
        for (const auto& cd : descriptor_factory_.create(qn, ct)) {
            const auto inc(includer_.includes_for_exception(cd));
            const auto fi(file_info_factory_.create(ei, cd, inc));
            r.push_back(fi);

            if (cd.aspect_type() != cpp::aspect_types::forward_decls)
                register_header(fi);
        }
    }

    BOOST_LOG_SEV(lg, debug) << "Finished generate exceptions activity";
    return r;
}

void workflow::generate_file_infos_activity(cpp::project& p) const {
    const auto a(generate_enums_activity());
    const auto b(generate_exceptions_activity());
    const auto c(generate_file_infos_for_classes_activity());
    const auto d(generate_file_infos_for_namespaces_activity());
    const auto e(generate_registrars_activity());
    const auto f(generate_visitors_activity());
    const auto g(generate_includers_activity());

    p.files().insert(p.files().end(), a.begin(), a.end());
    p.files().insert(p.files().end(), b.begin(), b.end());
    p.files().insert(p.files().end(), c.begin(), c.end());
    p.files().insert(p.files().end(), d.begin(), d.end());
    p.files().insert(p.files().end(), e.begin(), e.end());
    p.files().insert(p.files().end(), f.begin(), f.end());
    p.files().insert(p.files().end(), g.begin(), g.end());
}

void workflow::generate_cmakelists_activity(cpp::project& p) const {
    cpp::cmakelists_info ci;
    ci.model_name(model_.name().model_name());
    ci.file_name(cmakelists_file_name);
    ci.file_path(locator_.absolute_path_to_src(ci.file_name()));
    BOOST_LOG_SEV(lg, debug) << "Formatting: " << ci.file_path().string();

    if (!model_.name().external_module_path().empty())
        ci.product_name(model_.name().external_module_path().front());

    p.src_cmakelists(ci);
    if (!settings_.cpp().split_project()) {
        const auto f(settings_.cpp().enabled_facets());
        ci.file_path(locator_.absolute_path(ci.file_name()));
        p.include_cmakelists(ci);
    }
}

void workflow::generate_odb_options_activity(cpp::project& p) const {
    BOOST_LOG_SEV(lg, info) << "Generating ODB options file.";

    cpp::odb_options_info ooi;
    ooi.file_name(odb_options_file_name);
    ooi.file_path(locator_.absolute_path_to_src(ooi.file_name()));
    ooi.model_name(model_.name().model_name());
    ooi.odb_folder(settings_.cpp().odb_facet_folder());

    if (!model_.name().external_module_path().empty())
        ooi.product_name(model_.name().external_module_path().front());

    p.odb_options(ooi);
}

std::vector<boost::filesystem::path> workflow::managed_directories() const {
    return locator_.managed_directories();
}

cpp::project workflow::generation_sub_workflow() {
    cpp::project r;
    generate_file_infos_activity(r);
    if (settings_.cpp().disable_cmakelists())
        BOOST_LOG_SEV(lg, info) << "CMakeLists generation disabled.";
    else
        generate_cmakelists_activity(r);

    const auto f(settings_.cpp().enabled_facets());
    const bool odb_enabled(f.find(config::cpp_facet_types::odb) != f.end());
    if (odb_enabled)
        generate_odb_options_activity(r);
    else
        BOOST_LOG_SEV(lg, info) << "ODB options file generation disabled.";

    return r;
}

cpp::project workflow::execute() {
    BOOST_LOG_SEV(lg, info) << "SML to C++ workflow started.";

    transformation_sub_workflow();
    const auto r(generation_sub_workflow());

    BOOST_LOG_SEV(lg, info) << "SML to C++ workflow finished.";
    return r;
}

} }
