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
#include <ostream>
#include <boost/algorithm/string.hpp>
#include "dogen/yarn/io/meta_model/name_io.hpp"
#include "dogen/yarn/io/meta_model/module_io.hpp"
#include "dogen/yarn/io/meta_model/object_io.hpp"
#include "dogen/yarn/io/meta_model/builtin_io.hpp"
#include "dogen/yarn/io/meta_model/exomodel_io.hpp"
#include "dogen/yarn/io/meta_model/exception_io.hpp"
#include "dogen/yarn/io/meta_model/primitive_io.hpp"
#include "dogen/annotations/io/scribble_group_io.hpp"
#include "dogen/yarn/io/meta_model/exoelement_io.hpp"
#include "dogen/yarn/io/meta_model/enumeration_io.hpp"
#include "dogen/yarn/io/meta_model/object_template_io.hpp"
#include "dogen/yarn/io/meta_model/well_known_stereotypes_io.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::vector<dogen::yarn::meta_model::well_known_stereotypes>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::vector<std::string>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << "\"" << tidy_up_string(*i) << "\"";
    }
    s << "] ";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::pair<std::string, std::string>& v) {
    s << "{ " << "\"__type__\": " << "\"std::pair\"" << ", ";

    s << "\"first\": " << "\"" << tidy_up_string(v.first) << "\"" << ", ";
    s << "\"second\": " << "\"" << tidy_up_string(v.second) << "\"";
    s << " }";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<std::pair<std::string, std::string> >& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace boost {

inline std::ostream& operator<<(std::ostream& s, const boost::shared_ptr<dogen::yarn::meta_model::module>& v) {
    s << "{ " << "\"__type__\": " << "\"boost::shared_ptr\"" << ", "
      << "\"memory\": " << "\"" << static_cast<void*>(v.get()) << "\"" << ", ";

    if (v)
        s << "\"data\": " << *v;
    else
        s << "\"data\": ""\"<null>\"";
    s << " }";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::module> >& v) {
    s << "{ " << "\"__type__\": " << "\"std::pair\"" << ", ";

    s << "\"first\": " << v.first << ", ";
    s << "\"second\": " << v.second;
    s << " }";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::module> > >& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace boost {

inline std::ostream& operator<<(std::ostream& s, const boost::shared_ptr<dogen::yarn::meta_model::object_template>& v) {
    s << "{ " << "\"__type__\": " << "\"boost::shared_ptr\"" << ", "
      << "\"memory\": " << "\"" << static_cast<void*>(v.get()) << "\"" << ", ";

    if (v)
        s << "\"data\": " << *v;
    else
        s << "\"data\": ""\"<null>\"";
    s << " }";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::object_template> >& v) {
    s << "{ " << "\"__type__\": " << "\"std::pair\"" << ", ";

    s << "\"first\": " << v.first << ", ";
    s << "\"second\": " << v.second;
    s << " }";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::object_template> > >& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace boost {

inline std::ostream& operator<<(std::ostream& s, const boost::shared_ptr<dogen::yarn::meta_model::builtin>& v) {
    s << "{ " << "\"__type__\": " << "\"boost::shared_ptr\"" << ", "
      << "\"memory\": " << "\"" << static_cast<void*>(v.get()) << "\"" << ", ";

    if (v)
        s << "\"data\": " << *v;
    else
        s << "\"data\": ""\"<null>\"";
    s << " }";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::builtin> >& v) {
    s << "{ " << "\"__type__\": " << "\"std::pair\"" << ", ";

    s << "\"first\": " << v.first << ", ";
    s << "\"second\": " << v.second;
    s << " }";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::builtin> > >& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace boost {

inline std::ostream& operator<<(std::ostream& s, const boost::shared_ptr<dogen::yarn::meta_model::enumeration>& v) {
    s << "{ " << "\"__type__\": " << "\"boost::shared_ptr\"" << ", "
      << "\"memory\": " << "\"" << static_cast<void*>(v.get()) << "\"" << ", ";

    if (v)
        s << "\"data\": " << *v;
    else
        s << "\"data\": ""\"<null>\"";
    s << " }";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::enumeration> >& v) {
    s << "{ " << "\"__type__\": " << "\"std::pair\"" << ", ";

    s << "\"first\": " << v.first << ", ";
    s << "\"second\": " << v.second;
    s << " }";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::enumeration> > >& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace boost {

inline std::ostream& operator<<(std::ostream& s, const boost::shared_ptr<dogen::yarn::meta_model::primitive>& v) {
    s << "{ " << "\"__type__\": " << "\"boost::shared_ptr\"" << ", "
      << "\"memory\": " << "\"" << static_cast<void*>(v.get()) << "\"" << ", ";

    if (v)
        s << "\"data\": " << *v;
    else
        s << "\"data\": ""\"<null>\"";
    s << " }";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::primitive> >& v) {
    s << "{ " << "\"__type__\": " << "\"std::pair\"" << ", ";

    s << "\"first\": " << v.first << ", ";
    s << "\"second\": " << v.second;
    s << " }";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::primitive> > >& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace boost {

inline std::ostream& operator<<(std::ostream& s, const boost::shared_ptr<dogen::yarn::meta_model::object>& v) {
    s << "{ " << "\"__type__\": " << "\"boost::shared_ptr\"" << ", "
      << "\"memory\": " << "\"" << static_cast<void*>(v.get()) << "\"" << ", ";

    if (v)
        s << "\"data\": " << *v;
    else
        s << "\"data\": ""\"<null>\"";
    s << " }";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::object> >& v) {
    s << "{ " << "\"__type__\": " << "\"std::pair\"" << ", ";

    s << "\"first\": " << v.first << ", ";
    s << "\"second\": " << v.second;
    s << " }";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::object> > >& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace boost {

inline std::ostream& operator<<(std::ostream& s, const boost::shared_ptr<dogen::yarn::meta_model::exception>& v) {
    s << "{ " << "\"__type__\": " << "\"boost::shared_ptr\"" << ", "
      << "\"memory\": " << "\"" << static_cast<void*>(v.get()) << "\"" << ", ";

    if (v)
        s << "\"data\": " << *v;
    else
        s << "\"data\": ""\"<null>\"";
    s << " }";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::exception> >& v) {
    s << "{ " << "\"__type__\": " << "\"std::pair\"" << ", ";

    s << "\"first\": " << v.first << ", ";
    s << "\"second\": " << v.second;
    s << " }";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::exception> > >& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::yarn::meta_model::exoelement>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace dogen {
namespace yarn {
namespace meta_model {

std::ostream& operator<<(std::ostream& s, const exomodel& v) {
    s << " { "
      << "\"__type__\": " << "\"dogen::yarn::meta_model::exomodel\"" << ", "
      << "\"name\": " << v.name() << ", "
      << "\"meta_name\": " << v.meta_name() << ", "
      << "\"documentation\": " << "\"" << tidy_up_string(v.documentation()) << "\"" << ", "
      << "\"well_known_stereotypes\": " << v.well_known_stereotypes() << ", "
      << "\"unknown_stereotypes\": " << v.unknown_stereotypes() << ", "
      << "\"tagged_values\": " << v.tagged_values() << ", "
      << "\"modules\": " << v.modules() << ", "
      << "\"object_templates\": " << v.object_templates() << ", "
      << "\"builtins\": " << v.builtins() << ", "
      << "\"enumerations\": " << v.enumerations() << ", "
      << "\"primitives\": " << v.primitives() << ", "
      << "\"objects\": " << v.objects() << ", "
      << "\"exceptions\": " << v.exceptions() << ", "
      << "\"root_module\": " << v.root_module() << ", "
      << "\"new_name\": " << "\"" << tidy_up_string(v.new_name()) << "\"" << ", "
      << "\"elements\": " << v.elements()
      << " }";
    return(s);
}

} } }
