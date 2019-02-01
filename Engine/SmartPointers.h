#pragma once
#include <assert.h>
#include <stdint.h>

namespace Engine {

	typedef uint64_t	ref_counter_t;

	struct ReferenceCounters
	{
		ref_counter_t		OwnerReferences;
		ref_counter_t		ObserverReferences;

		ReferenceCounters(ref_counter_t i_InitialOwners, ref_counter_t i_InitialObservers) :
			OwnerReferences(i_InitialOwners),
			ObserverReferences(i_InitialObservers)
		{ }
	};

	// forward declare Observing pointer as we'll refer to it in OwningPointer definition
	template<class T>
	class ObservingPointer;

	template<class T>
	class OwningPointer
	{
		template<class U>
		friend class ObservingPointer;

		template<class U>
		friend class OwningPointer;

		T * m_pGameObject;
		ReferenceCounters * m_pRefCounter;

	public:
		// Default Constructor
		OwningPointer();

		// Standard Constructor
		explicit OwningPointer(T * i_ptr);

		// Copy Constructor
		OwningPointer(const OwningPointer & i_other);

		// Copy Constructor between polymorphic types
		// OwningPointer<Base> BasePtr( new Base() );
		// OwningPointer<Default> DefaultPtr = BasePtr; <-- Used here
		template<class U>
		OwningPointer(const OwningPointer<U> & i_other);

		// Copy Constructor - For creating an Owning Pointer from an Observing Pointer
		// Will create a OwningPointer that points to nullptr if the referenced object has been destroyed (no more Owners left, just Observers)
		OwningPointer(const ObservingPointer<T> & i_other);

		// Copy Constructor - For creating an Owning Pointer of a polymorphic type from an Observing Pointer
		template<class U>
		OwningPointer(const ObservingPointer<U> & i_other);

		// Assignment Operator
		OwningPointer & operator=(const OwningPointer & i_other);

		// Assignment Operator between polymorphic types
		template<class U>
		OwningPointer & operator=(const OwningPointer<U> & i_other);

		// Assignment Operator - Reassigns an existing Owning Pointer from an existing Observing Pointer
		OwningPointer & operator=(const ObservingPointer<T> & i_other);

		// Assignment Operator - Reassigns an existing Owning Pointer from an existing Observing Pointer of a polymorphic type
		template<class U>
		OwningPointer & operator=(const ObservingPointer<U> & i_other);

		// Assignment Operator - null specific
		// OwningPointer<Base> BasePtr( new Base() );
		// BasePtr = nullptr;
		// Don't really need to implement this. If it's not here it'll go through OwningPointer & operator=( OwningPointer & i_other);
		OwningPointer & operator=(std::nullptr_t i_null);

		// Assignment Operator - Assigning directly from an existing pointer
		// OwningPointer<Base> BasePtr( new Base() );
		// BasePtr = new Base();
		OwningPointer & operator=(T * i_ptr);

		// Destructor
		~OwningPointer();

		// Equality comparison operator
		inline bool operator==(const OwningPointer<T> & i_other) const;

		// Equality comparison operator between pointers to polymorphic types
		template<class U>
		inline bool operator==(const OwningPointer<U> & i_other) const;

		// Equality comparison operator for comparing to an Observing Pointer
		inline bool operator==(const ObservingPointer<T> & i_other) const;

		// Equality comparison operator for comparing to an Observing Pointer of a polymorphic type
		template<class U>
		inline bool operator==(const ObservingPointer<U> & i_other) const;

		// Inequality comparison operator
		inline bool operator!=(const OwningPointer<T> & i_other) const;

		// Inequality comparison operator between pointers to polymorphic types
		template<class U>
		inline bool operator!=(const OwningPointer<U> & i_other) const;

		// Inequality comparison operator for comparing to an Observing Pointer
		inline bool operator!=(const ObservingPointer<T> & i_other) const;

		// Inequality comparison operator for comparing to an Observing Pointer of a polymorphic type
		template<class U>
		inline bool operator!=(const ObservingPointer<U> & i_other) const;

		// Equality comparison operator directly to pointer 
		inline bool operator==(T * i_ptr) const;

		// Equality comparison operator directly to pointer (of polymorphic type)
		template<class U>
		inline bool operator==(U * i_ptr) const;

		// Equality comparison operator for nullptr
		inline bool operator==(std::nullptr_t nullp) const;

		// Inequality comparison operator directly to pointer 
		inline bool operator!=(T * i_ptr) const;

		// Inequality comparison operator directly to pointer (of polymorphic type)
		template<class U>
		inline bool operator!=(U * i_ptr) const;

		// Inequality comparison operator for nullptr
		inline bool operator==(std::nullptr_t nullp) const;

		// bool operator - shorthand for != nullptr;
		inline operator bool() const;

		// member access operator
		T * operator->();

		// indirection operator
		T & operator*();

	};

	template<class T>
	class ObservingPointer
	{
		template<class U>
		friend class OwningPointer;
		template<class U>
		friend class ObservingPointer;

	public:
		// Default Constructor
		ObservingPointer();

		// Copy Constructors
		ObservingPointer(const ObservingPointer & i_owner);

		template<class U>
		ObservingPointer(const OwningPointer<U> & i_owner);

		template<class U>
		ObservingPointer(const ObservingPointer<U> & i_owner);

		// Destructor
		~ObservingPointer();

		// Assignment operators
		ObservingPointer & operator=(const ObservingPointer & i_other);

		template<class U>
		ObservingPointer & operator=(const ObservingPointer<U> & i_other);

		template<class U>
		inline ObservingPointer & operator=(const OwningPointer<U> & i_other);

		ObservingPointer<T> & operator=(std::nullptr_t i_null);

		// Create an Owning Pointer from this Observering Pointer
		inline OwningPointer<T> AcquireOwnership();

		// Equality comparison operators
		inline bool operator==(const OwningPointer<T> & i_other) const;

		template<class U>
		inline bool operator==(const OwningPointer<U> & i_other) const;

		inline bool operator==(const ObservingPointer<U> & i_other) const;

		template<class U>
		inline bool operator==(const ObservingPointer<U> & i_other) const;

		inline bool operator==(T * i_ptr) const;

		template<class U>
		inline bool operator==(U * i_ptr) const;

		// Inequality comparison operators
		inline bool operator!=(const OwningPointer<T> & i_other) const;

		template<class U>
		inline bool operator!=(const OwningPointer<U> & i_other) const;

		inline bool operator!=(const ObservingPointer<U> & i_other) const;

		template<class U>
		inline bool operator!=(const ObservingPointer<U> & i_other) const;

		inline bool operator!=(T * i_ptr) const;

		template<class U>
		inline bool operator!=(U * i_ptr) const;

		// bool operator
		inline operator bool() const;
	};

} // namespace Engine