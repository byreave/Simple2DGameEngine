#pragma once
#include <stdint.h>
namespace Engine {
	typedef uint64_t	ref_counter_t;

	struct ReferenceCounters
	{
		ref_counter_t		StrongReferences;
		ref_counter_t		WeakReferences;

		ReferenceCounters(ref_counter_t i_InitialOwners, ref_counter_t i_InitialObservers) :
			StrongReferences(i_InitialOwners),
			WeakReferences(i_InitialObservers)
		{ }
	};

	// forward declare WeakPointer as we'll refer to it in StrongPointer definition
	template <class T>
	class WeakPointer;

	template <class T>
	class StrongPointer
	{
		template<class U>
		friend class WeakPointer;

		template<class U>
		friend class StrongPointer;

		T * m_pGameObject;
		ReferenceCounters * m_pRefCounter;

		void minusCounter()
		{
			if (m_pRefCounter != nullptr)
			{
				if (--m_pRefCounter->StrongReferences == 0)
				{
					delete m_pGameObject;
					if (m_pRefCounter->WeakReferences == 0)
						delete m_pRefCounter;
				}
			}
		}
	public:
		// Default Constructor
		StrongPointer();

		// Standard Constructor
		explicit StrongPointer(T * i_ptr);

		// Copy Constructor
		StrongPointer(const StrongPointer & i_other);

		// Copy Constructor between polymorphic types
		// StrongPointer<Base> BasePtr( new Base() );
		// StrongPointer<Default> DefaultPtr = BasePtr; <-- Used here
		template<class U>
		StrongPointer(const StrongPointer<U> & i_other);

		// Copy Constructor - For creating an Strong Pointer from an Weak Pointer
		// Will create a StrongPointer that points to nullptr if the referenced object has been destroyed (no more Owners left, just Observers)
		StrongPointer(const WeakPointer<T> & i_other)
		{
			if (i_other.m_pRefCounter->StrongReferences > 0)
			{
				m_pGameObject = i_other.m_pGameObject;
				m_pRefCounter = i_other.m_pRefCounter;
				m_pRefCounter->StrongReferences++;
			}
			else
			{
				m_pGameObject = nullptr;
				m_pRefCounter = nullptr;
			}
		}

		// Copy Constructor - For creating an Strong Pointer of a polymorphic type from an Weak Pointer
		template<class U>
		StrongPointer(const WeakPointer<U> & i_other)
		{
			if (i_other.m_pRefCounter->StrongReferences > 0)
			{
				m_pGameObject = i_other.m_pGameObject;
				m_pRefCounter = i_other.m_pRefCounter;
				m_pRefCounter->StrongReferences++;
			}
			else
			{
				m_pGameObject = nullptr;
				m_pRefCounter = nullptr;
			}
		}

		StrongPointer & operator=(std::nullptr_t nullp) const
		{
			minusCounter();
			m_pGameObject = nullptr;
			m_pRefCounter = nullptr;
		}
		// Assignment Operator
		StrongPointer & operator=(const StrongPointer & i_other);

		// Assignment Operator between polymorphic types
		template<class U>
		StrongPointer & operator=(const StrongPointer<U> & i_other)
		{
			if (i_other.m_pGameObject == m_pGameObject)
				return *this;
			if (i_other.m_pGameObject == nullptr)
			{
				minusCounter();
				m_pGameObject = nullptr;
				m_pRefCounter = nullptr;
				return *this;
			}
			minusCounter();
			m_pGameObject = i_other.m_pGameObject;
			m_pRefCounter = i_other.m_pRefCounter;
			m_pRefCounter->StrongReferences++;
			return *this;
		}

		// Assignment Operator - Reassigns an existing Strong Pointer from an existing Weak Pointer
		StrongPointer & operator=(const WeakPointer<T> & i_other)
		{
			if (i_other.m_pGameObject == m_pGameObject)
				return *this;
			if (i_other.m_pGameObject == nullptr)
			{
				minusCounter();
				m_pGameObject = nullptr;
				m_pRefCounter = nullptr;
				return *this;
			}
			minusCounter();
			m_pGameObject = i_other.m_pGameObject;
			m_pRefCounter = i_other.m_pRefCounter;
			m_pRefCounter->StrongReferences++;
			return *this;
		}

