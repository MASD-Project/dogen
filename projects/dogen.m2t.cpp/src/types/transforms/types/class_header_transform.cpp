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
#include "dogen.physical/types/helpers/name_factory.hpp"
#include "dogen.logical/types/entities/structural/object.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.m2t/types/formatters/sequence_formatter.hpp"
#include "dogen.m2t.cpp/types/transforms/assistant.hpp"
#include "dogen.m2t.cpp/types/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/inclusion_constants.hpp"
#include "dogen.m2t.cpp/types/transforms/io/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/serialization/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/types/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/hash/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/types/class_header_transform.hpp"

namespace dogen::m2t::cpp::transforms::types {

std::string class_header_transform::static_id() {
    return traits::class_header_archetype_qn();
}

std::string class_header_transform::id() const {
    return static_id();
}

physical::entities::name
class_header_transform::physical_name() const {
    using physical::helpers::name_factory;
    static auto r(name_factory::make(cpp::traits::backend_sn(),
        traits::facet_sn(), traits::class_header_archetype_sn()));
    return r;
}

const logical::entities::name& class_header_transform::meta_name() const {
    using logical::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_object_name());
    return r;
}

inclusion_support_types class_header_transform::inclusion_support_type() const {
    return inclusion_support_types::canonical_support;
}

boost::filesystem::path class_header_transform::inclusion_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_inclusion_path_for_cpp_header(n, static_id());
}

boost::filesystem::path class_header_transform::full_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_full_path_for_cpp_header(n, static_id());
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

    const auto carch(traits::canonical_archetype());
    builder.add(o.transparent_associations(), carch);

    const auto fwd_arch(traits::class_forward_declarations_archetype_qn());
    builder.add(o.opaque_associations(), fwd_arch);

    const auto self_arch(class_header_transform::static_id());
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
        builder.add(o.opaque_associations(), fwd_arch);

        const auto visitor_fwd_arch(traits::visitor_forward_declarations_archetype_qn());
        builder.add(*o.base_visitor(), visitor_fwd_arch);
    }
    return builder.build();
}

