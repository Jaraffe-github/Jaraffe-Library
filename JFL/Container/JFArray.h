//
//  File: JFArray.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFInclude.h"
#include "Memory/JFMemory.h"

namespace JFL
{
	template<class T, class Allocator=JFDefaultAllocator>
	class JFArray
	{
		enum { MinimumCapacity = 4 };

		template<class Contaioner, class U>
		class ArrayIterator
		{
		public:
			constexpr ArrayIterator(Contaioner& _container, size_t _index) : container(_container), index(_index) {}
			constexpr bool operator==(const ArrayIterator& other) const { return index == other.index; };
			constexpr bool operator!=(const ArrayIterator& other) const { return index != other.index; };
			constexpr ArrayIterator& operator++() { ++index; return *this; }
			constexpr U& operator*() { JFASSERT_DEBUG(container.Count() >= index); return container[index]; }

		private:
			Contaioner& container;
			size_t index;
		};

	public:
		using Iterator = ArrayIterator<JFArray, T>;
		using ConstIterator = ArrayIterator<const JFArray, const T>;

		constexpr Iterator begin() { return Iterator(*this, 0); }
		constexpr ConstIterator begin() const { return ConstIterator(*this, 0); }
		constexpr Iterator end() { return Iterator(*this, count); }
		constexpr ConstIterator end() const { return ConstIterator(*this, count); }

		constexpr JFArray() noexcept
			: data(nullptr), count(0), capacity(0) 
		{}
		constexpr explicit JFArray(size_t c, const T& v = T())
			: data(nullptr), count(0), capacity(0)
		{
			Add(v, c);
		}
		constexpr JFArray(std::initializer_list<T> il)
			: data(nullptr), count(0), capacity(0)
		{
			Reserve(il.size());
			for (const T& v : il)
				new (std::addressof(data[count++])) T(v);
		}
		constexpr JFArray(const JFArray& other) noexcept
			: data(nullptr), count(0), capacity(0)
		{
			Reserve(other.count);
			for (int i = 0; i < other.count; ++i)
				Add(other[i]);
		}
		constexpr JFArray(JFArray&& other) noexcept
			: data(nullptr), count(0), capacity(0)
		{
			data = other.data;
			count = other.count;
			capacity = other.capacity;
			other.data = nullptr;
			other.count = 0;
			other.capacity = 0;
		}

		~JFArray() noexcept
		{
			Clear();

			if (data)
				Allocator::Free(data);
		}

		void Clear()
		{
			for (size_t i = 0; i < count; ++i)
				data[i].~T();
			count = 0;
		}

		constexpr size_t Add(const T& v, size_t c)
		{
			ExpandCapacity(c);
			for (size_t i = 0; i < c; ++i)
				new (std::addressof(data[count+i])) T(v);
			count += c;
			return count - c;
		}
		constexpr size_t Add(const T& v)
		{
			ExpandCapacity(1);
			new (std::addressof(data[count])) T(v);
			return count++;
		}
		constexpr size_t Add(T&& v)
		{
			ExpandCapacity(1);
			new (std::addressof(data[count])) T(static_cast<T&&>(v));
			return count++;
		}
		template<class... Args>
		constexpr size_t EmplaceAdd(Args&&... args)
		{
			ExpandCapacity(1);
			new (std::addressof(data[count])) T(std::forward<Args>(args)...);
			return count++;
		}

		constexpr size_t Remove(size_t index)
		{
			if (index < count)
			{
				data[index].~T();
				if (size_t numberOfMoves = --count - index; numberOfMoves > 0)
					memmove(std::addressof(data[index]), std::addressof(data[index + 1]), sizeof(T) * numberOfMoves);
			}
			return count;
		}

		constexpr void PopBack()
		{
			if (count > 0)
				data[--count].~T();
		}

		constexpr T* Data() noexcept
		{
			return data;
		}
		constexpr const T* Data() const noexcept
		{
			return data;
		}

		constexpr T& Front()
		{
			JFASSERT_DEBUG(count > 0);
			return data[0];
		}

		constexpr T& Back()
		{
			JFASSERT_DEBUG(count > 0);
			return data[count - 1];
		}

		constexpr T& operator[] (size_t index)
		{
			JFASSERT_DEBUG(count >= index);
			return data[index];
		}
		constexpr const T& operator[] (size_t index) const
		{
			JFASSERT_DEBUG(count >= index);
			return data[index];
		}

		constexpr size_t Count() const noexcept
		{
			return count;
		}

		constexpr size_t Bytes() const noexcept
		{
			return count * sizeof(T);
		}

		constexpr void Reserve(size_t c)
		{
			if (capacity < c)
			{
				T* old = data;
				if (data)
					data = (T*)JFDefaultAllocator::Realloc(data, sizeof(T) * c);
				else
					data = (T*)JFDefaultAllocator::Alloc(sizeof(T) * c);
			
				JFASSERT_DEBUG(data);

				if (data)
					capacity = c;
				// roll back.
				else
					data = old;
			}
		}

		constexpr void ShrinkToFit()
		{
			if (count < capacity)
			{
				JFASSERT_DEBUG(data);
				if (count > 0)
				{
					T* newData = (T*)Allocator::Realloc(data, sizeof(T) * count);
					JFASSERT_DEBUG(newData);

					if (newData)
					{
						data = newData;
						capacity = count;
					}
				}
				else
				{
					Allocator::Free(data);
					data = nullptr;
					capacity = 0;
				}
			}
		}

		constexpr JFArray& operator = (const JFArray& other)
		{
			if (this != &other)
			{
				Clear();
				Reserve(other.count);
				for (int i = 0; i < other.count; ++i)
					Add(other[i]);
			}
			return *this;
		}

		constexpr JFArray& operator = (JFArray&& other) noexcept
		{
			if (this != &other)
			{
				Clear();
				if (data)
					Allocator::Free(data);

				data = other.data;
				count = other.count;
				capacity = other.capacity;
				other.data = nullptr;
				other.count = 0;
				other.capacity = 0;
			}
			return *this;
		}

	private:
		constexpr void ExpandCapacity(size_t requirementCount)
		{
			size_t necessaryCount = count + requirementCount;
			if (capacity < necessaryCount)
			{
				Reserve(Max(count + count / 2, necessaryCount, MinimumCapacity));
			}
		}

		T* data;
		size_t count;
		size_t capacity;
	};

	// deduction guid.
	template<class T>
	JFArray(T)->JFArray<typename std::iterator_traits<T>::value_type>;

	// @not supported yet.
	template<class Allocator>
	class JFArray<bool, Allocator>
	{

	};
}
