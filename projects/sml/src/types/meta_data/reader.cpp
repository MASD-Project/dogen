#include "dogen/sml/types/tags.hpp"
#include "dogen/sml/types/meta_data/reader.hpp"

namespace {

const std::string empty;

}

namespace dogen {
namespace sml {
namespace meta_data {

reader::reader(const boost::property_tree::ptree& meta_data)
    : meta_data_(meta_data) { }

bool reader::has_key(const std::string& key) const {
    const auto node(meta_data_.get_optional<std::string>(key));
    return node;
}

bool reader::is_true(const std::string& key) const {
    const auto value(get(key));
    return value == tags::bool_true;
}

bool reader::is_false(const std::string& key) const {
    return !is_true(key);
}

std::string reader::get(const std::string& key) const {
    const auto v(meta_data_.get_optional<std::string>(key));
    if (v)
        return *v;

    return empty;
}

bool reader::is_supported(const std::string& key) const {
    const auto value(get(key));
    return value == tags::status_supported;
}

std::list<std::pair<std::string,std::string> > reader::odb_pragma() const {
    std::list<std::pair<std::string, std::string> > r;

    using boost::property_tree::ptree;
    const auto child(meta_data_.get_child_optional(tags::odb_pragma));
    if (!child)
        return r;

    for (auto i(child->begin()); i != child->end(); ++i)
        r.push_back(std::make_pair(tags::odb_pragma, i->second.data()));

    return r;
}

} } }