physical::entities::artefact class_header_transform::
apply(const context& ctx, const logical::entities::element& e) const {
    assistant a(ctx, e, physical_name(), true/*requires_header_guard*/);
    const auto& o(a.as<logical::entities::structural::object>(e));

    {
        const auto sn(o.name().simple());
        const auto qn(a.get_qualified_name(o.name()));
        auto sbf(a.make_scoped_boilerplate_formatter(e));
        {
            const auto ns(a.make_namespaces(o.name()));
            auto snf(a.make_scoped_namespace_formatter(ns));
a.stream() << std::endl;
            a.comment(o.documentation());
            if (o.parents().empty()) {
a.stream() << "class " << sn << " " << a.make_final_keyword_text(o) << "{" << std::endl;
            } else {
                const auto& pn(o.parents().front());
                const auto pqn(a.get_qualified_name(pn));
a.stream() << "class " << sn << " " << a.make_final_keyword_text(o) << ": public " << pqn << " {" << std::endl;
            }

            /*
             * Compiler generated constructors and destructors.
             */
            if (a.supports_defaulted_functions()) {
a.stream() << "public:" << std::endl;
                if (!a.requires_manual_default_constructor())
a.stream() << "    " << sn << "() = default;" << std::endl;
a.stream() << "    " << sn << "(const " << sn << "&) = default;" << std::endl;
                if (!a.requires_manual_move_constructor())
a.stream() << "    " << sn << "(" << sn << "&&) = default;" << std::endl;
                if (!o.in_inheritance_relationship())
a.stream() << "    ~" << sn << "() = default;" << std::endl;
                if (o.is_immutable())
a.stream() << "    " << sn << "& operator=(const " << sn << "&) = delete;" << std::endl;
                else if (o.all_attributes().empty())
a.stream() << "    " << sn << "& operator=(const " << sn << "&) = default;" << std::endl;
a.stream() << std::endl;
            }

            /*
             * Manually generated default constructor.
             */
            if (a.requires_manual_default_constructor()) {
a.stream() << "public:" << std::endl;
a.stream() << "    " << sn << "();" << std::endl;
a.stream() << std::endl;
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
a.stream() << "    virtual ~" << sn << "()" << a.make_noexcept_keyword_text() << " = 0;" << std::endl;
a.stream() << std::endl;
            } else if (o.is_child() != 0) {
a.stream() << "    virtual ~" << sn << "()" << a.make_noexcept_keyword_text() << " { }" << std::endl;
a.stream() << std::endl;
            }

            /*
             * Manually generated move constructor.
             */
            if (a.requires_manual_move_constructor()) {
a.stream() << "public:" << std::endl;
a.stream() << "    " << sn << "(" << sn << "&& rhs);" << std::endl;
a.stream() << std::endl;
            }

            /*
             * Manually generated complete constructor.
             */
            if (!o.all_attributes().empty()) {
a.stream() << "public:" << std::endl;
                const auto attr_count(o.all_attributes().size());
                if (attr_count == 1) {
                    const auto attr(*o.all_attributes().begin());
a.stream() << "    explicit " << sn << "(const " << a.get_qualified_name(attr.parsed_type()) << a.make_by_ref_text(attr) << " " << attr.name().simple() << ");" << std::endl;
                } else {
a.stream() << "    " << sn << "(" << std::endl;
                    m2t::formatters::sequence_formatter sf(attr_count);
                    sf.postfix_configuration().last(");");
                    for (const auto& attr : o.all_attributes()) {
a.stream() << "        const " << a.get_qualified_name(attr.parsed_type()) << a.make_by_ref_text(attr) << " " << attr.name().simple() << sf.postfix() << std::endl;
                        sf.next();
                    }
                }
a.stream() << std::endl;
            }

            /*
             * Serialisaton Friends
             */
            if (a.is_serialization_enabled()) {
a.stream() << "private:" << std::endl;
a.stream() << "    template<typename Archive>" << std::endl;
a.stream() << "    friend void boost::serialization::save(Archive& ar, const " << qn << "& v, unsigned int version);" << std::endl;
a.stream() << std::endl;
a.stream() << "    template<typename Archive>" << std::endl;
a.stream() << "    friend void boost::serialization::load(Archive& ar, " << qn << "& v, unsigned int version);" << std::endl;
a.stream() << std::endl;
            }

            /*
             * Visitation.
             */
            if (o.is_visitation_root()) {
                const auto vsn(o.base_visitor()->simple());
a.stream() << "public:" << std::endl;
a.stream() << "    virtual void accept(const " << vsn << "& v) const = 0;" << std::endl;
a.stream() << "    virtual void accept(" << vsn << "& v) const = 0;" << std::endl;
a.stream() << "    virtual void accept(const " << vsn << "& v) = 0;" << std::endl;
a.stream() << "    virtual void accept(" << vsn << "& v) = 0;" << std::endl;
a.stream() << std::endl;
            } else if (o.is_visitation_leaf()) {
                std::string bvn;
                std::string rpn;
                if (o.derived_visitor()) {
                    bvn = a.get_qualified_name(*o.base_visitor());
                    rpn = a.get_qualified_name(o.root_parents().front());
                } else {
                    bvn = o.base_visitor()->simple();
                    rpn = o.root_parents().front().simple();
                }
a.stream() << "public:" << std::endl;
a.stream() << "    using " << rpn << "::accept;" << std::endl;
a.stream() << std::endl;
a.stream() << "    virtual void accept(const " << bvn << "& v) const" << a.make_override_keyword_text() << ";" << std::endl;
a.stream() << "    virtual void accept(" << bvn << "& v) const" << a.make_override_keyword_text() << ";" << std::endl;
a.stream() << "    virtual void accept(const " << bvn << "& v)" << a.make_override_keyword_text() << ";" << std::endl;
a.stream() << "    virtual void accept(" << bvn << "& v)" << a.make_override_keyword_text() << ";" << std::endl;
            }

            /*
             * Streaming
             */
            if (a.is_io_enabled()) {
                if (o.is_parent()) {
a.stream() << "public:" << std::endl;
a.stream() << "    virtual void to_stream(std::ostream& s) const;" << std::endl;
a.stream() << std::endl;
                } else if (!o.parents().empty()) {
a.stream() << "public:" << std::endl;
a.stream() << "    void to_stream(std::ostream& s) const" << a.make_override_keyword_text() << ";" << std::endl;
a.stream() << std::endl;
                }
            }

            /*
             * Getters and setters.
             */
            if (!o.local_attributes().empty()) {
a.stream() << "public:" << std::endl;
                for (const auto& attr : o.local_attributes()) {
                    a.comment_start_method_group(attr.documentation(), !attr.is_immutable());

                    if (attr.parsed_type().is_current_simple_type()) {
a.stream() << "    " << a.get_qualified_name(attr.parsed_type()) << " " << attr.name().simple() << "() const;" << std::endl;
                        if (attr.is_immutable()) {
a.stream() << std::endl;
                            continue;
                        }
a.stream() << "    " << a.make_setter_return_type(sn, attr) << " " << attr.name().simple() << "(const " << a.get_qualified_name(attr.parsed_type()) << a.make_by_ref_text(attr) << " v);" << std::endl;
                    } else {
a.stream() << "    const " << a.get_qualified_name(attr.parsed_type()) << "& " << attr.name().simple() << "() const;" << std::endl;
                        if (attr.is_immutable()) {
a.stream() << std::endl;
                            continue;
                        }
a.stream() << "    " << a.get_qualified_name(attr.parsed_type()) << a.make_by_ref_text(attr) << " " << attr.name().simple() << "();" << std::endl;
a.stream() << "    " << a.make_setter_return_type(sn, attr) << " " << attr.name().simple() << "(const " << a.get_qualified_name(attr.parsed_type()) << a.make_by_ref_text(attr) << " v);" << std::endl;
                        if (a.supports_move_operator()) {
a.stream() << "    " << a.make_setter_return_type(sn, attr) << " " << attr.name().simple() << "(const " << a.get_qualified_name(attr.parsed_type()) << "&& v);" << std::endl;
                        }
                    }
                    a.comment_end_method_group(attr.documentation(), !attr.is_immutable());
a.stream() << std::endl;
                }
            }

            /*
             * Equality.
             *
             * Equality is only public in leaf classes - MEC++-33.
             */
            if (o.is_parent()) {
a.stream() << "protected:" << std::endl;
a.stream() << "    bool compare(const " << sn << "& rhs) const;" << std::endl;
            } else {
a.stream() << "public:" << std::endl;
a.stream() << "    bool operator==(const " << sn << "& rhs) const;" << std::endl;
a.stream() << "    bool operator!=(const " << sn << "& rhs) const {" << std::endl;
a.stream() << "        return !this->operator==(rhs);" << std::endl;
a.stream() << "    }" << std::endl;
a.stream() << std::endl;
            }

            if (o.in_inheritance_relationship()) {
a.stream() << "public:" << std::endl;
                if (o.is_parent() && !o.is_child()) {
a.stream() << "    virtual bool equals(const " << sn << "& other) const = 0;" << std::endl;
                } else if (o.is_parent()) {
                    const auto rpn(o.root_parents().front());
a.stream() << "    virtual bool equals(const " << a.get_qualified_name(rpn) << "& other) const = 0;" << std::endl;
                } else if (!o.root_parents().empty()) {
                    const auto rpn(o.root_parents().front());
a.stream() << "    bool equals(const " << a.get_qualified_name(rpn) << "& other) const" << a.make_override_keyword_text() << ";" << std::endl;
                }
a.stream() << std::endl;
             }

            /*
             * Swap and assignment.
             *
             * Swap and assignment are only public in leaf classes - MEC++-33
             */
            if ((!o.all_attributes().empty() || o.is_parent()) && !o.is_immutable()) {
                if (o.is_parent()) {
a.stream() << "protected:" << std::endl;
                } else {
a.stream() << "public:" << std::endl;
                }
a.stream() << "    void swap(" << sn << "& other)" << a.make_noexcept_keyword_text() << ";" << std::endl;
                if (!o.is_parent() && !o.is_immutable()) {
a.stream() << "    " << sn << "& operator=(" << sn << " other);" << std::endl;
                }
a.stream() << std::endl;
            }

            /*
             * Member variables.
             */
            if (!o.local_attributes().empty()) {
a.stream() << "private:" << std::endl;
                for (const auto& attr : o.local_attributes()) {
a.stream() << "    " << a.get_qualified_name(attr.parsed_type()) << " " << attr.member_variable_name() << ";" << std::endl;
                }
            }
a.stream() << "};" << std::endl;
a.stream() << std::endl;
            /*
             * Destructor implementation.
             */
            if (o.is_parent()) {
a.stream() << "inline " << sn << "::~" << sn << "()" << a.make_noexcept_keyword_text() << " { }" << std::endl;
a.stream() << std::endl;
            }

            /*
             * Global equality operator implementation.
             */
            if (o.is_parent()) {
a.stream() << "inline bool operator==(const " << sn << "& lhs, const " << sn << "& rhs) {" << std::endl;
a.stream() << "    return lhs.equals(rhs);" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
            }
        }

        if (!o.all_attributes().empty() && !o.is_parent() && !o.is_immutable()) {
a.stream() << std::endl;
a.stream() << "namespace std {" << std::endl;
a.stream() << std::endl;
a.stream() << "template<>" << std::endl;
a.stream() << "inline void swap(" << std::endl;
a.stream() << "    " << qn << "& lhs," << std::endl;
a.stream() << "    " << qn << "& rhs) {" << std::endl;
a.stream() << "    lhs.swap(rhs);" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
a.stream() << "}" << std::endl;
        }
a.stream() << std::endl;
    } // sbf
    return a.make_artefact();
}
}
