#pragma once

#include "../Core.h"

#include <string>
#include <functional>

namespace Spectrum {

	// Event are not buffered, so the application stops until the event is done.
	// is not like it's in a FIFO queue. 

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		//BIT is defined in the core.h file
		// basically this is done to include each eventtype in a category. each row represents a category. 
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

// this macro is used to implement all the event type class virtual functions. In reality, these functions
	// are very simple and just need to know the type name. '### is token concatenation which essentially means
	// to tell the compiler to concatenate two elements. 

	// static is used since we dont need an instance to know, at runtime, the type of class. 
#define EVENT_CLASS_TYPE(type)  static EventType GetStaticType() {return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

// This is done also for the category
#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category;}

	class SP_API Event
	{
		friend class EventDispatcher;

	public:
		// these member functions are pure virtual which must be implemented by derived classes
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); } //by default provides this but with option to override. 

		inline bool IsInCategory(EventCategory category)
		{
			// it asks a certain event in the category of interest? , this is done with mask operation AND
			return GetCategoryFlags() & category;
		}

	protected:
		bool m_Handled = false; // to know if an event has been handled or not 
	};

	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>; //This seems like a predicate: returns bool and takes a reference event

	public:
		EventDispatcher(Event& event) // we receive a reference to an event, i.e is like an interface (it could be any type of event)
			:m_Event(event){}

		template<typename T> // T is the event function for each type
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType()) // thannks to call the function static, this is possibl
			{
				m_Event.m_Handled = func(*(T*)&m_Event); // type punning - because we dont know what type is m_Event (is the base class), we now type punning it (essentially cast the pointer to m_Event to T type and then dereference it. 
			}
		}
	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}


}