		// Assignment Operator - Reassigns an existing Strong Pointer from an existing Weak Pointer of a polymorphic type
		template<class U>
		StrongPointer & operator=(const WeakPointer<U> & i_other)
		{
			if (i_other.m_pGameObject == m_pGameObject)
				return *this;
			if (i_other.m_pGameObject == nullptr)
			{
				minusCounter();
				m_pGameObject = nullptr;
				m_pRefCounter = nullptr;
				return *this;
			}
			minusCounter();
			m_pGameObject = i_other.m_pGameObject;
			m_pRefCounter = i_other.m_pRefCounter;
			m_pRefCounter->StrongReferences++;
			return *this;
		}

		// Assignment Operator - Assigning directly from an existing pointer
		// StrongPointer<Base> BasePtr( new Base() );
		// BasePtr = new Base();
		StrongPointer & operator=(T * i_ptr)
		{
			if (m_pGameObject == i_ptr)
				return *this;

			minusCounter();
			m_pGameObject = i_ptr;
			if (i_ptr == nullptr)
				m_pRefCounter = nullptr;
			else
				m_pRefCounter = new ReferenceCounters(1, 0);
			return *this;
		}

		// Destructor
		~StrongPointer();

		// Equality comparison operator
		inline bool operator==(const StrongPointer<T> & i_other) const;

		// Equality comparison operator between pointers to polymorphic types
		template<class U>
		inline bool operator==(const StrongPointer<U> & i_other) const;

		// Equality comparison operator for comparing to an Weak Pointer
		inline bool operator==(const WeakPointer<T> & i_other) const
		{
			return m_pGameObject == i_other.m_pGameObject;
		}

		// Equality comparison operator for comparing to an Weak Pointer of a polymorphic type
		template<class U>
		inline bool operator==(const WeakPointer<U> & i_other) const
		{
			return m_pGameObject == i_other.m_pGameObject;
		}

		// Inequality comparison operator between pointers to polymorphic types
		template<class U>
		inline bool operator!=(const StrongPointer<U> & i_other) const
		{
			return m_pGameObject != i_other.m_pGameObject;
		}

		// Inequality comparison operator for comparing to an Weak Pointer
		inline bool operator!=(const WeakPointer<T> & i_other) const
		{
			return m_pGameObject != i_other.m_pGameObject;
		}

		// Inequality comparison operator for comparing to an Weak Pointer of a polymorphic type
		template<class U>
		inline bool operator!=(const WeakPointer<U> & i_other) const;

		// Equality comparison operator directly to pointer 
		inline bool operator==(T * i_ptr) const;

		// Equality comparison operator directly to pointer (of polymorphic type)
		template<class U>
		inline bool operator==(U * i_ptr) const;

		// Equality comparison operator for nullptr
		inline bool operator==(std::nullptr_t nullp) const
		{
			return m_pGameObject == nullptr;
		}

		// Inequality comparison operator directly to pointer 
		inline bool operator!=(T * i_ptr) const;

		// Inequality comparison operator directly to pointer (of polymorphic type)
		template<class U>
		inline bool operator!=(U * i_ptr) const;

		// Inequality comparison operator for nullptr
		//inline bool operator==(std::nullptr_t nullp) const;

		// bool operator - shorthand for != nullptr;
		inline operator bool() const;

		// member access operator
		T * operator->();

		// indirection operator
		T & operator*();
	};


	template<class T>
	class WeakPointer
	{
		template<class U>
		friend class StrongPointer;
		template<class U>
		friend class WeakPointer;

		T * m_pGameObject;
		ReferenceCounters * m_pRefCounter;
	public:
		// Default Constructor
		WeakPointer();

		// Copy Constructors
		WeakPointer(const WeakPointer & i_owner);

		template<class U>
		WeakPointer(const StrongPointer<U> & i_owner);

		template<class U>
		WeakPointer(const WeakPointer<U> & i_owner);

		// Destructor
		~WeakPointer();

		// Assignment operators
		WeakPointer & operator=(const WeakPointer & i_other);

		template<class U>
		WeakPointer & operator=(const WeakPointer<U> & i_other);

		template<class U>
		inline WeakPointer & operator=(const StrongPointer<U> & i_other);

		WeakPointer<T> & operator=(std::nullptr_t i_null);

		// Create an Strong Pointer from this Observering Pointer
		inline StrongPointer<T> AcquireOwnership() const;

