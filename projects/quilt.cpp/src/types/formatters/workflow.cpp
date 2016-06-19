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
#include "dogen/quilt.cpp/io/properties/formatter_properties_io.hpp"
#include "dogen/yarn/types/element_visitor.hpp"
#include "dogen/quilt.cpp/types/properties/class_info.hpp"
#include "dogen/quilt.cpp/types/properties/includers_info.hpp"
#include "dogen/quilt.cpp/types/properties/registrar_info.hpp"
#include "dogen/quilt.cpp/types/properties/cmakelists_info.hpp"
#include "dogen/quilt.cpp/types/properties/odb_options_info.hpp"
#include "dogen/quilt.cpp/types/properties/forward_declarations_info.hpp"
#include "dogen/quilt.cpp/types/properties/formattable_visitor.hpp"
#include "dogen/quilt.cpp/types/workflow_error.hpp"
#include "dogen/quilt.cpp/types/formatters/context.hpp"
#include "dogen/quilt.cpp/types/formatters/element_formatter.hpp"
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
class dispatcher final : public properties::formattable_visitor {
public:
    dispatcher(const context_factory& f, const container& c);
    ~dispatcher() noexcept { }

private:
    template<typename Formatter, typename Formatable>
    void format(const Formatter& f, const Formatable& e,
        const bool empty_out_content = false) {
        const auto fn(f.ownership_hierarchy().formatter_name());
        BOOST_LOG_SEV(lg, debug) << "Formatting with: '" << fn << "'";

        auto file(f.format(factory_.make_empty_context(), e));

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

        const auto ctx(factory_.make(e.id()));
        const auto fp(ctx.formatter_properties());
        const auto i(fp.find(fn));
        if (i == fp.end()) {
            BOOST_LOG_SEV(lg, error) << formatter_properties_not_found << fn;
            BOOST_THROW_EXCEPTION(
                workflow_error(formatter_properties_not_found + fn));
        }

        const auto is_formatter_enabled(i->second.enabled());
        if (!is_formatter_enabled) {
            BOOST_LOG_SEV(lg, debug) << "Formatter not enabled for type.";
            return;
        }

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
    void visit(const properties::class_info& c) override;
    void visit(const properties::forward_declarations_info& fd) override;
    void visit(const properties::registrar_info& r) override;
    void visit(const properties::cmakelists_info& c) override;
    void visit(const properties::odb_options_info& o) override;
    void visit(const properties::includers_info& o) override;

public:
    /**
     * @brief Converts the supplied entity into all supported
     * representations.
     */
    void format(const properties::formattable& f);

public:
    /**
     * @brief Returns all the generated files.
     */
    const std::forward_list<dogen::formatters::file>& files();

private:
    const context_factory factory_;
    const container& container_;
    std::forward_list<dogen::formatters::file> files_;
};

dispatcher::dispatcher(const context_factory& f, const container& c)
    : factory_(f), container_(c) { }

void dispatcher::visit(const properties::class_info& c) {
    const bool empty_out_content(
        c.generation_type() == yarn::generation_types::partial_generation);
    for (const auto f : container_.class_formatters())
        format_entity(*f, c, empty_out_content);
}

void dispatcher::visit(const properties::forward_declarations_info& fd) {
    format_entity(container_.forward_declarations_formatters(), fd);
}

void dispatcher::visit(const properties::registrar_info& r) {
    format_entity(container_.registrar_formatters(), r);
}

void dispatcher::visit(const properties::cmakelists_info& c) {
    format(container_.cmakelists_formatters(), c);
}

void dispatcher::visit(const properties::odb_options_info& o) {
    format(container_.odb_options_formatters(), o);
}

void dispatcher::visit(const properties::includers_info& i) {
    format_entity(container_.includers_formatters(), i);
}

void dispatcher::format(const properties::formattable& f) {
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

std::forward_list<dogen::formatters::file>
workflow::execute(const settings::bundle_repository& brp,
    const settings::helper_settings_repository& hsrp,
    const properties::formatter_properties_repository& fprp,
    const std::forward_list<
    std::shared_ptr<properties::formattable> >& f) const {
    BOOST_LOG_SEV(lg, debug) << "Starting workflow.";
    context_factory factory(brp, hsrp, fprp, registrar().formatter_helpers());
    dispatcher d(factory, registrar().formatter_container());
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
    const settings::helper_settings_repository& hsrp,
    const properties::formatter_properties_repository& fprp,
    const std::forward_list<
    boost::shared_ptr<yarn::element> >& elements) const {

    BOOST_LOG_SEV(lg, debug) << "Starting workflow - yarn version.";

    std::forward_list<dogen::formatters::file> r;
    context_factory factory(brp, hsrp, fprp, registrar().formatter_helpers());
    element_formatter ef(factory, registrar().formatter_container());
    for (const auto e : elements) {
        BOOST_LOG_SEV(lg, warn) << "Processing element: " << e->name().id();
        r.splice_after(r.before_begin(), ef.format(*e));
    }

    BOOST_LOG_SEV(lg, debug) << "Files generated: ";
    for (const auto& file : r)
        BOOST_LOG_SEV(lg, debug) << "Name: " << file.path().generic_string();

    BOOST_LOG_SEV(lg, debug) << "Finished workflow - yarn version.";
    return r;
}

} } } }
