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
#include <iterator>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/quilt.cpp/io/formattables/formatter_properties_io.hpp"
#include "dogen/yarn/types/element_visitor.hpp"
#include "dogen/quilt.cpp/types/formattables/enum_info.hpp"
#include "dogen/quilt.cpp/types/formattables/class_info.hpp"
#include "dogen/quilt.cpp/types/formattables/visitor_info.hpp"
#include "dogen/quilt.cpp/types/formattables/includers_info.hpp"
#include "dogen/quilt.cpp/types/formattables/registrar_info.hpp"
#include "dogen/quilt.cpp/types/formattables/cmakelists_info.hpp"
#include "dogen/quilt.cpp/types/formattables/odb_options_info.hpp"
#include "dogen/quilt.cpp/types/formattables/forward_declarations_info.hpp"
#include "dogen/quilt.cpp/types/formattables/formattable_visitor.hpp"
#include "dogen/quilt.cpp/types/workflow_error.hpp"
#include "dogen/quilt.cpp/types/formatters/context.hpp"
#include "dogen/quilt.cpp/types/formatters/workflow.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("quit.cpp.formatters.workflow"));

const std::string formatter_properties_not_found(
    "Could not find properties for formatter: ");
const std::string bundle_not_found(
    "Could not find settings bundle for: ");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {

/**
 * @brief Responsible for dispatching the formattable to the
 * appropriate formatters.
 */
class dispatcher final : public formattables::formattable_visitor {
public:
    dispatcher(const settings::bundle_repository& brp,
        const formattables::formatter_properties_repository& fprp,
        const container& c);
    ~dispatcher() noexcept { }

private:
    template<typename Formatter, typename Formatable>
    void format(const Formatter& f, const Formatable& e,
        const bool empty_out_content = false) {
        const auto fn(f.ownership_hierarchy().formatter_name());
        BOOST_LOG_SEV(lg, debug) << "Formatting with: '" << fn << "'";

        auto file(f.format(empty_context_, e));

        if (empty_out_content) {
            BOOST_LOG_SEV(lg, debug) << "Emptying out content.";
            file.content().clear();
        }

        files_.push_front(file);
        if (!file.overwrite()) {
            BOOST_LOG_SEV(lg, debug) << "Filename: "
                                     << file.path().generic_string();
            BOOST_LOG_SEV(lg, debug) << "Content: "
                                     << (file.content().empty() ? "<empty>" :
                                         file.content());
        } else {
            BOOST_LOG_SEV(lg, debug) << "Not dumping file contents to log "
                                     << "(overwrite is false).";
        }
    }

    template<typename Formatter, typename Entity>
    void format_entity(const Formatter& f, const Entity& e,
        const bool empty_out_content = false) {
        const auto fn(f.ownership_hierarchy().formatter_name());
        BOOST_LOG_SEV(lg, debug) << "Formatting: '" << e.name()
                                 << "' with '" << fn << "'";

        const auto fp(formatter_properties_.formatter_properties_by_name());
        const auto i(fp.find(e.id()));
        if (i == fp.end()) {
            BOOST_LOG_SEV(lg, error) << formatter_properties_not_found
                                     << e.id();
            BOOST_THROW_EXCEPTION(
                workflow_error(formatter_properties_not_found + e.id()));
        }

        const auto j(i->second.find(fn));
        if (j == i->second.end()) {
            BOOST_LOG_SEV(lg, error) << formatter_properties_not_found << fn;
            BOOST_THROW_EXCEPTION(
                workflow_error(formatter_properties_not_found + fn));
        }

        const auto is_formatter_enabled(j->second.enabled());
        if (!is_formatter_enabled) {
            BOOST_LOG_SEV(lg, debug) << "Formatter not enabled for type.";
            return;
        }

        const auto& b(bundle_.bundles_by_name());
        const auto k(b.find(e.id()));
        if (k == b.end()) {
            BOOST_LOG_SEV(lg, error) << bundle_not_found << e.id();
            BOOST_THROW_EXCEPTION(workflow_error(bundle_not_found + e.id()));
        }

        const context ctx(k->second, i->second);
        auto file(f.format(ctx, e));

        if (empty_out_content) {
            BOOST_LOG_SEV(lg, debug) << "Emptying out content.";
            file.content().clear();
        }

        files_.push_front(file);
        if (!file.overwrite()) {
            BOOST_LOG_SEV(lg, debug) << "Filename: "
                                     << file.path().generic_string();
            BOOST_LOG_SEV(lg, debug) << "Content: "
                                     << (file.content().empty() ? "<empty>" :
                                         file.content());
            BOOST_LOG_SEV(lg, debug) << "Finished formatting: '" << e.name()
                                     << "'";
        } else {
            BOOST_LOG_SEV(lg, debug) << "Not dumping file contents to log "
                                     << "(overwrite is false).";
        }
    }

    template<typename Formatter, typename Entity>
    void format_entity(const std::forward_list<std::shared_ptr<Formatter>>& fc,
        const Entity& e) {
        for (const auto f : fc)
            format_entity(*f, e);
    }


    template<typename Formatter, typename Formattable>
     void format(const std::forward_list<std::shared_ptr<Formatter>>& fc,
            const Formattable& e) {
        for (const auto f : fc)
            format(*f, e);
    }

public:
    using formattable_visitor::visit;
    void visit(const formattables::class_info& c) override;
    void visit(const formattables::forward_declarations_info& fd) override;
    void visit(const formattables::enum_info& e) override;
    void visit(const formattables::registrar_info& r) override;
    void visit(const formattables::visitor_info& v) override;
    void visit(const formattables::cmakelists_info& c) override;
    void visit(const formattables::odb_options_info& o) override;
    void visit(const formattables::includers_info& o) override;

public:
    /**
     * @brief Converts the supplied entity into all supported
     * representations.
     */
    void format(const formattables::formattable& f);

public:
    /**
     * @brief Returns all the generated files.
     */
    const std::forward_list<dogen::formatters::file>& files();

private:
    const context empty_context_;
    const settings::bundle_repository& bundle_;
    const formattables::formatter_properties_repository& formatter_properties_;
    const container& container_;
    std::forward_list<dogen::formatters::file> files_;
};

dispatcher::dispatcher(const settings::bundle_repository& brp,
    const formattables::formatter_properties_repository& fprp,
    const container& c) : empty_context_(), bundle_(brp),
                          formatter_properties_(fprp), container_(c) { }

void dispatcher::visit(const formattables::class_info& c) {
    const bool empty_out_content(
        c.generation_type() == yarn::generation_types::partial_generation);
    for (const auto f : container_.class_formatters())
        format_entity(*f, c, empty_out_content);
}

void dispatcher::visit(const formattables::forward_declarations_info& fd) {
    format_entity(container_.forward_declarations_formatters(), fd);
}

void dispatcher::visit(const formattables::enum_info& e) {
    format_entity(container_.enum_formatters(), e);
}

void dispatcher::visit(const formattables::registrar_info& r) {
    format_entity(container_.registrar_formatters(), r);
}

void dispatcher::visit(const formattables::visitor_info& v) {
    format_entity(container_.visitor_formatters(), v);
}

void dispatcher::visit(const formattables::cmakelists_info& c) {
    format(container_.cmakelists_formatters(), c);
}

void dispatcher::visit(const formattables::odb_options_info& o) {
    format(container_.odb_options_formatters(), o);
}

void dispatcher::visit(const formattables::includers_info& i) {
    format_entity(container_.includers_formatters(), i);
}

void dispatcher::format(const formattables::formattable& f) {
    f.accept(*this);
}

const std::forward_list<dogen::formatters::file>& dispatcher::files() {
    return files_;
}

std::shared_ptr<cpp::formatters::registrar> workflow::registrar_;

cpp::formatters::registrar& workflow::registrar() {
    if (!registrar_)
        registrar_ = std::make_shared<cpp::formatters::registrar>();

    return *registrar_;
}

class yarn_dispatcher final : public yarn::element_visitor {
public:
    yarn_dispatcher(const settings::bundle_repository& brp,
        const formattables::formatter_properties_repository& fprp,
        const container& c) : bundle_(brp), formatter_properties_(fprp),
        container_(c) {}

public:
    /**
     * @brief Returns all the generated files.
     */
    const std::forward_list<dogen::formatters::file>& files();

private:
    const std::unordered_map<std::string,
                             formattables::formatter_properties>&
    properties_for_name(const yarn::name& n) const;

    bool is_formatter_enabled(const std::unordered_map<std::string,
        formattables::formatter_properties>& fp,
        const std::string& formatter_name) const;

    context create_context_for_name(const std::unordered_map<std::string,
        formattables::formatter_properties>& fp, const yarn::name& n) const;

private:
    template<typename Formatter, typename YarnElement>
    void format(const Formatter& f, const YarnElement& e) {

        const auto qn(e.name().qualified());
        const auto fn(f.ownership_hierarchy().formatter_name());
        BOOST_LOG_SEV(lg, debug) << "Formatting: '" << qn << "' with '"
                                 << fn << "'";

        const auto& fp(properties_for_name(e.name()));
        if (!is_formatter_enabled(fp, fn)) {
            BOOST_LOG_SEV(lg, debug) << "Formatter not enabled for type.";
            return;
        }

        const auto ctx(create_context_for_name(fp, e.name()));
        auto file(f.format(ctx, e));

        files_.push_front(file);
        if (!file.overwrite()) {
            BOOST_LOG_SEV(lg, debug) << "Filename: "
                                     << file.path().generic_string();
            BOOST_LOG_SEV(lg, debug) << "Content: "
                                     << (file.content().empty() ? "<empty>" :
                                         file.content());
            BOOST_LOG_SEV(lg, debug) << "Finished formatting: '" << qn << "'";
        } else {
            BOOST_LOG_SEV(lg, debug) << "Not dumping file contents to log "
                                     << "(overwrite is false).";
        }
    }

    template<typename Formatter, typename Formattable>
        void format(const std::forward_list<std::shared_ptr<Formatter>>& fc,
            const Formattable& e) {
        for (const auto f : fc)
            format(*f, e);
    }


public:
    using yarn::element_visitor::visit;
    void visit(const dogen::yarn::module& m) override {
        if (m.documentation().empty())
            return;

        format(container_.namespace_formatters(), m);
    }
    void visit(const dogen::yarn::concept& /*c*/) override {}
    void visit(const dogen::yarn::primitive& /*p*/) override {}
    void visit(const dogen::yarn::enumeration& /*e*/) override {}
    void visit(const dogen::yarn::object& /*o*/) override {}
    void visit(const dogen::yarn::exception& e) override {
        format(container_.exception_formatters(), e);
    }
    void visit(const dogen::yarn::visitor& /*v*/) override {}

public:
    /**
     * @brief Converts the supplied entity into all supported
     * representations.
     */
    void format(const yarn::element& e);

private:
    const settings::bundle_repository& bundle_;
    const formattables::formatter_properties_repository& formatter_properties_;
    const container& container_;
    std::forward_list<dogen::formatters::file> files_;
};

const std::forward_list<dogen::formatters::file>& yarn_dispatcher::files() {
    return files_;
}

const std::unordered_map<std::string, formattables::formatter_properties>&
yarn_dispatcher::properties_for_name(const yarn::name& n) const {
    const auto& fp(formatter_properties_.formatter_properties_by_name());
    const auto qn(n.qualified());
    const auto i(fp.find(qn));
    if (i == fp.end()) {
        BOOST_LOG_SEV(lg, error) << formatter_properties_not_found << qn;
        BOOST_THROW_EXCEPTION(
            workflow_error(formatter_properties_not_found + qn));
    }
    return i->second;
}

bool yarn_dispatcher::is_formatter_enabled(const std::unordered_map<std::string,
    formattables::formatter_properties>& fp,
    const std::string& formatter_name) const {
    const auto i(fp.find(formatter_name));
    if (i == fp.end()) {
        BOOST_LOG_SEV(lg, error) << formatter_properties_not_found
                                 << formatter_name;
        BOOST_THROW_EXCEPTION(
            workflow_error(formatter_properties_not_found + formatter_name));
    }
    BOOST_LOG_SEV(lg, debug) << "enabled: " << i->second.enabled();
    return i->second.enabled();
}

context yarn_dispatcher::
create_context_for_name(const std::unordered_map<std::string,
    formattables::formatter_properties>& fp, const yarn::name& n) const {
    const auto& b(bundle_.bundles_by_name());
    const auto qn(n.qualified());
    const auto i(b.find(qn));
    if (i == b.end()) {
        BOOST_LOG_SEV(lg, error) << bundle_not_found << qn;
        BOOST_THROW_EXCEPTION(workflow_error(bundle_not_found + qn));
    }
    return context(i->second, fp);
}

void yarn_dispatcher::format(const yarn::element& e) {
    e.accept(*this);
}

std::forward_list<dogen::formatters::file>
workflow::execute(const settings::bundle_repository& brp,
    const formattables::formatter_properties_repository& fprp,
    const std::forward_list<
    std::shared_ptr<formattables::formattable> >& f) const {
    BOOST_LOG_SEV(lg, debug) << "Starting workflow.";
    dispatcher d(brp, fprp, registrar().formatter_container());
    for (const auto sp : f)
        d.format(*sp);

    const auto r(d.files());
    BOOST_LOG_SEV(lg, debug) << "Files generated: ";
    for (const auto& file : r)
        BOOST_LOG_SEV(lg, debug) << "Name: " << file.path().generic_string();

    BOOST_LOG_SEV(lg, debug) << "Finished workflow.";
    return r;
}

std::forward_list<dogen::formatters::file>
workflow::execute(const settings::bundle_repository& brp,
    const formattables::formatter_properties_repository& fprp,
    const std::forward_list<
    boost::shared_ptr<yarn::element> >& elements) const {

    BOOST_LOG_SEV(lg, debug) << "Starting workflow - yarn version.";
    yarn_dispatcher d(brp, fprp, registrar().formatter_container());
    for (const auto e : elements) {
        BOOST_LOG_SEV(lg, warn) << "Processing element: " << e->name().qualified();
        d.format(*e);
    }

    const auto r(d.files());
    BOOST_LOG_SEV(lg, debug) << "Files generated: ";
    for (const auto& file : r)
        BOOST_LOG_SEV(lg, debug) << "Name: " << file.path().generic_string();

    BOOST_LOG_SEV(lg, debug) << "Finished workflow - yarn version.";
    return r;
}

} } } }
