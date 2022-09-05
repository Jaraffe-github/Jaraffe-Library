//
//  File: JFObject.h
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2021 Seungmin Choi. All rights reserved.
//

#pragma once
#include "JFRefCounter.h"
#include <type_traits>

namespace JFL
{
	template<class T>
	concept HasRefCounter = std::is_convertible_v<T*, JFRefCounter*>;

	template<class T, class U>
	concept Convertible = std::is_convertible_v<T*, U*>;

	template<HasRefCounter T>
	class JFObject final
	{
	public:
		JFObject(T* p = nullptr)
			: target(p)
		{
			InternalAddRef();
		}
		JFObject(const JFObject& obj)
			: target(obj.target)
		{
			InternalAddRef();
		}
		JFObject(JFObject&& obj) noexcept
			: target(obj.target)
		{
			obj.target = nullptr;
		}

		// convertible
		template<Convertible U>
		JFObject(U* p)
			: target(p)
		{
			InternalAddRef();
		}
		template<Convertible U>
		JFObject(const JFObject<U>& obj)
			: target(obj.target)
		{
			InternalAddRef();
		}
		template<Convertible U>
		JFObject(JFObject<U>&& obj) noexcept
			: target(obj.target)
		{
			obj.target = nullptr;
		}

		~JFObject() noexcept
		{
			InternalRelease();
		}

		JFObject& operator = (T* obj)
		{
			if (target != obj)
				InternalRelease();

			target = obj;
			InternalAddRef();
			return *this;
		}
		JFObject& operator = (const JFObject& obj)
		{
			if (target != obj.target)
				InternalRelease();

			target = obj.target;
			InternalAddRef();
			return *this;
		}
		JFObject& operator = (JFObject&& obj) noexcept
		{
			if (target != obj.target)
				InternalRelease();

			target = obj.target;
			obj.target = nullptr;
			return *this;
		}

		// convertible
		template<Convertible U>
		JFObject& operator = (U* obj)
		{
			if (target != obj)
				InternalRelease();

			target = obj;
			InternalAddRef();
			return *this;
		}
		template<Convertible U>
		JFObject& operator = (const JFObject<U>& obj)
		{
			if (target != obj.target)
				InternalRelease();

			target = obj.target;
			InternalAddRef();
			return *this;
		}
		template<Convertible U>
		JFObject& operator = (JFObject<U>&& obj) noexcept
		{
			if (target != obj.target)
				InternalRelease();

			target = obj.target;
			obj.target = nullptr;
			return *this;
		}

		template<class U>
		JFObject<U> DynamicCast()
		{
			return dynamic_cast<U*>(target);
		}

		template<class U>
		const JFObject<U> DynamicCast() const
		{
			return dynamic_cast<U*>(target);
		}

		T* operator -> ()
		{
			return target;
		}
		const T* operator -> () const
		{
			return target;
		}

		T* operator * ()
		{
			return target;
		}
		const T* operator * () const
		{
			return target;
		}

		operator T* ()
		{
			return target;
		}
		operator const T* () const
		{
			return target;
		}

		T* Ptr()
		{
			return target;
		}
		const T* Ptr() const
		{
			return target;
		}

	private:
		void InternalAddRef()
		{
			if (target)
				target->AddRef();
		}

		void InternalRelease()
		{
			if (target && target->Release() == 0)
			{
				delete target;
				target = nullptr;
			}
		}

		T* target;
	};
}