		// Equality comparison operators
		inline bool operator==(const StrongPointer<T> & i_other) const;

		template<class U>
		inline bool operator==(const StrongPointer<U> & i_other) const;

		inline bool operator==(const WeakPointer<T> & i_other) const;

		template<class U>
		inline bool operator==(const WeakPointer<U> & i_other) const;

		inline bool operator==(T * i_ptr) const;

		template<class U>
		inline bool operator==(U * i_ptr) const;

		// Inequality comparison operators
		inline bool operator!=(const StrongPointer<T> & i_other) const;

		template<class U>
		inline bool operator!=(const StrongPointer<U> & i_other) const;

		inline bool operator!=(const WeakPointer<T> & i_other) const;

		template<class U>
		inline bool operator!=(const WeakPointer<U> & i_other) const;

		inline bool operator!=(T * i_ptr) const;

		template<class U>
		inline bool operator!=(U * i_ptr) const;

		// bool operator
		inline operator bool() const;
	};
	template<class T>
	inline StrongPointer<T>::StrongPointer()
	{
		m_pGameObject = nullptr;
		m_pRefCounter = nullptr;
	}
	template<class T>
	inline StrongPointer<T>::StrongPointer(T * i_ptr)
	{
		m_pGameObject = i_ptr;
		m_pRefCounter = new ReferenceCounters(1, 0);
	}
	template<class T>
	inline StrongPointer<T>::StrongPointer(const StrongPointer & i_other)
	{
		m_pRefCounter = i_other.m_pRefCounter;
		if (m_pRefCounter)
			m_pRefCounter->StrongReferences++;
		m_pGameObject = i_other.m_pGameObject;
	}

	template<class T>
	template<class U>
	inline StrongPointer<T>::StrongPointer(const StrongPointer<U> & i_other)
	{
		m_pRefCounter = i_other.m_pRefCounter;
		if (m_pRefCounter)
			m_pRefCounter->StrongReferences++;
		m_pGameObject = i_other.m_pGameObject;
	}

	template<class T>
	inline StrongPointer<T> & StrongPointer<T>::operator=(const StrongPointer & i_other)
	{
		if (i_other.m_pGameObject == m_pGameObject)
			return *this;
		if (i_other.m_pGameObject == nullptr)
		{
			minusCounter();
			m_pGameObject = nullptr;
			m_pRefCounter = nullptr;
			return *this;
		}
		minusCounter();
		m_pGameObject = i_other.m_pGameObject;
		m_pRefCounter = i_other.m_pRefCounter;
		m_pRefCounter->StrongReferences++;
		return *this;
	}
	template<class T>
	inline WeakPointer<T>::WeakPointer()
	{
		m_pGameObject = nullptr;
		m_pRefCounter = nullptr;
	}
	template<class T>
	template<class U>
	inline WeakPointer<T>::WeakPointer(const StrongPointer<U>& i_owner)
	{
		m_pGameObject = i_owner.m_pGameObject;
		m_pRefCounter = i_owner.m_pRefCounter;
		m_pRefCounter->WeakReferences++;
	}
	template<class T>
	inline WeakPointer<T>::WeakPointer(const WeakPointer & i_owner)
	{
		m_pGameObject = i_owner.m_pGameObject;
		m_pRefCounter = i_owner.m_pRefCounter;
		m_pRefCounter->WeakReferences++;
	}
	template<class T>
	inline WeakPointer<T>::~WeakPointer()
	{
		if (m_pRefCounter != nullptr)
		{
			if (--m_pRefCounter->WeakReferences == 0 && m_pRefCounter->StrongReferences == 0)
			{
				delete m_pRefCounter;
				m_pRefCounter = nullptr;
			}
		}
	}
	template<class T>
	inline WeakPointer<T> & WeakPointer<T>::operator=(const WeakPointer & i_other)
	{
		if (i_other->m_pGameObject == m_pGameObject)
			return *this;
		m_pGameObject = i_other.m_pGameObject;
		m_pRefCounter = i_other.m_pRefCounter;
		m_pRefCounter->WeakReferences++;
		return *this;
	}
	template<class T>
	template<class U>
	inline WeakPointer<T> & WeakPointer<T>::operator=(const StrongPointer<U>& i_other)
	{
		if (m_pRefCounter != nullptr)
			m_pRefCounter->WeakReferences --;
		m_pRefCounter = i_other.m_pRefCounter;
		m_pRefCounter->WeakReferences++;
		m_pGameObject = i_other.m_pGameObject;
		return *this;
	}
	template<class T>
	inline WeakPointer<T>& WeakPointer<T>::operator=(std::nullptr_t i_null)
	{
		if (m_pRefCounter != nullptr)
			m_pRefCounter->WeakReferences--;
		m_pRefCounter = nullptr;
		m_pGameObject = nullptr;
		return *this;
	}
	template<class T>
	inline StrongPointer<T> WeakPointer<T>::AcquireOwnership() const
	{
		return StrongPointer<T>(*this);
	}
	template<class T>
	inline bool WeakPointer<T>::operator==(const StrongPointer<T>& i_other) const
	{
		return m_pGameObject == i_other.m_pGameObject;
	}

