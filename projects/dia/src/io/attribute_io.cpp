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
#include <ostream>
#include <boost/variant/apply_visitor.hpp>
#include "dogen/utility/io/vector_io.hpp"
#include "dogen/utility/io/jsonify_io.hpp"
#include "dogen/dia/io/color_io.hpp"
#include "dogen/dia/io/point_io.hpp"
#include "dogen/dia/io/real_io.hpp"
#include "dogen/dia/io/integer_io.hpp"
#include "dogen/dia/io/boolean_io.hpp"
#include "dogen/dia/io/string_io.hpp"
#include "dogen/dia/io/composite_io.hpp"
#include "dogen/dia/io/attribute_io.hpp"
#include "dogen/dia/io/rectangle_io.hpp"
#include "dogen/dia/io/font_io.hpp"
#include "dogen/dia/io/enumeration_io.hpp"

namespace {

/**
 * @brief Writes all possible attribute value types into the stream.
 */
class attribute_value_visitor : public boost::static_visitor<> {
public:
    attribute_value_visitor(std::ostream& stream) : stream_(stream) {}

public:
    void operator()(const dogen::dia::color& value) const {
        stream_ << value;
    }

    void operator()(const dogen::dia::point& value) const {
        stream_ << value;
    }

    void operator()(const dogen::dia::real& value) const {
        stream_ << value;
    }

    void operator()(const dogen::dia::integer& value) const {
        stream_ << value;
    }

    void operator()(const dogen::dia::boolean& value) const {
        stream_ << value;
    }

    void operator()(const dogen::dia::string& value) const {
        stream_ << value;
    }

    void operator()(const dogen::dia::rectangle& value) const {
        stream_ << value;
    }

    void operator()(const dogen::dia::font& value) const {
        stream_ << value;
    }

    void operator()(const dogen::dia::enumeration& value) const {
        stream_ << value;
    }

    void operator()(const dogen::dia::composite& value) const {
        stream_ << value;
    }

private:
    std::ostream& stream_;
};

}

namespace dogen {
namespace dia {

std::ostream&
operator<<(std::ostream& stream, const dogen::dia::attribute& attribute) {
    stream << "\"attribute\": {"
           << " \"name\": \"" << attribute.name() << "\",";

    stream << " \"value\": [ ";
    const auto& values(attribute.values());
    for(auto i(values.cbegin()); i != values.cend(); ++i) {
        if (i != values.cbegin()) stream << ", ";

        // we need to create a local variable here because the visitor
        // uses a non-const reference to the value and we cannot have
        // non-const references to temporaries.
        dogen::dia::attribute::attribute_value v(*i);
        boost::apply_visitor(attribute_value_visitor(stream), v);
    }
    stream << " ]";
    stream << " }";
    return(stream);
}

} }
