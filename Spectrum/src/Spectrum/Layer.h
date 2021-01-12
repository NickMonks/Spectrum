#pragma once

#include "Spectrum/Core.h"
#include "Spectrum/Events/Event.h"

namespace Spectrum {

	class SP_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");

		//The idea is to subclass this class and implement the methods
		virtual ~Layer();
		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName;  }

	protected:
		std::string m_DebugName; //In release mode we will add a macro to disable the naming of the layers, since we are not interested in it and could potentially affect performance
	};
}
