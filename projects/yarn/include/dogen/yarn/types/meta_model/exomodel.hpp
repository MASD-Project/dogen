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
#ifndef DOGEN_YARN_TYPES_META_MODEL_EXOMODEL_HPP
#define DOGEN_YARN_TYPES_META_MODEL_EXOMODEL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <utility>
#include <algorithm>
#include <boost/shared_ptr.hpp>
#include "dogen/yarn/types/meta_model/name.hpp"
#include "dogen/annotations/types/scribble_group.hpp"
#include "dogen/yarn/types/meta_model/exoelement.hpp"
#include "dogen/yarn/types/meta_model/module_fwd.hpp"
#include "dogen/yarn/types/meta_model/object_fwd.hpp"
#include "dogen/yarn/types/meta_model/builtin_fwd.hpp"
#include "dogen/yarn/types/meta_model/exception_fwd.hpp"
#include "dogen/yarn/types/meta_model/primitive_fwd.hpp"
#include "dogen/yarn/types/meta_model/enumeration_fwd.hpp"
#include "dogen/yarn/types/meta_model/static_stereotypes.hpp"
#include "dogen/yarn/types/meta_model/object_template_fwd.hpp"
#include "dogen/yarn/serialization/meta_model/exomodel_fwd_ser.hpp"

namespace dogen {
namespace yarn {
namespace meta_model {

class exomodel final {
public:
    exomodel(const exomodel&) = default;
    exomodel(exomodel&&) = default;
    ~exomodel() = default;

public:
    exomodel();

public:
    exomodel(
        const dogen::yarn::meta_model::name& name,
        const dogen::yarn::meta_model::name& meta_name,
        const std::string& documentation,
        const std::list<dogen::yarn::meta_model::static_stereotypes>& static_stereotypes,
        const std::list<std::string>& dynamic_stereotypes,
        const std::list<std::pair<std::string, std::string> >& tagged_values,
        const std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::module> > >& modules,
        const std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::object_template> > >& object_templates,
        const std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::builtin> > >& builtins,
        const std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::enumeration> > >& enumerations,
        const std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::primitive> > >& primitives,
        const std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::object> > >& objects,
        const std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::exception> > >& exceptions,
        const std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::module> >& root_module,
        const std::string& new_name,
        const std::list<dogen::yarn::meta_model::exoelement>& elements,
        const bool use_new_code);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::yarn::meta_model::exomodel& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::yarn::meta_model::exomodel& v, unsigned int version);

public:
    /**
     * @brief Fully qualified name.
     */
    /**@{*/
    const dogen::yarn::meta_model::name& name() const;
    dogen::yarn::meta_model::name& name();
    void name(const dogen::yarn::meta_model::name& v);
    void name(const dogen::yarn::meta_model::name&& v);
    /**@}*/

    /**
     * @brief Name of the element in the meta-model that this instance conforms to.
     */
    /**@{*/
    const dogen::yarn::meta_model::name& meta_name() const;
    dogen::yarn::meta_model::name& meta_name();
    void meta_name(const dogen::yarn::meta_model::name& v);
    void meta_name(const dogen::yarn::meta_model::name&& v);
    /**@}*/

    /**
     * @brief Code comments.
     *
     * These are expected to follow the grammar of the comment processing tools
     * of the programming language in question, e.g. Doxygen for C++, JavaDoc
     * for Java, etc.
     */
    /**@{*/
    const std::string& documentation() const;
    std::string& documentation();
    void documentation(const std::string& v);
    void documentation(const std::string&& v);
    /**@}*/

    /**
     * @brief Stereotypes that are part of the yarn UML profile, and so are well-known to the
     * model.
     */
    /**@{*/
    const std::list<dogen::yarn::meta_model::static_stereotypes>& static_stereotypes() const;
    std::list<dogen::yarn::meta_model::static_stereotypes>& static_stereotypes();
    void static_stereotypes(const std::list<dogen::yarn::meta_model::static_stereotypes>& v);
    void static_stereotypes(const std::list<dogen::yarn::meta_model::static_stereotypes>&& v);
    /**@}*/

