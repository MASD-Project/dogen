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
#include <iterator>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/cpp/types/formattables/formattable_visitor.hpp"
#include "dogen/cpp/types/workflow_error.hpp"
#include "dogen/cpp/types/formatters/workflow.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("cpp.formatters.workflow"));

const std::string formatter_properties_not_found(
    "Could not find properties for formatter: ");
}

namespace dogen {
namespace cpp {
namespace formatters {

/**
 * @brief Responsible for dispatching the formattable to the
 * appropriate formatters.
 */
class dispatcher final : public formattables::formattable_visitor {
public:
    explicit dispatcher(const container& c);
    ~dispatcher() noexcept { }

private:
    template<typename Formatter, typename Entity>
    void format(const Formatter& f, const Entity& e,
        const bool empty_content = false,
        const bool skip_push = false) {
        const auto fn(f.ownership_hierarchy().formatter_name());
        BOOST_LOG_SEV(lg, debug) << "Formatting: '" << e.name()
                                 << "' with '" << fn << "'";

        const auto i(e.formatter_properties().find(fn));
        if (i == e.formatter_properties().end()) {
            BOOST_LOG_SEV(lg, error) << formatter_properties_not_found << fn;
            BOOST_THROW_EXCEPTION(
                workflow_error(formatter_properties_not_found + fn));
        }

        const auto is_formatter_enabled(i->second.enabled());
        if (!is_formatter_enabled) {
            BOOST_LOG_SEV(lg, debug) << "Formatter not enabled for type.";
            return;
        }

        auto file(f.format(e));

        if (empty_content)
            file.content().clear();

        if (!skip_push)
            files_.push_front(file);

        BOOST_LOG_SEV(lg, debug) << "Filename: "
                                 << file.path().generic_string();
        BOOST_LOG_SEV(lg, debug) << "Content: " << file.content();
        BOOST_LOG_SEV(lg, debug) << "Finished formatting: '" << e.name() << "'";
    }

public:
    using formattable_visitor::visit;
    void visit(const formattables::class_info& c) override;
    void visit(const formattables::forward_declarations_info& fd) override;
    void visit(const formattables::enum_info& e) override;
    void visit(const formattables::exception_info& e) override;
    void visit(const formattables::registrar_info& r) override;
    void visit(const formattables::namespace_info& n) override;
    void visit(const formattables::visitor_info& v) override;
    void visit(const formattables::concept_info& c) override;
    void visit(const formattables::primitive_info& p) override;

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
    const container& container_;
    std::forward_list<dogen::formatters::file> files_;
};

dispatcher::dispatcher(const container& c) : container_(c) { }

void dispatcher::visit(const formattables::class_info& c) {
    // for now we must not generate services.
    const auto service(formattables::class_types::service);
    const bool empty_content(c.class_type() == service);
    for (const auto f : container_.class_formatters())
        format(*f, c, empty_content, true/*skip_push*/);
}

void dispatcher::visit(const formattables::forward_declarations_info& fd) {
    for (const auto f : container_.forward_declarations_formatters())
        format(*f, fd);
}

void dispatcher::visit(const formattables::enum_info& /*e*/) {
}

void dispatcher::visit(const formattables::exception_info& /*e*/) {
}

void dispatcher::visit(const formattables::registrar_info& /*r*/) {
}

void dispatcher::visit(const formattables::namespace_info& /*n*/) {
}

void dispatcher::visit(const formattables::visitor_info& /*v*/) {
}

void dispatcher::visit(const formattables::concept_info& /*c*/) {
}

void dispatcher::visit(const formattables::primitive_info& /*p*/) {
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

std::forward_list<dogen::formatters::file>
workflow::execute(const std::forward_list<
        std::shared_ptr<formattables::formattable>
        >& f)
    const {
    BOOST_LOG_SEV(lg, debug) << "Starting workflow.";
    dispatcher d(registrar().formatter_container());
    for (const auto sp : f)
        d.format(*sp);

    const auto r(d.files());
    BOOST_LOG_SEV(lg, debug) << "Files generated: ";
    for (const auto& file : r)
        BOOST_LOG_SEV(lg, debug) << "Name: " << file.path().generic_string();

    BOOST_LOG_SEV(lg, debug) << "Finished workflow.";
    return r;
}

} } }
