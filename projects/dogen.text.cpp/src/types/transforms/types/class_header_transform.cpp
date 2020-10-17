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
#include "dogen.utility/types/io/shared_ptr_io.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.logical/io/entities/element_io.hpp"
#include "dogen.physical/io/entities/artefact_io.hpp"
#include "dogen.identification/types/helpers/physical_meta_name_factory.hpp"
#include "dogen.logical/types/entities/structural/object.hpp"
#include "dogen.identification/types/helpers/logical_meta_name_factory.hpp"
#include "dogen.utility/types/formatters/sequence_formatter.hpp"
#include "dogen.text.cpp/types/transforms/assistant.hpp"
#include "dogen.text.cpp/types/traits.hpp"
#include "dogen.text.cpp/types/transforms/traits.hpp"
#include "dogen.text.cpp/types/transforms/inclusion_constants.hpp"
#include "dogen.text.cpp/types/transforms/io/traits.hpp"
#include "dogen.text.cpp/types/transforms/serialization/traits.hpp"
#include "dogen.text.cpp/types/transforms/types/traits.hpp"
#include "dogen.text.cpp/types/transforms/hash/traits.hpp"
#include "dogen.text.cpp/types/transforms/types/class_header_transform.hpp"
#include "dogen.text.cpp/types/transforms/types/class_header_factory.hpp"

