//
//  File: JFTuple.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
//#include <type_traits>

namespace JFL
{
	template<class T> struct JFTupleElementTraits
	{
		using StorableType = std::remove_cv_t<T>;
		using Type = T;
		using InputType = const T;
		using RefType = T&;
		using CRefType = const T&;
	};
	template<class T> struct JFTupleElementTraits<T&>
	{
		using StorableType = std::remove_cv_t<T>*;
		using Type = T;
		using InputType = T;
		using RefType = T&;
		using CRefType = const T&;
	};
	template<class T> struct JFTupleElementTraits<T&&>
	{
		using StorableType = std::remove_cv_t<T>;
		using Type = T;
		using InputType = const T;
		using RefType = T&;
		using CRefType = const T&;
	};

	template <class T> 
	struct JFTupleElement
	{
		using Type = typename JFTupleElementTraits<T>::Type;
		using RefType = typename JFTupleElementTraits<T>::RefType;
		using CRefType = typename JFTupleElementTraits<T>::CRefType;
		using InputType = typename JFTupleElementTraits<T>::InputType;
		using ValueType = typename JFTupleElementTraits<T>::StorableType;

		constexpr JFTupleElement() = default;
		constexpr JFTupleElement(Type&& v) : value(std::forward<T>(v)) {}
		constexpr JFTupleElement(InputType& v) { SetValue(v); }
		constexpr JFTupleElement(const JFTupleElement& t) { *this = t; }
		constexpr JFTupleElement(JFTupleElement&& t) noexcept { *this = t; }

		constexpr RefType Value()
		{ 
			if constexpr (std::is_pointer_v<ValueType>)
				return *value;
			else
				return value;
		}
		constexpr CRefType Value() const
		{ 
			if constexpr (std::is_pointer_v<ValueType>)
				return *value;
			else
				return value;
		}

		constexpr void SetValue(Type&& v) noexcept
		{
			value = std::forward<T>(v);
		}
		constexpr void SetValue(InputType& v)
		{
			if constexpr (std::is_pointer_v<ValueType>)
				value = const_cast<ValueType>(&v);
			else
				value = v;
		}

		constexpr JFTupleElement& operator = (const JFTupleElement& t)
		{
			value = t.value;
			return *this;
		}
		constexpr JFTupleElement& operator = (JFTupleElement&& t) noexcept
		{
			if constexpr (std::is_pointer_v<ValueType>)
			{
				value = t.value;
				t.value = nullptr;
			}
			else
			{
				value = static_cast<ValueType&&>(t.value);
			}
			return *this;
		}

	private:
		ValueType value;
	};

	template <class... Types> 
	class JFTuple
	{
	private:
		template<int, class...>
		struct TupleElementList {};

		template<int Index, class T, class... Ts>
		struct TupleElementList<Index, T, Ts...>
			: public TupleElementList<Index + 1, Ts...>
		{
			using NextType = TupleElementList<Index + 1, Ts...>;
			using ElementType = JFTupleElement<T>;

			constexpr TupleElementList() = default;
			constexpr TupleElementList(T&& element, Ts&&... elements)
				: NextType(std::forward<Ts>(elements)...)
				, element(std::forward<T>(element))
			{}

			ElementType element;
		};

		template<int, int, class...> 
		struct TupleElementListSequence;

		template<int Index, class... Ts> 
		struct TupleElementListSequence<Index, Index, Ts...>
		{
			using ElementList = TupleElementList<Index, Ts...>;
		};

		template<int Count, int Index, class T, class... Ts>
		struct TupleElementListSequence<Count, Index, T, Ts...>
			: TupleElementListSequence<Count + 1, Index, Ts...>
		{};

	public:
		enum { Count = sizeof...(Types) };
		template<int Index> using ElementListType = typename TupleElementListSequence<0, Index, Types...>::ElementList;
		template<int Index> using ElementType = typename ElementListType<Index>::ElementType;

		constexpr JFTuple() {}
		constexpr JFTuple(Types&&... types)
			: elementList(std::forward<Types>(types)...)
		{}
		constexpr JFTuple(const JFTuple& t)
			: elementList(t.elementList)
		{}
		constexpr JFTuple(JFTuple&& t) noexcept
			: elementList(static_cast<decltype(elementList)&&>(t.elementList))
		{}

		template <int Index> constexpr auto Element() -> ElementType<Index>&
		{
			return static_cast<ElementListType<Index>&>(elementList).element;
		}
		template <int Index> constexpr auto Element() const -> const ElementType<Index>&
		{
			return static_cast<const ElementListType<Index>&>(elementList).element;
		}

		template <int Index> constexpr auto Value() -> typename ElementType<Index>::RefType
		{
			return Element<Index>().Value();
		}
		template <int Index> constexpr auto Value() const -> typename ElementType<Index>::CRefType
		{
			return Element<Index>().Value();
		}

		template <int Index> constexpr void SetValue(typename ElementType<Index>::Type&& v) noexcept
		{
			Element<Index>().SetValue(std::forward<ElementType<Index>::Type>(v));
		}
		template <int Index> constexpr void SetValue(typename ElementType<Index>::InputType& v)
		{
			Element<Index>().SetValue(v);
		}

		constexpr JFTuple& operator = (const JFTuple& t)
		{
			elementList = t.elementList;
			return *this;
		}
		constexpr JFTuple& operator = (JFTuple&& t) noexcept
		{
			elementList = static_cast<decltype(elementList)&&>(t.elementList);
			return *this;
		}

	private:
		ElementListType<0> elementList;
	};

	// Deduce signature
	template<class... Types> JFTuple(Types&&...)->JFTuple<Types&&...>;
}
