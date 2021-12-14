#ifndef PLAYGROUND_UTILS_H
#define PLAYGROUND_UTILS_H

#include <vector>
#include <string>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <stack>
#include <queue>
#include <concepts>
#include <list>
#include <forward_list>

std::vector<std::string> read_input() {
    std::vector<std::string> input;
    std::string line;

    while (getline(std::cin, line)) {
        input.push_back(line);
    }

    return input;
}

std::vector<std::string> split_str(const std::string &s, const char delim = ' ') {
    std::stringstream ss(s);
    std::vector<std::string> words;
    std::string temp;

    while (std::getline(ss, temp, delim))
        words.push_back(temp);
    return words;
}

std::vector<int> str_vec_to_int(const std::vector<std::string> &vec, int base = 10) {
    std::vector<int> result;

    for (const std::string &str : vec) {
        if (str.empty())
            continue;
        result.push_back(stoi(str, nullptr, base));
    }

    return result;
}

namespace is_stl_container_impl {
    template <typename T>       struct is_stl_container : std::false_type{};
    template <typename T, std::size_t N> struct is_stl_container<std::array    <T,N>>     : std::true_type{};
    template <typename... Args> struct is_stl_container<std::vector            <Args...>> : std::true_type{};
    template <typename... Args> struct is_stl_container<std::deque             <Args...>> : std::true_type{};
    template <typename... Args> struct is_stl_container<std::list              <Args...>> : std::true_type{};
    template <typename... Args> struct is_stl_container<std::forward_list      <Args...>> : std::true_type{};
    template <typename... Args> struct is_stl_container<std::set               <Args...>> : std::true_type{};
    template <typename... Args> struct is_stl_container<std::multiset          <Args...>> : std::true_type{};
    template <typename... Args> struct is_stl_container<std::map               <Args...>> : std::true_type{};
    template <typename... Args> struct is_stl_container<std::multimap          <Args...>> : std::true_type{};
    template <typename... Args> struct is_stl_container<std::unordered_set     <Args...>> : std::true_type{};
    template <typename... Args> struct is_stl_container<std::unordered_multiset<Args...>> : std::true_type{};
    template <typename... Args> struct is_stl_container<std::unordered_map     <Args...>> : std::true_type{};
    template <typename... Args> struct is_stl_container<std::unordered_multimap<Args...>> : std::true_type{};
    template <typename... Args> struct is_stl_container<std::stack             <Args...>> : std::true_type{};
    template <typename... Args> struct is_stl_container<std::queue             <Args...>> : std::true_type{};
    template <typename... Args> struct is_stl_container<std::priority_queue    <Args...>> : std::true_type{};
}

template <typename T>
static constexpr bool const is_stl_container = is_stl_container_impl::is_stl_container<std::decay_t<T>>::value;

template <typename T>
concept Container = is_stl_container<T>;

template <typename T>
concept Element = (std::is_integral_v<T>
    || std::is_floating_point_v<T>
    || std::same_as<T, std::string>
    || std::same_as<T, std::_Bit_reference>); // vector<bool> doesn't store bools (shocking) (zamn)

template<class T>
concept Pair = requires(T p) {
    typename T::first_type;
    typename T::second_type;
    p.first;
    p.second;
    requires std::same_as<decltype(p.first), typename T::first_type>;
    requires std::same_as<decltype(p.second), typename T::second_type>;
};

template<Element T>
void my_print(T el, bool newline = false, bool niceprint = true) {
    std::cout << el;

    if (newline) {
        std::cout << "\n";
    }
}

template<Container T>
void my_print(T cont, bool newline = false, bool niceprint = true);

template<Pair T>
void my_print(T pair, bool newline = false, bool niceprint = true) {
    if (niceprint)
        std::cout << "(";
    my_print(pair.first, newline, niceprint);
    if (niceprint)
        std::cout << ", ";
    my_print(pair.second, newline, niceprint);
    if (niceprint)
        std::cout << ")";

    if (newline) {
        std::cout << "\n";
    }
}

template<Container T>
void my_print(T cont, bool newline, bool niceprint) {
    static constexpr bool const is_nested_cont = Container<decltype(*cont.begin())>;
    if (niceprint) {
        std::cout << "[";
        if (!is_nested_cont) {
            std::cout << " ";
        }
    }

    for (auto it = cont.begin(); it != cont.end(); it++) {
        if (is_nested_cont) {
            if (niceprint && it != cont.begin()) {
                std::cout << " ";
            }
            my_print(*it, std::next(it) != cont.end(), niceprint);
        }
        else {
            my_print(*it);
            if (niceprint) {
                if (std::next(it) != cont.end()) {
                    std::cout << ",";
                }
                std::cout << " ";
            }
        }
    }

    if (niceprint)
        std::cout << "]";
    if (newline) {
        std::cout << "\n";
    }
}

#endif //PLAYGROUND_UTILS_H