namespace dogen::text::cpp::transforms::types {
namespace {

const std::string transform_id("text.cpp.transforms.types.class_header_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

const physical::entities::archetype& class_header_transform::static_archetype() {
    static auto r(class_header_factory::make());
    return r;
}

const physical::entities::archetype& class_header_transform::archetype() const {
    return static_archetype();
}

inclusion_support_types class_header_transform::inclusion_support_type() const {
    return inclusion_support_types::canonical_support;
}

boost::filesystem::path class_header_transform::inclusion_path(
    const formattables::locator& l, const identification::entities::logical_name& n) const {
    return l.make_inclusion_path_for_cpp_header(n, archetype().meta_name().id().value());
}

std::list<std::string> class_header_transform::inclusion_dependencies(
    const formattables::dependencies_builder_factory& f,
    const logical::entities::element& e) const {

    using logical::entities::structural::object;
    const auto& o(assistant::as<object>(e));
    auto builder(f.make());

    // algorithm: domain headers need it for the swap function.
    builder.add(inclusion_constants::std::algorithm());

    const auto io_arch(transforms::io::traits::class_header_archetype_qn());
    const bool in_inheritance(o.is_parent() || o.is_child());
    const bool io_enabled(builder.is_enabled(o.name(), io_arch));
    const bool requires_io(io_enabled && in_inheritance);

    const auto ios(inclusion_constants::std::iosfwd());
    if (requires_io)
        builder.add(ios);

    using ser = transforms::serialization::traits;
    const auto ser_fwd_arch(ser::class_forward_declarations_archetype_qn());
    builder.add(o.name(), ser_fwd_arch);

    const identification::entities::physical_meta_id carch(traits::canonical_archetype());
    builder.add(o.transparent_associations(), carch);

    const auto fwd_arch(traits::class_forward_declarations_archetype_qn());
    builder.add(o.opaque_associations(), fwd_arch);

    const auto self_arch(class_header_transform::static_archetype().meta_name().id().value());
    builder.add(o.parents(), self_arch);

    using hash = transforms::hash::traits;
    const auto hash_carch(hash::traits::canonical_archetype());
    builder.add(o.associative_container_keys(), hash_carch);

    if (o.is_visitation_root()) {
        /*
         * On the header files of the visitation root we only care
         * about the base visitor; as such we can get away with a
         * forward declaration. For the visitation leaves, since we
         * must include the parent we do not need any additional
         * includes.
         */
        const auto visitor_fwd_arch(traits::visitor_forward_declarations_archetype_qn());
        builder.add(*o.base_visitor(), visitor_fwd_arch);
    }
    return builder.build();
}

void class_header_transform::apply(const context& ctx, const logical::entities::element& e,
    physical::entities::artefact& a) const {
    tracing::scoped_transform_tracer stp(lg, "class header",
        transform_id, e.name().qualified().dot(), *ctx.tracer(), e);

    assistant ast(ctx, e, archetype().meta_name(), true/*requires_header_guard*/, a);
    const auto& o(ast.as<logical::entities::structural::object>(e));

    {
        const auto sn(o.name().simple());
        const auto qn(ast.get_qualified_name(o.name()));
        auto sbf(ast.make_scoped_boilerplate_formatter(e));
        {
            const auto ns(ast.make_namespaces(o.name()));
            auto snf(ast.make_scoped_namespace_formatter(ns));
ast.stream() << std::endl;
            ast.comment(o.documentation());
            if (o.parents().empty()) {
ast.stream() << "class " << sn << " " << ast.make_final_keyword_text(o) << "{" << std::endl;
            } else {
                const auto& pn(o.parents().front());
                const auto pqn(ast.get_qualified_name(pn));
ast.stream() << "class " << sn << " " << ast.make_final_keyword_text(o) << ": public " << pqn << " {" << std::endl;
            }

            /*
             * Compiler generated constructors and destructors.
             */
            if (ast.supports_defaulted_functions()) {
ast.stream() << "public:" << std::endl;
                if (!ast.requires_manual_default_constructor())
ast.stream() << "    " << sn << "() = default;" << std::endl;
ast.stream() << "    " << sn << "(const " << sn << "&) = default;" << std::endl;
                if (!ast.requires_manual_move_constructor())
ast.stream() << "    " << sn << "(" << sn << "&&) = default;" << std::endl;
                if (!o.in_inheritance_relationship())
ast.stream() << "    ~" << sn << "() = default;" << std::endl;
                if (o.is_immutable())
ast.stream() << "    " << sn << "& operator=(const " << sn << "&) = delete;" << std::endl;
                else if (o.all_attributes().empty())
ast.stream() << "    " << sn << "& operator=(const " << sn << "&) = default;" << std::endl;
ast.stream() << std::endl;
            }

            /*
             * Manually generated default constructor.
             */
            if (ast.requires_manual_default_constructor()) {
ast.stream() << "public:" << std::endl;
ast.stream() << "    " << sn << "();" << std::endl;
ast.stream() << std::endl;
            }

            /*
             * Manually generated destructor.
             *
             * according to MEC++, item 33, base classes should always be
             * abstract. this avoids all sorts of tricky problems with
             * assignment and swap.
             *
             * incidentally, this also fixes some strange clang errors:
             * undefined reference to `vtable.
             */
            if (o.is_parent()) {
ast.stream() << "    virtual ~" << sn << "()" << ast.make_noexcept_keyword_text() << " = 0;" << std::endl;
ast.stream() << std::endl;
            } else if (o.is_child() != 0) {
ast.stream() << "    virtual ~" << sn << "()" << ast.make_noexcept_keyword_text() << " { }" << std::endl;
ast.stream() << std::endl;
            }

            /*
             * Manually generated move constructor.
             */
            if (ast.requires_manual_move_constructor()) {
ast.stream() << "public:" << std::endl;
ast.stream() << "    " << sn << "(" << sn << "&& rhs);" << std::endl;
ast.stream() << std::endl;
            }

            /*
             * Manually generated complete constructor.
             */
            if (!o.all_attributes().empty()) {
ast.stream() << "public:" << std::endl;
                const auto attr_count(o.all_attributes().size());
                if (attr_count == 1) {
                    const auto attr(*o.all_attributes().begin());
ast.stream() << "    explicit " << sn << "(const " << ast.get_qualified_name(attr.parsed_type()) << ast.make_by_ref_text(attr) << " " << attr.name().simple() << ");" << std::endl;
                } else {
ast.stream() << "    " << sn << "(" << std::endl;
                    utility::formatters::sequence_formatter sf(attr_count);
                    sf.postfix_configuration().last(");");
                    for (const auto& attr : o.all_attributes()) {
ast.stream() << "        const " << ast.get_qualified_name(attr.parsed_type()) << ast.make_by_ref_text(attr) << " " << attr.name().simple() << sf.postfix() << std::endl;
                        sf.next();
                    }
                }
ast.stream() << std::endl;
            }

            /*
             * Serialisaton Friends
             */
            if (ast.is_serialization_enabled()) {
ast.stream() << "private:" << std::endl;
ast.stream() << "    template<typename Archive>" << std::endl;
ast.stream() << "    friend void boost::serialization::save(Archive& ar, const " << qn << "& v, unsigned int version);" << std::endl;
ast.stream() << std::endl;
ast.stream() << "    template<typename Archive>" << std::endl;
ast.stream() << "    friend void boost::serialization::load(Archive& ar, " << qn << "& v, unsigned int version);" << std::endl;
ast.stream() << std::endl;
            }

            /*
             * Visitation.
             */
            if (o.is_visitation_root()) {
                const auto vsn(o.base_visitor()->simple());
ast.stream() << "public:" << std::endl;
ast.stream() << "    virtual void accept(const " << vsn << "& v) const = 0;" << std::endl;
ast.stream() << "    virtual void accept(" << vsn << "& v) const = 0;" << std::endl;
ast.stream() << "    virtual void accept(const " << vsn << "& v) = 0;" << std::endl;
ast.stream() << "    virtual void accept(" << vsn << "& v) = 0;" << std::endl;
ast.stream() << std::endl;
            } else if (o.is_visitation_leaf()) {
                std::string bvn;
                std::string rpn;
                if (o.derived_visitor()) {
                    bvn = ast.get_qualified_name(*o.base_visitor());
                    rpn = ast.get_qualified_name(o.root_parents().front());
                } else {
                    bvn = o.base_visitor()->simple();
                    rpn = o.root_parents().front().simple();
                }
ast.stream() << "public:" << std::endl;
ast.stream() << "    using " << rpn << "::accept;" << std::endl;
ast.stream() << std::endl;
ast.stream() << "    virtual void accept(const " << bvn << "& v) const" << ast.make_override_keyword_text() << ";" << std::endl;
ast.stream() << "    virtual void accept(" << bvn << "& v) const" << ast.make_override_keyword_text() << ";" << std::endl;
ast.stream() << "    virtual void accept(const " << bvn << "& v)" << ast.make_override_keyword_text() << ";" << std::endl;
ast.stream() << "    virtual void accept(" << bvn << "& v)" << ast.make_override_keyword_text() << ";" << std::endl;
            }

            /*
             * Streaming
             */
            if (ast.is_io_enabled()) {
                if (o.is_parent()) {
ast.stream() << "public:" << std::endl;
ast.stream() << "    virtual void to_stream(std::ostream& s) const;" << std::endl;
ast.stream() << std::endl;
                } else if (!o.parents().empty()) {
ast.stream() << "public:" << std::endl;
ast.stream() << "    void to_stream(std::ostream& s) const" << ast.make_override_keyword_text() << ";" << std::endl;
ast.stream() << std::endl;
                }
            }

            /*
             * Getters and setters.
             */
            if (!o.local_attributes().empty()) {
ast.stream() << "public:" << std::endl;
                for (const auto& attr : o.local_attributes()) {
                    ast.comment_start_method_group(attr.documentation(), !attr.is_immutable());

                    if (attr.parsed_type().is_current_simple_type()) {
ast.stream() << "    " << ast.get_qualified_name(attr.parsed_type()) << " " << attr.name().simple() << "() const;" << std::endl;
                        if (attr.is_immutable()) {
ast.stream() << std::endl;
                            continue;
                        }
ast.stream() << "    " << ast.make_setter_return_type(sn, attr) << " " << attr.name().simple() << "(const " << ast.get_qualified_name(attr.parsed_type()) << ast.make_by_ref_text(attr) << " v);" << std::endl;
                    } else {
ast.stream() << "    const " << ast.get_qualified_name(attr.parsed_type()) << "& " << attr.name().simple() << "() const;" << std::endl;
                        if (attr.is_immutable()) {
ast.stream() << std::endl;
                            continue;
                        }
ast.stream() << "    " << ast.get_qualified_name(attr.parsed_type()) << ast.make_by_ref_text(attr) << " " << attr.name().simple() << "();" << std::endl;
ast.stream() << "    " << ast.make_setter_return_type(sn, attr) << " " << attr.name().simple() << "(const " << ast.get_qualified_name(attr.parsed_type()) << ast.make_by_ref_text(attr) << " v);" << std::endl;
                        if (ast.supports_move_operator()) {
ast.stream() << "    " << ast.make_setter_return_type(sn, attr) << " " << attr.name().simple() << "(const " << ast.get_qualified_name(attr.parsed_type()) << "&& v);" << std::endl;
                        }
                    }
                    ast.comment_end_method_group(attr.documentation(), !attr.is_immutable());
ast.stream() << std::endl;
                }
            }

            /*
             * Equality.
             *
             * Equality is only public in leaf classes - MEC++-33.
             */
            if (o.is_parent()) {
ast.stream() << "protected:" << std::endl;
ast.stream() << "    bool compare(const " << sn << "& rhs) const;" << std::endl;
            } else {
ast.stream() << "public:" << std::endl;
ast.stream() << "    bool operator==(const " << sn << "& rhs) const;" << std::endl;
ast.stream() << "    bool operator!=(const " << sn << "& rhs) const {" << std::endl;
ast.stream() << "        return !this->operator==(rhs);" << std::endl;
ast.stream() << "    }" << std::endl;
ast.stream() << std::endl;
            }

            if (o.in_inheritance_relationship()) {
ast.stream() << "public:" << std::endl;
                if (o.is_parent() && !o.is_child()) {
ast.stream() << "    virtual bool equals(const " << sn << "& other) const = 0;" << std::endl;
                } else if (o.is_parent()) {
                    const auto rpn(o.root_parents().front());
ast.stream() << "    virtual bool equals(const " << ast.get_qualified_name(rpn) << "& other) const = 0;" << std::endl;
                } else if (!o.root_parents().empty()) {
                    const auto rpn(o.root_parents().front());
ast.stream() << "    bool equals(const " << ast.get_qualified_name(rpn) << "& other) const" << ast.make_override_keyword_text() << ";" << std::endl;
                }
ast.stream() << std::endl;
             }

            /*
             * Swap and assignment.
             *
             * Swap and assignment are only public in leaf classes - MEC++-33
             */
            if ((!o.all_attributes().empty() || o.is_parent()) && !o.is_immutable()) {
                if (o.is_parent()) {
ast.stream() << "protected:" << std::endl;
                } else {
ast.stream() << "public:" << std::endl;
                }
ast.stream() << "    void swap(" << sn << "& other)" << ast.make_noexcept_keyword_text() << ";" << std::endl;
                if (!o.is_parent() && !o.is_immutable()) {
ast.stream() << "    " << sn << "& operator=(" << sn << " other);" << std::endl;
                }
ast.stream() << std::endl;
            }

            /*
             * Member variables.
             */
            if (!o.local_attributes().empty()) {
ast.stream() << "private:" << std::endl;
                for (const auto& attr : o.local_attributes()) {
ast.stream() << "    " << ast.get_qualified_name(attr.parsed_type()) << " " << attr.member_variable_name() << ";" << std::endl;
                }
            }
ast.stream() << "};" << std::endl;
ast.stream() << std::endl;
            /*
             * Destructor implementation.
             */
            if (o.is_parent()) {
ast.stream() << "inline " << sn << "::~" << sn << "()" << ast.make_noexcept_keyword_text() << " { }" << std::endl;
ast.stream() << std::endl;
            }

            /*
             * Global equality operator implementation.
             */
            if (o.is_parent()) {
ast.stream() << "inline bool operator==(const " << sn << "& lhs, const " << sn << "& rhs) {" << std::endl;
ast.stream() << "    return lhs.equals(rhs);" << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
            }
        }

        if (!o.all_attributes().empty() && !o.is_parent() && !o.is_immutable()) {
ast.stream() << std::endl;
ast.stream() << "namespace std {" << std::endl;
ast.stream() << std::endl;
ast.stream() << "template<>" << std::endl;
ast.stream() << "inline void swap(" << std::endl;
ast.stream() << "    " << qn << "& lhs," << std::endl;
ast.stream() << "    " << qn << "& rhs) {" << std::endl;
ast.stream() << "    lhs.swap(rhs);" << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
ast.stream() << "}" << std::endl;
        }
ast.stream() << std::endl;
    } // sbf
    ast.update_artefact();
    stp.end_transform(a);
}
}
