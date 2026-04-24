#pragma once

#include <array>

template<typename T>
class ForwardIterator
{
public:
    using difference_type = std::ptrdiff_t;
    using value_type      = T;

    ForwardIterator()
            : m_ptr{nullptr}
    {
    }

    ForwardIterator(value_type* ptr)
            : m_ptr{ptr}
    {
    }

    ForwardIterator operator++(int) { return m_ptr++; }

    ForwardIterator& operator++()
    {
        ++m_ptr;
        return *this;
    }

    value_type operator*() const { return *m_ptr; }

    auto operator<=>(const ForwardIterator& rhs) const = default;

private:
    value_type* m_ptr;
};

template<typename T, std::size_t N>
class ForwardIterable
{
public:
    using value_type          = T;
    using iterator_type       = ForwardIterator<value_type>;
    using const_iterator_type = ForwardIterator<const value_type>;

    template<typename... Ts>
    ForwardIterable(Ts&&... values)
            : m_arr{std::forward<Ts>(values)...}
    {
        static_assert(sizeof...(values) <= N);
    }

    const_iterator_type begin() const { return m_arr.data(); }
    const_iterator_type end() const { return m_arr.data() + size(); }

    iterator_type begin() { return m_arr.data(); }
    iterator_type end() { return m_arr.data() + size(); }

    std::size_t size() const { return m_arr.size(); }

private:
    std::array<value_type, N> m_arr;
};