    /**
     * @brief Stereotypes that are not part of the yarn UML profile. These are user defined.
     */
    /**@{*/
    const std::list<std::string>& dynamic_stereotypes() const;
    std::list<std::string>& dynamic_stereotypes();
    void dynamic_stereotypes(const std::list<std::string>& v);
    void dynamic_stereotypes(const std::list<std::string>&& v);
    /**@}*/

    const std::list<std::pair<std::string, std::string> >& tagged_values() const;
    std::list<std::pair<std::string, std::string> >& tagged_values();
    void tagged_values(const std::list<std::pair<std::string, std::string> >& v);
    void tagged_values(const std::list<std::pair<std::string, std::string> >&& v);

    const std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::module> > >& modules() const;
    std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::module> > >& modules();
    void modules(const std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::module> > >& v);
    void modules(const std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::module> > >&& v);

    const std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::object_template> > >& object_templates() const;
    std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::object_template> > >& object_templates();
    void object_templates(const std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::object_template> > >& v);
    void object_templates(const std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::object_template> > >&& v);

    const std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::builtin> > >& builtins() const;
    std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::builtin> > >& builtins();
    void builtins(const std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::builtin> > >& v);
    void builtins(const std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::builtin> > >&& v);

    const std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::enumeration> > >& enumerations() const;
    std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::enumeration> > >& enumerations();
    void enumerations(const std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::enumeration> > >& v);
    void enumerations(const std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::enumeration> > >&& v);

    const std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::primitive> > >& primitives() const;
    std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::primitive> > >& primitives();
    void primitives(const std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::primitive> > >& v);
    void primitives(const std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::primitive> > >&& v);

    const std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::object> > >& objects() const;
    std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::object> > >& objects();
    void objects(const std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::object> > >& v);
    void objects(const std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::object> > >&& v);

    const std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::exception> > >& exceptions() const;
    std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::exception> > >& exceptions();
    void exceptions(const std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::exception> > >& v);
    void exceptions(const std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::exception> > >&& v);

    const std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::module> >& root_module() const;
    std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::module> >& root_module();
    void root_module(const std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::module> >& v);
    void root_module(const std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::module> >&& v);

    const std::string& new_name() const;
    std::string& new_name();
    void new_name(const std::string& v);
    void new_name(const std::string&& v);

    const std::list<dogen::yarn::meta_model::exoelement>& elements() const;
    std::list<dogen::yarn::meta_model::exoelement>& elements();
    void elements(const std::list<dogen::yarn::meta_model::exoelement>& v);
    void elements(const std::list<dogen::yarn::meta_model::exoelement>&& v);

    bool use_new_code() const;
    void use_new_code(const bool v);

public:
    bool operator==(const exomodel& rhs) const;
    bool operator!=(const exomodel& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(exomodel& other) noexcept;
    exomodel& operator=(exomodel other);

private:
    dogen::yarn::meta_model::name name_;
    dogen::yarn::meta_model::name meta_name_;
    std::string documentation_;
    std::list<dogen::yarn::meta_model::static_stereotypes> static_stereotypes_;
    std::list<std::string> dynamic_stereotypes_;
    std::list<std::pair<std::string, std::string> > tagged_values_;
    std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::module> > > modules_;
    std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::object_template> > > object_templates_;
    std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::builtin> > > builtins_;
    std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::enumeration> > > enumerations_;
    std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::primitive> > > primitives_;
    std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::object> > > objects_;
    std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::exception> > > exceptions_;
    std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::module> > root_module_;
    std::string new_name_;
    std::list<dogen::yarn::meta_model::exoelement> elements_;
    bool use_new_code_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::yarn::meta_model::exomodel& lhs,
    dogen::yarn::meta_model::exomodel& rhs) {
    lhs.swap(rhs);
}

}

#endif