	template<class T>
	template<class U>
	inline bool WeakPointer<T>::operator==(const StrongPointer<U>& i_other) const
	{
		return m_pGameObject == i_other.m_pGameObject;
	}

	template<class T>
	inline bool WeakPointer<T>::operator==(const WeakPointer<T> & i_other) const
	{
		return m_pGameObject == i_other.m_pGameObject;
	}
	template<class T>
	template<class U>
	inline bool WeakPointer<T>::operator==(const WeakPointer<U>& i_other) const
	{
		return m_pGameObject == i_other.m_pGameObject;
	}
	template<class T>
	template<class U>
	inline bool WeakPointer<T>::operator==(U * i_ptr) const
	{
		return m_pGameObject == i_ptr;
	}
	template<class T>
	inline bool WeakPointer<T>::operator==(T * i_ptr) const
	{
		return m_pGameObject == i_ptr;
	}
	template<class T>
	inline bool WeakPointer<T>::operator!=(const StrongPointer<T>& i_other) const
	{
		return m_pGameObject != i_other.m_pGameObject;
	}

	template<class T>
	template<class U>
	inline bool WeakPointer<T>::operator!=(const StrongPointer<U>& i_other) const
	{
		return m_pGameObject != i_other.m_pGameObject;
	}

	template<class T>
	inline bool WeakPointer<T>::operator!=(const WeakPointer<T>& i_other) const
	{
		return m_pGameObject != i_other.m_pGameObject;
	}
	template<class T>
	template<class U>
	inline bool WeakPointer<T>::operator!=(const WeakPointer<U>& i_other) const
	{
		return m_pGameObject != i_other.m_pGameObject;
	}
	template<class T>
	template<class U>
	inline bool WeakPointer<T>::operator!=(U * i_ptr) const
	{
		return m_pGameObject != i_ptr;
	}
	template<class T>
	inline bool WeakPointer<T>::operator!=(T * i_ptr) const
	{
		return m_pGameObject != i_ptr;
	}
	template<class T>
	inline WeakPointer<T>::operator bool() const
	{
		return m_pGameObject != nullptr;
	}
	template<class T>
	template<class U>
	inline bool StrongPointer<T>::operator==(U * i_ptr) const
	{
		return m_pGameObject == i_ptr;
	}
	template<class T>
	template<class U>
	inline bool StrongPointer<T>::operator!=(U * i_ptr) const
	{
		return m_pGameObject != i_ptr;
	}
	template<class T>
	inline bool StrongPointer<T>::operator==(T * i_ptr) const
	{
		return m_pGameObject == i_ptr;
	}
	template<class T>
	inline bool StrongPointer<T>::operator!=(T * i_ptr) const
	{
		return m_pGameObject != i_ptr;
	}
	template<class T>
	inline StrongPointer<T>::operator bool() const
	{
		return m_pGameObject != nullptr;
	}
	template<class T>
	inline T * StrongPointer<T>::operator->()
	{
		return m_pGameObject;
	}
	template<class T>
	inline T & StrongPointer<T>::operator*()
	{
		if (m_pGameObject)
			return *m_pGameObject;
	}
	template<class T>
	inline StrongPointer<T>::~StrongPointer()
	{
		minusCounter();
		m_pGameObject = nullptr;
		m_pRefCounter = nullptr;
	}
	template<class T>
	inline bool StrongPointer<T>::operator==(const StrongPointer<T>& i_other) const
	{
		return m_pGameObject == i_other.m_pGameObject;
	}
}

